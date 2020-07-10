# RuleSets for all-optical quantum repeaters

Before we dive into individual RuleSets for various types of network nodes we go over the notation used in this document.

We begin with the __repeater graph state (RGS)__:

<center>
<img src="img/rgs1_rgs.png" width="700" />
</center>

The RGS is given by <img src="https://render.githubusercontent.com/render/math?math=\Big|G(m,\vec{b})\rangle"> as shown in the Figure 1. It consists of two types of vertices. Orange vertices represent 1st leaf qubits which are encoded using a tree encoding with a branching vector denoted by <img src="https://render.githubusercontent.com/render/math?math=\vec{b}=(b_0,b_1,\ldots,b_n)">.
The blue vertices represent physical qubits, usually called 2nd leaf qubits or arm qubits.
Total number of physical qubits for <img src="https://render.githubusercontent.com/render/math?math=\Big|G(m,\vec{b})\rangle"> is <img src="https://render.githubusercontent.com/render/math?math=N_l=2m [\sum_{j=0}^n\product_{i=0}^jb_{i}%2B1]">.
The example shown in Figure 1 with m=3 and <img src="https://render.githubusercontent.com/render/math?math=\vec{b}=(3,2)"> contains 60 physical qubits.

The __network link__ is shown in the following figure:

<center>
<img src="img/rgs2_link.png" width="700" />
</center>

Each link consists of three types of nodes:
* __RGS node__ generates the photonic RGS using matter qubits and sends one half of the qubits to its neighbor to the right and the other half of the qubits to the left.
* __Mesurement node__ or __Advanced Bell State Analyzer (ABSA)__ receives one half of a RGS from boths its neighboring RGS nodes. The ABSA then measures the arm qubits in Bell basis. Depending on the outcome of the Bell mesurements the orange qubits are then measured in corresponding Pauli X or Pauli Z basis. The network link is composed of alternative RGS nodes and ABSA nodes.
* __End nodes__ of the link are the nodes trying to establish a shared entangled pair. [Comment: their precise functionality still needs to be discussed and determined. For now we assume they receive one half of a RGS from the neighboring RGS node.]


## 1. Repeater nodes

Time flow of the generation of the RGS:

1. Generate the encoded RGS. *[Comment: need to consider step-by-step generation using matter qubits and operation on them.]*
2. Send left half of the RGS to the left neighbor. Send right half to the right neoghbor.


## 2. ABSA nodes

__Assumptions:__
* We assume that the arrival of qubits at the ABSA is appropritely synchronized. *[Comment: Need to discuss how to synchronize the distribution of RGS across the link.]*

__Overview:__  
The RuleSet for ABSA nodes depends on the order of arrival of qubits from the source nodes. A pair of arm qubits arrive first from the left and right source nodes followed by their respective 1st-leaft neighbors as shown in Figure 3.

<center>
<img src="img/rgs3_arrival.png" width="1000" />
</center>

The explicit time schedule is also shown in Figure 3.
Each orange block represents <img src="https://render.githubusercontent.com/render/math?math=N_l"> physical qubits corresponding to a single logical qubit.
The physical qubits constituting one logical qubit arrive in a way shown in Figure 3.


__Indirect Z measurement:__

Local Pauli measurements can be performed in a fault-tolerant manner on logical qubits encoded using a tree graph state as shown in Figure 1.
An indirect Z measurement can be used even after a failed direct Z measurement or after the qubit to be measured had been lost.

<center>
<img src="img/rgs4_indirectZ.png" width="400" />
</center>

Figure 4 shows an indirect Z measurement. The parity of a failed Z measurement on qubit (i,j) can be inferred from a successful X measurement on any of the qubits on level i+1 that are leafs of qubit (i,j), and subsequent Z measurements (direct or indirect) on their leafs on level i+2. Figure 4 shows a successful inidirect measurement on qubit (i,j) despite two of the attempts having failed on subtree B and subtree C. Parity of the Z measurement on qubit (i,j) is given by the total parity of X and Z measurements on qubits of level i+1 and level i+2.

__Encoded measurements:__

The 1st-leaf qubits of an RGS ar eencoded in a tree structure and therefore have to be measured using encoded Pauli operators as shown in Figure 5.

<center>
<img src="img/rgs5_encodedPauli.png" width="1200" />
</center>


Encoded Z measurement is performed by measuring all Level 1 qubits in Z basis, Level 2 qubits in X basis, Level 3 qubits in Z basis and so on.
The encoded measurement succeeds if all Level 1 qubits are measured successfully (either via direct or indirect Z measurements).

Encoded X measurement is performed by measuring all Level 1 qubits in X basis, Level 2 qubits in Z basis, Level 3 qubits in X basis and so on.
The encoded measurement succeeds if at least one of the Level 1 X measurements is successful and all its Level 2 leafs are successfully measured in Z (either via direct or indirect measurements).

__Algorithm 1:__ initializeConditionalClause(arrivalTimeList)  
__This conditional clause checks whether current time is less than the scheduled arrival of first qubit.__  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Input: arrivalTimeList <- list of when qubits are scheduled to arrive at the ABSA node.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Output: initalTime <- Boolean value.

<pre>
1:  <b>procedure</b> initializeConditionalClause(arrivalTimeList)
2:    initialTime = False
3:    currentTime = time.get()
4:    <b>if</b> currentTime < arrivalTimeList[0] <b>then</b>
5:      initialTime = True
6:    <b>end if</b>
7:    <b>return</b> initialTime
8:  <b>end procedure</b>
</pre>

__Algorithm 2:__ initializeAction(branchingVector)  
__This Action is used to set the measurement basis to Bell basis before the arrival of the first arm qubits, initialize the list of measurement outcomes, the Boolean value tracking whether a successful Bell measurement has occurred, and creates two tree arrays according to the branching vector used for encoded X and Z measurements.__  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Input: branchingVector <- tree array used for encoding 1st-leaf qubits.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Output: basis <- measurement basis, outcomeList <- list of measurement results for physical qubits, successBell <- Boolean value indicating whether successful Bell measurement has occured yet, encodedX <- tree array with Pauli bases (see Figure 5), encodedZ <- tree array with Pauli bases (see Figure 5).

<pre>
<b>Require:</b> initialTime == True
1:  <b>procedure</b> initializeAction()
2:    basis = Bell
3:    outcomeList = []
4:    successBell = False
5:    encodedX <- tree array for encoded X measurement
6:    encodedZ <- tree array for encoded Z measurement
7:    <b>return</b> basis, outcomeList, successBell, encodedX, encodedZ
8:  <b>end procedure</b>
</pre>

__Algorithm 3:__ measureConditionalClause(arrivalTime)  
__This conditional clause determines whether the ABSA should measure anything.__  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Input: arrivalTimeList.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Output: measurementNeeded <- Boolean value.

<pre>
1:  <b>procedure</b> measurementConditionalClause(arrivalTime)
2:    currentTime = time.get()
3:    measurementNeeded = False
4:    <b>if</b> arrivalTime[0] <= currentTime <= arrivalTime[end] <b>then</b>
5:      measurementNeeded = True
6:    <b>end if</b>
7:    <b>return</b> measurementNeeded
8:  <b>end procedure</b>
</pre>

__Algorithm 4:__ postBellConditionalClause(outcomeList,successBell)  
__This Conditional Clause determines the basis for upcoming encoded Pauli measurement following a Bell measurement.__  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Input: outcomeList, successBell.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Output: basis <- measurement basis.

<pre>
1:  <b>procedure</b> postBellConditionalClause(outcomeList,successBell)
2:    <b>if</b> successBell == True or outcomeList[end].success() == False <b>then</b>
3:      basis = encodedZ
4:    <b>else</b>
5:      basis = encodedX
6:    <b>end if</b>
7:    <b>return</b> basis
8:  <b>end procedure</b>
</pre>

__Algorithm 5:__ measureAction(outcomeList,basis)  
__This Action Clause performs measurements on the incoming qubits.__  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Input: outcomeList, basis.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Ouput: outcomeList. 

<pre>
<b>Require:</b> measurementNeeded == True
1:  <b>procedure</b> measureAction(outcomeList, basis)
2:    <b>for</b> i=0, i&ltlength(basis), i++
3:      resource1 <- qubit from right source node
4:      resource2 <- qubit from left source node
5:      outcome = measure(resource1, resource2, basis[i])
6:      outcomeList.append((basis,outcome))
7:    <b>end for</b>
8:    <b>return</b> outcomeList
9:  <b>end procedure</b>
</pre>

## 3. End nodes

__Final state__
<center>
<img src="img/rgs4_correction.png" width="500" />
</center>
