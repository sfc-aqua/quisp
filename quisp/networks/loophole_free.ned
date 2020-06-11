//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

package networks;

network Loophole_Free
{
    parameters:
        **.Speed_of_light_in_fiber = 205336.986301 km;
        //**.HoM_handshake = false;

    submodules:
        source: QNode {
            address = 1;
            nodeType = "EndNode";
            @display("i=device/pc");
        }
        HoM: HoM {
            address = 2;
            @display("i=device/bsm");
        }
        target: QNode {
            address = 3;
            nodeType = "EndNode";
            @display("i=device/pc");
        }

    connections:
        source.port++ <--> ClassicalChannel {  distance = 0.493km; } <--> HoM.port++;
        HoM.port++ <--> ClassicalChannel {  distance = 0.818km; } <--> target.port++;
        source.quantum_port++ <--> QuantumChannel {  distance = 0.493km; } <--> HoM.quantum_port++;
        HoM.quantum_port++ <--> QuantumChannel {  distance = 0.818km; } <--> target.quantum_port++;
}