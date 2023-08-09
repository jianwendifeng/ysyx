package rv64

import chisel3._
import chisel3.util._
import ALU_Signals._
import Decode._

class IDU(Xlen: Int) extends Module{
    val io = IO(new IDUIO(Xlen))
    val decode = Module(new Decode(Xlen))
    decode.io.inst := io.inst
    
    val ctr_signals = RegNext(decode.io.ctr_signals)
    io.ctr_signals_out <> ctr_signals
    
    //立即数提取&扩展
    val imm_s = Cat(io.inst(31,25),io.inst(11,7))
    val imm_s_sext = Cat(Fill(20, imm_s(11)), imm_s)
    val imm_i = io.inst(31,20)
    val imm_i_sext = Cat(Fill(20, imm_i(11)), imm_i)
    val imm_j = Cat(io.inst(31), io.inst(19, 12), io.inst(20), io.inst(30,21))
    val imm_j_sext = Cat(Fill(11,imm_j(19)), imm_j, 0.U(1.W))
    val imm_u = io.inst(31, 12)
    val imm_u_shifted = Cat(imm_u, Fill(12, 0.U))

    val imm = RegInit(0.U(Xlen.W))
    imm := MuxLookup(decode.io.ctr_signals.imm_sel, 0.U,
        Array(
            IMM_X -> 0.U,
            IMM_I -> imm_i_sext,
            IMM_S -> imm_s_sext,
            IMM_J -> imm_j_sext,
            IMM_U -> imm_u_shifted
        )
    )

    val rs1_addr = io.inst(19,15)
    val rs2_addr = io.inst(24,20)
    io.rs1 := rs1_addr
    io.rs2 := rs2_addr

    val a = RegInit(0.U(Xlen.W))
    val b = RegInit(0.U(Xlen.W))
    a := MuxLookup(decode.io.ctr_signals.a_sel, io.rs1_data,
        Array(
            A_RS1 -> io.rs1_data,
            A_PC  -> io.pc
        )
    )

    b := MuxLookup(decode.io.ctr_signals.b_sel, io.rs2_data,
        Array(
            B_RS2 -> io.rs2_data,
            B_IMM -> imm  
        )
    )

    val rd_addr = io.inst(11,7)
    io.rd := rd_addr
    io.a := a
    io.b := b

}



