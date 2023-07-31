package top

import chisel3._
import chisel3.util._
import chisel3.stage._

import rv64._

// class top extends Module {
//   val io = IO(new Bundle {
//     val raddr1 = Input(UInt(5.W))
//     val raddr2 = Input(UInt(5.W))
//     val rdata1 = Output(UInt(5.W))
//     val rdata2 = Output(UInt(5.W))
//     val wen = Input(Bool())
//     val waddr = Input(UInt(5.W))
//     val wdata = Input(UInt(5.W))
//   })
  
  

//   val regfile = Module(new RegFile(64))

//   regfile.io.raddr1 := io.raddr1
//   regfile.io.raddr2 := io.raddr2
//   io.rdata1 := regfile.io.rdata1
//   io.rdata2 := regfile.io.rdata2
//   regfile.io.wen := io.wen
//   regfile.io.waddr := io.waddr
//   regfile.io.wdata := io.wdata

// }

// object topMain extends App {
//   (new ChiselStage).emitVerilog(new top, args)
// }

class top extends Module {
   val io = IO(new Bundle {
    val input = Input(UInt32.W)
    val output = Output(UInt32.W)
   })

   val ifstage = Module(new PC)
   val idstage = Module(new Decoder)
   val exstage = Module(new Exu)
   val memstage = Module(new Memory)
   val wbstage = Module(new WB)


   ifstate.io.input <> io.input
   ifstage.io.output <> idstage.io.input
   idstage.io.output <> exstage.io.input
   memstage.io.output <> wbstage.io.input
   
}

object topMain extends APP {
  (new ChiselStage).emitVerilog(new top, args)
}