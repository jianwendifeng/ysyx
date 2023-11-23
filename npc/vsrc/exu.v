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
    
endmodule
