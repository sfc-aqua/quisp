# Entangled Photon Pair Source

The EPPS component in QuISP comprises two modules, the EntangledPhotonPairSource and the EPPSController.
EntangledPhotonPairSource is the physical module where it only concerns itself with emmiting entangled photon pairs from the two ports.
EPPSController on the other hand, handles the messaging and signalling of neighbour QNode(s), sending emission partner information and telling them when the first photon should arrive.
