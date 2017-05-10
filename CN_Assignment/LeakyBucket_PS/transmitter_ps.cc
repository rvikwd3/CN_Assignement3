#include<string.h>
#include<stdio.h>
#include<omnetpp.h>

#include "PacketSize_m.h"

using namespace omnetpp;

class Transmitter_PS : public cSimpleModule{
	protected:
		virtual void initialize() override;
		virtual void handleMessage(cMessage *msg);
};

Define_Module(Transmitter_PS);

void Transmitter_PS::initialize(){
	EV<<"Initialized\n";
	
	PacketSize *ps0 = new PacketSize();

	ps0->setPacket_size(20);
	ps0->setVisited_bucket(false);
	ps0->setPacket_source(0);

	EV<<"\nPacket_size\t=\t"<<ps0->getPacket_size()<<"\n";
	EV<<"\nVisited Bucket\t=\t"<<ps0->getVisited_bucket()<<"\n";
	EV<<"\nPacket source\t=\t"<<ps0->getPacket_source()<<"\n";
}

void Transmitter_PS::handleMessage(cMessage *msg){
	bubble("Message received");
	sendDelayed(msg, 1, "out");
}
