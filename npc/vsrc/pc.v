module pc #(ADDR_WIDTH = 32, RESET_VAL = 32'h80000000)(
  input clk,
  input rst,
  input [ADDR_WIDTH-1 : 0] pc_in,
  output reg [ADDR_WIDTH-1 :0] pc_out
);

	always @ (posedge clk) begin
		if(rst) pc_out <= RESET_VAL;
		else pc_out <= pc_in;
	end

endmodule
