simple Txc4
{
	parameters:
		@display("i=block/routing");
		bool sendMsgOnInit = default(false);
		int limit = default(2);
	gates:
		input in;
		output out;
}
network Tictoc4
{
submodules:
	tic: Txc4 {
		parameters:
			sendMsgOnInit = true;
			@display("i=,cyan");
		}
	toc: Txc4 {
		parameters:
			sendMsgOnInit = false;
			@display("i=,gold");
	}
connections:
	tic.out --> {  delay = 100ms; } --> toc.in;
	tic.in <-- {  delay = 100ms; } <-- toc.out;
}
