simple Txc6
{
	parameters:
		@display("i=block/routing");
		bool sendMsgOnInit = default(false);
		int limit = default(2);
	gates:
		input in;
		output out;
}
simple Tic6 extends Txc6{
	parameters:
		@display("i=,cyan");
		sendMsgOnInit = true;
}
simple Toc6 extends Txc6{
	parameters:
		@display("i=,gold");
		sendMsgOnInit = false;
}

network Tictoc6
{
submodules:
	tic: Tic6;
	toc: Toc6;
connections:
	tic.out --> {  delay = 100ms; } --> toc.in;
	tic.in <-- {  delay = 100ms; } <-- toc.out;
}
