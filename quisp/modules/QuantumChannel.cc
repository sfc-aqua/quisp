/** \file QuantumChannel.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *
 *  \brief QuantumChannel
 */
//#include "QuantumChannel.h"
#include <vector>
#include <omnetpp.h>
#include <unsupported/Eigen/MatrixFunctions>
//#include <Eigen/Dense>
#include "../PhotonicQubit_m.h"

using namespace Eigen;
using namespace omnetpp;


/*The sum of Z,X and Y error rate equates to pauli_error_rate. Value could potentially between 0 ~ 1. */
typedef struct _channel_error_model{
    double pauli_error_rate;//Overall error rate
    double Z_error_rate;
    double X_error_rate;
    double Y_error_rate;
} channel_error_model;



/** \class QuantumChannel QuantumChannel.cc
 *  \todo Documentation of the class header.
 *
 *  \brief QuantumChannel
 */
class QuantumChannel : public cDatarateChannel
{
    public:
        channel_error_model err;
        double photon_loss_rate;
        double distance = 0; //in km
    private:
       double No_error_ceil;
       double X_error_ceil;
       double Y_error_ceil;
       double Z_error_ceil;
       virtual void setErrorCeilings();
    public:
        QuantumChannel();
        virtual void initialize();
        virtual void processMessage(cMessage *msg, simtime_t t, result_t& result);

};

Define_Channel(QuantumChannel)

QuantumChannel::QuantumChannel()
{

}

void QuantumChannel::initialize(){
    cDatarateChannel::initialize();
    distance = par("distance");//in km
    double Z_error_ratio = par("Z_error_ratio");//par("name") will be read from .ini or .ned file
    double X_error_ratio = par("X_error_ratio");
    double Y_error_ratio = par("Y_error_ratio");
    double ratio_sum = Z_error_ratio+X_error_ratio+Y_error_ratio;//Get the sum of x:y:z for normalization
    err.pauli_error_rate = par("channel_error_rate");//This is per km.
    err.X_error_rate = err.pauli_error_rate * (X_error_ratio/ratio_sum);
    err.Y_error_rate = err.pauli_error_rate * (Y_error_ratio/ratio_sum);
    err.Z_error_rate = err.pauli_error_rate * (Z_error_ratio/ratio_sum);
    photon_loss_rate = par("photon_loss_rate");//Photon Loss rate per km.

    setErrorCeilings();
    EV<<"\nNo_error_ceil = "<<No_error_ceil<<", X_error_ceil = "<< X_error_ceil << ", Z_error_ceil"<<Z_error_ceil<<", Y_error_ceil"<<Y_error_ceil<<"\n";

}

void QuantumChannel::setErrorCeilings(){
    MatrixXd Initial_condition(1,5);//Input state condition of the qubit. The syntax here is symmetric to the one below.
    Matrix<double,1,5> Output_condition;//Output state distribution will be kept because the channel length is static.

    Initial_condition << 1,0,0,0,0;// I, X, Z, Y, Photon Lost

    MatrixXd Transition_matrix(5,5);
    MatrixXd Q_to_the_distance(5,5);

    Transition_matrix << 1-err.pauli_error_rate-photon_loss_rate, err.X_error_rate,err.Z_error_rate,err.Y_error_rate,photon_loss_rate,
                err.X_error_rate, 1-err.pauli_error_rate-photon_loss_rate, err.Y_error_rate,err.Z_error_rate,photon_loss_rate,
                err.Z_error_rate,err.Y_error_rate, 1-err.pauli_error_rate-photon_loss_rate,err.X_error_rate, photon_loss_rate,
                err.Y_error_rate,err.Z_error_rate, err.X_error_rate, 1-err.pauli_error_rate-photon_loss_rate, photon_loss_rate,
                0,0,0,0,1;

    MatrixPower<MatrixXd> Apow(Transition_matrix);
    Q_to_the_distance = Apow(distance);
    Output_condition = Initial_condition * Q_to_the_distance;
    EV<<Output_condition;
    No_error_ceil = Output_condition(0,0);
    X_error_ceil = Output_condition(0,0)+Output_condition(0,1);
    Z_error_ceil = Output_condition(0,0)+Output_condition(0,1)+Output_condition(0,2);
    Y_error_ceil = Output_condition(0,0)+Output_condition(0,1)+Output_condition(0,2)+Output_condition(0,3);
}

void QuantumChannel::processMessage(cMessage *msg, simtime_t t, result_t& result)
{

    cDatarateChannel::processMessage(msg, t, result);//Call the original processMessage

    try{
        PhotonicQubit *q = check_and_cast<PhotonicQubit *>(msg);

        double rand = dblrand();//Gives a random double between 0.0 ~ 1.0
        if(rand < No_error_ceil){
            //Qubit will end up with no error
            //return;
        }else if(No_error_ceil <= rand && rand < X_error_ceil && (No_error_ceil!=X_error_ceil)){
            //X error
            q->setPauliXerr(true);
        }else if(X_error_ceil <= rand && rand < Z_error_ceil && (X_error_ceil!=Z_error_ceil)){
            //Z error
            q->setPauliZerr(true);
        }else if(Z_error_ceil <= rand && rand < Y_error_ceil && (Z_error_ceil!=Y_error_ceil)){
            //Y error
            q->setPauliXerr(true);
            q->setPauliZerr(true);
        }else{
            //Photon was lost
            q->setPhotonLost(true);
        }
        q->setError_random_for_debug(rand);//For debugging purpose
    }catch(std::exception& e){
        //error("Only PhotonicQubit is allowed in quantum channel");
        EV<<"Only PhotonicQubit is allowed in quantum channel";
    }
}

