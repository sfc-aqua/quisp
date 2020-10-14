# How to add a new ruleset to QuISP?

This guide is written for any interested developer who wants to add a new ruleset to QuISP.

To add a new ruleset, follow these steps.

## 1 Define your rules logically in a Markdown file
Before you start editing the code, you need to state your new ruleset in a Markdown file. This will help you understand why you decided to add this ruleset, how it differs from the existing ones, and what tasks it performs.


## 2 Does your ruleset define a new node type?
If you need to define a node type that doesn't exist in QuISP, you will need to explain this node before you start coding your rules.
Any node in QuISP has two aspects, software, and hardware.
### The software aspect of a node:
QuISP currently has different node types: BSA node is an example of that. 
To define the node's software aspect, you need to create a class controlling the node's different characteristics and behavior. The class needs to be in a similar format to the [BSA node](https://github.com/sfc-aqua/quisp/blob/master/quisp/modules/BellStateAnalyzer.cc).

### The hardware aspect of a node:
Every node's software needs a hardware code to facilitate it. In order to complete creating a new node type, you need to create a hardware controller for this node. 
For example, the BSA node's controller is [HoM_controller](https://github.com/sfc-aqua/quisp/blob/master/quisp/modules/HoM_Controller.cc). Hardware controller has both a .cc and .h files.

Once you created both the hardware and software aspects of your new node type, you can start coding your ruleset.

## 3 Code your ruleset
Before you start coding your ruleset, you need to divide them into three categories:
1. Conditions. (To be added to condtion.cc and condition.h)
2. Clauses. (To be added to clause.cc and clause.h)
3. Actions. (To be added to action.cc and action.h)
Each of these three categories requires a specific syntax and needs to be added to particular code files. These files are located in the [rules](https://github.com/sfc-aqua/quisp/tree/master/quisp/rules) directory of the QuISP repository.

## 4 Facilitate your ruleset
Add the facilitation code to QuantumRoutingSoft.
