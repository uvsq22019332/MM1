/*** Generator.cc ***/

#include <stralign.h>
#include <omnetpp.h>
using namespace omnetpp;
class Generator : public cSimpleModule {
    private:
        cMessage *sendMsgEvent;
    public:
        Generator (); //constructeur
    protected:
        virtual void initialize();
        virtual void finish();
        virtual void handleMessage(cMessage *msg);

};

Define_Module(Generator);
Generator::Generator(){
    sendMsgEvent = NULL;
}



void Generator::initialize(){
    //creation des paquets d'envoi
    sendMsgEvent = new cMessage("sendEvent");
    //planifier le premier �v�nement � un moment al�atoire
    scheduleAt(par("interArrivalTime"),sendMsgEvent);

}

void Generator::finish(){

}

void Generator::handleMessage(cMessage *msg){
    cMessage *pkt;
    simtime_t departure_time;
    // creation d'un nouveau paquet;
    pkt = new cMessage("paquet");
    //envoi a la sortie
    send(pkt,"out");
    //calculer le nouveau temps de d�part
    departure_time=simTime()+par("interArrivalTime");
    //programmer la g�n�ration de nouveaux paquets
    scheduleAt(departure_time, sendMsgEvent);
}
