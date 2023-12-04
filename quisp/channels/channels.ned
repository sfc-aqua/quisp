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
    double orbital_period @unit(s) = default(86400s);
    delay = this.distance / speed_of_light_in_FS * 1s @mutable;
    datarate = uniform(1kbps, 100kbps);
}

channel FiberChannel extends DatarateChannel {
	double cost = default(1);
    double distance @unit(m) = default(20km);
    double speed_of_light_in_fiber @unit(km) = default(208189.206944km);
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
    double wavelength @unit(m) = default(810nm);
    double transmitter_telescope_diameter @unit(m) = default(50cm);
    double receiver_telescope_diameter @unit(m) = default(1m);
    double Fried_parameter @unit(m) = default(15cm);
    double elevation_angle @unit(deg) = default(90deg); //TODO: this should be a function of time!
    double atmospheric_attenuation_zenith @unit(dB) = default(3dB);
    
    string Aatm_CSV;
}
