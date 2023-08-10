package rv64

import chisel3._
import chisel3.util._

class ctr_signalsIO extends Bundle {
    val alu_sel = Output(UInt(4.W))
    val a_sel = Output(UInt(1.W))
    val b_sel = Output(UInt(1.W))
    val imm_sel = Output(UInt(3.W))
    val rf_en = Output(Bool())
    val mem_en = Output(Bool())
    val wb_en = Output(Bool())
    val pc_sel = Output(UInt(2.W))
    val br_sel = Output(UInt(3.W))
}

class IFUIO(Xlen: Int) extends Bundle {
    val pc_in = Input(UInt(Xlen.W))
    val inst_in = Input(UInt(Xlen.W))
    val ctr_signals_in = Flipped(new ctr_signalsIO)
    val inst = Output(UInt(Xlen.W))
    val pc_out = Output(UInt(Xlen.W)) 
    val pc_next = Output(UInt(Xlen.W))
    val alu_data = Input(UInt(Xlen.W))
    val br_en = Input(Bool())
    }
class IDUIO(Data_Len: Int) extends Bundle{
    val inst = Input(UInt(32.W))
    val pc = Input(UInt(32.W))
    val rs1_data = Input(UInt(Data_Len.W))
    val rs2_data = Input(UInt(Data_Len.W))
    val rs1 = Output(UInt(5.W))
    val rs2 = Output(UInt(5.W))
    val rd = Output(UInt(5.W))
    val a = Output(UInt(Data_Len.W))
    val b = Output(UInt(Data_Len.W))
    val ctr_signals_out = new ctr_signalsIO
}


class DecodeIO(Xlen: Int) extends Bundle
{
    val inst = Input(UInt(Xlen.W))
    val ctr_signals = new ctr_signalsIO
   
}

class EXUIO(Data_Len: Int) extends Bundle {
    val a = Input(UInt(Data_Len.W))
    val b = Input(UInt(Data_Len.W))
    val ctr_signals_in = Flipped(new ctr_signalsIO)
    val ctr_signals_out = new ctr_signalsIO
    val rd_in = Input(UInt(5.W))
    val pc = Input(UInt(32.W))
    val rd_out = Output(UInt(5.W))
    val data = Output(UInt(Data_Len.W))
    // val alu_result = Output(UInt(Data_Len.W))
    val br_en = Output(Bool())
}

class ALUIO(Data_Len: Int) extends Bundle {
    val a = Input(UInt(Data_Len.W))
    val b = Input(UInt(Data_Len.W))
    
    val result = Output(UInt(Data_Len.W))
    val ctr_signals_in = Flipped(new ctr_signalsIO)
}


class MEMIO(Data_Len: Int) extends Bundle {
    val rd_in = Input(UInt(5.W))
    val result_in = Input(UInt(Data_Len.W))
    val ctr_signals_in = Flipped(new ctr_signalsIO)
    val ctr_signals_out = new ctr_signalsIO
    // val wen_out = Output(Bool())
    val rd_out = Output(UInt(5.W))
    val result_out = Output(UInt(Data_Len.W))
}

class WBUIO(Data_Len: Int) extends Bundle {
    val ctr_signals_in = Flipped(new ctr_signalsIO)
    val wen = Output(Bool())
    val waddr_in = Input(UInt(5.W))
    val wdata_in = Input(UInt(Data_Len.W))
    val waddr_out = Output(UInt(5.W))
    val wdata_out = Output(UInt(Data_Len.W))
}

class RegFileIO(Data_Len: Int) extends Bundle {
    val raddr1 = Input(UInt(5.W))
    val raddr2 = Input(UInt(5.W))
    val rdata1 = Output(UInt(Data_Len.W))
    val rdata2 = Output(UInt(Data_Len.W))
    val ren = Input(Bool())
    val wen = Input(Bool())
    val waddr = Input(UInt(5.W))
    val wdata = Input(UInt(Data_Len.W))
}

class ImemIO extends Bundle {
    val addr = Input(UInt(32.W))
    val inst = Output(UInt(32.W))
}