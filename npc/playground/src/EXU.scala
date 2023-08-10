package rv64

import chisel3._
import chisel3.util._
import Decode._

class EXU(Xlen: Int) extends Module {
    val io = IO(new EXUIO(Xlen))
    val ctr_signals = RegNext(io.ctr_signals_in)
    io.ctr_signals_out <> ctr_signals
    
    val alu_result = RegInit(0.U(Xlen.W))
    val rd = RegInit(0.U(5.W))
    val pc = io.pc

    val alu = Module(new ALU(Xlen))
    
    alu.io.ctr_signals_in <> io.ctr_signals_in

    alu.io.a <> io.a
    alu.io.b <> io.b
    alu.io.result <> alu_result

    rd := io.rd_in
    io.rd_out := rd
    io.data := alu_result

    val br_en = RegInit(false.B)    //br_en为1，判断成功，pc跳转到br_target的位置
    br_en := MuxLookup(io.ctr_signals_in.br_sel, false.B,
        Array(
            BR_XXX -> false.B,
            BR_BEQ -> (io.a === io.b),
            BR_BNE -> (io.a =/= io.b),
            BR_BLT -> (io.a.asSInt() < io.b.asSInt()),
            BR_BLTU -> (io.a < io.b),
            BR_BGE -> (io.a.asSInt() >= io.b.asSInt()),
            BR_BGEU -> (io.a >= io.b)
        )
    )
    io.br_en := br_en
}
