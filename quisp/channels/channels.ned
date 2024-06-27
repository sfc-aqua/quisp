package channels;
@namespace(quisp::channels);

import ned.DatarateChannel;
import ned.DelayChannel;
import ned.IdealChannel;

channel FiberChannel extends DatarateChannel {
	double cost = default(1);
    double distance @unit(km) = default(20km);
    double speed_of_light_in_fiber @unit(km) = default(208189.206944km);
    delay = this.distance / speed_of_light_in_fiber * 1s;
}

channel FreeSpaceChannel extends DatarateChannel {
    @class(FreeSpaceChannel);
    double cost = default(1);
    double distance @unit(km) = default(20km) @mutable;
    string distance_csv;
    double speed_of_light_in_freespace @unit(m) = default(299792.458km);
    double orbital_period @unit(s) = default(24h);
    bool csv_varies_delay = default(true);
    delay = this.distance / speed_of_light_in_freespace * 1s @mutable;
    datarate = uniform(1kbps, 100kbps);
}

channel ClassicalChannel extends FiberChannel
{
    datarate = uniform(1kbps, 100kbps);

}

channel QuantumChannel extends FiberChannel
{
    @class(QuantumChannel);
    double channel_loss_rate = default(0);
    double channel_x_error_rate = default(0);
    double channel_z_error_rate = default(0);
    double channel_y_error_rate = default(0);
}

channel ClassicalChannel_FS extends FreeSpaceChannel
{

}

channel FreeSpaceQuantumChannel extends FreeSpaceChannel
{
    @class(FreeSpaceQuantumChannel);
    double channel_x_error_rate = default(0);
    double channel_z_error_rate = default(0);
    double channel_y_error_rate = default(0);
    double wavelength @unit(m) = default(1550nm);
    double transmitter_telescope_diameter @unit(m) = default(13.5cm);
    double receiver_telescope_diameter @unit(m) = default(1m);
    double fried_parameter @unit(m) = default(10cm);
    double elevation_angle @unit(rad) = default(90deg); //TODO: this should be a function of time!
    double atmospheric_attenuation_zenith @unit(dB) = default(-3dB);
    string t_atm_csv;
}
