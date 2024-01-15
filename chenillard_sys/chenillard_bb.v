
module chenillard (
	clk_clk,
	pio_0_external_connection_export,
	pio_1_external_connection_export,
	reset_reset_n,
	pio_2_external_connection_export);	

	input		clk_clk;
	output	[7:0]	pio_0_external_connection_export;
	input	[7:0]	pio_1_external_connection_export;
	input		reset_reset_n;
	input	[7:0]	pio_2_external_connection_export;
endmodule
