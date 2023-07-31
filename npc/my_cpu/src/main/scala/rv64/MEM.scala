package rv64.ifu

import chisel3._

class ImemIO extends Bundle {
    val ren = Input(Bool())
    val raddr = Input(UInt(32.W))
    val rdata = Output(UInt(64.W))
}

class Memory extends Module {
    val io = IO(new Bundle{
        val imen = new ImemIO()
    })

    val Imem = Mem(4096, UInt(64.W))

    io.rdata := Mux(io.ren, Imem.read(io.raddr), 0.U)
}