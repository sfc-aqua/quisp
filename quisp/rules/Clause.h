/** \file Clause.h
 *  \authors cldurand,takaakimatsuo
 *  \date 2018/07/03
 *
 *  \brief Clause
 */
#ifndef QUISP_RULES_CLAUSE_H_
#define QUISP_RULES_CLAUSE_H_

#include <modules/QNIC.h>
#include <modules/QUBIT.h>
#include <omnetpp.h>
#include <memory>

using namespace quisp::modules;

namespace quisp {
namespace rules {

/** \class Clause Clause.h
 *
 *  \brief Clause
 */
class Clause {
 protected:
  int partner; /**< Identifies entanglement partner. */
  QNIC_type qnic_type;
  int qnic_id;
  int resource; /**< Identifies qubit */

 public:
  Clause(){};
  Clause(int partner, int resource) : Clause(partner, QNIC_N, -1, resource){};
  Clause(int part, QNIC_type qt, int qi, int res) {
    partner = part;
    qnic_type = qt;
    qnic_id = qi;
    resource = res;
  };
  Clause(int part, QNIC_type qt, int qi) {
    partner = part;
    qnic_type = qt;
    qnic_id = qi;
  };

  void setQnic(QNIC_type qt, int qi) {
    // if (qt >= QNIC_N) omnetpp::error("Not that many QNIC types.");
    // if (qi < 0) omnetpp::error("Negative qnic index.");
    qnic_type = qt;
    qnic_id = qi;
  };
  void checkQnic() const {
      // if (qnic_type >= QNIC_N) omnetpp::error("Not that many QNIC types.");
      // if (qnic_id < 0) omnetpp::error("Negative qnic index.");
  };
  // virtual bool check(qnicResources *resources) const = 0;
  virtual bool check(std::multimap<int, StationaryQubit*>) const = 0;
  // virtual bool checkTerminate(qnicResources *resources) const = 0;
  virtual bool checkTerminate(std::multimap<int, StationaryQubit*>) const = 0;
  // virtual StationaryQubit* getQubit(qnicResources* resources, QNIC_type qtype, int qid, int partner, int res_id) const = 0;
};

typedef std::unique_ptr<Clause> pClause;

class FidelityClause : public Clause {
 protected:
  double threshold;

 public:
  FidelityClause(int partner, int resource, double fidelity) : Clause(partner, resource) { threshold = fidelity; };
  FidelityClause(int part, QNIC_type qt, int qi, int res, double fidelity) : Clause(part, qt, qi, res) { threshold = fidelity; };
  // bool check(qnicResources *resources) const override;
  // bool checkTerminate(qnicResources *resources) const override {return 0;} ;
  bool check(std::multimap<int, StationaryQubit*>) const override;
  bool checkTerminate(std::multimap<int, StationaryQubit*>) const override { return false; };
};

class EnoughResourceClause : public Clause {
 protected:
  int num_resource_required;
  int partner;

 public:
  EnoughResourceClause(int part, int num_res) : Clause() {
    num_resource_required = num_res;
    partner = part;
  };
  bool check(std::multimap<int, StationaryQubit*>) const override;
  bool checkTerminate(std::multimap<int, StationaryQubit*>) const override { return false; };
};

/**EnoughResourceClauseLeft is for checking if node have enough resource to left node.
 *  This is for entanglement swapping.
 */
class EnoughResourceClauseLeft : public Clause {
 protected:
  int num_resource_required_left;
  int partner_left;

 public:
  EnoughResourceClauseLeft(int part_left, int num_res_left) : Clause() {
    num_resource_required_left = num_res_left;
    partner_left = part_left;
  }

  bool check(std::multimap<int, StationaryQubit*>) const override;
  bool checkTerminate(std::multimap<int, StationaryQubit*>) const override { return false; };
};

class EnoughResourceClauseRight : public Clause {
 protected:
  int num_resource_required_right;
  int partner_right;

 public:
  EnoughResourceClauseRight(int part_right, int num_res_right) : Clause() {
    num_resource_required_right = num_res_right;
    partner_right = part_right;
  }

  bool check(std::multimap<int, StationaryQubit*>) const override;
  bool checkTerminate(std::multimap<int, StationaryQubit*>) const override { return false; };
};

class NoClause : public Clause {
 public:
  NoClause()
      : Clause(){

        };
  // bool check(qnicResources *resources) const override {return true;};
  // bool checkTerminate(qnicResources *resources) const override {return false;} ;
  bool check(std::multimap<int, StationaryQubit*>) const override { return true; };
  bool checkTerminate(std::multimap<int, StationaryQubit*>) const override { return false; };
};

class MeasureCountClause : public Clause {
 public:
  int max_count;
  int mutable current_count;
  MeasureCountClause(int max, int part, QNIC_type qt, int qi, int res) : Clause(part, qt, qi, res) {  // May not need this
    max_count = max;
    current_count = 0;
  };
  MeasureCountClause(int max) : Clause() {
    max_count = max;
    current_count = 0;
  };
  // bool check(qnicResources *resources) const override;
  // bool checkTerminate(qnicResources *resources) const override;
  bool check(std::multimap<int, StationaryQubit*>) const override;
  bool checkTerminate(std::multimap<int, StationaryQubit*>) const override;
  // void increment(){current_count++;};
};

class PurificationCountClause : public Clause {
 public:
  int num_purify_must;
  // int mutable current_count;
  PurificationCountClause(int part, QNIC_type qt, int qi, int n_purify) : Clause(part, qt, qi) {  // May not need this
    // max_count = max;
    // current_count = 0;
    num_purify_must = n_purify;
  };

  // bool check(qnicResources *resources) const override;
  // bool checkTerminate(qnicResources *resources) const override;
  bool check(std::multimap<int, StationaryQubit*>) const override;
  // void increment(){current_count++;};
};

class XErrClause : public Clause {};
  
//ABSA clauses start here
  //Algorithm 1
class initConditionalClause : public Clause {
 protected:
 	int qubit_arrival_time;

 public:
  initConditionalClause(int arrivalTime) : Clause() {
    qubit_arrival_time = arrivalTime;

  };
  bool check(std::arrivalTime<int) const override;
  bool checkTerminate(std::arrivalTime<int) const override { return false; };
};

//do we need both?
class arrivalTimeClause : public Clause{
 public:
  bool initialTime;
  simtime_t currentTime;
  std::vector<simtime_t> arrivalTimeList;
  // maybe here we need qnic type and index as well to identify the qubit
  arrivalTimeClause(bool initialTime, simtime_t currentTime, std::vector<simtime_t> arrivalTimeList){
  initialTime = initialTime;
  currentTime = currentTime;
  arrivalTimeList = arrivalTimeList;
  };
  virtual check() const override;
  virtual checkTerminate() const override {return false;};
};

//how will clause 1 and 3 differ in the h file?
//Algorithm 3
class MeasureConditionalClause : public Clause {
 protected:
 	int qubit_arrival_time;

 public:
    MeasureConditionalClause(int arrivalTime) : Clause() {
    qubit_arrival_time = arrivalTime;

  };
  bool check(std::arrivalTime<int) const override;
  bool checkTerminate(std::arrivalTime<int) const override { return false; };
};

//Algorithm 4
class postBellConditionalClause : public Clause {
 protected:
 	StationaryQubit* resources;
 	bool bellSuccess;

 public:
    postBellConditionalClause(int *outList, bool success) : Clause() {
    resources = outList;
    bellSuccess = success;

  };
  bool check(int *outList, std::successBell<bool) const override;
  bool checkTerminate(int *outList, std::successBell<bool) const override { return false; };
};


//Algorithm 6
class finalConditionalClause : public Clause {
 protected:
 	int qubit_arrival_time;
 	bool msg_sent;

 public:
    finalConditionalClause(int arrivalTime, bool msgSent) : Clause() {
    qubit_arrival_time = arrivalTime;
    msg_sent = msgSent;

  };
  bool check(std::arrivalTime<int, std::msgSent<bool) const override;
  bool checkTerminate(std::arrivalTime<int, std::msgSent<bool) const override { return false; };
};


//Algorithm 8 
class qkdInitConditionalClause : public Clause {
 protected:
 	int* qubit_arrival_time;

 public:
    qkdInitConditionalClause(int* arrivalTime) : Clause() {
    qubit_arrival_time = arrivalTime;

  };
  bool check(std::arrivalTime<int *) const override;
  bool checkTerminate(std::arrivalTime<int *) const override { return false; };
};


//Algorithm 10 Clause
//Needs to be modified
class qkdMeasureConditionClause : public Clause {
 protected:
 	int* qubit_arrival_time;
 	//what type will the basis list be?

 public:
    qkdMeasureConditionClause(int *arrivalTimeList, *basisList) : Clause() {
    qubit_arrival_time = arrivalTime;

  };
  bool check(std::arrivalTimeList<int*, *basisList) const override;
  bool checkTerminate(std::arrivalTimeList<int*, *basisList) const override { return false; };
};

//Algorithm 12
class qkdFinalConditionClause : public Clause {
 protected:
 	int* algo;

 public:
    qkdFinalConditionClause(int *Algorithm) : Clause() {
    algo = Algorithm;

  };
  bool check(std::Algorithm<int *) const override;
  bool checkTerminate(std::Algorithm<int *) const override { return false; };
};

}  // namespace rules
}  // namespace quisp

#endif  // QUISP_RULES_CLAUSE_H_
