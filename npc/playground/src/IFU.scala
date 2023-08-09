package src
import chisel3._
import chisel3.util._
import Decode._


class IFU(Xlen: Int) extends Module {
  val io = IO(new IFUIO(Xlen))

  // 创建一个 32 位的 指令寄存器，并初始化为 0
  val inst_reg = RegInit(0.U(Xlen.W))
  
  val pc = RegInit(0.U(Xlen.W))
  val br_sel = io.ctr_signals_in.br_sel

  pc := MuxLookup(br_sel, 4.U,
    Array(
      PC_4 -> (io.pc_in + 4.U),
      PC_0 -> (io.pc_in + 0.U),
      (PC_ALU & io.br_en) -> (io.pc_in + io.alu_data)
    )
  )

  inst_reg := io.inst_in

  io.inst := inst_reg
  io.pc_out := pc
  io.pc_next := pc
}


