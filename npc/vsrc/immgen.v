`include "define.v"

module immgen #(ADDR_WIDTH = 32, DATA_WIDTH = 32) (
    input [ADDR_WIDTH-1:0] imm_instr,
    output [DATA_WIDTH-1:0] immgem_num
);
     
	wire imm_I_type;
	wire imm_U_type;
	wire imm_J_type;
	wire imm_B_type;
	wire imm_S_type;
	
	wire [DATA_WIDTH-1:0]immI;
	wire [DATA_WIDTH-1:0]immU;
	wire [DATA_WIDTH-1:0]immJ;
	wire [DATA_WIDTH-1:0]immB;
	wire [DATA_WIDTH-1:0]immS;
	
	
	// assign imm_opcode = imm_instr[6:0];
	
	assign imm_I_type = (imm_instr[6:0] == `jalr) | (imm_instr[6:0] == `load) | (imm_instr[6:0] == `I_type);
	assign imm_U_type = (imm_instr[6:0] == `lui) | (imm_instr[6:0] == `auipc);
	assign imm_J_type = (imm_instr[6:0] == `jal);
	assign imm_B_type = (imm_instr[6:0] == `B_type);
	assign imm_S_type = (imm_instr[6:0] == `store);
	
	
	assign immI = {{20{imm_instr[31]}} , imm_instr[31:20]}; 
	assign immU = {imm_instr[31:12] , {12{1'b0}}};
	assign immS = {{20{imm_instr[31]}} , imm_instr[31:25] , imm_instr[11:7]}; 
	assign immB = {{20{imm_instr[31]}} , imm_instr[7] , imm_instr[30:25] , imm_instr[11:8],1'b0};
	assign immJ = {{12{imm_instr[31]}} , imm_instr[19:12] , imm_instr[20] , imm_instr[30:21],1'b0};   
	
	assign immgem_num =	imm_I_type ? immI :
				 		imm_U_type ? immU :
				 		imm_J_type ? immJ :
				 		imm_B_type ? immB :
				 		imm_S_type ? immS : 32'd0;

endmodule
