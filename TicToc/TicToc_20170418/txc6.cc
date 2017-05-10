#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
using namespace omnetpp;
class Txc6 : public cSimpleModule
{
  private:
    int counter;  // Note the counter here
    cMessage *event;
    cMessage *tictocMsg;

  public:
    Txc6();
    virtual ~Txc6();
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Txc6);

Txc6::Txc6(){
	event = tictocMsg = nullptr;
}
Txc6::~Txc6(){
	cancelAndDelete(event);
	delete tictocMsg;
}

void Txc6::initialize()
{
    counter = par("limit");

    event = new cMessage("event");
    tictocMsg = nullptr;
    if (strcmp("tic", getName()) == 0) {
        EV << "Scheduling first send to t=5s\n";
        tictocMsg = new cMessage("tictocMsg");
	scheduleAt(5.0, event);
    }
}
void Txc6::handleMessage(cMessage *msg)
{
	if(msg == event){
		EV<<"Wait period over, sending back message\n";
		counter--;
		if (counter == 0) {
			EV << getName() << "'s counter reached zero, deleting message\n";
			delete msg;
	    	}else{
			EV << getName() << "'s counter is " << counter << ", sending back message\n";
			send(tictocMsg, "out");
			tictocMsg = nullptr;
		}
	}else{
			EV<<"This is a tictoc msg\nWaiting for 1s\n";
			tictocMsg = new cMessage("tictocMsg");
			scheduleAt(simTime()+1.0, event);
	}
}
