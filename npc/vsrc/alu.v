// module Mulpler (
//     input clk, rst,
//     input [63:0] x, y,
//     input in_valid,
//     output [63:0] p,
//     output out_vaild
// );

//     reg [6:0] cn;
//     always @(posedge clk or posedge rst) begin
//         if(rst) cn <= 0;
//         else if (in_vaild) cn <= 64;
//         else if (cn != 0) cn <= cn -1;
//     end

//     reg[63:0] rx, ry, rp;
//     wire[63:0] aluout;
//     wire c;
//     parameter ALU_ADD = 2'b10;
//     Adder64 Mul_Adder64(   
//         .A(x),
//         .B(y),
//         .Cin(0),
//         .S(aluout),
//         .Cout(c)
//     );

//     always @(posedge clk or posedge rst) begin
//         if(rst) {rp, ry, rx} <= 0;
//         else if (in_vaild) {rp, ry, rx} <= {64'b0, y, x};
//         else if (cn != 0) {rp, ry} <= {c, aluout, ry} >> 1;
//     end   

//     assign out_vaild = {cn == 0};
//     assign p = {rp, ry};
// endmodule

module alu #(DATA_WIDTH = 64)(
  input [3:0] alu_ctrl,
  input [DATA_WIDTH-1 : 0] alu_a, alu_b,
  output [DATA_WIDTH-1 : 0] alu_out,
  output alu_zero
  );

  wire alu_SUBctr, alu_SIGctr;
  wire [1:0] alu_OPctr;

  //alu_ctrl 信号的使用:
  //0000 add    0010 slt    0011 sltu  
  //0110  or    1000 sub    1111 srcB
  assign alu_SUBctr = (~alu_ctrl[3] & ~alu_ctrl[2] & alu_ctrl[1]) | alu_ctrl[3];  
  assign alu_SIGctr = ~alu_ctrl[0];
  assign alu_OPctr[1] = (~alu_ctrl[3] & ~alu_ctrl[2] & alu_ctrl[1]) | (alu_ctrl[3] & alu_ctrl[2] & alu_ctrl[1] & alu_ctrl[0]);            
                           //slt,sltu                                     //srcB
  assign alu_OPctr[0] = (~alu_ctrl[3] & ~alu_ctrl[2] & alu_ctrl[1]) | (~alu_ctrl[3] & alu_ctrl[2] & alu_ctrl[1] & ~alu_ctrl[0]);           
                          //slt,sltu                                     //or 

  wire [DATA_WIDTH-1 : 0] alu_data_b, alu_adder_sum, alu_or_sum, alu_slt_sum;     //alu 最后多路选择器的输出
  wire alu_FO, alu_SF, alu_ZF, alu_CF; //alu标识信号
  // wire alu_carry;      

  assign alu_data_b = alu_b ^ {64{alu_SUBctr}};   //当subctrl信号为1，b变为-b
  assign alu_or_sum = alu_a | alu_b;   //按位或操作

  //加法器
  Adder64 alu_Adder64(
            .A(alu_a),
            .B(alu_data_b),
            .Cin(alu_SUBctr), //a-b = a + (-b) + 1,此时负号作为进位信号
            .S(alu_adder_sum),
            .OF(alu_FO),  //溢出
            .SF(alu_SF),  //符号
            .ZF(alu_ZF),  //零标识
            .CF(alu_CF)  //进位
            // .Cout(alu_carry)
          );
  
  //slt/sltu
  wire alu_slt_unsign, alu_slt_sign, alu_slt_less;
  assign alu_slt_unsign = alu_CF ^ alu_SUBctr;
  assign alu_slt_sign = alu_FO ^ alu_SF;
  
  assign alu_slt_less = alu_SIGctr ? alu_slt_sign : alu_slt_unsign;
  assign alu_slt_sum = {63'b0, alu_slt_less};

  //alu最后结果的输出
 
  assign alu_out = (alu_OPctr == 2'b00 ? alu_adder_sum: alu_OPctr == 2'b01 ? alu_or_sum: alu_OPctr == 2'b10 ? alu_data_b : alu_slt_sum);

  assign alu_zero = alu_ZF;

endmodule
