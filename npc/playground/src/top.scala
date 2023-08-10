import circt.stage._
import chisel3._
import chisel3.util._
import chisel3.stage._

class TOP extends Module {
  val io = IO(new Bundle {
    val inst = Input(UInt(32.W)) // 外部指令输入，如verilator
    val pc = Output(UInt(32.W))
    val exit = Output(UInt(32.W))
    val idu_op = Output(UInt(32.W))
    val exu_data = Output(UInt(32.W))
    val exu_data1 = Output(UInt(32.W))
    val exu_data2 = Output(UInt(32.W))
    val mem_data = Output(UInt(32.W))
    val wbu_data = Output(UInt(32.W))
    val reg_wdata = Output(UInt(32.W))
  })

  val core = Module(new Core())
  val imem = Module(new Imem)

  // core.io.inst := Mux(false.B, io.inst, imem.io.imem.inst) //verilator和imem的指令输入选择，imem写入固定数据
  core.io.inst := imem.io.imem.inst
  core.io.pc <> imem.io.imem.addr

  io.pc := core.io.pc
  io.exit := core.io.exit
  io.idu_op := core.io.idu_op
  io.exu_data := core.io.exu_data
  io.exu_data1 := core.io.exu_data1
  io.exu_data2 := core.io.exu_data2
  io.mem_data := core.io.mem_data
  io.wbu_data := core.io.wbu_data
  io.reg_wdata := core.io.reg_wdata
}

object topMain extends App{
  (new ChiselStage).emitVerilog(new TOP(), args)
}