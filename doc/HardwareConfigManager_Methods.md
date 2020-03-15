# Hardware Configuration Manager Methods #

*Note: This is an old design document, which we expect to still be useful, but it may or may not correspond well to the current implementation.

The Routing Daemon has to query the Hardware Configuration Manager to
find out about the links.  It needs to know who the neighbors are, and
how fast the links are.

Question: Assuming raw Bell pairs are F < 0.98, who does the
conversion to seconds per Bell pair at F=0.98?  As written here, that
is done somewhere below here.

    ListOfInterfaces EnumerateLinks();

    struct Interface {
        IPAddr Neighbor;
        float SecondsPerGoodBellPair();
    }

Next question: what functions does the HardwareConfigurationManager
require of the QNIC_Controller?

## Link Tomography ##

The HM is responsible for link-level tomography (or other form of
monitoring).  See
[Distributed Tomography and State Monitoring](Distributed%20Tomography%20and%20State%20Monitoring.md)
for more information.

Note that the selection of states to be used for tomography must be
coordinated with the neighboring node, and that the sequence of base
Bell pairs used for tomography must be cryptographically securely
selected.  Coordinating this with the RuleEngine is necessary in the
real world, but probably not used in these simulations.
