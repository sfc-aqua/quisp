package networks;
@namespace(quisp::channels);

import ned.DatarateChannel;
import ned.DelayChannel;
import ned.IdealChannel;

channel ClassicalChannel extends DatarateChannel{
		double cost = default(1);
        double distance @unit(km) = default(20km);
        //delay = uniform(0.01ms, 1s);
        double Speed_of_light_in_fiber @unit(km) = default(208189.206944km);
        delay = this.distance / Speed_of_light_in_fiber * 1s;
        datarate = uniform(1kbps, 100kbps);
}

channel QuantumChannel extends DatarateChannel
{
            @class(QuantumChannel);
            double cost = default(1);
            double distance @unit(km) = default(20km);
            //delay = uniform(0.01ms, 1s);
            double Speed_of_light_in_fiber @unit(km) = default(208189.206944km);
            delay = this.distance / Speed_of_light_in_fiber * 1s;
            double channel_Loss_error_rate = default(0);
            double channel_X_error_rate = default(0);
            double channel_Z_error_rate = default(0);
            double channel_Y_error_rate = default(0);
}
