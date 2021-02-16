


#ifndef QUISP_MODULES_LOGICAL_STATIONARYQUBIT_H_
#define QUISP_MODULES_LOGICAL_STATIONARYQUBIT_H_

#include <stationaryQubit.h>

using namespace Eigen;
using namespace omnetpp;
using namespace quisp::messages;

namespace quisp {
    namespace modules {

        typedef std::complex<double> Complex;

        typedef struct _logical_quantum_state{
            MatrixXcd state_in_density_matrix;
            VectorXcd state_in_ket;
        } logical_quantum_state;

        typedef struct _measurement_outcome{
            char basis;
            bool outcome_is_plus;
        }measurement_outcome;

        typedef struct _logical_measurement_operator{
            MatrixXcd plus;
            MatrixXcd minus;
            VectorXcd plus_ket;
            VectorXcd minus_ket;
            char basis;
        }logical_measurement_operator;

        class logicalStationaryQubit : public cSimpleModule{
            public:
                bool locked;
                unsigned long locked_ruleset_id;
                int locked_rule_id;
                int action_index;

                bool isBusy;
                bool allocated;

                // Possible not nessesary for logical qubit
                simtime_t emitted_time = -1;
                simtime_t updated_time = -1;

                // Parameters to deal with if logical parter was measured.
                bool logical_partner_measured; // To flag which method to calculate the outcome.
                MatrixXcd Density_matrix_Collapsed; // Density matrix after another logical qubit is measured
                // v2
                logical_quantum_state logicalQuantumState;
                vector<stationaryQubit> combine_entangled_list;
                std::map<int, std::string> physical_readout;
                // end v2

                // Logical information
                vector<StationaryQubit*> encoded_qubits_list; 
                logicalStationaryQubit *logical_entangled_partner = nullptr; 

        }

    }

}

#endif /* QUISP_MODULES_LOGICAL_STATIONARYQUBIT_H_ */