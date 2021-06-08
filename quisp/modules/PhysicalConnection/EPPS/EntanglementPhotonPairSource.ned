simple EntangledPhotonPairSource{
	parameters:
	    int address;
      numBuffer=default(10);
	    double frequency;
	    double error_rate;
	    double Y_error_ratio;
	    double X_error_ratio;
	    double Z_error_ratio;
	    double emission_std;
	 gates:
	      inout fromController;
	     inout to_quantum_port[2];
}
