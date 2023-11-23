module Adder64(
    input [63:0] A,B,
    input Cin,
    output [63:0] S,
    output OF, SF, ZF, CF
    // output Cout
);
    wire [63:0] p,g,P,G;
    wire [64:0] C;
    assign C[0] = Cin;

    genvar j;
        for(j=0;j<64;j=j+1)
            begin: carry_mod
                assign C[j+1] = G[j] | (P[j]&Cin); 
            end
            
    generate 
        genvar i;
        for(i=0; i<64; i=i+1)
            begin: add_init_bg
                //生成初始p，g
                pg_init pg_init0(   
                    .A(A[i]),.B(B[i]),.Cin(C[i]),.S(S[i]),.p(p[i]),.g(g[i])
                );
                
            end
    endgenerate

    // assign Cout = C[64];
    assign OF = C[64] ^ C[63];  //溢出
    assign SF = S[63];          //和的符号
    assign ZF = ~(|S);          //零标识
    assign CF = C[64] ^ C[0];   //进位、借位信号
    
    //fs树
    fs_tree fs_tree0(
        .p(p), .g(g), .P(P), .G(G)
    );
endmodule
