simple Txc3
{
	parameters:
		@display("i=block/routing");
		bool sendMsgOnInit = default(false);
		int limit = default(2);
	gates:
		input in;
		output out;
}
network Tictoc3
{
submodules:
	tic: Txc3 {
		parameters:
		@display("i=,cyan");
	}
	toc: Txc3 {
		parameters:
		@display("i=,gold");
	}
connections:
	tic.out --> {  delay = 100ms; } --> toc.in;
	tic.in <-- {  delay = 100ms; } <-- toc.out;
}
