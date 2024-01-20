from qiskit import QuantumCircuit, assemble, Aer, transpile
from qiskit.circuit.library import ZGate

n = 4
L = 5
qc = QuantumCircuit(n)
    # Write your code here:

target_qubit = n-1

for num in range(L,pow(2,n)+1):
    binary_string = bin(num)[2:]  # Convert to binary and remove the '0b' prefix
    binary_list = [int(bit) for bit in binary_string[::-1]]
    control_qubits = []
    counter = 0
    flag = 0
    for b in binary_list:
        if b==1:
            control_qubits.append(counter)
            counter+=1
        else:
            counter+=1
        if counter == target_qubit:
            flag = 1
            break
    if flag == 0:
        cz_gate = ZGate().control(len(control_qubits))
        qc.append(cz_gate, control_qubits+[target_qubit])



# Simulate the circuit to obtain the statevector
simulator = Aer.get_backend('statevector_simulator')
compiled_circuit = transpile(qc, simulator)
result = simulator.run(assemble(compiled_circuit)).result()
statevector = result.get_statevector()

# Display the final statevector
print("\nFinal statevector:")
print(statevector)
