module pg_init(
    input A,B,Cin,
    output S,
    output p,g
);
    assign S = A ^ B ^ Cin;
    assign p = A ^ B;
    assign g = A & B;
endmodule
