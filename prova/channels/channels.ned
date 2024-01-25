package channels;
@namespace(channels);

import ned.DatarateChannel;
import ned.DelayChannel;
import ned.IdealChannel;

channel FSChannel extends DatarateChannel {
    @class(FSChannel);
    double cost = default(1);
    double distance @unit(km) = default(20km);
    double speed_of_light_in_FS @unit(km) = default(299792.458km);
    delay = this.distance / speed_of_light_in_FS * 1s;
    datarate = uniform(1kbps, 100kbps);
}

channel FiberChannel extends DatarateChannel {
    @class(FiberChannel);
	double cost = default(1);
    double distance @unit(km) = default(20km);
    double speed_of_light_in_fiber @unit(km) = default(208189.206944km);
    delay = this.distance / speed_of_light_in_fiber * 1s;
    datarate = uniform(1kbps, 100kbps);
}

channel ClassicalChannel extends DatarateChannel {
	double cost = default(1);
    double distance @unit(km) = default(20km);
    double speed_of_light_in_fiber @unit(km) = default(208189.206944km);
    delay = this.distance / speed_of_light_in_fiber * 1s;
    datarate = uniform(1kbps, 100kbps);
}



channel ClassicalChannel_FS extends FSChannel
{
      
}


