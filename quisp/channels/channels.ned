package channels;
@namespace(quisp::channels);

import ned.DatarateChannel;
import ned.DelayChannel;
import ned.IdealChannel;

channel FSChannel extends DatarateChannel {
    @class(FSChannel);
    double cost = default(1);
    double distance @unit(m) = default(20km) @mutable;
    string distance_CSV;
    double speed_of_light_in_FS @unit(m) = default(299792.458km);
    double orbital_period @unit(s) = default(24h);
    bool CSV_varies_delay = default(false);
    delay = this.distance / speed_of_light_in_FS * 1s @mutable;
    datarate = uniform(1kbps, 100kbps);
}

channel FiberChannel extends DatarateChannel {
	double cost = default(1);
    double distance @unit(m) = default(20km);
    double speed_of_light_in_fiber @unit(m) = default(208189.206944km);
    delay = this.distance / speed_of_light_in_fiber * 1s;
    datarate = uniform(1kbps, 100kbps);
}

channel ClassicalChannel extends FiberChannel {
}

channel QuantumChannel extends FiberChannel
{
    @class(QuantumChannel);
    double channel_loss_rate = default(0);
    double channel_x_error_rate = default(0);
    double channel_z_error_rate = default(0);
    double channel_y_error_rate = default(0);
}

channel ClassicalChannel_FS extends FSChannel
{
      
}

channel QuantumChannel_FS extends FSChannel
{
    @class(QuantumChannel_FS);
    double channel_x_error_rate = default(0);
    double channel_z_error_rate = default(0);
    double channel_y_error_rate = default(0);
    double wavelength @unit(m) = default(1550nm);
    double transmitter_telescope_diameter @unit(m) = default(13.5cm);
    double receiver_telescope_diameter @unit(m) = default(1m);
    double Fried_parameter @unit(m) = default(10cm);
    string Aatm_CSV;
    
    @signal[channel_length](type=long);
    @statistic[channel_length](record=vector);
    @signal[channel_delay](type=long);
    @statistic[channel_delay](record=vector);
    @signal[channel_att](type=long);
    @statistic[channel_att](record=vector);
    @signal[channel_att_dB](type=long);
    @statistic[channel_att_dB](record=vector);
}
