simple Transmitter_PS{
	parameters:
		@display("i=block/downarrow,cyan");
	gates:
		input in;
		output out;
}

network LeakyBucket_PS{
	submodules:
		tx1: Transmitter_PS;
		tx2: Transmitter_PS;
	connections:
		tx1.out --> {  delay 100ms; } --> tx2.in;
		tx2.out --> {  delay 100ms; } --> tx1.in;
}
