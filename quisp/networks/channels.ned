package networks;
@namespace(quisp::channels);

import ned.DatarateChannel;
import ned.DelayChannel;
import ned.IdealChannel;

channel ClassicalChannel extends DatarateChannel{
		double cost = default(1);
        double distance @unit(km);
        distance = default(20km);
        //delay = uniform(0.01ms, 1s);
        double Speed_of_light_in_fiber @unit(km) = default(205336.986301km);
        delay = this.distance / Speed_of_light_in_fiber * 1s;
        datarate = uniform(1kbps, 100kbps);
}

channel QuantumChannel extends DatarateChannel
{
            @class(QuantumChannel);
            double cost = default(1);
            double distance @unit(km) = default(20km);
            //delay = uniform(0.01ms, 1s);
            double Speed_of_light_in_fiber @unit(km) = default(205336.986301km);
            delay = this.distance / Speed_of_light_in_fiber * 1s;
            //datarate = uniform(1kbps, 100kbps);
            double photon_loss_rate = default(0);//per km
            double channel_error_rate = default(0);//per km
            double Z_error_ratio = default(1);
            double X_error_ratio = default(1);
            double Y_error_ratio = default(1);
}

//I am not using this though..... All delays caused by internal connections are considered negligible in the simulation.
channel QuantumChannel_internal extends QuantumChannel
{
            distance @unit(cm) = default(1cm);
            photon_loss_rate = default(0);//per km
            channel_error_rate = default(0);//per km
            Z_error_ratio = default(1);
            X_error_ratio = default(1);
            Y_error_ratio = default(1);
}
