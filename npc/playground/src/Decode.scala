package rv64
import chisel3._
import chisel3.util._
import ALU_Signals._
import Instructions._



object Decode {
    // //PC_SEL
    // val PC_SEL_LEN = 2
    // val PC_4 = 0.U(PC_SEL_LEN.W)
    // val PC_0 = 1.U(PC_SEL_LEN.W)
    // val PC_ALU = 2.u(PC_SEL_LEN.W)

    //A_SEl
    val A_SEL_LEN = 1
    val A_XXX = 0.U(A_SEL_LEN.W)
    val A_PC = 0.U(A_SEL_LEN.W)
    val A_RS1 = 1.U(A_SEL_LEN.W)

    //B_SEL
    val B_SEL_LEN = 1
    val B_XXX = 0.U(B_SEL_LEN.W)
    val B_IMM = 0.U(B_SEL_LEN.W)
    val B_RS2 = 1.U(B_SEL_LEN.W)

    //IMM_SEL
    val IMM_SEL_LEN = 3
    val IMM_X = 0.U(IMM_SEL_LEN.W)
    val IMM_I = 1.U(IMM_SEL_LEN.W)
    val IMM_U = 2.U(IMM_SEL_LEN.W)
    val IMM_S = 3.U(IMM_SEL_LEN.W)
    val IMM_J = 4.U(IMM_SEL_LEN.W)
    val IMM_B = 5.U(IMM_SEL_LEN.W)

    //RF_SEL
    // val RF_SEL_LEN = 1
    // val RF_XXX = 0.U(RF_SEL_LEN.W)
    val RF_N = false.B
    val RF_Y = true.B

    // //MEM_EN
    // val MEM_SEL_LEN = 1
    // val MEM_XXX = 0.U(MEM_SEL_LEN.W)
    val MEM_N = false.B
    val MEM_Y = true.B

    // //WB_EN
    // val WB_SEL_LEN = 1
    // val WB_XXX = 0.U(MEM_SEL_LEN.W)
    val WB_N = false.B
    val WB_Y = true.B

    val N = false.B
    val Y = true.B

    val PC_SEL_LEN = 2
    val PC_XXX = 0.U(PC_SEL_LEN.W)
    val PC_4 = 0.U(PC_SEL_LEN.W)
    val PC_0 = 1.U(PC_SEL_LEN.W)
    val PC_ALU = 2.U(PC_SEL_LEN.W)

    val BR_SEL_LEN = 3
    val BR_XXX = 0.U(BR_SEL_LEN.W)
    val BR_BEQ = 1.U(BR_SEL_LEN.W)
    val BR_BNE = 2.U(BR_SEL_LEN.W) 
    val BR_BLT = 3.U(BR_SEL_LEN.W)
    val BR_BLTU = 4.U(BR_SEL_LEN.W)
    val BR_BGE = 5.U(BR_SEL_LEN.W)
    val BR_BGEU = 6.U(BR_SEL_LEN.W)

    // format: off
    val default =
        //                                              wb_en                     
    //      alu_sel  A_sel   B_sel  imm_sel reg_en mem_en|  
    //          |       |       |     |      |      |    |   
        List(ALU_XXX, A_XXX, B_XXX, IMM_X, RF_N, MEM_N, WB_N, PC_4, BR_XXX )     //RF_N  regfile不使能，RF_Y   regfile使能

    val map = Array(
        ADD   -> List(ALU_ADD,      A_RS1, B_RS2, IMM_X, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),
        ADDI  -> List(ALU_ADD,      A_RS1, B_IMM, IMM_I, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),
        AND   -> List(ALU_AND,      A_RS1, B_RS2, IMM_X, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),
        ANDI  -> List(ALU_AND,      A_RS1, B_IMM, IMM_I, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),
        AUIPC -> List(ALU_ADD,      A_PC,  B_IMM, IMM_U, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),
        SUB   -> List(ALU_SUB,      A_RS1, B_RS2, IMM_X, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),
        OR    -> List(ALU_OR,       A_RS1, B_RS2, IMM_X, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),
        ORI   -> List(ALU_OR,       A_RS1, B_IMM, IMM_X, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),
       
        XOR   -> List(ALU_XOR,      A_RS1, B_RS2, IMM_I, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),
        SLL   -> List(ALU_SLL,      A_RS1, B_RS2, IMM_X, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),
        SRL   -> List(ALU_SRL,      A_RS1, B_RS2, IMM_X, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),
        SRA   -> List(ALU_SRA,      A_RS1, B_RS2, IMM_X, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),
        SLT   -> List(ALU_SLT,      A_RS1, B_RS2, IMM_X, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),
        SLTU  -> List(ALU_SLTU,     A_RS1, B_RS2, IMM_X, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),

        BEQ   -> List(ALU_ADD,      A_PC,  B_IMM, IMM_B, RF_N, MEM_N, WB_Y, PC_ALU, BR_BEQ),
        BNE   -> List(ALU_ADD,      A_PC,  B_IMM, IMM_B, RF_N, MEM_N, WB_Y, PC_ALU, BR_BNE),
        BLT   -> List(ALU_ADD,      A_PC,  B_IMM, IMM_B, RF_N, MEM_N, WB_Y, PC_ALU, BR_BLT),
        BLTU  -> List(ALU_ADD,      A_PC,  B_IMM, IMM_B, RF_N, MEM_N, WB_Y, PC_ALU, BR_BLTU),
        BGEU  -> List(ALU_ADD,      A_PC,  B_IMM, IMM_B, RF_N, MEM_N, WB_Y, PC_ALU, BR_BGEU),
        BGE   -> List(ALU_ADD,      A_PC,  B_IMM, IMM_B, RF_N, MEM_N, WB_Y, PC_ALU, BR_BGE),

        LUI   -> List(ALU_ADD,      A_XXX, B_IMM, IMM_U, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),
        JAL   -> List(ALU_ADD,      A_PC,  B_IMM, IMM_J, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),
        JALR  -> List(ALU_ADD,      A_PC,  B_IMM, IMM_I, RF_Y, MEM_N, WB_Y, PC_4, BR_XXX),

    )
}

class Decode(Inst_len: Int) extends Module 
{
    val io = IO(new DecodeIO(Inst_len))
    val signals = ListLookup(io.inst,Decode.default,Decode.map)

    io.ctr_signals.alu_sel := signals(0)
    io.ctr_signals.a_sel := signals(1)
    io.ctr_signals.b_sel := signals(2)
    io.ctr_signals.imm_sel := signals(3)
    io.ctr_signals.rf_en := signals(4)
    io.ctr_signals.mem_en := signals(5)
    io.ctr_signals.wb_en := signals(6)   
    io.ctr_signals.pc_sel := signals(7)
    io.ctr_signals.br_sel := signals(8)
}