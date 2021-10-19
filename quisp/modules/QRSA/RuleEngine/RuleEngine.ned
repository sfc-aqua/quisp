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

package modules.QRSA.RuleEngine;

simple RuleEngine
{
    parameters:
        int address;
        int number_of_qnics;
        int number_of_qnics_r;
        int number_of_qnics_rp;
        int total_number_of_qnics;
        // # of resources system hasbeen recognized
        // @signal[recog_res](type="int");
        // @statistic[recog_res](title="recognized number of resource"; record=vector, max; interpolationmode=sample-hold);
        // # of resources in the physically generated
        @signal[actual_res](type=long);
        @statistic[actual_res](title="actual number of resource"; record=vector, max; interpolationmode=sample-hold);

        // creation time
        @signal[creation_time](type=simtime_t);
        @statistic[creation_time](title="link established time"; record=vector; interpolationmode=sample-hold);


    gates:
        inout RouterPort;
        inout HardwareMonitorPort;
}
