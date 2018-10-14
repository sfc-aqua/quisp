/** \file HardwareMonitor.cc
 *  \todo clean Clean code when it is simple.
 *  \todo doc Write doxygen documentation.
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/03/19
 *
 *  \brief HardwareMonitor
 */
#include "HardwareMonitor.h"
#include "classical_messages_m.h"
#include <sstream>
#include <string>
#include <unsupported/Eigen/MatrixFunctions>
#include <unsupported/Eigen/KroneckerProduct>

namespace quisp {
namespace modules {

using namespace rules;

Define_Module(HardwareMonitor);

//Hm is also responsible for calculating the rssi/oka's protocol/fidelity calcu and give it to the rd
void HardwareMonitor::initialize(int stage)
{
  EV<<"HardwareMonitor booted\n";
  output_count initial;
  initial.minus_minus=0;
  initial.minus_plus=0;
  initial.plus_minus=0;
  initial.plus_plus=0;
  initial.total_count=0;

  Pauli.X << 0,1,1,0;
  Pauli.Y << 0,Complex(0,-1),Complex(0,1),0;
  Pauli.Z << 1,0,0,-1;
  Pauli.I << 1,0,0,1;


  numQnic_rp = par("number_of_qnics_rp");// number of qnics connected to epps.
  numQnic_r = par("number_of_qnics_r");// number of qnics connected to internal hom.
  numQnic = par("number_of_qnics");// number of qnics connected to stand alone HoM or internal hom in the neighbor.
  numQnic_total = numQnic + numQnic_r + numQnic_rp;

  /*This is used to keep your own tomography data, and also to match and store the received partner's tomography data*/
   all_temporal_tomography_output_holder = new Temporal_Tomography_Output_Holder[numQnic_total];//Assumes link tomography only between neighbors.

  /*Once all_temporal_tomography_output_holder is filled in, those data are summarized into basis based measurement outcome table. This accumulates the number of ++, +-, -+ and -- for each basis combination.*/
  tomography_data = new raw_data[numQnic_total];//Raw count table for tomography per link/qnic
  for(int i=0; i<numQnic_total; i++){
      tomography_data[i].insert(std::make_pair("XX",initial));
      tomography_data[i].insert(std::make_pair("XY",initial));
      tomography_data[i].insert(std::make_pair("XZ",initial));
      tomography_data[i].insert(std::make_pair("ZX",initial));
      tomography_data[i].insert(std::make_pair("ZY",initial));
      tomography_data[i].insert(std::make_pair("ZZ",initial));
      tomography_data[i].insert(std::make_pair("YX",initial));
      tomography_data[i].insert(std::make_pair("YY",initial));
      tomography_data[i].insert(std::make_pair("YZ",initial));
  }
  //std::cout<<"numQnic_total"<<numQnic_total<<"\n";


   /*This keeps which node is connected to which local qnic.*/
  ntable = prepareNeighborTable(ntable, numQnic_total);
  do_link_level_tomography = par("link_tomography");
  num_purification_tomography = par("initial_purification");
  num_measure = par("num_measure");
  myAddress = par("address");
  std::stringstream ss;
  for(auto it = ntable.cbegin(); it != ntable.cend(); ++it){
      ss << it->first << "(d)->(i)" << it->second.qnic.index <<", ";
  }
  std::string s = ss.str();
  par("ntable") = s;

  if(do_link_level_tomography && stage == 1){
      for(auto it = ntable.cbegin(); it != ntable.cend(); ++it){
          if(myAddress > it->second.neighborQNode_address){//You dont want 2 separate tomography processes to run for each link. Not a very good solution, but makes sure that only 1 request per link is generated.
              EV<<"Generating tomography rules... for node "<<it->second.neighborQNode_address<<"\n";
              LinkTomographyRequest *pk = new LinkTomographyRequest;
              pk->setDestAddr(it->second.neighborQNode_address);
              pk->setSrcAddr(myAddress);
              pk->setKind(6);
              send(pk,"RouterPort$o");
          }
      }
  }
}

void HardwareMonitor::handleMessage(cMessage *msg){
    if(dynamic_cast<LinkTomographyRequest *>(msg) != nullptr){
        /*Received a tomography request from neighbor*/
        LinkTomographyRequest *request = check_and_cast<LinkTomographyRequest *>(msg);
        /*Prepare an acknowledgement*/
        LinkTomographyAck *pk = new LinkTomographyAck;
        pk->setSrcAddr(myAddress);
        pk->setDestAddr(request->getSrcAddr());
        pk->setKind(6);
        QNIC_type qnic_type;
        int qnic_index = -1;
        for(auto it = ntable.cbegin(); it != ntable.cend(); ++it){
            if(it->second.neighborQNode_address == request->getSrcAddr()){
                qnic_type = it->second.qnic.type;
                qnic_index = it->second.qnic.index;
                break;
            }
        }if(qnic_index == -1){
            error("1. Something is wrong when finding out local qnic address from neighbor address in ntable.");
        }
        pk->setQnic_index(qnic_index);
        pk->setQnic_type(qnic_type);

        send(pk,"RouterPort$o");

    }else if(dynamic_cast<LinkTomographyAck *>(msg) != nullptr){
        /*Received an acknowledgement for tomography from neighbor.*/
        LinkTomographyAck *ack = check_and_cast<LinkTomographyAck *>(msg);
        /*Create and send RuleSets*/
        int partner_address = ack->getSrcAddr();
        QNIC_type partner_qnic_type = ack->getQnic_type();
        int partner_qnic_index = ack->getQnic_index();

        QNIC_type my_qnic_type;
        int my_qnic_index = -1;

        for(auto it = ntable.cbegin(); it != ntable.cend(); ++it){
            if(it->second.neighborQNode_address == ack->getSrcAddr()){
                my_qnic_type = it->second.qnic.type;
                my_qnic_index = it->second.qnic.index;
                break;
            }
        }if(my_qnic_index == -1){
            error("2. Something is wrong when finding out local qnic address from neighbor address in ntable.");
        }
        //RuleSets sent for this node and the partner node.
        sendLinkTomographyRuleSet(myAddress, partner_address, my_qnic_type, my_qnic_index,num_purification_tomography/*Number of purification is first set to 0*/);
        sendLinkTomographyRuleSet(partner_address,myAddress, partner_qnic_type, partner_qnic_index,num_purification_tomography);

    }else if (dynamic_cast<LinkTomographyResult *>(msg) != nullptr){
        /*Link tomography measurement result/basis from neighbor received.*/
        LinkTomographyResult *result = check_and_cast<LinkTomographyResult *>(msg);
        QNIC local_qnic = search_QNIC_from_Neighbor_QNode_address(result->getPartner_address());
        auto it = all_temporal_tomography_output_holder[local_qnic.index].find(result->getCount_id());
        if (it != all_temporal_tomography_output_holder[local_qnic.index].end()){
            EV<<"Data already found.";
            tomography_outcome temp = it->second;
            if(result->getSrcAddr() == myAddress){
                temp.my_basis = result->getBasis();
                temp.my_output_is_plus = result->getOutput_is_plus();
            }else{
                temp.partner_basis = result->getBasis();
                temp.partner_output_is_plus = result->getOutput_is_plus();
            }it->second = temp;
        }else{
            EV<<"Fresh data";
            tomography_outcome temp;
            if(result->getSrcAddr() == myAddress){
                temp.my_basis = result->getBasis();
                temp.my_output_is_plus = result->getOutput_is_plus();
            }else{
                temp.partner_basis = result->getBasis();
                temp.partner_output_is_plus = result->getOutput_is_plus();
            }
            all_temporal_tomography_output_holder[local_qnic.index].insert(std::make_pair(result->getCount_id(), temp));
        }
    }
    delete msg;
}

void HardwareMonitor::finish(){
    //EV<<"This is just a test!\n";
    EV<<"numQnic_total = "<<numQnic_total;
    for(int i=0; i<numQnic_total; i++){
        EV<<"\n \n \n \n \n QNIC["<<i<<"] \n";
        for(auto it =  all_temporal_tomography_output_holder[i].cbegin(); it != all_temporal_tomography_output_holder[i].cend(); ++it){
            //EV <<"Count["<< it->first << "] = " << it->second.my_basis << ", " << it->second.my_output_is_plus << ", " << it->second.partner_basis << ", "  << it->second.partner_output_is_plus << " " << "\n";
            std::string basis_combination = "";
            basis_combination+=it->second.my_basis;
            basis_combination+=it->second.partner_basis;
            if(tomography_data[i].count(basis_combination)!=1){
                //EV<<it->second.my_basis<<", "<<it->second.partner_basis<<" = "<<basis_combination<<"\n";
                error("Basis combination for tomography not found\n");
            }
            tomography_data[i][basis_combination].total_count++;
            if(it->second.my_output_is_plus && it->second.partner_output_is_plus){
                            tomography_data[i][basis_combination].plus_plus++;
                            //EV<<"basis_combination(++)="<<basis_combination <<" is now "<<tomography_data[basis_combination].plus_plus<<"\n";
            }
            else if(it->second.my_output_is_plus && !it->second.partner_output_is_plus){
                            tomography_data[i][basis_combination].plus_minus++;
                            //EV<<"basis_combination(++)="<<basis_combination <<" is now "<<tomography_data[basis_combination].plus_minus<<"\n";
            }
            else if(!it->second.my_output_is_plus && it->second.partner_output_is_plus){
                            tomography_data[i][basis_combination].minus_plus++;
                            //EV<<"basis_combination(++)="<<basis_combination <<" is now "<<tomography_data[basis_combination].minus_plus<<"\n";
            }
            else if(!it->second.my_output_is_plus && !it->second.partner_output_is_plus){
                            tomography_data[i][basis_combination].minus_minus++;
                            //EV<<"basis_combination(++)="<<basis_combination <<" is now "<<tomography_data[basis_combination].minus_minus<<"\n";
            }
            else
                 error("This should not happen though..... ?");

        }
        //For each qnic or link, reconstruct the dm.
        reconstruct_Density_Matrix(i);
    }
}


void HardwareMonitor::reconstruct_Density_Matrix(int qnic_id){
    //II
       double S00 = 1.0;
       double S01 = (double)tomography_data[qnic_id]["XX"].plus_plus/(double)tomography_data[qnic_id]["XX"].total_count - (double)tomography_data[qnic_id]["XX"].plus_minus/(double)tomography_data[qnic_id]["XX"].total_count + (double)tomography_data[qnic_id]["XX"].minus_plus/(double)tomography_data[qnic_id]["XX"].total_count - (double)tomography_data[qnic_id]["XX"].minus_minus/(double)tomography_data[qnic_id]["XX"].total_count;
       double S02 = (double)tomography_data[qnic_id]["YY"].plus_plus/(double)tomography_data[qnic_id]["YY"].total_count - (double)tomography_data[qnic_id]["YY"].plus_minus/(double)tomography_data[qnic_id]["YY"].total_count + (double)tomography_data[qnic_id]["YY"].minus_plus/(double)tomography_data[qnic_id]["YY"].total_count - (double)tomography_data[qnic_id]["YY"].minus_minus/(double)tomography_data[qnic_id]["YY"].total_count;
       double S03 = (double)tomography_data[qnic_id]["ZZ"].plus_plus/(double)tomography_data[qnic_id]["ZZ"].total_count - (double)tomography_data[qnic_id]["ZZ"].plus_minus/(double)tomography_data[qnic_id]["ZZ"].total_count + (double)tomography_data[qnic_id]["ZZ"].minus_plus/(double)tomography_data[qnic_id]["ZZ"].total_count - (double)tomography_data[qnic_id]["ZZ"].minus_minus/(double)tomography_data[qnic_id]["ZZ"].total_count;
       //XX
       double S10 = (double)tomography_data[qnic_id]["XX"].plus_plus/(double)tomography_data[qnic_id]["XX"].total_count + (double)tomography_data[qnic_id]["XX"].plus_minus/(double)tomography_data[qnic_id]["XX"].total_count - (double)tomography_data[qnic_id]["XX"].minus_plus/(double)tomography_data[qnic_id]["XX"].total_count - (double)tomography_data[qnic_id]["XX"].minus_minus/(double)tomography_data[qnic_id]["XX"].total_count;
       double S11 = (double)tomography_data[qnic_id]["XX"].plus_plus/(double)tomography_data[qnic_id]["XX"].total_count - (double)tomography_data[qnic_id]["XX"].plus_minus/(double)tomography_data[qnic_id]["XX"].total_count - (double)tomography_data[qnic_id]["XX"].minus_plus/(double)tomography_data[qnic_id]["XX"].total_count + (double)tomography_data[qnic_id]["XX"].minus_minus/(double)tomography_data[qnic_id]["XX"].total_count;
       double S12 = (double)tomography_data[qnic_id]["XY"].plus_plus/(double)tomography_data[qnic_id]["XY"].total_count - (double)tomography_data[qnic_id]["XY"].plus_minus/(double)tomography_data[qnic_id]["XY"].total_count - (double)tomography_data[qnic_id]["XY"].minus_plus/(double)tomography_data[qnic_id]["XY"].total_count + (double)tomography_data[qnic_id]["XY"].minus_minus/(double)tomography_data[qnic_id]["XY"].total_count;
       double S13 = (double)tomography_data[qnic_id]["XZ"].plus_plus/(double)tomography_data[qnic_id]["XZ"].total_count - (double)tomography_data[qnic_id]["XZ"].plus_minus/(double)tomography_data[qnic_id]["XZ"].total_count - (double)tomography_data[qnic_id]["XZ"].minus_plus/(double)tomography_data[qnic_id]["XZ"].total_count + (double)tomography_data[qnic_id]["XZ"].minus_minus/(double)tomography_data[qnic_id]["XZ"].total_count;
       //YY
       double S20 = (double)tomography_data[qnic_id]["YY"].plus_plus/(double)tomography_data[qnic_id]["YY"].total_count + (double)tomography_data[qnic_id]["YY"].plus_minus/(double)tomography_data[qnic_id]["YY"].total_count - (double)tomography_data[qnic_id]["YY"].minus_plus/(double)tomography_data[qnic_id]["YY"].total_count - (double)tomography_data[qnic_id]["YY"].minus_minus/(double)tomography_data[qnic_id]["YY"].total_count;
       double S21 = (double)tomography_data[qnic_id]["YX"].plus_plus/(double)tomography_data[qnic_id]["YX"].total_count - (double)tomography_data[qnic_id]["YX"].plus_minus/(double)tomography_data[qnic_id]["YX"].total_count - (double)tomography_data[qnic_id]["YX"].minus_plus/(double)tomography_data[qnic_id]["YX"].total_count + (double)tomography_data[qnic_id]["YX"].minus_minus/(double)tomography_data[qnic_id]["YX"].total_count;
       double S22 = (double)tomography_data[qnic_id]["YY"].plus_plus/(double)tomography_data[qnic_id]["YY"].total_count - (double)tomography_data[qnic_id]["YY"].plus_minus/(double)tomography_data[qnic_id]["YY"].total_count - (double)tomography_data[qnic_id]["YY"].minus_plus/(double)tomography_data[qnic_id]["YY"].total_count + (double)tomography_data[qnic_id]["YY"].minus_minus/(double)tomography_data[qnic_id]["YY"].total_count;
       double S23 = (double)tomography_data[qnic_id]["YZ"].plus_plus/(double)tomography_data[qnic_id]["YZ"].total_count - (double)tomography_data[qnic_id]["YZ"].plus_minus/(double)tomography_data[qnic_id]["YZ"].total_count - (double)tomography_data[qnic_id]["YZ"].minus_plus/(double)tomography_data[qnic_id]["YZ"].total_count + (double)tomography_data[qnic_id]["YZ"].minus_minus/(double)tomography_data[qnic_id]["YZ"].total_count;
       //ZZ
       double S30 = (double)tomography_data[qnic_id]["ZZ"].plus_plus/(double)tomography_data[qnic_id]["ZZ"].total_count + (double)tomography_data[qnic_id]["ZZ"].plus_minus/(double)tomography_data[qnic_id]["ZZ"].total_count - (double)tomography_data[qnic_id]["ZZ"].minus_plus/(double)tomography_data[qnic_id]["ZZ"].total_count - (double)tomography_data[qnic_id]["ZZ"].minus_minus/(double)tomography_data[qnic_id]["ZZ"].total_count;
       double S31 = (double)tomography_data[qnic_id]["ZX"].plus_plus/(double)tomography_data[qnic_id]["ZX"].total_count - (double)tomography_data[qnic_id]["ZX"].plus_minus/(double)tomography_data[qnic_id]["ZX"].total_count - (double)tomography_data[qnic_id]["ZX"].minus_plus/(double)tomography_data[qnic_id]["ZX"].total_count + (double)tomography_data[qnic_id]["ZX"].minus_minus/(double)tomography_data[qnic_id]["ZX"].total_count;
       double S32 = (double)tomography_data[qnic_id]["ZY"].plus_plus/(double)tomography_data[qnic_id]["ZY"].total_count - (double)tomography_data[qnic_id]["ZY"].plus_minus/(double)tomography_data[qnic_id]["ZY"].total_count - (double)tomography_data[qnic_id]["ZY"].minus_plus/(double)tomography_data[qnic_id]["ZY"].total_count + (double)tomography_data[qnic_id]["ZY"].minus_minus/(double)tomography_data[qnic_id]["ZY"].total_count;
       double S33 = (double)tomography_data[qnic_id]["ZZ"].plus_plus/(double)tomography_data[qnic_id]["ZZ"].total_count - (double)tomography_data[qnic_id]["ZZ"].plus_minus/(double)tomography_data[qnic_id]["ZZ"].total_count - (double)tomography_data[qnic_id]["ZZ"].minus_plus/(double)tomography_data[qnic_id]["ZZ"].total_count + (double)tomography_data[qnic_id]["ZZ"].minus_minus/(double)tomography_data[qnic_id]["ZZ"].total_count;
       double S = (double)tomography_data[qnic_id]["XX"].plus_plus/(double)tomography_data[qnic_id]["XX"].total_count + (double)tomography_data[qnic_id]["XX"].plus_minus/(double)tomography_data[qnic_id]["XX"].total_count + (double)tomography_data[qnic_id]["XX"].minus_plus/(double)tomography_data[qnic_id]["XX"].total_count + (double)tomography_data[qnic_id]["XX"].minus_minus/(double)tomography_data[qnic_id]["XX"].total_count;


       EV<<S00<<", "<<S01<<", "<<S02<<", "<<S03<<"\n";
       EV<<S10<<", "<<S11<<", "<<S12<<", "<<S13<<"\n";
       EV<<S20<<", "<<S21<<", "<<S22<<", "<<S23<<"\n";
       EV<<S30<<", "<<S31<<", "<<S32<<", "<<S33<<"\n";

    Matrix4cd density_matrix_reconstructed =
            (double)1/(double)4*(
            S01*kroneckerProduct(Pauli.I,Pauli.X).eval() +
            S02*kroneckerProduct(Pauli.I,Pauli.Y).eval() +
            S03*kroneckerProduct(Pauli.I,Pauli.Z).eval() +
            S10*kroneckerProduct(Pauli.X,Pauli.I).eval() +
            S11*kroneckerProduct(Pauli.X,Pauli.X).eval() +
            S12*kroneckerProduct(Pauli.X,Pauli.Y).eval() +
            S13*kroneckerProduct(Pauli.X,Pauli.Z).eval() +
            S20*kroneckerProduct(Pauli.Y,Pauli.I).eval() +
            S21*kroneckerProduct(Pauli.Y,Pauli.X).eval() +
            S22*kroneckerProduct(Pauli.Y,Pauli.Y).eval() +
            S23*kroneckerProduct(Pauli.Y,Pauli.Z).eval() +
            S30*kroneckerProduct(Pauli.Z,Pauli.I).eval() +
            S31*kroneckerProduct(Pauli.Z,Pauli.X).eval() +
            S32*kroneckerProduct(Pauli.Z,Pauli.Y).eval() +
            S33*kroneckerProduct(Pauli.Z,Pauli.Z).eval() +
            S*kroneckerProduct(Pauli.I,Pauli.I).eval());

    EV<<"DM = "<<density_matrix_reconstructed<<"\n";

    Vector4cd Bellpair;
    Bellpair << 1/sqrt(2), 0, 0, 1/sqrt(2);
    Matrix4cd density_matrix_ideal = Bellpair*Bellpair.adjoint();
    double fidelity = (density_matrix_reconstructed.real()* density_matrix_ideal.real() ).trace();
    //double Xerr = (density_matrix_reconstructed.real()* (density_matrix_ideal.real()) ).trace();

    EV<<"FOR QNIC["<<qnic_id<<"] \n";
    EV<<"F = "<<fidelity<<"\n";

    Vector4cd Bellpair_X;
    Bellpair_X << 0,1/sqrt(2), 1/sqrt(2),0;
    Matrix4cd density_matrix_X = Bellpair_X*Bellpair_X.adjoint();
    double Xerr_rate = (density_matrix_reconstructed.real()* density_matrix_X.real() ).trace();
    EV<<"Xerr = "<<Xerr_rate<<"\n";

    Vector4cd Bellpair_Z;
    Bellpair_Z << 1/sqrt(2),0,0,-1/sqrt(2);
    Matrix4cd density_matrix_Z = Bellpair_Z*Bellpair_Z.adjoint();
    double Zerr_rate = (density_matrix_reconstructed.real()* density_matrix_Z.real() ).trace();
    Complex checkZ = Bellpair_Z.adjoint()*density_matrix_reconstructed*Bellpair_Z;
    EV<<"Zerr = "<<Zerr_rate<<" or, "<<checkZ.real()<<"+"<<checkZ.imag()<<"\n";

    Vector4cd Bellpair_Y;
    Bellpair_Y << 0,Complex(0,1/sqrt(2)),Complex(0,-1/sqrt(2)),0;
    Matrix4cd density_matrix_Y = Bellpair_Y*Bellpair_Y.adjoint();
    double Yerr_rate = (density_matrix_reconstructed.real()* density_matrix_Y.real() ).trace();
    EV<<"Yerr = "<<Yerr_rate<<"\n";

    Vector4cd Bellpair_Y2;
    Bellpair_Y2 << 0,Complex(0,-1/sqrt(2)),Complex(0,1/sqrt(2)),0;
    Matrix4cd density_matrix_Y2 = Bellpair_Y2*Bellpair_Y2.adjoint();
    double Yerr_rate2 = (density_matrix_reconstructed.real()* density_matrix_Y2.real() ).trace();
    EV<<"Yerr = "<<Yerr_rate2<<"\n";

}

//Excludes Hom, Epps and other intermediate nodes.
QNIC HardwareMonitor::search_QNIC_from_Neighbor_QNode_address(int neighbor_address){
    QNIC qnic;
    for(auto it = ntable.cbegin(); it != ntable.cend(); ++it){

        if(it->second.neighborQNode_address == neighbor_address){
            qnic = it->second.qnic;
            break;
        }if(it == ntable.end()){
            error("Something is wrong when looking for QNIC info from neighbor QNode address. Tomography is also only available between neighbor.");
        }
    }
    return qnic;
}

void HardwareMonitor::sendLinkTomographyRuleSet(int my_address, int partner_address, QNIC_type qnic_type, int qnic_index, int num_purification){
            LinkTomographyRuleSet *pk = new LinkTomographyRuleSet;
            pk->setDestAddr(my_address);
            pk->setSrcAddr(partner_address);
            pk->setNumber_of_measuring_resources(num_measure);
            pk->setKind(6);

            //Empty RuleSet
            RuleSet* tomography_RuleSet = new RuleSet(my_address,partner_address);//Tomography between this node and the sender of Ack.


            if(num_purification>0){/*RuleSet including purification*/
                for(int i=0; i<num_purification; i++){
                    /*Rule* X_Purification = new Rule();
                    Condition* Purify_to_measure = new Condition();//Technically, there is no condition because an available resource is guaranteed whenever the rule is ran.
                    Clause* measure_count_clause = new MeasureCountClause(num_measure, partner_address, qnic_type , qnic_index, 0);//3000 measurements in total. There are 3*3 = 9 patterns of measurements. So each combination must perform 3000/9 measurements.
                    total_measurements->addClause(measure_count_clause);
                    X_Purification->setCondition(total_measurements);
                    quisp::rules::Action* Purify_X = new PurifyXAction(partner_address, qnic_type , qnic_index, 0, my_address);//Measure the local resource between it->second.neighborQNode_address.
                    Random_measure_tomo->setAction(measure);*/
                }
                Rule* Random_measure_tomo = new Rule();//Let's make nodes select measurement basis randomly, because it it easier.
                Condition* total_measurements = new Condition();//Technically, there is no condition because an available resource is guaranteed whenever the rule is ran.
                Clause* measure_count_clause = new MeasureCountClause(num_measure, partner_address, qnic_type , qnic_index, 0);//3000 measurements in total. There are 3*3 = 9 patterns of measurements. So each combination must perform 3000/9 measurements.
                Clause* purification_count_clause = new PurificationCountClause(partner_address, qnic_type , qnic_index, num_purification);
                total_measurements->addClause(measure_count_clause);
                Random_measure_tomo->setCondition(total_measurements);
                quisp::rules::Action* measure = new RandomMeasureAction(partner_address, qnic_type , qnic_index, 0, my_address);//Measure the local resource between it->second.neighborQNode_address.
                Random_measure_tomo->setAction(measure);
                //---------
                //Add the rule to the RuleSet
                tomography_RuleSet->addRule(Random_measure_tomo);
                //---------------------------
                pk->setRuleSet(tomography_RuleSet);
                send(pk,"RouterPort$o");

            }else{//RuleSet with no purification. Pure measurement only link level tomography.
                //-------------
                //-First rule-
                Rule* Random_measure_tomo = new Rule();//Let's make nodes select measurement basis randomly, because it it easier.
                Condition* total_measurements = new Condition();//Technically, there is no condition because an available resource is guaranteed whenever the rule is ran.
                Clause* measure_count_clause = new MeasureCountClause(num_measure, partner_address, qnic_type , qnic_index, 0);//3000 measurements in total. There are 3*3 = 9 patterns of measurements. So each combination must perform 3000/9 measurements.
                total_measurements->addClause(measure_count_clause);
                Random_measure_tomo->setCondition(total_measurements);
                quisp::rules::Action* measure = new RandomMeasureAction(partner_address, qnic_type , qnic_index, 0, my_address);//Measure the local resource between it->second.neighborQNode_address.
                Random_measure_tomo->setAction(measure);
                //---------
                //Add the rule to the RuleSet
                tomography_RuleSet->addRule(Random_measure_tomo);
                //---------------------------
                pk->setRuleSet(tomography_RuleSet);
                send(pk,"RouterPort$o");
            }
}




int HardwareMonitor::checkNumBuff(int qnic_index, QNIC_type qnic_type){
    Enter_Method("checkNumBuff()");

    cModule *qnode = nullptr;
    if (qnic_type>=QNIC_N) error("Only 3 qnic types are currently recognized...."); // avoid segfaults <3
    qnode = getQNode()->getSubmodule(QNIC_names[qnic_type], qnic_index);
    return qnode->par("numBuffer");
}


Interface_inf HardwareMonitor::getInterface_inf_fromQnicAddress(int qnic_index, QNIC_type qnic_type){
    cModule *local_qnic;
    if (qnic_type>=QNIC_N) error("Only 3 qnic types are currently recognized...."); // avoid segfaults <3
    local_qnic = getQNode()->getSubmodule(QNIC_names[qnic_type], qnic_index);//QNIC itself
    Interface_inf inf;
    inf.qnic.pointer = local_qnic;
    inf.qnic.address = local_qnic->par("self_qnic_address");//Extract from QNIC parameter
    inf.qnic.index = qnic_index;
    inf.qnic.type = qnic_type;
    inf.buffer_size = local_qnic->par("numBuffer");

    //Just read link cost from channel parameter for now as a dummy (or as an initialization).
    //int cost = local_qnic->gate("qnic_quantum_port$o")->getNextGate()->getChannel()->par("cost");//This is false because the channel may only be between the node and HOM.
    inf.link_cost = 1;//Dummy it up. This cost must be the cost based on the neighboring QNode (excluding SPDC and HOM nodes)

    return inf;
}

connection_setup_inf HardwareMonitor::return_setupInf(int qnic_address){
    Enter_Method("return_setupInf()");
    connection_setup_inf inf = {
        .qnic = {
            .type = QNIC_N,
            .index = -1,
        },
        .neighbor_address = -1,
        .quantum_link_cost = -1
    };
    for(auto it = ntable.cbegin(); it != ntable.cend(); ++it){
        if(it->second.qnic.address == qnic_address){
            inf.qnic.type = it->second.qnic.type;
            inf.qnic.index = it->second.qnic.index;
            inf.neighbor_address = it->second.neighborQNode_address;
            //cModule *node = getModuleByPath("network.HoM");
            inf.quantum_link_cost = it->second.link_cost;
            break;
        }
    }
    return inf;
}





//This neighbor table includes all neighbors of qnic, qnic_r and qnic_rp
HardwareMonitor::NeighborTable HardwareMonitor::prepareNeighborTable(NeighborTable ntable, int total_numQnic){
    cModule *qnode = getQNode();//Get the parent QNode that runs this connection manager.
        for (int index=0; index<numQnic; index++){//Travese through all local qnics to check where they are connected to. HoM and EPPS will be ignored in this case.
            Interface_inf inf = getInterface_inf_fromQnicAddress(index, QNIC_E);
            neighborInfo n_inf = findNeighborAddress(inf.qnic.pointer);
            int neighborNodeAddress = n_inf.address;//get the address of the Node nearby.
            inf.neighborQNode_address = n_inf.neighborQNode_address;
            ntable[neighborNodeAddress] = inf;
        }
        for (int index=0; index<numQnic_r; index++){
            Interface_inf inf = getInterface_inf_fromQnicAddress(index, QNIC_R);
            neighborInfo n_inf = findNeighborAddress(inf.qnic.pointer);
            int neighborNodeAddress = n_inf.address;//get the address of the Node nearby.
            inf.neighborQNode_address = n_inf.neighborQNode_address;
            ntable[neighborNodeAddress] = inf;
        }
        for (int index=0; index<numQnic_rp; index++){
            Interface_inf inf = getInterface_inf_fromQnicAddress(index, QNIC_RP);
            neighborInfo n_inf = findNeighborAddress(inf.qnic.pointer);
            int neighborNodeAddress = n_inf.address;//get the address of the Node nearby.
            inf.neighborQNode_address = n_inf.neighborQNode_address;
            ntable[neighborNodeAddress] = inf;
        }
        return ntable;
}


//This method finds out the address of the neighboring node with respect to the local unique qnic addres.
neighborInfo  HardwareMonitor::findNeighborAddress(cModule *qnic_pointer){
    cGate *gt = qnic_pointer->gate("qnic_quantum_port$o")->getNextGate();//qnic_quantum_port$o is connected to the node's outermost quantum_port
    //EV<<"gt = "<<gt->getName()<<"\n";
    cGate *neighbor_gt = gt->getNextGate();
    //EV<<"neighbor_gt = "<<neighbor_gt->getName()<<"\n";
    cModule *neighbor_node = neighbor_gt->getOwnerModule();//Ownner could be HoM, EPPS, QNode
    //EV<<"neighbor_node = "<<neighbor_node->getName()<<"\n";
    neighborInfo neighbor_is_QNode = checkIfQNode(neighbor_node);
    return neighbor_is_QNode;
}

cModule* HardwareMonitor::getQNode(){
         cModule *currentModule = getParentModule();//We know that Connection manager is not the QNode, so start from the parent.
         try{
             cModuleType *QNodeType =  cModuleType::get("networks.QNode");//Assumes the node in a network has a type QNode
             while(currentModule->getModuleType()!=QNodeType){
                 currentModule = currentModule->getParentModule();
             }
             return currentModule;
         }catch(std::exception& e){
             error("No module with QNode type found. Have you changed the type name in ned file?");
             endSimulation();
         }
         return currentModule;
}

neighborInfo HardwareMonitor::checkIfQNode(cModule *thisNode){

    neighborInfo inf;//Return this
    if(thisNode->getModuleType()!=QNodeType){//Not a Qnode!

        if(thisNode->getModuleType()==HoMType){
            EV<<thisNode->getModuleType()->getFullName()<<" == "<<HoMType->getFullName()<<"\n";
            inf.isQNode=false;
            int address_one = thisNode->getSubmodule("Controller")->par("neighbor_address");
            int address_two = thisNode->getSubmodule("Controller")->par("neighbor_address_two");
            int myaddress = par("address");
            EV<<"\n myaddress = "<<myaddress<<", address = "<<address_one<<", address_two = "<<address_two<<" in "<<thisNode->getSubmodule("Controller")->getFullName()<<"\n";
            //endSimulation();
            if(address_one==myaddress){
                inf.neighborQNode_address = address_two;
            }else if(address_two==myaddress){
                inf.neighborQNode_address = address_one;
            }else{
                //endSimulation();
                //EV<<"address _one = "<<address_one<<", address_two = "<<address_two;
                //error("Something is wrong with tracking the neighbor address. It is here.");
            }
        }else if(thisNode->getModuleType()== SPDCType){
            error("TO BE IMPLEMENTED");
        }else{
            error("This simulator only recognizes the following network level node types: QNode, EPPS and HoM. Not %s",thisNode->getClassName());
            endSimulation();
        }
    }
    else{
        inf.isQNode=true;
        inf.neighborQNode_address = thisNode->par("address");
    }
    inf.type = thisNode->getModuleType();
    inf.address = thisNode->par("address");
    return inf;
}

HardwareMonitor::NeighborTable HardwareMonitor::passNeighborTable(){
    Enter_Method("passNeighborTable()");
    return ntable;
}

} // namespace modules
} // namespace quisp
