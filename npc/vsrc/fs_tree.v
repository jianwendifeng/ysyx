/* verilator lint_off UNOPTFLAT */
module fs_tree(
    input [63:0] p, g,
    output [63:0] P, G
);

    wire [63:0] GL[6:0], PL[6:0];
    assign GL[0] = g;
    assign PL[0] = p;
    genvar i, j, k;

    generate
        for (i = 0; i < 6; i = i + 1) begin: fs_tree
            for (j = (1 << i); j < 64; j = j + 1) begin: gpunion0
                pg_union pg_union0(
                    .p2(PL[i][j]),
                    .g2(GL[i][j]),
                    .p1(PL[i][j - (1 << i)]),
                    .g1(GL[i][j - (1 << i)]),
                    .P(PL[i + 1][j]),
                    .G(GL[i + 1][j])
                );
            end

            for (k = 0; k < (1 << i); k = k + 1) begin: pgwire
                assign PL[i + 1][k] = PL[i][k];
                assign GL[i + 1][k] = GL[i][k];
            end
        end
    endgenerate

    assign P = PL[6];
    assign G = GL[6];

endmodule

/* verilator lint_on UNOPTFLAT */
