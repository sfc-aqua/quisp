#include <iterator>
#include <map>
#include "logicalStationaryQubit.h"
#include <vector>
#include <omnetpp.h>
#include <classical_messages_m.h>
#include <unsupported/Eigen/MatrixFunctions>
#include <unsupported/Eigen/KroneckerProduct>
#include <PhotonicQubit_m.h>
#include <bitset>
#include <fstream>

namespace quisp {
    namespace modules {
        Define_Module(logicalStationaryQubit);

        void logicalStationaryQubit::initialize(){

            // Logical measurement basis

            /*
            std::vector<int> data;
            std::ifstream fin("LogicalBellSteane713.txt");
            int element;
            while (fin >> element){
                data.push_back(element);
            }
            VectorXcd Measurement_state = data;

            meas_op.X_basis.plus_ket << 1 / sqrt(2), 1 / sqrt(2);
            meas_op.X_basis.minus_ket << 1 / sqrt(2), -1 / sqrt(2);
            meas_op.X_basis.plus << 0.5, 0.5, 0.5, 0.5;
            meas_op.X_basis.minus << 0.5, -0.5, -0.5, 0.5;
            meas_op.X_basis.basis = 'X';
            
            meas_op.Z_basis.plus_ket << 1, 0;
            meas_op.Z_basis.minus_ket << 0, 1;
            meas_op.Z_basis.plus << 1, 0, 0, 0;
            meas_op.Z_basis.minus << 0, 0, 0, 1;
            meas_op.Z_basis.basis = 'Z';
            
            meas_op.Y_basis.plus_ket << 1 / sqrt(2), Complex(0, 1 / sqrt(2));
            meas_op.Y_basis.minus_ket << 1 / sqrt(2), -Complex(0, 1 / sqrt(2));
            meas_op.Y_basis.plus << 0.5, Complex(0, -0.5), Complex(0, 0.5), 0.5;
            meas_op.Y_basis.minus << 0.5, Complex(0, 0.5), Complex(0, -0.5), 0.5;
            meas_op.Y_basis.basis = 'Y';
            
            meas_op.identity << 1, 0, 0, 1;

            */
            setPhysicalFree(false); 
        }

        void logicalStationaryQubit::setPhysicalFree(bool consumed){

            // set initial parameter

            // Parameters for task locking.
            locked = false;
            locked_ruleset_id = -1;
            locked_rule_id = -1;
            action_index = -1;

            isBusy = false;
            allocated = false;
            emitted_time = -1;
            updated_time = -1;

            // Parameters to deal with if logical parter was measured.
            logical_partner_measured = false; // To flag which method to calculate the outcome.
            // GOD_dm_Zerror_list = nullptr; // List of Z error that already occur to another logical qubit that used to this logical qubit.
            // GOD_dm_Xerror_list = nullptr; // Same as above but with X error
            MatrixXcd Density_matrix_Collapsed;
            // v2
            logicalQuantumState = getIdealLogicalQuantumState();
            std::vector<StationaryQubit*> combine_entangled_list;
            std::map<int, std::string> physical_readout;
            // end v2

            // Logical information
            std::vector<StationaryQubit*> encoded_qubits_list;
            logical_entangled_partner = nullptr; 

            if(hasGUI()){
                if(consumed){
                    bubble("Consumed!");
                    getDisplayString().setTagArg("i", 1, "yellow");
                }
                else{
                    bubble("Failed to entangle!");
                    getDisplayString().setTagArg("i", 1, "blue");
                }
            }

        }

        void logicalStationaryQubit::addToLogicalList(StationaryQubit *encode_qubit){

            // Add encode qubit to list of physical qubits used for encode logical qubit
            if (this->encoded_qubits_list.empty()){
                std::vector<StationaryQubit*> encode_list;
                this->encoded_qubits_list = encode_list;
            }
            
            this->encoded_qubits_list.push_back(encode_qubit);
        
        }

        bool logicalStationaryQubit::checkBusy() {
            Enter_Method("checkBusy()");
            return isBusy;
        }

        void logicalStationaryQubit::Lock(unsigned long rs_id, int rule_id, int action_id) {
            if (rs_id == -1 || rule_id == -1 || action_id == -1) {
                error("ruleset_id || rule_id || action_id == -1");
            }

            locked = true;
            locked_ruleset_id = rs_id;  // Used to identify what this qubit is locked for.
            locked_rule_id = rule_id;
            action_index = action_id;

            if (hasGUI()) {
                bubble("Locked!");
                getDisplayString().setTagArg("i", 1, "purple");
            }
        }

        void logicalStationaryQubit::Unlock() {
            locked = false;
            locked_ruleset_id = -1;  // Used to identify what this qubit is locked for.
            locked_rule_id = -1;
            action_index = -1;

            if (hasGUI()) {
                bubble("Unlocked!");
                getDisplayString().setTagArg("i", 1, "pink");
            }
        }

        bool logicalStationaryQubit::isLocked() { return locked; }

        void logicalStationaryQubit::Allocate() {
            allocated = true;
            if (hasGUI()) {
                bubble("Allocated!");
                getDisplayString().setTagArg("i", 1, "purple");
            }
        }

        void logicalStationaryQubit::Deallocate() { allocated = false; }

        bool logicalStationaryQubit::isAllocated() { return allocated; }

        //S1 Need more research to define those functions below
        void logicalStationaryQubit::setLogicalCompletelyMixedDensityMatrix() {}
        void logicalStationaryQubit::setLogicalExcitedDensityMatrix() {}
        void logicalStationaryQubit::setLogicalRelaxedDensityMatrix() {}
        //end S1

        void logicalStationaryQubit::setLogicalEntangledPartnerInfo(logicalStationaryQubit *partner) {
            this->logical_entangled_partner = partner;
            partner->logical_entangled_partner = this;

            //v2
            std::vector<StationaryQubit*> comb_list;
            comb_list.reserve( this->encoded_qubits_list.size() + this->logical_entangled_partner->encoded_qubits_list.size() );
            comb_list.insert( comb_list.end(), this->encoded_qubits_list.begin(), this->encoded_qubits_list.end() );
            comb_list.insert( comb_list.end(), this->logical_entangled_partner->encoded_qubits_list.begin(), this->logical_entangled_partner->encoded_qubits_list.end() );
            this->combine_entangled_list = comb_list;
            //end v2
        }

        // For logical qubit gate,
        /*
            This should be generalize to any code.
            2020/01/12 - Steane Code is an only option.
        */
        void logicalStationaryQubit::Hadamard_gate(){
            // Steane Code
            for (int i; i < encoded_qubits_list.size(); i++ ){
                this->encoded_qubits_list[i]->Hadamard_gate();
            }
        }
        void logicalStationaryQubit::Z_gate(){
            // Steane Code
            for (int i; i < encoded_qubits_list.size(); i++ ){
                this->encoded_qubits_list[i]->Z_gate();
            }
        }
        void logicalStationaryQubit::x_gate(){
            // Steane Code
            for (int i; i < encoded_qubits_list.size(); i++ ){
                this->encoded_qubits_list[i]->X_gate();
            }
        }

        void logicalStationaryQubit::CNOT_gate(logicalStationaryQubit *control_qubit) {
            for (int i; i < encoded_qubits_list.size(); i++ ){
                this->encoded_qubits_list[i]->CNOT_gate(control_qubit->encoded_qubits_list[i]); // Target -> Control
            }
        }

        logical_quantum_state logicalStationaryQubit::getLogicalQuantumState(){
            if (this->encoded_qubits_list.size() != 7){ // <-- Specifically for Steane code
                error("The number of physical qubits used to encoded is not 7");
            }
            if (this->logical_entangled_partner == nullptr){
                error("There is no entangled logical qubit partner");
            }
            if (this->logical_entangled_partner->encoded_qubits_list.size() != 7){
                error("The number of physical qubits used to encoded partner logical qubit is not 7");
            }

            // Get Combined Error matrix of each physical qubits from this logical qubit.
            MatrixXcd combined_errors_self = this->encoded_qubits_list[0]->getErrorMatrix(this->encoded_qubits_list[0]);
            for (int i=1; i=this->encoded_qubits_list.size(); i++){
                combined_errors_self =  kroneckerProduct(combined_errors_self, this->encoded_qubits_list[i]->getErrorMatrix(this->encoded_qubits_list[i])).eval();
            }
            // Get Combined Error matrix of each physical qubits from partner logical qubit.
            MatrixXcd combined_errors_partner = this->logical_entangled_partner->encoded_qubits_list[0]->getErrorMatrix(this->logical_entangled_partner->encoded_qubits_list[0]);
            for (int i=1; i=this->encoded_qubits_list.size(); i++){
                combined_errors_partner =  kroneckerProduct(combined_errors_partner, this->logical_entangled_partner->encoded_qubits_list[i]->getErrorMatrix(this->logical_entangled_partner->encoded_qubits_list[i])).eval();
            }

            MatrixXcd combined_errors = kroneckerProduct(combined_errors_self, combined_errors_partner);

/*
            std::vector<std::complex<double> > data;

            std::ifstream fin("LogicalBellSteane713.txt");
            std::complex<double> element;
            while (fin >> element){
                data.push_back(element);
            }
            VectorXcd ideal_logical_Bell_pair = data;
*/
            VectorXcd ideal_logical_Bell_pair = this->logicalQuantumState.state_in_ket;
            VectorXcd actual_logical_Bell_state = combined_errors * ideal_logical_Bell_pair;
            // EV<<"Current physical state is = "<<actual_Bell_state;
            MatrixXcd logical_density_matrix = actual_logical_Bell_state * actual_logical_Bell_state.adjoint();
            // EV<<"dm = "<<density_matrix<<"\n";

            logical_quantum_state q;
            q.state_in_density_matrix = logical_density_matrix;
            q.state_in_ket = actual_logical_Bell_state;
            return q;
        }

        logical_quantum_state logicalStationaryQubit::getIdealLogicalQuantumState(){
            
            std::vector<std::complex<double> > data;
            //VectorXcd data;
            std::ifstream fin("LogicalBellSteane713.txt");
            double real;
            double img;
            while (fin >> real >> img){
                const std::complex<double> temp(real, img);
                data.push_back(temp);
            }
            //VectorXcd ideal_logical_Bell_pair = data;
            //VectorXcd ideal_logical_Bell_pair(data.data());
            Eigen::Map<VectorXcd> ideal_logical_Bell_pair(data.data(), data.size());
            MatrixXcd ideal_logical_density_matrix = ideal_logical_Bell_pair * ideal_logical_Bell_pair.adjoint();

            logical_quantum_state q;
            q.state_in_density_matrix = ideal_logical_density_matrix;
            q.state_in_ket = ideal_logical_Bell_pair;
            return q;
        }
/*
        measurement_outcome logicalStationaryQubit::logical_measure_density_independent_v1() {

            // This version will implement the easiest way to measure logical qubit for tomography without decoding.
            // This method will alter Density_matrix_collasped in the logical partner qubit.

            logical_measurement_operator this_measurement = logical_Random_Measurement_Basis_Selection();  // Select basis randomly

            // Apply memory error and measurement operator error
            for(int i = 0; i < this->encoded_qubits_list.size(); i++){
                this->encoded_qubits_list[i]->apply_memory_error(encoded_qubits_list[i]);
                this->encoded_qubits_list[i]->apply_single_qubit_gate_error(this->encoded_qubits_list[i]->Measurement_error, encoded_qubits_list[i]);
            }
            char Output;
            char Output_is_plus;

            if(this->logical_partner_measured) {
                MatrixXcd Error_after = this->encoded_qubits_list[0]->Pauli.I;

                for (int j = 0; j < this->encoded_qubits_list.size(); j++){
                    Matrix2cd Error_on_this_qubit = this->encoded_qubits_list[j]->Pauli.I;
                    if (this->encoded_qubits_list[j]->par("GOD_Xerror" != GOD_dm_Xerror_list[j])){
                        Error_on_this_qubit = Error_on_this_qubit*this->encoded_qubits_list[j]->Pauli.X;
                    }
                    if (this->encoded_qubits_list[j]->par("GOD_Zerror" != GOD_dm_Xerror_list[j])){
                        Error_on_this_qubit = Error_on_this_qubit*this->encoded_qubits_list[j]->Pauli.Z;
                    }
                    Error_after = kroneckerProduct(Error_after, Error_on_this_qubit);
                }

                Density_Matrix_Collapsed = Error_after * Density_Matrix_Collapsed * Error_after.adjoint();

                Complex Prob_plus = (Density_Matrix_Collapsed * this_measurement.plus.adjoint() * this_measurement.plus).trace();
                Complex Prob_minus = (Density_Matrix_Collapsed * this_measurement.minus.adjoint() * this_measurement.minus).trace();
                double dbl = dblrand();
                if (dbl < Prob_plus.real()) {
                    Output = '+';
                    Output_is_plus = true;
                } else {
                    Output = '-';
                    Output_is_plus = false;
                }

            } else if(!this->logical_partner_measured){

                logical_quantum_state current_state = getLogicalQuantumState();

                Complex Prob_plus = current_state.state_in_ket.adjoint() * kroneckerProduct(this_measurement.plus, meas_op.identity).eval().adjoint() *
                        kroneckerProduct(this_measurement.plus, meas_op.identity).eval() * current_state.state_in_ket;
                Complex Prob_minus = current_state.state_in_ket.adjoint() * kroneckerProduct(this_measurement.minus, meas_op.identity).eval().adjoint() *
                         kroneckerProduct(this_measurement.minus, meas_op.identity).eval() * current_state.state_in_ket;

                double dbl = dblrand();
                VectorXcd ms;
                if (dbl < Prob_plus.real()) {  // Measurement output was plus
                    Output = '+';
                    ms = this_measurement.plus_ket;
                    Output_is_plus = true;
                } else {  // Otherwise, it was negative.
                    Output = '-';
                    ms = this_measurement.minus_ket;
                    Output_is_plus = false;
                }

                //Calculate the remaining density matrix for partner
                MatrixXcd partners_dm, normalized_partners_dm;
                partners_dm = kroneckerProduct(ms.adjoint(), meas_op.identity).eval() * current_state.state_in_density_matrix * kroneckerProduct(ms.adjoint(), meas_op.identity).eval().adjoint();
                normalized_partners_dm = partners_dm / partners_dm.trace();

                //Set calculated density matrix
                logical_entangled_partner->Density_Matrix_Collapsed = normalized_partners_dm;

                logical_entangled_partner->logical_partner_measured = true;
                logical_entangled_partner->logical_entangled_partner = nullptr;

                // Save error...?
                for(int i = 0; i < logical_entangled_partner->encoded_qubits_list.size(); i++){
                    logical_entangled_partner->encoded_qubits_list[i]->GOD_dm_Xerror = logical_entangled_partner->encoded_qubits_list[i]->par("GOD_Xerror");
                    logical_entangled_partner->encoded_qubits_list[i]->GOD_dm_Zerror = logical_entangled_partner->encoded_qubits_list[i]->par("GOD_Zerror");
                }
            }

        }

        logical_measurement_operator logicalStationaryQubit::logical_Random_Measurement_Basis_Selection() {

            // This function is different from physical level such that the measurement operator will be in logical form.

            measurement_operator this_measurement;
            double dbl = dblrand();  // Random double value for random basis selection.
            EV << "Random dbl = " << dbl << "! \n ";

            if (dbl < ((double)1 / (double)3)) {  // X measurement!
                EV << "X measurement\n";
                this_measurement.plus = meas_op.X_basis.plus;
                this_measurement.minus = meas_op.X_basis.minus;
                this_measurement.basis = meas_op.X_basis.basis;
                this_measurement.plus_ket = meas_op.X_basis.plus_ket;
                this_measurement.minus_ket = meas_op.X_basis.minus_ket;
            } else if (dbl >= ((double)1 / (double)3) && dbl < ((double)2 / (double)3)) {
                EV << "Z measurement\n";
                this_measurement.plus = meas_op.Z_basis.plus;
                this_measurement.minus = meas_op.Z_basis.minus;
                this_measurement.basis = meas_op.Z_basis.basis;
                this_measurement.plus_ket = meas_op.Z_basis.plus_ket;
                this_measurement.minus_ket = meas_op.Z_basis.minus_ket;
            } else {
                EV << "Y measurement\n";
                this_measurement.plus = meas_op.Y_basis.plus;
                this_measurement.minus = meas_op.Y_basis.minus;
                this_measurement.basis = meas_op.Y_basis.basis;
                this_measurement.plus_ket = meas_op.Y_basis.plus_ket;
                this_measurement.minus_ket = meas_op.Y_basis.minus_ket;
            }
            return this_measurement;
        }
*/
        measurement_outcome logicalStationaryQubit::logical_measure_density_independent_v2(StationaryQubit *physicalQubit, measurement_operator this_measurement){

            /*
                After consideration, what original QuISP expected is just 2 physical qubits.
                So the meaurement operation is specifically design for that case, which involve two part.
                If no physical qubit has measured, then it will get (noisy) full-quantum state,
                then use that to calculate the outcome of the first qubit. After that, the resulting density martrix
                will calculated and stored in "Density_Matrix_Collapsed" parameter. Which link to another condition,
                if there is a qubit already measured then it will use "Density_Matrix_Collapsed" to calculate the outcome 
                upon calling this function, but! with update of its. Because this qubit also subject to noise during some waiting time too,
                so the function will check "GOD_dm_?Error" which act like a save point after measured the first qubit.

                So in order to serve th propose of this save point in more general cases, 
                my idea is to re-design this function to just reset "GOD_?Error" after whichever qubit was measured.
                Instead of save error that already considerd in previous measurement, and carry the check point to another qubits,
                I suggest to reset "GOD_?Error" of all physical qubit to false as a flag that we already deal with qubit's current error.
                If the qubit suject to new error before the measurement then fine! The function just have to applie that error to the carried 
                density matrix instead. 

                Let's dive into pesudo-code.

                logicalQuantumState = Ideal 14-physical qubits that encode 2 logical Bell pair. (Shared variable)
                encoded_qubits_list = List of 7 physical qubits used to encode logical qubit.
                combine_entangled_list = List of 14 physical qubits used to encode logical Bell pair. (Shared variable)
                physical_readout = Readout ordered-list of physcial qubits, initialize to be nullptr

                function logical_measure_density_independent_v2(physicalQubit, this_measurement): // this_measurement is measurement basis.
                    index_qubit = get index of qubit in combine_entangled_list associate with physicalQubit
                    index_qubit_in_system = get index of qubit from encoded_qubits_list
                    measurement_plus_ket = tensor product of identity and this_measurement.plus_ket associate with index_qubit
                    measurement_plus = outer product of measurement_plus_ket
                    Apply memory error to all physicalQubits
                    Apply measurement error to physicalQubit
                    Error_matrix = tensor product of all error (GOD_?Error from getErrorMatrix) that occur on all remaining physical qubit from list
                    current_state = Error_matrix * logicalQuantumState.state_in_ket
                    Prob_plus = inner product of measurement_plus and current_state
                    outcome = Get measurement outcome based on Prob_plus 
                    physical_readout[index_qubit_in_system] = outcome in form of string '+' or '-'.
                    logicalQuantumState = measurement_plus_ket * current_state * measurement_plus_ket.adjoint() and renormalize it.
                    reset GOD_?Error of all remaining physical qubits to false.
                    remove physicalQubit from combine_entangled_list
                
            */

            // Get index of qubit in combine_entangled_list associate with physicalQubit
            int index_qubit;
            for(int i=0; i < combine_entangled_list.size(); i++){
                if (combine_entangled_list[i] == physicalQubit){
                    index_qubit = i;
                }
            }

            // get index of qubit from encoded_qubits_list
            int index_qubit_in_system;
            for(int i=0; i < encoded_qubits_list.size(); i++){
                if (encoded_qubits_list[i] == physicalQubit){
                    index_qubit_in_system = i;
                }
            }

            // Randomly choose basis (call Random_Measurement_Basis_Selection())
            // measurement_operator this_measurement = physicalQubit->Random_Measurement_Basis_Selection();

            // tensor product of identity and this_measurement.plus_ket associate with index_qubit
            MatrixXcd measurement_plus = physicalQubit->Pauli.I;
            if ( index_qubit == 0 ){
                measurement_plus = this_measurement.plus;
            }
            Matrix2cd m_operator;
            for(int i=1; i < combine_entangled_list.size(); i++){
                if ( i == index_qubit){
                    m_operator = this_measurement.plus;
                }
                else {
                    m_operator = physicalQubit->Pauli.I;
                }
                measurement_plus = kroneckerProduct( measurement_plus, m_operator).eval();
            }

            // Outer product of measurement_plus_ket
            // MatrixXcd measurement_plus = measurement_plus_ket * measurement_plus_ket.adjoint();

            // Apply memory error to all physicalQubits
            

            for(int i=0; i < combine_entangled_list.size(); i++){
                this->combine_entangled_list.at(i)->apply_memory_error(this->combine_entangled_list.at(i));
            }

            //physicalQubit->apply_memory_error(physicalQubit);

            // Apply measurement error to physicalQubit
            physicalQubit->apply_single_qubit_gate_error(physicalQubit->Measurement_error, physicalQubit);

            // Tensor product of all error (GOD_?Error from getErrorMatrix) that occur on all remaining physical qubit from list
            MatrixXcd Error_matrix = this->combine_entangled_list.at(0)->getErrorMatrix(this->combine_entangled_list.at(0));
            for(int i=1; i < combine_entangled_list.size(); i++){
                Error_matrix = kroneckerProduct(Error_matrix, this->combine_entangled_list.at(i)->getErrorMatrix(this->combine_entangled_list.at(i))).eval();
            }
            
            // Error_matrix * logicalQuantumState.state_in_ket
            MatrixXcd current_state;
            current_state = Error_matrix * this->logicalQuantumState.state_in_density_matrix * Error_matrix.adjoint();


            // Prob_plus = inner product of measurement_plus and current_state
            //Complex Prob_plus = (current_state.adjoint() * measurement_plus * current_state).value();
            Complex Prob_plus = (current_state * measurement_plus ).trace();

            // Get measurement outcome based on Prob_plus 
            double dbl = dblrand();
            Vector2cd ms;

            char Output;
            bool Output_is_plus;

            if (dbl < Prob_plus.real()){         //Measurement output was plus
                Output = '+';
                ms = measurement_plus;
                Output_is_plus = true;
            } else {                             //Otherwise, it was negative.
                Output = '-';
                
                MatrixXcd measurement_minus = physicalQubit->Pauli.I;
                if ( index_qubit == 0 ){
                    measurement_minus = this_measurement.minus;
                }
                Matrix2cd m_operator;
                for(int i=1; i < combine_entangled_list.size(); i++){
                    if ( i == index_qubit){
                        m_operator = this_measurement.minus;
                    }
                    else {
                        m_operator = physicalQubit->Pauli.I;
                    }
                    measurement_minus = kroneckerProduct( measurement_minus, m_operator).eval();
                }

                ms = measurement_minus;
                Output_is_plus = false;
            }

            // physical_readout[index_qubit_in_system] = outcome in form of string '+''' or '-'.
            this->physical_readout[index_qubit_in_system] = Output;

            // Calculate the new density matrix; logicalQuantumState = measurement_plus_ket * current_state * measurement_plus_ket.adjoint() and renormalize it.

            MatrixXcd partners_dm, normalized_partners_dm;
            //partners_dm = ms.adjoint() * (current_state * current_state.adjoint()) * ms;
            partners_dm = ms * (current_state) * ms.adjoint();
            normalized_partners_dm = partners_dm / partners_dm.trace();
            logicalQuantumState.state_in_density_matrix = normalized_partners_dm;

            // reset GOD_?Error of all remaining physical qubits to false.

            for(int i=0; i < combine_entangled_list.size(); i++){
                this->combine_entangled_list[i]->par("GOD_Xerror") = false;
                this->combine_entangled_list[i]->par("GOD_Zerror") = false;
            }

            // remove physicalQubit from combine_entangled_list

            this->combine_entangled_list.erase(combine_entangled_list.begin()+index_qubit);

            measurement_outcome o;
            o.basis = this_measurement.basis;
            o.outcome_is_plus = Output_is_plus;
            return o;

        }

        measurement_outcome logicalStationaryQubit::logical_readout_v2(StationaryQubit *physicalQubit){
            
            // Randomly choose basis (call Random_Measurement_Basis_Selection())
            measurement_operator this_measurement = physicalQubit->Random_Measurement_Basis_Selection();

            for(int i=0; i < encoded_qubits_list.size(); i++){
                this->logical_measure_density_independent_v2( this->encoded_qubits_list[i], this_measurement);
            }

            std::string combind_outcome_string = "";
            std::map<int, std::string>::iterator it;
            for(it=this->physical_readout.begin(); it != this->physical_readout.end(); it++){
                combind_outcome_string += combind_outcome_string + it->second;
            }

            int num_encoded = 8;
            std::string logical_zero[8] = { "+++++++", "-+-+-+-", "+--++--", "--++--+", "+++----", "-+--+-+", "+----++", "--+-++-" };
            std::string logical_one[8] =  { "-------", "+-+-+-+", "-++--++", "++--++-", "---++++", "+-++-+-", "-++++--", "++-+--+" };

            char Output_is_plus;

            for (int i=0; i < num_encoded; i++){
                if (combind_outcome_string == logical_zero[i]) {
                    Output_is_plus = true;
                } else if (combind_outcome_string == logical_one[i]){
                    Output_is_plus = false;
                } else {
                    error("Invalid cordword");
                }
            }

            measurement_outcome o;
            o.basis = this_measurement.basis;
            o.outcome_is_plus = Output_is_plus;
            
        }

    }
}
