

module ifu #(ADDR_WIDTH = 32) (
    input clk,
    input rst, 
    input [ADDR_WIDTH-1 : 0] ifu_in,
    output [ADDR_WIDTH-1 : 0] ifu_out_inst,
    output [ADDR_WIDTH-1 : 0] ifu_out_pc
);
    wire [ADDR_WIDTH-1 : 0]pc_addr;
    pc pc0(
      .clk(clk), 
      .rst(rst), 
      .pc_in(ifu_in), 
      .pc_out(pc_addr)
      );
    assign ifu_out_pc = pc_addr;
    inst_rom inst_rom0(.inst_addr(pc_addr), .inst_data(ifu_out_inst));
    

endmodule
