module top #(ADDR_WIDTH = 32, DATA_WIDTH = 64) (
  input clk,
  input rst 
);

  wire top_idu_reg_wen;
  wire [4 : 0] top_idu_reg_waddr;
  wire [4 : 0] top_idu_regaddr_a;
  wire [4 : 0] top_idu_regaddr_b;
  wire [DATA_WIDTH-1 : 0] top_idu_regdata_a;
  wire [DATA_WIDTH-1 : 0] top_idu_regdata_b;
  wire [DATA_WIDTH-1 : 0] top_exu_reg_wdata;

  Reg Reg0(
    .clk(clk), 
    .Reg_wen(top_idu_reg_wen),
    .Reg_waddr(top_idu_reg_waddr), 
    .Reg_wdata(top_exu_reg_wdata), 
    .Reg_raddr_a(top_idu_regaddr_a), 
    .Reg_raddr_b(top_idu_regaddr_b), 
    .Reg_rdata_a(top_idu_regdata_a), 
    .Reg_rdata_b(top_idu_regdata_b)
  );

  wire top_pc_ctrl;
  wire [ADDR_WIDTH-1 : 0] top_pc_addr;
  wire [ADDR_WIDTH-1 : 0] top_ifu_inst;
  wire [3:0] top_alu_ctrl;

  ifu ifu0(
    .clk(clk),
    .rst(rst),
    .ifu_in(top_ifu_pc_in),
    .ifu_out_pc(top_pc_addr),
    .ifu_out_inst(top_ifu_inst)
  );
  wire [ADDR_WIDTH-1 : 0] top_ifu_pc_in;
  wire [ADDR_WIDTH-1 : 0] top_immnum;
  assign top_ifu_pc_in = (top_bench_sign&top_pc_ctrl) ? top_pc_addr + top_immnum : top_pc_addr + 4;

  wire [DATA_WIDTH-1 : 0] top_idu_data_a;
  wire [DATA_WIDTH-1 : 0] top_idu_data_b;

  idu idu0(
    .idu_inst_in(top_ifu_inst),
    .idu_regdata_in_a(top_idu_regdata_a),
    .idu_regdata_in_b(top_idu_regdata_b),
    .idu_regaddr_out_a(top_idu_regaddr_a),
    .idu_regaddr_out_b(top_idu_regaddr_b),
    .idu_data_a(top_idu_data_a),
    .idu_data_b(top_idu_data_b),
    .idu_out_imm(top_immnum),
    .idu_wen(top_idu_reg_wen),
    .idu_waddr(top_idu_reg_waddr),
    .idu_alu_ctrl(top_alu_ctrl),
    .idu_pc_ctrl(top_pc_ctrl)
  );
  

  wire top_bench_sign;
  exu exu0(
    .exu_alu_ctrl(top_alu_ctrl),
    .exu_data_a(top_idu_data_a),
    .exu_data_b(top_idu_data_b),
    .exu_result(top_exu_reg_wdata),
    .exu_zero(top_bench_sign)
  );
endmodule 
