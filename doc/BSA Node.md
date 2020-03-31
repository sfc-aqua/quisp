# Bell State Analyzer (BSA) Node (Bnode) #

*Note: This is an old design document, which we expect to still be useful, but it may or may not correspond well to the current implementation.

As a standalone node, appears in an [MIM Link](MIM_Link.md).

The Bnode must drive timing of photon arrival.  See, e.g. Fig. 2 in
Hensen & Hanson, which shows the relative transmission offset.  The
Bnode is in the best position to determine that timing.  This could be
done via recognizing the differential and telling only one end to
adjust, for example.  (n.b.: Hensen-Hanson generates this from the end
holding the AWG.  I'm not clear on how the signal is relayed to the
other end point.)


#Entanglement Distribution Protocol for MIM and MM (notes by kaaki)#

There are two main ways, with or without hand-shake, to distribute entangled pairs using a stand-alone or an internal BSA.
Slides explaining those with figures can be found [slides](HoMProtocol.pptx).
The one without hand-shake is assuming a timeout, but we can also mark the beginning and end of emission by sandwiching the qubits by pulses (in the simulation, I have just marked them as setKind(n) with n=1 as the first and n=-1 as last). On the other hand, the method with handshake only requires to detect the existence of the photon ,which the physical hardware cost may be cheaper. 
The one without hand-shake could be less efficient if the buffer size difference between neighbors is big (with handshake, each node knows the exact number of qubits, therefore, other unused qubits may be used for other qnics e.g. qnic buffer virtualization).
In case with hand-shake, if one node says "no qubit to entangle...!!" then how should the BSA node schedule the next trial...?
Similarly, in case without handshake, if both neighbors didnt transmit any qubit to BSA because all of them were busy, how should the BSA node recognize that? When should it schedule the request? I think BSA needs a time-out anyway... (If the time-out is short relative to emission timing jitter, then it may cause problem)

I think things get very complicated if emission lag is large relative to the burst interval.
Let's say, each neighbor wants to entangle 10 qubits, and each photon is scheduled so that they get emitted with a 1 sec interval (from both neighbors). Photons from the left-side neighbor are assumed to arrive perfectly time-wise to the BSA node, 1 qubit per 1 sec.
However, if the first photon from the right-side neighbor arrived at the BSA node with a 1 sec lag, then the BSA could potentially say "the second photons got entangled!", while it actually was the 2nd of the left and the 1st of the right. This problem may not occur depending on the parameter settings (accepted arrival interval of BSA, and emission timing jitter).



The current BSA module returns the BSA results all together when it receives the last photon from either  neighbor.
Once the result is received by the neighbor, if any, the neighbor terminates the emission, and resets all qubits that failed entangling. If the BSA receives the last qubit from right, and generates/sends the classical BSA results packet,  but if another last qubit from left arrives because it had a larger buffer size, the BSA needs to know that he already sent back the results for this trial - it needs to correctly ignore the last qubit from left. In the simulation, I have avoided this problem by tracking the first photon (pulse indicating the start of photon burst). The boolean "this_trial_done" becomes true if the last qubit from either neighbor has been detected. While "this_trial_done == true", any BSA result will be dumped. "this_trial_done" will be set false when the BSA detects the first photon from either qubit.
What's important is that the BSA nodes need to recognize the beginning and the end of each trial, both of them!!!
