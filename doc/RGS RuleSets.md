# RuleSets for all-optical quantum repeaters

Before we dive into individual RuleSets for various types of network nodes we go over the notation used in this document.

We begin with the __repeater graph state (RGS)__:

<center>
<img src="img/rgs1.png" width="700" />
</center>

The RGS is given by <img src="https://render.githubusercontent.com/render/math?math=\Big|G(m,\vec{b})\rangle"> as shown in the figure. It consists of two types of vertices. Orange vertices represent 1st leaf qubits which are encoded using a tree encoding with a branching vector denoted by <img src="https://render.githubusercontent.com/render/math?math=\vec{b}">. In the figure, <img src="https://render.githubusercontent.com/render/math?math=\vec{b}=(3,2)">.
The blue vertices represent physical qubits, usually called 2nd leaf qubits or arm qubits. Each RGS has <img src="https://render.githubusercontent.com/render/math?math=2m"> 1st leaf qubits and <img src="https://render.githubusercontent.com/render/math?math=2m"> arms qubits.

The __network link__ is shown in the following figure:

<center>
<img src="img/rgs2.png" width="700" />
</center>

Each link consists of three types of nodes:
* __RGS nodes__ generate the RGS and send one half of the qubits to its neighbor to the right and the other half of the qubits to the left.
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
The RuleSet for ABSA nodes depends on the order of arrival of qubits from the source nodes. A pair of arm qubits arrive first from the left and right source nodes followed by their respective 1st-leaft neighbors as shown below.

<center>
<img src="img/rgs3.png" width="400" />
</center>

__Algorithm 1:__ initialTimeConditionalClause(arrivalTimeList)  
__This conditional clause checks whether current time is less than the scheduled arrival of first qubit.__  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Input: arrivalTimeList <- list of when qubits are scheduled to arrive at the ABSA node.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Output: initalTime <- Boolean value.

<pre>
1:  <b>procedure</b> initialTimeConditionalClause(arrivalTimeList)
2:    initialTime = False
3:    currentTime = time.get()
4:    <b>if</b> currentTime <= arrivalTimeList[0] <b>then</b>
5:      initialTime = True
6:    <b>end if</b>
7:    <b>return</b> initialTime
8:  <b>end procedure</b>
</pre>

__Algorithm 2:__ initializeAction()  
__This Action is used to set the measurement basis to Bell basis before the arrival of the first arm qubits, initialize the list of measurement outcomes and the counter of successful Bell measurements.__  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Input: none.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Output: basis <- measurement basis, outcomeList <- list of measurement results, successBell <- Boolean value indicating whether successful Bell measurement has occured yet.

<pre>
<b>Require:</b> initialTime == True
1:  <b>procedure</b> initializeAction()
2:    basis = Bell
3:    outcomeList = []
4:    successBell = False
5:    <b>return</b> basis, outcomeList, successBell
6:  <b>end procedure</b>
</pre>

__Algorithm 3:__ timeConditionalClause(arrivalTimeList)  
__This conditional clause checks the current time and whether the ABSA node is required to measure any more qubits.__  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Input: arrivalTimeList.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Output: measurementNeeded <- Boolean value.

<pre>
1:  <b>procedure</b> timeConditionalClause(arrivalTimeList)
2:    measurementNeeded = False
3:    currentTime = time.get()
4:    <b>if</b> currentTime <= arrivalTimeList[end] <b>then</b>
5:      measurementNeeded = True
6:    <b>end if</b>
7:    <b>return</b> measurementNeeded
8:  <b>end procedure</b>
</pre>

__Algorithm 4:__ measurementAction(basis, outcomeList, successBell)  
__This Action  performs the correct measurements on the two arriving qubits, updates the outcomeList and basis for the next measurements.__  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Input: basis, outcomeList, successBell.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Output: basis, outcomeList, successBell.

<pre>
<b>Require:</b> measurementNeeded == True
1:  <b>procedure</b> measurementAction(basis, outcomeList, successBell)
2:    resource1 = qubit from left source node
3:    resource2 = qubit from right source node
4:    outcome = measure(resource1, resource2, basis)
5:    outcomeList.append((basis, outcome))
6:    <b>if</b> basis != Bell <b>then</b>
7:      basis = Bell
8:    <b>else if</b> basis == Bell <b>then</b>
9:      <b>if</b> (outcome.success() == True and successBell == False) <b>then</b>
10:       basis = X
11:       successBell = True
12:     <b>else</b>
13:       basis = Z
14:     <b>end if</b>
15:   <b>end if</b>
16:   <b>return</b> basis, outcomeList, successBell
17: <b>end procedure</b>
</pre>

## 3. End nodes

__Final state__
<center>
<img src="img/rgs4_correction.png" width="500" />
</center>
