# Path Setup #

*Note: this file is an early design document, but should correspond well
to the existing implementation for single networks.  Internetworking
(recursive) connections and networks are not yet handled.  The Flat
Path setup should also correspond fairly closely to the [Internet Draft
by Van Meter &
Matsuo](https://tools.ietf.org/html/draft-van-meter-qirg-quantum-connection-setup-01)
(which, as of this writing, has expired, but will be revived).*

# Basic Idea #

The basic concept is that the path creation is triggered by an
application at the Initiator, information is accumulated on an
outbound pass, then the RuleSet is created at the Responder.  RuleSets
are installed on the return pass.  See
[FlatPathSetup Processing](FlatPathSetup%20Processing.md) for details.

# Easy and Hard #

- [FlatPathSetup Processing](FlatPathSetup%20Processing.md)
- [Recursive Path Setup](Recursive%20Path%20Setup.md) (including inter-networking)

# Network Types #

- [Dur-Briegel Path Setup](Dur-Briegel%20Path%20Setup.md)
- [Fowler Path Setup](Fowler%20Path%20Setup.md)
- [Jiang Path Setup](Jiang%20Path%20Setup.md)

# Path Setup protocol #

Assume that A wants to setup a quantum link with F and that we have access to two routing tables: S.CR(D) gives the best next hop for classical messaging from S to D, and S.QR(D) does the same for quantum.

- A gets next hop A.QR(F) = D
- A sends the classical message to D by using the classical routing table:
```
Establish Quantum Link A <--> F
```
- D receives this and gets next hop D.QR(F) = E
- D sends the classical message to E by using the classical routing table:
```
Establish Quantum Link A <--> F
A-D cost: ***
```
- E receives this and gets next hop E.QR(F) = F
- E sends the classical message to F:
```
Establish Quantum Link A <--> F
A-D cost: ***
D-E cost: ***
```
- F is the final destination. It adds its capacity and sends back to the previous hop E.
```
Return Establish Quantum Link A <--> F
A-D cost: ***
D-E cost: ***
E-F cost: ***
```
- E receives, sends back to D
- D receives, sends back to A
At this point, everybody knows the list (and capacities) of the hops that are going to be used for swapping and establishing the quantum link.