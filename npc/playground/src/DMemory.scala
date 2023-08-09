package rv64
import chisel3._

class DmemIO(Data_Len: Int) extends Bundle {
    val addr = Input(UInt(Data_Len.W))
    val wen = Input(Bool())
    val wdata = Input(UInt(Data_Len.W))
    val rdata = Output(UInt(Data_Len.W))
}

class DMem(Data_Len: Int) extends Module {
    val io = IO(new Bundle{
        val dmem = new DmemIO(Data_Len)
    })

    val mem = Mem(4096, UInt(32.W)) //2^14  16384/4=4096,最多4096条指令
    // loadMemoryFromFile(mem, "mem.hex",MemoryLoadFileType.Hex)  //读取指令

    io.dmem.rdata := mem(io.dmem.addr)
    when(io.dmem.wen) {
        mem(io.dmem.addr) := io.dmem.wdata
    }
}