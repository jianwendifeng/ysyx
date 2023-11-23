/* verilator lint_off UNOPTFLAT */
module pg_union(
    input p2,g2,p1,g1,
    output P,G
);
    assign P = p1 & p2;
    assign G = g2 | p2 & g1;
endmodule

/* verilator lint_on UNOPTFLAT */
