/** \todo header Write doxygen file header. */
/** \todo clean Clean code when it is simple. */
/** \todo doc Write doxygen documentation. */
//#include "QuantumChannel.h"
#include <vector>
#include <omnetpp.h>
#include "../PhotonicQubit_m.h"

using namespace omnetpp;

typedef struct channel_error{
    double error_rate;//Overall error rate
    double Z_error_ratio;//Phase flip error ratio
    double X_error_ratio;//Bit flip error ratio
    double Y_error_ratio;//Phase and Bit flip error ratio
    double total_ratio;
};

class QuantumChannel : public cDatarateChannel
{
    public:
        channel_error err;
        double photon_loss_rate;
        double distance = 0; //in km
    public:
        QuantumChannel();
        virtual void initialize();
        virtual void processMessage(cMessage *msg, simtime_t t, result_t& result);
        virtual void applyPhotonLoss();

};

Define_Channel(QuantumChannel)


QuantumChannel::QuantumChannel()
{

}

void QuantumChannel::initialize(){
    cDatarateChannel::initialize();
    distance = par("distance");
    err.Z_error_ratio = par("Z_error_ratio");//par("name") will be read from .ini or .ned file
    err.X_error_ratio = par("X_error_ratio");
    err.Y_error_ratio = par("Y_error_ratio");
    err.total_ratio = err.Z_error_ratio+err.X_error_ratio+err.Y_error_ratio;//Get the sum of x:y:z for normalization
    err.error_rate = par("channel_error_rate");//This is per km.
    //Treat anything more than 100% as 100%
    err.error_rate = par("channel_error_rate");//per km
    if(err.error_rate>1){//Treat any error rate greater than 100% as 100%
        err.error_rate = 1;
    }

    photon_loss_rate = par("photon_loss_rate");//Photon Loss rate per km.
}



void QuantumChannel::processMessage(cMessage *msg, simtime_t t, result_t& result)
{

    cDatarateChannel::processMessage(msg, t, result);//Call the original processMessage

    try{
        PhotonicQubit *q = check_and_cast<PhotonicQubit *>(msg);
        if(photon_loss_rate!=0){
            if(dblrand() < photon_loss_rate*distance){
                q->setPhotonLost(true);
            }
        }
        if(err.error_rate!=0){
             double rand = dblrand();
             if(rand < err.error_rate){
                 EV<<"rand = "<<rand<<" < channel_error"<<err.error_rate;
                 double Xceil=(err.error_rate)*(err.X_error_ratio/err.total_ratio);
                 double Zceil=(err.error_rate)*((err.Z_error_ratio+err.X_error_ratio)/err.total_ratio);
                 if(0<=rand && rand<Xceil){
                     q->setPauliXerr(true);
                 }else if(Xceil<=rand && rand<Zceil){
                     q->setPauliZerr(true);
                 }else{
                     q->setPauliXerr(true);
                     q->setPauliZerr(true);
                 }
                 q->setError_random_for_debug(rand);//For debugging purpose
             }
        }
    }catch(std::exception& e){
        //error("Only PhotonicQubit is allowed in quantum channel");
        EV<<"Only PhotonicQubit is allowed in quantum channel";
    }
}



void QuantumChannel::applyPhotonLoss(){

}


