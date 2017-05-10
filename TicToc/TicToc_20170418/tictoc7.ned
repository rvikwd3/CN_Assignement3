simple Txc7
{
	parameters:
		@display("i=block/routing");
		bool sendMsgOnInit = default(false);
		int limit = default(2);
	gates:
		input in;
		output out;
}
simple Tic7 extends Txc7{
	parameters:
		@display("i=,cyan");
		sendMsgOnInit = true;
}
simple Toc7 extends Txc7{
	parameters:
		@display("i=,gold");
		sendMsgOnInit = false;
}

network Tictoc7
{
submodules:
	tic: Tic7;
	toc: Toc7;
connections:
	tic.out --> {  delay = 100ms; } --> toc.in;
	tic.in <-- {  delay = 100ms; } <-- toc.out;
}
