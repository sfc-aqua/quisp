//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//


message PhotonicQubit
{
    
    string message_type = "qubit";
    //int SrcAddr = -1;
    //int DestAddr = -1;
    bool pauliXerr = false;
    bool pauliZerr = false;
    bool photonLost = false;
    bool nonPaulierr = false;
    bool nonPaulierrTwo = false;
    int NodeEntangledWith = -1;//Which node it is entangled with. -1 if not entangled. Equivalent to SrcAddress.
    int QNICEntangledWith = -1;//Which QNIC it is entangled with
    int StationaryQubitEntangledWith = -1;//Which buffer it is entangled with
    //EntangledWith entangledWith;
    double error_random_for_debug;
    	bool first = false;
	bool last = false;
}
