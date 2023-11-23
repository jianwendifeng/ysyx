<<<<<<< HEAD
module pc #(RESET_VAL = 32'h80000000) (
  input clk,
  input rst,
  output reg [31:0] pc_out
=======
module pc #(ADDR_WIDTH = 32, RESET_VAL = 32'h80000000)(
  input clk,
  input rst,
  input [ADDR_WIDTH-1 : 0] pc_in,
  output reg [ADDR_WIDTH-1 :0] pc_out
>>>>>>> 51f4568c (单周期基本框架)
);

	always @ (posedge clk) begin
		if(rst) pc_out <= RESET_VAL;
<<<<<<< HEAD
		else pc_out <= pc_out + 4;
=======
		else pc_out <= pc_in;
>>>>>>> 51f4568c (单周期基本框架)
	end

endmodule
