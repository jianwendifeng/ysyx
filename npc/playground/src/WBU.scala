package rv64

import chisel3._
import chisel3.util._



class WBU(Xlen: Int) extends Module {
    val io = IO(new WBUIO(Xlen))

    io.wen := io.ctr_signals_in.wb_en
    io.waddr_out  := io.waddr_in
    io.wdata_out  := io.wdata_in
}
