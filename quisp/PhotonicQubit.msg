
cplusplus {{
    #include <vector>
    #include <unsupported/Eigen/MatrixFunctions>

	using namespace omnetpp;
    typedef cModule *GOD_statQubitPtr;
    typedef cMessage *GOD_photonicQubitPtr;
}} // C++ typedef
class noncobject GOD_statQubitPtr; // For tracking the truely entangled ones (Only God knows!). The system may think the qubit is entangled but it may not (darkcount)!
class noncobject GOD_photonicQubitPtr;



namespace quisp::messages;

message PhotonicQubit
{
    @customize(true);
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
    GOD_statQubitPtr entangled_with;
    GOD_photonicQubitPtr entangled_photon;
    int QNICtypeEntangledWith = -1;
    //cModulePtr qnic_pointer;
    //EntangledWith entangledWith;
    double error_random_for_debug;
    bool first = false;
    bool last = false;
    bool is_entangled_with_photon = false;
}

//See https://www.omnetpp.org/pmwiki/index.php?n=Main.FixUnresolvedInclusion
//	  https://www.omnetpp.org/doc/omnetpp/manual/#sec:msg-defs:other-types-as-fields
cplusplus{{
    class PhotonicQubit : public PhotonicQubit_Base
	{
  		public:
    			PhotonicQubit(const char *name=nullptr) : PhotonicQubit_Base(name) {}
    			PhotonicQubit(const PhotonicQubit& other) : PhotonicQubit_Base(other) {}
    			PhotonicQubit& operator=(const PhotonicQubit& other)
        		{PhotonicQubit_Base::operator=(other); return *this;}
    			virtual PhotonicQubit *dup() const {return new PhotonicQubit(*this);}

	};Register_Class(PhotonicQubit);
	
}}

