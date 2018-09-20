/** \file stationaryQubit.cc
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/14
 *
 *  \brief stationaryQubit
 */
#include "stationaryQubit.h"
#include <vector>
#include <omnetpp.h>
#include <classical_messages_m.h>
#include <unsupported/Eigen/MatrixFunctions>
#include <unsupported/Eigen/KroneckerProduct>
#include <PhotonicQubit_m.h>
#include<bitset>

namespace quisp {
namespace modules {


Define_Module(stationaryQubit);

/**
 * \brief Initialize stationaryQubit
 *
 * Omnet called method to initialize objects.
 *
 */
void stationaryQubit::initialize()
{

    double rand = dblrand();

    /*Photon emission time error rates*/
    double Z_error_ratio = par("emission_Z_error_ratio");//par("name") will be read from .ini or .ned file
    double X_error_ratio = par("emission_X_error_ratio");
    double Y_error_ratio = par("emission_Y_error_ratio");
    double ratio_sum = Z_error_ratio+X_error_ratio+Y_error_ratio;//Get the sum of x:y:z for normalization
    err.pauli_error_rate = par("emission_error_rate");//This is per photon emission.
    err.X_error_rate = err.pauli_error_rate * (X_error_ratio/ratio_sum);
    err.Y_error_rate = err.pauli_error_rate * (Y_error_ratio/ratio_sum);
    err.Z_error_rate = err.pauli_error_rate * (Z_error_ratio/ratio_sum);
    setErrorCeilings();

    /*Memory error rates*/

    double memory_Z_error_ratio = par("memory_Z_error_ratio");//par("name") will be read from .ini or .ned file
    double memory_X_error_ratio = par("memory_X_error_ratio");
    double memory_Y_error_ratio = par("memory_Y_error_ratio");
    double memory_ratio_sum = Z_error_ratio+X_error_ratio+Y_error_ratio;
    memory_err.pauli_error_rate = par("memory_error_rate");//This is per μs.
    memory_err.X_error_rate = memory_err.pauli_error_rate * (memory_X_error_ratio/memory_ratio_sum);
    memory_err.Y_error_rate = memory_err.pauli_error_rate * (memory_Y_error_ratio/memory_ratio_sum);
    memory_err.Z_error_rate = memory_err.pauli_error_rate * (memory_Z_error_ratio/memory_ratio_sum);


    Memory_Transition_matrix << 1-memory_err.pauli_error_rate, memory_err.X_error_rate,memory_err.Y_error_rate, memory_err.Z_error_rate,
               memory_err.X_error_rate, memory_err.pauli_error_rate, memory_err.Y_error_rate,memory_err.Z_error_rate,
               memory_err.Z_error_rate,memory_err.Y_error_rate, memory_err.pauli_error_rate,memory_err.X_error_rate,
               memory_err.Y_error_rate,memory_err.Z_error_rate, memory_err.X_error_rate, 1-memory_err.pauli_error_rate,

/*なんかおかしい。Qchannelも要確認*/

    //Set error matrices. This is used in the process of simulating tomography.
    Pauli.X << 0,1,1,0;
    Pauli.Y << 0,Complex(0,-1),Complex(0,1),0;
    Pauli.Z << 1,0,0,-1;
    Pauli.I << 1,0,0,1;

    //Set measurement operators. This is used in the process of simulating tomography.
    meas_op.X_plus << 0.5,0.5,0.5,0.5;
    meas_op.X_minus << 0.5,-0.5,-0.5,0.5;
    meas_op.Z_plus << 1,0,0,0;
    meas_op.Z_minus << 0,0,0,1;
    meas_op.Y_plus << 0.5,Complex(0,-0.5),Complex(0,0.5),0.5;
    meas_op.Y_minus << 0.5,Complex(0,0.5),Complex(0,-0.5),0.5;

    // Get parameters from omnet
    stationaryQubit_address = par("stationaryQubit_address");
    node_address = par("node_address");
    qnic_address = par("qnic_address");
    qnic_type = par("qnic_type");
    std = par("std");
    setFree();
    setFidelity(-1.);

    /* e^(t/T1) energy relaxation, e^(t/T2) phase relaxation. Want to use only 1/10 of T1 and T2 in general.*/
}


void stationaryQubit::setErrorCeilings(){
    No_error_ceil =1-err.pauli_error_rate;/* if 0 <= dblrand < fidelity = No error*/
    X_error_ceil = No_error_ceil + err.X_error_rate; /* if fidelity <= dblrand < fidelity+X error rate = X error*/
    Z_error_ceil = X_error_ceil + err.Z_error_rate;
    Y_error_ceil = 1;
}



/**
 * \brief cSimpleModule handleMessage function
 *
 * \param msg is the message
 */
void stationaryQubit::handleMessage(cMessage *msg){
    bubble("Got a photon!!");
    setBusy();
    setEmissionPauliError();
    send(msg, "tolens_quantum_port$o");
}

void stationaryQubit::setEmissionPauliError(){
    if(par("GOD_Xerror") || par("GOD_Zerror")){
        error("There shouldn't be an error existing before photon emission. This error may have not been reinitialized since last use. Better check!");
    }
    double rand = dblrand();//Gives a random double between 0.0 ~ 1.0
    if(rand < No_error_ceil){
               //Qubit will end up with no error
               EV<<"No error :"<<rand<<" < "<<No_error_ceil<<"\n";
    }else if(No_error_ceil <= rand && rand < X_error_ceil && (No_error_ceil!=X_error_ceil)){
               //X error
                par("GOD_Xerror") = true;
                EV<<"Xerror :"<<No_error_ceil<<"<="<<rand<<" < "<<X_error_ceil<<"\n";
    }else if(X_error_ceil <= rand && rand < Z_error_ceil && (X_error_ceil!=Z_error_ceil)){
               //Z error
                par("GOD_Zerror") = true;
                EV<<"Zerror :"<<X_error_ceil<<"<="<<rand<<" < "<<Z_error_ceil<<"\n";
    }else if(Z_error_ceil <= rand && rand < Y_error_ceil && (Z_error_ceil!=Y_error_ceil)){
               //Y error
                par("GOD_Xerror") = true;
                par("GOD_Zerror") = true;
                EV<<"Yerror :"<<Z_error_ceil<<"<="<<rand<<" < "<<Y_error_ceil<<"\n";
   }else{
       error("Either the error ceilings or the random double generator is wrong.");
   }
}

bool stationaryQubit::measure_X(){
    //Need to add noise here later

    return !par("GOD_Zerror");
}

/**
 *  Returns true if the measurement outcome was correct
 */
bool stationaryQubit::measure_Y(){
    //Need to add noise here later

    return !(par("GOD_Zerror") || par("GOD_Xerror"));
}

bool stationaryQubit::measure_Z(){
    //Need to add noise here later

    return !par("GOD_Xerror");
}

//Convert X to Z, and Z to X error. Therefore, Y error stays as Y.
void stationaryQubit::Hadamard_gate(){
    //Need to add noise here later

    bool z = par("GOD_Zerror");
    par("GOD_Zerror") = par("GOD_Xerror");
    par("GOD_Xerror") = z;
}

void stationaryQubit::Z_gate(){
    //Need to add noise here later
    par("GOD_Zerror") = !par("GOD_Zerror");
}

void stationaryQubit::X_gate(){
    //Need to add noise here later
    par("GOD_Xerror") = !par("GOD_Xerror");
}

void stationaryQubit::CNOT_gate(stationaryQubit *control_qubit){
    //Need to add noise here later

    if(control_qubit->par("GOD_Xerror")){
        par("GOD_Xerror") = !par("GOD_Xerror");//X error propagates from control to target. If an X error is already present, then it cancels out.
    }

    if(par("GOD_Zerror")){
        control_qubit->par("GOD_Zerror") = ! control_qubit->par("GOD_Zerror");//Z error propagates from target to control. If an Z error is already present, then it cancels out.
    }
}

//This is invoked whenever a photon is emitted out from this particular qubit.
void stationaryQubit::setBusy(){
    isBusy = true;
    emitted_time = simTime();
    updated_time = simTime();//Should be no error at this time.
    par("photon_emitted_at") = emitted_time.dbl();
    par("last_updated_at") = updated_time.dbl();
    par("isBusy") = true;
    // GUI part
    if(hasGUI()){
        getDisplayString().setTagArg("i", 1, "red");
    }
}

//Re-initialization of this stationary qubit
//This is called at the beginning of the simulation (in initialization() above), and whenever it is reinitialized via the RealTimeController.
void stationaryQubit::setFree(){
    isBusy = false;
    emitted_time = -1;
    updated_time = -1;
    par("photon_emitted_at") = emitted_time.dbl();
    par("last_updated_at") = updated_time.dbl();
    par("GOD_Xerror") = false;
    par("GOD_Zerror") = false;
    par("isBusy") = false;
    par("GOD_entangled_stationaryQubit_address") = -1;
    par("GOD_entangled_node_address") = -1;
    par("GOD_entangled_qnic_address") = -1;
    par("GOD_entangled_qnic_type") = -1;
    entangled_partner = nullptr;
    // GUI part
    if(hasGUI()){
        getDisplayString().setTagArg("i", 1, "blue");
    }
}

bool stationaryQubit::checkBusy(){
    Enter_Method("checkBusy()");
    return !!isBusy;
}

/**
 * \brief Generate photon entangled with the memory
 * \warning Shouldn't we destroy a possibly existing photon object before? <- No, I dont think so...
 */
PhotonicQubit *stationaryQubit::generateEntangledPhoton(){
    Enter_Method("generateEntangledPhoton()");
    photon = new PhotonicQubit("Photon");

    //To simulate the actual physical entangled partner, not what the system thinks!!! we need this.
    photon->setNodeEntangledWith(node_address);//This photon is entangled with.... node_address = node's index
    photon->setQNICEntangledWith(qnic_address);//qnic_address != qnic_index. qnic_index is not unique because there are 3 types.
    photon->setStationaryQubitEntangledWith(stationaryQubit_address);//stationaryQubit_address = stationaryQubit's index
    photon->setQNICtypeEntangledWith(qnic_type);
    photon->setEntangled_with(this);
    return photon;
}

/**
 * \brief Emit photon
 *
 * \param pulse: 0 for nothing, 1 for first, 2 for last, 3 for first and last
 *
 * The stationary qubit shouldn't be already busy.
 */
void stationaryQubit::emitPhoton(int pulse)
{
    Enter_Method("emitPhoton()");
    if (checkBusy()) {
        error("Requested a photon emission to a busy qubit... this should not happen!");
        return;
    }
    PhotonicQubit *pk = generateEntangledPhoton();
    if (pulse & STATIONARYQUBIT_PULSE_BEGIN) pk->setFirst(true);
    if (pulse & STATIONARYQUBIT_PULSE_END) pk->setLast(true);
    if (pulse & STATIONARYQUBIT_PULSE_BOUND) pk->setKind(3);
    float jitter_timing = normal(0,std);
    float abso = fabs(jitter_timing);
    scheduleAt(simTime()+abso,pk); //cannot send back in time, so only positive lag
}

void stationaryQubit::setEntangledPartnerInfo(stationaryQubit *partner){
    //When BSA succeeds, this method gets invoked to store entangled partner information. This will also be sent classically to the partner node afterwards.
    entangled_partner = partner;

    par("GOD_entangled_stationaryQubit_address") = partner->par("stationaryQubit_address");
    par("GOD_entangled_node_address") = partner->par("node_address");
    par("GOD_entangled_qnic_address") = partner->par("qnic_address");
    par("GOD_entangled_qnic_type") = partner->par("qnic_type");
}


/*Add another X error. If an X error already exists, then they cancel out*/
void stationaryQubit::addXerror(){
    par("GOD_Xerror") = !par("GOD_Xerror");/*Switches true to false or false to true*/
}

/*Add another Z error. If an Z error already exists, then they cancel out*/
void stationaryQubit::addZerror(){
    par("GOD_Zerror") = !par("GOD_Zerror");/*Switches true to false or false to true*/
}


void stationaryQubit::purify(stationaryQubit * resource_qubit) {
    resource_qubit->CNOT_gate(this);
    bool meas = resource_qubit->measure_Z();
    // communicate, values of measurement
    // probably need to store ours until receiving the partners'
    // if agree (truetrue or falsefalse), keep
}

/*Single qubit memory error based on Markov-Chain*/
void stationaryQubit::apply_memory_error(stationaryQubit *qubit){
    /*Check when the error got updated last time. Errors will be performed depending on the difference between that time and the current time.*/
    double time_evolution = simTime().dbl() - qubit->updated_time.dbl();
    double time_evolution_microsec  =time_evolution * 1000000;
    if(time_evolution_microsec > 0){
        EV<<"\n Memory error applied for time = "<<time_evolution_microsec<<" μs, on qubit "<<qubit<<"in node["<<qubit->par("node_address").str()<<"] \n";
        //Perform Monte-Carlo error simulation on this qubit.
        MatrixXd Initial_condition(1,4);/*I, X, Y, Z*/
        if(qubit->par("GOD_Zerror") && qubit->par("GOD_Xerror")){
            Initial_condition << 0,0,1,0;//Has a Y error
        }else if(qubit->par("GOD_Zerror") && !qubit->par("GOD_Xerror")){
            Initial_condition << 0,0,0,1;//Has a Z error
        }else if(!qubit->par("GOD_Zerror") && qubit->par("GOD_Xerror")){
            Initial_condition << 0,1,0,0;//Has an X error
        }else{
            Initial_condition << 1,0,0,0;//No error
        }
        MatrixPower<MatrixXd> Apow(Memory_Transition_matrix);
        MatrixXd Dynamic_transition_matrix(4,4);
        Dynamic_transition_matrix = Apow(time_evolution_microsec);
        MatrixXd Output_condition(1,4);//I, X, Y, Z
        Output_condition = Initial_condition * Dynamic_transition_matrix;//I,X,Y,Z
        EV<<"Input was "<<Initial_condition<<"Output is now"<<Output_condition<<"\n";
        double No_error_ceil = Output_condition(0,0);
        double X_error_ceil = Output_condition(0,0)+Output_condition(0,1);
        double Y_error_ceil = Output_condition(0,0)+Output_condition(0,1)+Output_condition(0,2);

        /*Reinitialize to no error for convenience*/
        qubit->par("GOD_Zerror") = false;
        qubit->par("GOD_Xerror") = false;

        double rand = dblrand();//Gives a random double between 0.0 ~ 1.0
        if(rand < No_error_ceil){
            //Qubit will end up with no error
        }else if(No_error_ceil <= rand && rand < X_error_ceil && (No_error_ceil!=X_error_ceil)){
                   //X error
            qubit->par("GOD_Xerror") = true;
        }else if(Y_error_ceil <= rand && rand < Z_error_ceil && (X_error_ceil!=Z_error_ceil)){
                   //Z error
            qubit->par("GOD_Zerror") = true;
            qubit->par("GOD_Xerror") = true;
        }else{
            qubit->par("GOD_Zerror") = true;
         }
    }
    EV<<Memory_Transition_matrix<<"\n";
    qubit->updated_time = simTime();//Update parameter, updated_time, to now.
}


Matrix2cd stationaryQubit::getErrorMatrix(stationaryQubit *qubit){
    Matrix2cd error;
    if(qubit->par("GOD_Zerror") && qubit->par("GOD_Xerror")){//Y error on this qubit
            error = Pauli.Y;
            EV<<"Y error"<<"\n";
    }
    else if(qubit->par("GOD_Zerror") && !qubit->par("GOD_Xerror")){//Z error
            error = Pauli.Z;
            EV<<"Z error"<<"\n";
    }
    else if(!qubit->par("GOD_Zerror") && qubit->par("GOD_Xerror")){//X error
            error = Pauli.X;
            EV<<"X error"<<"\n";
    }
    else{
            error = Pauli.I;
            EV<<"I error"<<"\n";
    }
    return error;

    // Matrix4cd test = kroneckerProduct(Pauli.I,Pauli.Y).eval();
}

//returns the density matrix of the Bell pair with error. This assumes that this is entangled with another stationary qubit.
//Measurement output will be based on this matrix, as long as it is still entnagled.
quantum_state stationaryQubit::getQuantumState(){
    Vector4cd ideal_Bell_state(1/sqrt(2),0,0,1/sqrt(2));//Assumes that the state is a 2 qubit state |00> + |11>

    Matrix4cd combined_errors = kroneckerProduct(getErrorMatrix(this),getErrorMatrix(entangled_partner)).eval();

    //EV<<"Combined errors  = "<<combined_errors<<"\n";
    Vector4cd actual_Bell_state = combined_errors*ideal_Bell_state;
    //EV<<"Current physical state is = "<<actual_Bell_state;
    Matrix4cd density_matrix = actual_Bell_state*actual_Bell_state.adjoint();
    //EV<<"dm = "<<density_matrix<<"\n";

    quantum_state q;
    q.state_in_density_matrix = density_matrix;
    q.state_in_ket = actual_Bell_state;
    return q;
}

measurement_output_probabilities stationaryQubit::getOutputProbabilities(quantum_state state, char meas_basis){
    Matrix2cd meas_op_plus, meas_op_minus;
    switch(meas_basis){
        case 'X':
            EV<<"X measurement\n";
            meas_op_plus = meas_op.X_plus;
            meas_op_minus = meas_op.X_minus;
            break;
        case 'Y':
            EV<<"X measurement\n";
            meas_op_plus = meas_op.Y_plus;
            meas_op_minus = meas_op.Y_minus;
            break;
        case 'Z':
            EV<<"X measurement\n";
            meas_op_plus = meas_op.Z_plus;
            meas_op_minus = meas_op.Z_minus;
            break;
        default:
            error("Measurement basis not recognized.");
            break;
    }
    measurement_output_probabilities p;
    Complex Prob = state.state_in_ket.adjoint()*kroneckerProduct(meas_op_plus,meas_op_plus).eval().adjoint()*kroneckerProduct(meas_op_plus,meas_op_plus).eval()*state.state_in_ket;
    p.probability_plus_plus = Prob.real();
    Complex Prob2 = state.state_in_ket.adjoint()*kroneckerProduct(meas_op_plus,meas_op_minus).eval().adjoint()*kroneckerProduct(meas_op_plus,meas_op_minus).eval()*state.state_in_ket;
    p.probability_plus_minus = Prob2.real();
    Complex Prob3 = state.state_in_ket.adjoint()*kroneckerProduct(meas_op_minus,meas_op_plus).eval().adjoint()*kroneckerProduct(meas_op_minus,meas_op_plus).eval()*state.state_in_ket;
    p.probability_minus_plus = Prob3.real();
    Complex Prob4 = state.state_in_ket.adjoint()*kroneckerProduct(meas_op_minus,meas_op_minus).eval().adjoint()*kroneckerProduct(meas_op_minus,meas_op_minus).eval()*state.state_in_ket;
    p.probability_minus_minus = Prob4.real();
    return p;
}



//Assumes that this qubit is entangled with another one, as Bell pair 00+11. 1st qubit is self, 2nd is partner.
//When do we perform measurements? I think we can just ignore the success/fail of entanglement attempt, and measure it beforehand anyway. Waiting cause error.
//How do we know when to measure though?
//Return value: 1 if output is +, 0 if output is -.
std::bitset<1> stationaryQubit::measure_density(char basis_this_qubit){
    if(entangled_partner == nullptr){
        error("Measuring a qubit that is not entangled with another qubit. Not allowed!");
    }
    /*if(entangled_partner->emitted_time=-1 && single_qubit_dm == null){
        error("Something is wrong.");
    }*/

    //todo Check if entangled state has collapsed already (partner qubit measured already).

    //if not, then measure it and get the output (density matrix required)!
    apply_memory_error(this);//Noise due to idle time in memory. This updates the par("GOD_Zerror") and par("GOD_Xerror") of this particular qubit.
    quantum_state current_state = getQuantumState();//Get the density matrix of the Bell pair that involves this particular qubit.
    measurement_output_probabilities p = getOutputProbabilities(current_state, basis_this_qubit);
    EV <<" P(++) = "<<p.probability_plus_plus<<", P(+-) = "<<p.probability_plus_minus<<", P(-+) = "<<p.probability_minus_plus<<", P(--) = "<<p.probability_minus_minus<<"\n";
    double rand = dblrand();//Gives a random double between 0.0 ~ 1.0

    std::bitset<2> output(0);//by default, output is -- (in binary 00)
    if(rand < p.probability_plus_plus){
        //Output is ++
        output.set(0);//00->01
        output.set(1);//01->11
        EV<<"Output is ++"<<output<<"\n";
    }else if(p.probability_plus_plus <= rand && rand < (p.probability_plus_plus+p.probability_plus_minus)){
        //Output is +-
        output.set(1);//00->10
        EV<<"Output is +-"<<output<<"\n";
    }else if((p.probability_plus_plus+p.probability_plus_minus) <= rand && rand < (p.probability_plus_plus+p.probability_plus_minus+p.probability_minus_plus)){
        //Output is -+
        output.set(0);//00->01
        EV<<"Output is -+"<<output<<"\n";
    }else{
        EV<<"Output is --"<<output<<"\n";
    }
    //return output.test(1);
}

void stationaryQubit::measure_density_independent(char measurement_basis){
    if(entangled_partner == nullptr){
            error("Measuring a qubit that is not entangled with another qubit. Probably not what you want!");
    }
    apply_memory_error(this);//Add memory error depending on the idle time.
    apply_memory_error(entangled_partner);//Also do the same on the partner!

    quantum_state current_state = getQuantumState();
    EV<<"current state is "<<current_state.state_in_ket<<"\n";

}






} // namespace modules
} // namespace quisp
