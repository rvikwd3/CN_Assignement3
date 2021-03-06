#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
using namespace omnetpp;
class Txc7 : public cSimpleModule
{
  private:
    int counter;  // Note the counter here
    cMessage *event;
    cMessage *tictocMsg;

  public:
    Txc7();
    virtual ~Txc7();
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Txc7);

Txc7::Txc7(){
	event = tictocMsg = nullptr;
}
Txc7::~Txc7(){
	cancelAndDelete(event);
	delete tictocMsg;
}

void Txc7::initialize()
{
    counter = par("limit");
    WATCH(counter);

    event = new cMessage("event");
    tictocMsg = nullptr;
    if (strcmp("tic", getName()) == 0) {
        EV << "Scheduling first send to t=5s\n";
        tictocMsg = new cMessage("tictocMsg");
	scheduleAt(5.0, event);
    }
}
void Txc7::handleMessage(cMessage *msg)
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
		if(uniform(0,1.0) < 0.1){
			EV << "Lost message\n";
			delete msg;
		}else{

			simtime_t delay = exponential(3);

			EV<<"This is a tictoc msg\nWaiting for "<< delay << "s\n";
			tictocMsg = msg;
			scheduleAt(simTime()+delay, event);
		}
	}
}
