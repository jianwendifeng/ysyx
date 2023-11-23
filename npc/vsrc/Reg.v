<<<<<<< HEAD
module Reg #(ADDR_WIDTH = 5, DATA_WIDTH = 32) (
  input clk,
  input [DATA_WIDTH-1:0] wdata,
  input [ADDR_WIDTH-1:0] waddr,
  input wen,
  input  [ADDR_WIDTH-1:0] raddr,
  output reg [DATA_WIDTH-1:0] rdata
=======
module Reg #(ADDR_WIDTH = 5, DATA_WIDTH = 64) (
  input clk,
  input [4:0] Reg_waddr,
  input [DATA_WIDTH-1:0] Reg_wdata,
  input Reg_wen,
  input  [4:0] Reg_raddr_a,
  input  [4:0] Reg_raddr_b,
  output reg [DATA_WIDTH-1:0] Reg_rdata_a,
  output reg [DATA_WIDTH-1:0] Reg_rdata_b
>>>>>>> 51f4568c (单周期基本框架)
);
  
	reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];

    // 初始化
  initial begin
<<<<<<< HEAD
    rf[0] = 32'b0;  // 寄存器0不进行初始化
    for (integer i = 0; i < 2**ADDR_WIDTH; i = i + 1) begin
      rf[i] = i;
=======
    rf[0] = 64'b0;  // 寄存器0不进行初始化
    for (integer i = 0; i < 2**ADDR_WIDTH; i = i + 1) begin
      rf[i] = 8;
>>>>>>> 51f4568c (单周期基本框架)
    end
  end
  
	always @(posedge clk) begin
<<<<<<< HEAD
    if (wen) rf[waddr] <= wdata;
  end

  assign rdata = rf[raddr];
=======
    if (Reg_wen) rf[Reg_waddr] <= Reg_wdata;
  end

  assign Reg_rdata_a = rf[Reg_raddr_a];
  assign Reg_rdata_b = rf[Reg_raddr_b];
>>>>>>> 51f4568c (单周期基本框架)

endmodule
