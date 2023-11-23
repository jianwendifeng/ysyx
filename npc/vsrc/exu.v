<<<<<<< HEAD
//`define OP_ADDI 7'b0010011
//`define FUNCT3_ADDI 3'b000

module exu(
	input [6:0] ex_op,
	input [31:0] ex_src1,
	input [11:0] ex_imm,
	input [14:12] ex_funct3,
	output reg [31:0] ex_result
);



	always @(*) begin
	case (ex_op)
		7'b0010011 : begin
			case (ex_funct3)
				3'b000:  ex_result = ex_src1 + {20'b0,ex_imm};	//clk use <= ,this not have clk
				default: ex_result = 32'b0;
			endcase
		end
		default: ex_result = 32'b0;
	endcase
end
=======
module exu #(DATA_WIDTH = 64) (
    input [3 : 0] exu_alu_ctrl,
    input [DATA_WIDTH-1 : 0] exu_data_a,
    input [DATA_WIDTH-1 : 0] exu_data_b,
    output [DATA_WIDTH-1 : 0] exu_result,
    output exu_zero
);


  alu alu0(
    .alu_ctrl(exu_alu_ctrl),
    .alu_a(exu_data_a),
    .alu_b(exu_data_b),
    .alu_out(exu_result),
    .alu_zero(exu_zero)
  );
    
>>>>>>> 51f4568c (单周期基本框架)
endmodule
