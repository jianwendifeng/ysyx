`include "define.v"

module idu #(ADDR_WIDTH = 32, DATA_WIDTH = 64) (
    input	[ADDR_WIDTH-1:0] idu_inst_in,
	input	[DATA_WIDTH-1:0] idu_regdata_in_a,
	input	[DATA_WIDTH-1:0] idu_regdata_in_b,
	output 	[4:0] idu_regaddr_out_a,
	output 	[4:0] idu_regaddr_out_b,
    output 	[DATA_WIDTH-1:0] idu_data_a,
    output 	[DATA_WIDTH-1:0] idu_data_b,
	output 	[ADDR_WIDTH-1:0] idu_out_imm,
	output 	idu_wen,
	output 	[4:0] idu_waddr,
    output 	[3:0] idu_alu_ctrl,
    output 	idu_pc_ctrl
);	

	assign idu_pc_ctrl = 1'b0;	//分支指令还没写

	wire idu_R_type;
	// wire idu_I_type;
	// wire idu_U_type;
	// wire idu_J_type;
	// wire idu_B_type;
	// wire idu_S_type;

	wire [6:0] idu_opcode;
	assign idu_opcode = idu_inst_in[6:0];
	assign idu_waddr = idu_inst_in[11:7];
	assign idu_regaddr_out_a = idu_inst_in[19:15];
	assign idu_regaddr_out_b = idu_inst_in[24:20];

	assign idu_R_type = ( idu_opcode== `R_type);
	// assign idu_I_type = (idu_inst_in[6:0] == `jalr) | (idu_inst_in[6:0] == `load) | (idu_inst_in[6:0] == `I_type);
	// assign idu_U_type = (idu_inst_in[6:0] == `lui) | (idu_inst_in[6:0] == `auipc);
	// assign idu_J_type = (idu_inst_in[6:0] == `jal);
	// assign idu_B_type = (idu_inst_in[6:0] == `B_type);
	// assign idu_S_type = (idu_inst_in[6:0] == `store);
	wire [2:0] idu_func3;
	// wire [6:0] idu_func7;
	assign idu_func3 = idu_inst_in[14:12];
	// assign idu_func7 = idu_inst_in[31:25];

	assign idu_alu_ctrl[3] = (~idu_inst_in[6] & idu_inst_in[5] & idu_inst_in[4] & ~idu_inst_in[3] & idu_inst_in[2] & idu_inst_in[1] & idu_inst_in[0]) | (idu_inst_in[6] & idu_inst_in[5] & ~idu_inst_in[4] & ~idu_inst_in[3] & ~idu_inst_in[2] & idu_inst_in[1] & idu_inst_in[0]); 

	assign idu_alu_ctrl[2] = ((~idu_inst_in[6] & idu_inst_in[5] & idu_inst_in[4] & ~idu_inst_in[3] & ~idu_inst_in[2] & idu_inst_in[1] & idu_inst_in[0]) | (~idu_inst_in[6] & ~idu_inst_in[5] & idu_inst_in[4] & ~idu_inst_in[3] & ~idu_inst_in[2] & idu_inst_in[1] & idu_inst_in[0])) & idu_func3[2] | (~idu_inst_in[6] & idu_inst_in[5] & idu_inst_in[4] & ~idu_inst_in[3] & idu_inst_in[2] & idu_inst_in[1] & idu_inst_in[0]); 

	assign idu_alu_ctrl[1] = ((~idu_inst_in[6] & idu_inst_in[5] & idu_inst_in[4] & ~idu_inst_in[3] & ~idu_inst_in[2] & idu_inst_in[1] & idu_inst_in[0]) | (~idu_inst_in[6] & ~idu_inst_in[5] & idu_inst_in[4] & ~idu_inst_in[3] & ~idu_inst_in[2] & idu_inst_in[1] & idu_inst_in[0])) & idu_func3[1] | (~idu_inst_in[6] & idu_inst_in[5] & idu_inst_in[4] & ~idu_inst_in[3] & idu_inst_in[2] & idu_inst_in[1] & idu_inst_in[0]); 

	assign idu_alu_ctrl[0] = ((~idu_inst_in[6] & idu_inst_in[5] & idu_inst_in[4] & ~idu_inst_in[3] & ~idu_inst_in[2] & idu_inst_in[1] & idu_inst_in[0]) | (~idu_inst_in[6] & idu_inst_in[5] & idu_inst_in[4] & ~idu_inst_in[3] & ~idu_inst_in[2] & idu_inst_in[1] & idu_inst_in[0])) & idu_func3[0] | (~idu_inst_in[6] & idu_inst_in[5] & idu_inst_in[4] & ~idu_inst_in[3] & idu_inst_in[2] & idu_inst_in[1] & idu_inst_in[0]); 

    wire [31 : 0] idu_immnum;
	assign idu_out_imm = idu_immnum;

    immgen immgen0(
		.imm_instr(idu_inst_in),
		.immgem_num(idu_immnum)
	);

	assign idu_data_a = idu_regdata_in_a;
	assign idu_data_b =	idu_R_type ? idu_regdata_in_b : {{32{idu_immnum[31]}},idu_immnum};
	assign idu_wen = 1'b1;
endmodule
