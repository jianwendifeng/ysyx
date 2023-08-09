package rv64

import chisel3._
import chisel3.util._
import chisel3.stage._
import chisel3.util.experimental.loadMemoryFromFile
import firrtl.annotations.MemoryLoadFileType
import scala.io.Source

class Imem extends Module {
    val io = IO(new Bundle{
        val imem = new ImemIO()
    })

    //val mem = Mem(4096, UInt(8.W)) //2^14  16384/4=4096,最多4096条指令//8位宽
    //loadMemoryFromFile(mem, "mem.hex",MemoryLoadFileType.Hex)  //读取指令，目前没成功过

    val mem = SyncReadMem(1024, UInt(32.W)) //2^14  16384/4=4096,最多4096条指令

//     val memData = Seq(
//     0x12.U, 0x34.U, 0x56.U, 0x78.U,
//     0x9A.U, 0xBC.U, 0xDE.U, 0xEF.U,
//     // ... more data ...
//   )
     val memData = Seq(     //32位宽
    0x002182b3,
    0x00a323b3,
    0x012343b3,
    0x01a363b3,
    0x022383b3,
    0x0,0x0,0x0,0x0,
    0x6f2020e7, //jal
    0x00030363, //beq
    0x00030363, //bne
    0x00030363, //blt
    0x00030363, //bge
    // ... more data ...
  )
  for (i <- 0 until 1024) {
    mem.write(i.U, memData(i%14).U)        //初始化数据,循环写入20条数据
  }
  io.imem.inst := mem(io.imem.addr/4.U(32.W))
    //8位宽的数据
    //io.imem.inst :=  Cat(mem(io.imem.addr + 3.U), mem(io.imem.addr + 2.U), mem(io.imem.addr + 1.U), mem(io.imem.addr) )
}
