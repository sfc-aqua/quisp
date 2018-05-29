/** \file BellStateAnalyzer.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *
 *  \brief BellStateAnalyzer
 */
#include <vector>
#include <omnetpp.h>
#include "../classical_messages_m.h"
#include "../PhotonicQubit_m.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

using namespace omnetpp;

/** \class BellStateAnalyzer BellStateAnalyzer.cc
 *  \todo Documentation of the class header.
 *
 *  \brief BellStateAnalyzer
 */
class BellStateAnalyzer : public cSimpleModule
{
    private:
        double darkcount_rate;
        double loss_rate;
        double error_rate;
        bool left_clicked;
        bool right_click;
        bool left_last_photon_detected;
        bool right_last_photon_detected;
        bool send_result;
        double required_precision;//1.5ns
        simtime_t left_arrived_at;
        int left_photon_origin_node_address;
        int left_photon_origin_qnic_index;
        int left_photon_origin_qubit_index;
        simtime_t right_arrived_at;
        int right_photon_origin_node_address;
        int right_photon_origin_qnic_index;
        int right_photon_origin_qubit_index;
        int count_X=0, count_Y=0, count_Z=0, count_I=0, count_L=0, count_total=0;//for debug
        bool handshake = false;
        bool this_trial_done = false;
        double BSAsuccess_rate = 0.5;
        int left_count, right_count = 0;
    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);
        virtual bool isPhotonLost(cMessage *msg);
        virtual void forDEBUG_countErrorTypes(cMessage *msg);
        virtual void sendBSAresult(bool result, bool last);
        virtual void initializeVariables();
};

Define_Module(BellStateAnalyzer);

void BellStateAnalyzer::initialize()
{
   darkcount_rate = par("darkcount_rate");
   loss_rate = par("loss_rate");
   error_rate = par("error_rate");
   //duration = par("duration");
   required_precision = par("required_precision");
   left_arrived_at = -1;
   right_arrived_at = -1;
   left_last_photon_detected = false;
   right_last_photon_detected = false;
   send_result = false;
   left_photon_origin_node_address = -1;
   left_photon_origin_qnic_index = -1;
   left_photon_origin_qubit_index = -1;
   right_photon_origin_node_address = -1;
   right_photon_origin_qnic_index = -1;
   right_photon_origin_qubit_index = -1;
}

void BellStateAnalyzer::handleMessage(cMessage *msg){
    PhotonicQubit *photon = check_and_cast<PhotonicQubit *>(msg);
    if(photon->getFirst() && this_trial_done == true){//Next round started
        this_trial_done = false;
        left_arrived_at = -1;
        right_arrived_at = -1;
        right_last_photon_detected = false;
        left_last_photon_detected = false;
        send_result = false;
        right_count = 0;
        left_count = 0;
        EV<<"------------------Next round!\n";
        bubble("Next round!");
    }

    if(msg->arrivedOn("fromHoM_quantum_port$i",0)){
        left_arrived_at=simTime();
        left_photon_origin_node_address = photon->getNodeEntangledWith();
        left_photon_origin_qnic_index = photon->getQNICEntangledWith();
        left_photon_origin_qubit_index = photon->getStationaryQubitEntangledWith();
        if(photon->getFirst()){
            left_last_photon_detected = false;
            //send_result = false;
        }
        if(photon->getLast()){
            left_last_photon_detected = true;
            //send_result = true;
        }
        left_count++;
        //EV<<"Photon from Left arrived at = "<<simTime()<<"\n";
    }else if(msg->arrivedOn("fromHoM_quantum_port$i",1)){
        right_arrived_at=simTime();
        right_photon_origin_node_address = photon->getNodeEntangledWith();
        right_photon_origin_qnic_index = photon->getQNICEntangledWith();
        right_photon_origin_qubit_index = photon->getStationaryQubitEntangledWith();
        if(photon->getFirst()){
            right_last_photon_detected = false;
            //send_result = false;
        }
        if(photon->getLast()){
            right_last_photon_detected = true;
            //send_result = true;
        }
        right_count++;
        //EV<<"Right = "<<simTime()<<"\n";
    }else{
        error("This shouldn't happen....! Only 2 connections to the BSA allowed");
    }

    if((right_last_photon_detected || left_last_photon_detected)){
        send_result = true;
    }


    //Just for debugging purpose
    forDEBUG_countErrorTypes(msg);

    double difference = (left_arrived_at-right_arrived_at).dbl();
    //EV<<"!!!!!!!!!!!!!!!!!!!!!!!!!!this_trial_done == "<<this_trial_done<<"\n";
    if(this_trial_done == true){
        bubble("dumping result");
        //No need to do anything. Just ignore the BSA result for this shot 'cause the trial is over and only 1 photon will arrive anyway.
        delete msg;
        return;
    }else if((left_arrived_at != -1 && right_arrived_at != -1) && std::abs(difference)<=(required_precision)){
        //Both arrived perfectly fine
        bool lost = isPhotonLost(msg);
        if(!lost){

            double rand = dblrand();
            if(rand < BSAsuccess_rate){
                bubble("Success...!");
                sendBSAresult(false, send_result);//succeeded because both reached, and both clicked

            }//we also need else if darkcount....
            else{
                bubble("Failed...!");
                EV<<"rand = "<<rand<<" <"<<BSAsuccess_rate;
                sendBSAresult(true, send_result);//just failed because only 1 detector clicked while both reached
            }
        }else{
            bubble("Photon lost!");
            sendBSAresult(true, send_result);
            //If Dark count...

        }
        initializeVariables();

    }else if((left_arrived_at != -1 && right_arrived_at != -1) && std::abs(difference)>(required_precision)){
        //Both qubits arrived, but the timing was bad.
        bubble("Emission Timing Failed");
        initializeVariables();
        sendBSAresult(true,send_result);
    }else{
        bubble("Waiting...");
        /*if(photon->getLast() && (left_count == 0 || right_count == 0)){//This is wrong, because it will ignore the 2nd photon arrival if both of the photons are the first and last.
            //sendBSAresult(true,send_result);
            bubble("Ehhh");
            EV<<"left_count = "<<left_count<<", right_count = "<<right_count;
        }*/
        //Just waiting for the other qubit to arrive.
    }
    delete msg;
}

void BellStateAnalyzer::initializeVariables(){
    left_arrived_at = -1;
    left_photon_origin_node_address = -1;
    left_photon_origin_qnic_index = -1;
    left_photon_origin_qubit_index = -1;
    right_arrived_at = -1;
    right_photon_origin_node_address = -1;
    right_photon_origin_qnic_index = -1;
    right_photon_origin_qubit_index = -1;
    left_count = 0;
    right_count = 0;
}

void BellStateAnalyzer::sendBSAresult(bool result,bool sendresults){
    //result could be false positive (actually ok but recognized as ng),
    //false negative (actually ng but recognized as ok) due to darkcount
    //true positive and true negative is no problem.
    //EV<<"send?="<<sendresults<<"___________________________________\n";
    if(!sendresults){
        BSAresult *pk = new BSAresult;
        pk->setEntangled(result);
        send(pk, "toHoMController_port");
    }else{//Was the last photon. End pulse detected.
        BSAfinish *pk = new BSAfinish();
        pk->setKind(7);
        pk->setEntangled(result);
        send(pk, "toHoMController_port");
        bubble("trial done now");
        this_trial_done = true;
        //EV<<"!!!!!!!!!!!!!!!over!!!!!!!!!!!this_trial_done == "<<this_trial_done<<"\n";
    }
}

void BellStateAnalyzer::forDEBUG_countErrorTypes(cMessage *msg){
    PhotonicQubit *q = check_and_cast<PhotonicQubit *>(msg);
    if(q->getPauliXerr() && q->getPauliZerr()){
        count_Y++;
    }else if(q->getPauliXerr() && !q->getPauliZerr()){
        count_X++;
    }else if(!q->getPauliXerr() && q->getPauliZerr()){
        count_Z++;
    }else if(q->getPhotonLost()){
        count_L++;
    }else{
        count_I++;
    }count_total++;
    //EV<<"Y%="<<(double)count_Y/(double)count_total<<", X%="<<(double)count_X/(double)count_total<<", Z%="<<(double)count_Z/(double)count_total<<", L%="<<(double)count_L/(double)count_total<<", I% ="<<(double)count_I/(double)count_total<<"\n";
}

bool BellStateAnalyzer::isPhotonLost(cMessage *msg){
    PhotonicQubit *q = check_and_cast<PhotonicQubit *>(msg);
    if(q->getPhotonLost()){
        return true; //Lost
    }else{
        return false;
    }
    delete msg;
}
