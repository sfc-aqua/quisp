/** \file QuantumChannel.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors takaakimatsuo
 *
 *  \brief QuantumChannel
 */
#include <vector>
#include <omnetpp.h>
#include <unsupported/Eigen/MatrixFunctions>
//#include <Eigen/Dense>
#include <PhotonicQubit_m.h>


using namespace Eigen;
using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
namespace channels {

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
        //int less = 0, more = 0;
    private:
       double No_error_ceil;
       double X_error_ceil;
       double Y_error_ceil;
       double Z_error_ceil;
       double Lost_ceil;
       int DEBUG_darkcount_count = 0;
       MatrixXd Q_to_the_distance;
       virtual void initialize();
       virtual void processMessage(cMessage *msg, simtime_t t, result_t& result);
    public:
       QuantumChannel();

};

Define_Channel(QuantumChannel)

QuantumChannel::QuantumChannel()
{

}

void QuantumChannel::initialize(){
    cDatarateChannel::initialize();
    Q_to_the_distance(5,5);
    distance = par("distance");//in km


    /*double Z_error_ratio = par("Z_error_ratio");//par("name") will be read from .ini or .ned file
    double X_error_ratio = par("X_error_ratio");
    double Y_error_ratio = par("Y_error_ratio");
    double Loss_error_ratio = par("photon_loss_ratio");
    if(Z_error_ratio==0 && X_error_ratio==0 && Y_error_ratio==0 && Loss_error_ratio==0){
        Z_error_ratio=1;//To avoid bug.
        X_error_ratio=1;
        Y_error_ratio=1;
        Loss_error_ratio=1;
    }



    double ratio_sum = Z_error_ratio + X_error_ratio + Y_error_ratio + Loss_error_ratio;//Get the sum of x:y:z for normalization
    err.pauli_error_rate = par("channel_error_rate");//This is per km.
    err.X_error_rate = err.pauli_error_rate * (X_error_ratio/ratio_sum);
    err.Y_error_rate = err.pauli_error_rate * (Y_error_ratio/ratio_sum);
    err.Z_error_rate = err.pauli_error_rate * (Z_error_ratio/ratio_sum);
    photon_loss_rate = err.pauli_error_rate * (Loss_error_ratio/ratio_sum);//Photon Loss rate per km.
    */

    photon_loss_rate = par("channel_Loss_error_rate");
    err.X_error_rate = par("channel_X_error_rate");
    err.Y_error_rate = par("channel_Y_error_rate");
    err.Z_error_rate = par("channel_Z_error_rate");
    err.pauli_error_rate =  err.X_error_rate +  err.Y_error_rate +  err.Z_error_rate + photon_loss_rate;

    /*
    int num_err_type = 0;
    if(err.X_error_rate !=0){
        num_err_type++;
    }
    if(err.Z_error_rate !=0){
        num_err_type++;
    }
    if(err.Y_error_rate !=0){
        num_err_type++;
    }

    if((1-err.pauli_error_rate) < double(1)/double(num_err_type)){
        //error("Error rate inaccurate.");
        std::cout<<"Inaccurate error rate \n";
    }*/

    //std::cout<<"Sum of errors must be ... = "<<err.X_error_rate+err.Y_error_rate+err.Z_error_rate+photon_loss_rate<<"\n";
    //std::cout<<"Channel err:"<<err.pauli_error_rate<<" X = " <<err.X_error_rate << "Y = "<< err.Y_error_rate << ", Z = "<< err.Z_error_rate<<",Loss"<<photon_loss_rate<<"\n";
    MatrixXd Transition_matrix(5,5);

    Transition_matrix << 1-err.pauli_error_rate, err.X_error_rate,err.Z_error_rate,err.Y_error_rate,photon_loss_rate,
                err.X_error_rate, 1-err.pauli_error_rate, err.Y_error_rate,err.Z_error_rate,photon_loss_rate,
                err.Z_error_rate,err.Y_error_rate, 1-err.pauli_error_rate,err.X_error_rate, photon_loss_rate,
                err.Y_error_rate,err.Z_error_rate, err.X_error_rate, 1-err.pauli_error_rate, photon_loss_rate,
                0,0,0,0,1;

    std::cout<<"Transition mat per km = \n"<<Transition_matrix<<"\n";
    MatrixPower<MatrixXd> Apow(Transition_matrix);
    Q_to_the_distance = Apow(distance);
    std::cout<<"Transition mat = "<<Q_to_the_distance<<"\n";


    //std::cout<<"\nNo_error_ceil = "<<No_error_ceil<<", X_error_ceil = "<< X_error_ceil << ", Z_error_ceil"<<Z_error_ceil<<", Y_error_ceil"<<Y_error_ceil<<" pauli err rate is "<<err.pauli_error_rate<<"\n";
    //std::cout<<" 1-err.pauli_error_rate" <<1-err.pauli_error_rate<<"err.X_error_rate"<<err.X_error_rate<<"err.Z_error_rate"<<err.Z_error_rate<<"err.Y_error_rate"<<err.Y_error_rate<<"photon_loss_rate"<<photon_loss_rate<<"\n";
}




void QuantumChannel::processMessage(cMessage *msg, simtime_t t, result_t& result)
{

    cDatarateChannel::processMessage(msg, t, result);//Call the original processMessage

    try{
        PhotonicQubit *q = check_and_cast<PhotonicQubit *>(msg);

        bool lost = q->getPhotonLost();
        bool Zerr = q->getPauliZerr();
        bool Xerr = q->getPauliXerr();

        //The photon may have an error when emitted.
        MatrixXd Initial_condition(1,5);//I, X, Z, Y, Photon Lost
        if(lost){
                    Initial_condition << 0,0,0,0,1;//Photon already lost. Maybe by emission time. Not implemented though.
        }else if(Zerr && Xerr){
                    Initial_condition << 0,0,0,1,0;//Has a Y error
        }else if(Zerr && !Xerr){
                    Initial_condition << 0,0,1,0,0;//Has a Z error
        }else if(!Zerr && Xerr){
                    Initial_condition << 0,1,0,0,0;//Has an X error
        }else{
                    Initial_condition << 1,0,0,0,0;//No error
        }
        MatrixXd Output_condition(1,5);
        Output_condition = Initial_condition * Q_to_the_distance;

        //std::cout<<"Q_to_the_distance"<<Q_to_the_distance<<"\n";
        //std::cout<<"Output_condition = "<<Output_condition<<"\n";
        No_error_ceil = Output_condition(0,0);
        X_error_ceil = No_error_ceil+Output_condition(0,1);
        Z_error_ceil = X_error_ceil+Output_condition(0,2);
        Y_error_ceil = Z_error_ceil+Output_condition(0,3);
        Lost_ceil = Y_error_ceil + Output_condition(0,4);

        //std::cout<<"NO error ceil = "<<No_error_ceil<<", X = "<<X_error_ceil<<"Z, "<<Z_error_ceil<<", Y = "<<Y_error_ceil<<", Lost = "<<Lost_ceil<<"\n";


        double rand = dblrand();//Gives a random double between 0.0 ~ 1.0
       /* if(rand<0.5){
            less++;
        }else{
            more++;
        }*/
        //double rand = std::rand()/(RAND_MAX + 1.);
        if(rand < No_error_ceil){
            //Qubit will end up with no error
        }else if(No_error_ceil <= rand && rand < X_error_ceil && (No_error_ceil!=X_error_ceil)){
            //X error
            bool xerr = q->getPauliXerr();
            q->setPauliXerr(!xerr);//if xerr already was true, then another x error will make it false
        }else if(X_error_ceil <= rand && rand < Z_error_ceil && (X_error_ceil!=Z_error_ceil)){
            //Z error
            bool zerr = q->getPauliZerr();
            q->setPauliZerr(!zerr);
        }else if(Z_error_ceil <= rand && rand < Y_error_ceil && (Z_error_ceil!=Y_error_ceil)){
            //Y error
            bool xerr = q->getPauliXerr();
            q->setPauliXerr(!xerr);
            bool zerr = q->getPauliZerr();
            q->setPauliZerr(!zerr);
        }else{
            //Photon was lost
            DEBUG_darkcount_count++;
            //std::cout<<"less = "<<less<<", more = "<<more<<"\n";
            //std::cout<<"dbl="<<rand<<" count = "<<DEBUG_darkcount_count<<"\n";
            q->setPhotonLost(true);
        }
        q->setError_random_for_debug(rand);//For debugging purpose
    }catch(std::exception& e){
        //error("Only PhotonicQubit is allowed in quantum channel");
        EV<<"Only PhotonicQubit is allowed in quantum channel";
    }
}

} // namespace channels
} // namespace quisp
