package channels;
@namespace(quisp::channels);

import ned.DatarateChannel;
import ned.DelayChannel;
import ned.IdealChannel;

channel ClassicalChannel extends DatarateChannel
{
    double cost = default(1);
    double distance @unit(km) = default(20km);
    double speed_of_light_in_fiber @unit(km) = default(208189.206944km);
    delay = this.distance / speed_of_light_in_fiber * 1s;
    datarate = uniform(1kbps, 100kbps);
}

channel QuantumChannel extends DatarateChannel
{
    @class(QuantumChannel);
    double cost = default(1);
    double distance @unit(km) = default(20km);
    double speed_of_light_in_fiber @unit(km) = default(208189.206944km);
    delay = this.distance / speed_of_light_in_fiber * 1s;
    double channel_loss_rate = default(0);
    double channel_x_error_rate = default(0);
    double channel_z_error_rate = default(0);
    double channel_y_error_rate = default(0);
}
