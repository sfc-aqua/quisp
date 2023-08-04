#include "TomographyManager.h"
#include <map>
#include <memory>
#include <tuple>
#include <utility>
#include "messages/tomography_messages_m.h"
#include "omnetpp/cexception.h"
#include "rules/RuleSet.h"

using omnetpp::cRuntimeError;
using quisp::utils::TomographyManager;

namespace quisp::utils {

TomographyManager::TomographyManager() {
  Pauli.X << 0, 1, 1, 0;
  Pauli.Y << 0, std::complex<double>(0, -1), std::complex<double>(0, 1), 0;
  Pauli.Z << 1, 0, 0, -1;
  Pauli.I << 1, 0, 0, 1;
}

TomographyManager::~TomographyManager() {
}

void TomographyManager::addLocalResult(int qnic_id, int partner, int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean) {
  // Local measurement result
  TomographyOutput self_record;
  self_record.basis = measurement_basis;
  self_record.output_is_plus = is_plus;
  self_record.my_GOD_clean = my_GOD_clean;

  appendTomographyRecord(std::make_tuple(qnic_id, partner), tomography_round, self_record, true);
}

void TomographyManager::addPartnerResult(int self_qnic_id, int partner, int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean) {
  TomographyOutput partner_record;
  partner_record.basis = measurement_basis;
  partner_record.output_is_plus = is_plus;
  partner_record.my_GOD_clean = my_GOD_clean;

  appendTomographyRecord(std::make_tuple(self_qnic_id, partner), tomography_round, partner_record, false);
}

void TomographyManager::appendTomographyRecord(std::tuple<int, int> partner_key, int tomography_round, TomographyOutput tomography_output, bool is_self_record) {
  // Check if the partner record has already been prepared

  if (!tomography_records.count(partner_key)) {
    // Tomography record for this partner cannot be found.
    // Even if the tomography round is 0, there might be existing partner key
    // since there is a possibility that the partner node perform measurement
    // earlier than this node.

    if (tomography_round != 0) {
      // Tomography round must be 0 since this must be the first record for this partner.
      throw cRuntimeError("Previous tomography round is not properly recorded.");
    }

    // Prepare the first record for this partner.
    // auto tomography_record = std::make_unique<TomographyRecord>();
    TomographyRecord tomography_record;
    if (is_self_record) {
      // Self record is added, leave partner_record empty here
      tomography_record.self_output = tomography_output;
    } else {
      // Partner record is added, leave self_record empty here
      tomography_record.partner_output = tomography_output;
    }

    // round -> record
    // std::map<int, std::unique_ptr<TomographyRecord>> tomography_round_record;
    std::map<int, TomographyRecord> tomography_round_record;
    tomography_round_record.insert(std::make_pair(tomography_round, tomography_record));
    tomography_records.insert(std::make_pair(partner_key, tomography_round_record));
  } else {
    // Partner key found in the map, add this round of record to the existing parter record.
    // Find i th tomography record
    if (!tomography_records.at(partner_key).count(tomography_round)) {
      // No i th tomography record found
      // Add new tomography record as i th record
      // auto new_tomography_record = std::make_unique<TomographyRecord>();
      TomographyRecord new_tomography_record;
      if (is_self_record) {
        // Self record is added, leave partner_record empty here
        new_tomography_record.self_output = tomography_output;
      } else {
        // Partner record is added, leave self_record empty here
        new_tomography_record.partner_output = tomography_output;
      }
      // Leave partner_record empty here
      tomography_records.at(partner_key).insert(std::make_pair(tomography_round, new_tomography_record));

    } else {
      // i th tomography record found, get reference and update it.
      auto &ith_tomography_record = tomography_records.at(partner_key).at(tomography_round);
      if (is_self_record) {
        // Partner record already exists. Add self record to the existing record.
        ith_tomography_record.self_output = tomography_output;
        // existing_record.setSelfOutput(tomography_output);
      } else {
        // Self record already exists. Add partner record to the existing record.
        ith_tomography_record.partner_output = tomography_output;
      }
    }
  }
};

/// Reconstruct density matrix from tomogrpahy records
/// Data is recorded with qnic_id since there are multiple paths from this node to partner node
/// @param qnic_id
/// @param partner
/// @return density_matrix in Eigen::Matrix4cd
Matrix4cd TomographyManager::reconstructDensityMatrix(int qnic_id, int partner) {
  // Get tomography records for this partner
  if (!tomography_records.count(std::make_tuple(qnic_id, partner))) {
    throw cRuntimeError("Tomography record for this partner is not found.");
  }

  auto partner_key = std::make_tuple(qnic_id, partner);
  // II
  double S00 = 1.0;
  double S01 = getStokesParameter(partner_key, "XX", std::make_tuple('m', 'p', 'm'));
  double S02 = getStokesParameter(partner_key, "YY", std::make_tuple('m', 'p', 'm'));
  double S03 = getStokesParameter(partner_key, "ZZ", std::make_tuple('m', 'p', 'm'));

  // XX
  double S10 = getStokesParameter(partner_key, "XX", std::make_tuple('p', 'm', 'm'));
  double S11 = getStokesParameter(partner_key, "XX", std::make_tuple('m', 'm', 'p'));
  double S12 = getStokesParameter(partner_key, "XY", std::make_tuple('m', 'm', 'p'));
  double S13 = getStokesParameter(partner_key, "XZ", std::make_tuple('m', 'm', 'p'));

  // YY
  double S20 = getStokesParameter(partner_key, "YY", std::make_tuple('p', 'm', 'm'));
  double S21 = getStokesParameter(partner_key, "YX", std::make_tuple('m', 'm', 'p'));
  double S22 = getStokesParameter(partner_key, "YY", std::make_tuple('m', 'm', 'p'));
  double S23 = getStokesParameter(partner_key, "YZ", std::make_tuple('m', 'm', 'p'));

  // ZZ
  double S30 = getStokesParameter(partner_key, "ZZ", std::make_tuple('p', 'm', 'm'));
  double S31 = getStokesParameter(partner_key, "ZX", std::make_tuple('m', 'm', 'p'));
  double S32 = getStokesParameter(partner_key, "ZY", std::make_tuple('m', 'm', 'p'));
  double S33 = getStokesParameter(partner_key, "ZZ", std::make_tuple('m', 'm', 'p'));

  double S = getStokesParameter(partner_key, "XX", std::make_tuple('p', 'p', 'p'));

  Matrix4cd reconstructed_density_matrix = (double)1 / (double)4 *
                                           (S01 * kroneckerProduct(Pauli.I, Pauli.X).eval() +  // IX
                                            S02 * kroneckerProduct(Pauli.I, Pauli.Y).eval() +  // IY
                                            S03 * kroneckerProduct(Pauli.I, Pauli.Z).eval() +  // IZ
                                            S10 * kroneckerProduct(Pauli.X, Pauli.I).eval() +  // XI
                                            S11 * kroneckerProduct(Pauli.X, Pauli.X).eval() +  // XX
                                            S12 * kroneckerProduct(Pauli.X, Pauli.Y).eval() +  // XY
                                            S13 * kroneckerProduct(Pauli.X, Pauli.Z).eval() +  // XZ
                                            S20 * kroneckerProduct(Pauli.Y, Pauli.I).eval() +  // YI
                                            S21 * kroneckerProduct(Pauli.Y, Pauli.X).eval() +  // YX
                                            S22 * kroneckerProduct(Pauli.Y, Pauli.Y).eval() +  // YY
                                            S23 * kroneckerProduct(Pauli.Y, Pauli.Z).eval() +  // YZ
                                            S30 * kroneckerProduct(Pauli.Z, Pauli.I).eval() +  // ZI
                                            S31 * kroneckerProduct(Pauli.Z, Pauli.X).eval() +  // ZX
                                            S32 * kroneckerProduct(Pauli.Z, Pauli.Y).eval() +  // ZY
                                            S33 * kroneckerProduct(Pauli.Z, Pauli.Z).eval() +  // ZZ
                                            S * kroneckerProduct(Pauli.I, Pauli.I).eval());  // II
  return reconstructed_density_matrix;
}

// Altepeter, Joseph B., Evan R. Jeffrey, and Paul G. Kwiat. "Photonic state tomography." Advances in atomic, molecular, and optical physics 52 (2005): 105-159.
double TomographyManager::getStokesParameter(const std::tuple<int, int> partner_key, const std::string basis_combination, const std::tuple<char, char, char> operators) {
  auto tomography_record = tomography_records.at(partner_key);
  if (tomography_record.size() == 0) {
    throw cRuntimeError("No tomography result found.");
  }
  int total_count = 0;
  int plus_plus = 0;
  int plus_minus = 0;
  int minus_plus = 0;
  int minus_minus = 0;
  // Go through all the records and count the number of each outcome
  for (const auto &record : tomography_record) {
    if (record.second.getBasisCombination() == basis_combination) {
      auto self_output = record.second.getSelfOutcome();
      auto partner_output = record.second.getPartnerOutcome();
      // If there is missing record, ignore it and go next record

      if (self_output && partner_output) {
        plus_plus += 1;
      } else if (self_output && !partner_output) {
        plus_minus += 1;
      } else if (!self_output && partner_output) {
        minus_plus += 1;
      } else if (!self_output && partner_output) {
        minus_minus += 1;
      } else {
        throw cRuntimeError("Tomography result unreachable!");
      }
      total_count += 1;
    } else {
      continue;
    }
  }
  if (total_count == 0) {
    throw cRuntimeError("No tomography result found basis for %s. The number of tomography performed for this basis might not be good enough. ", basis_combination.c_str());
  }
  // plus plus
  auto stokes_param = (double)plus_plus / (double)total_count;

  // Currently, the size of operator is limited so that using tuple should be fine.
  // If we have more parameters, we should consider using other ways.
  // plus minus
  if (std::get<0>(operators) == 'p') {
    stokes_param += (double)plus_minus / (double)total_count;
  } else {
    stokes_param -= (double)plus_minus / (double)total_count;
  };

  // minus plus
  if (std::get<1>(operators) == 'p') {
    stokes_param += (double)minus_plus / (double)total_count;
  } else {
    stokes_param -= (double)minus_plus / (double)total_count;
  };

  // minus minus
  if (std::get<2>(operators) == 'p') {
    stokes_param += (double)minus_minus / (double)total_count;
  } else {
    stokes_param -= (double)minus_minus / (double)total_count;
  };
  return stokes_param;
};

RuleSet *TomographyManager::createLinkTomographyRuleSet(int my_address, int partner_address, QNIC_type qnic_type, int qnic_index, unsigned long ruleset_id, int num_purification,
                                                        int purification_type, bool x_purification, bool z_purification, int num_measure) {
  // add rules to this ruleset
  auto *tomography_ruleset = new RuleSet(ruleset_id, my_address);
  int shared_tag = 0;
  std::string rule_name;
  std::vector<int> partners = {partner_address};
  if (num_purification > 0) {
    if (purification_type == 2002) {
      /// # Purification_type 2002: #
      /// - name: Ss-Sp / perfect binary tree, even rounds
      /// - rounds: 2n
      /// - input Bell pairs per round: 2
      /// - total Bell pairs: 2^(2n)
      /// - circuit: Fig. 6.3 in Takaaki's master's thesis
      /// - scheduling: symmetric tree
      /// ## description: ##
      /// Ss-Sp is single selection, single error purification.
      /// Between rounds, Hadamard gates are applied
      /// to switch basis, creating alternating
      /// rounds of X and Z purification.
      ///
      /// The only difference between 2002 and 3003
      /// is the semantics of initial_purification.
      /// Here, each iteration results in two rules,
      /// guaranteeing an even number of rounds.
      ///
      /// X always goes first.
      /// ![](../img/PhysRevA.100.052320-Fig11.png)
      for (int i = 0; i < num_purification; i++) {
        // First stage X purification
        {
          rule_name = "X purification with: " + std::to_string(partner_address);
          auto rule = constructPurifyRule(my_address, rule_name, PurType::SINGLE_X, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::SINGLE_X, partner_address, qnic_type, qnic_index, shared_tag++));
        }
        // Second stage Z purification (Using X purified resources)
        {
          rule_name = "Z purification with: " + std::to_string(partner_address);
          auto rule = constructPurifyRule(my_address, rule_name, PurType::SINGLE_Z, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::SINGLE_Z, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }
    } else if (purification_type == 3003) {
      /// # Purification_type 3003: #
      /// - name: Ss-Sp / perfect binary tree, odd or even rounds
      /// - rounds: n
      /// - input Bell pairs per round: 2
      /// - total Bell pairs: 2^n
      /// - circuit: Fig. 6.3 in Takaaki's master's thesis
      /// - scheduling: perfect binary (symmetric) tree
      /// ## description: ##
      /// Ss-Sp is single selection, single error purification.
      /// Between rounds, Hadamard gates are applied
      /// to switch basis, creating alternating
      /// rounds of X and Z purification.
      ///
      /// The only difference between 2002 and 3003
      /// is the semantics of initial_purification.
      /// Here, each iteration results in one rule,
      /// X for even-numbered rounds (counting from zero),
      /// Z for odd-numbered ones, so it is possible to
      /// do XZX or XZXZX (but not ZXZ or ZXZXZ).
      /// ![](../img/PhysRevA.100.052320-Fig11.png)
      // First stage X purification
      for (int i = 0; i < num_purification; i++) {
        std::unique_ptr<Rule> rule;
        if (i % 2 == 0) {
          rule_name = "X purification with: " + std::to_string(partner_address);
          rule = constructPurifyRule(my_address, rule_name, PurType::SINGLE_X, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::SINGLE_X, partner_address, qnic_type, qnic_index, shared_tag++));
        } else {
          rule_name = "Z purification with: " + std::to_string(partner_address);
          rule = constructPurifyRule(my_address, rule_name, PurType::SINGLE_Z, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::SINGLE_Z, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }
    } else if (purification_type == 1001) {
      /// # Purification_type 1001: #
      /// - name: Ss-Dp XZ Purification
      /// - rounds: n
      /// - input Bell pairs per round: 3
      /// - total Bell pairs: 3^n
      /// - circuit: Fig. 12 in arXiv:1904.08605
      /// - scheduling: symmetric tree
      /// ## description: ##
      /// Both X and Z purification in a single action.  If A
      /// is the pair being purified, and C and E are tools,
      /// CNOT(A,C), MEAS(C), CNOT(E,A), MEAS(E)
      /// then select after comparing outcomes.
      /// Note that bases are not flipped between rounds.
      /// Similar to 1221.
      /// ![](../img/PhysRevA.100.052320-Fig12.png)
      for (int i = 0; i < num_purification; i++) {
        rule_name = "Double purification with: " + std::to_string(partner_address);
        auto rule = constructPurifyRule(my_address, rule_name, PurType::DOUBLE, partner_address, qnic_type, qnic_index, shared_tag);
        tomography_ruleset->addRule(std::move(rule));
        tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DOUBLE, partner_address, qnic_type, qnic_index, shared_tag++));
      }
    } else if (purification_type == 1221) {
      /// # Purification_type 1221: #
      /// - name: Ss-Dp XZ, ZX alternating
      /// - rounds: n
      /// - input Bell pairs per round: 3
      /// - total Bell pairs: 3^n
      /// - circuit: *almost* Fig. 12 from arXiv:1904.08605, but order
      /// of CNOTs reversed in alternating rounds
      /// - scheduling: symmetric tree
      /// ## description: ##
      /// Almost the same as 1001, but first round
      /// is XZ, second round is ZX.  Results in better alternating
      /// error suppression, but still not great.
      /// ![](../img/PhysRevA.100.052320-Fig12.png)
      for (int i = 0; i < num_purification; i++) {
        std::unique_ptr<Rule> rule;
        if (i % 2 == 0) {
          rule_name = "Double purification with: " + std::to_string(partner_address);
          rule = constructPurifyRule(my_address, rule_name, PurType::DOUBLE, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DOUBLE, partner_address, qnic_type, qnic_index, shared_tag++));
        } else {
          rule_name = "Double purification Inverse with: " + std::to_string(partner_address);
          rule = constructPurifyRule(my_address, rule_name, PurType::DOUBLE_INV, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DOUBLE_INV, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }
    } else if (purification_type == 1011) {
      /// # Purification_type 1011: #
      /// - name: Ds-Sp: Fujii-san's Double selection purification
      /// - rounds: n
      /// - input Bell pairs per round: 3
      /// - total Bell pairs: 3^n
      /// - circuit: Fig. 13 in arXiv:1904.08605
      /// - scheduling: symmetric tree
      /// ## description: ##
      /// Similar to 1001 and 1221 except that the control and target
      /// of the first CNOT are flipped, corresponding to Fujii-san's
      /// paper (PRA 80, 042308).
      /// Every round is identical.
      /// Note there is no basis change between rounds.
      /// ![](../img/arxiv.1904.08605-Fig13.png)
      for (int i = 0; i < num_purification; i++) {
        rule_name = "Double Selection with: " + std::to_string(partner_address);
        auto rule = constructPurifyRule(my_address, rule_name, PurType::DSSA, partner_address, qnic_type, qnic_index, shared_tag);
        tomography_ruleset->addRule(std::move(rule));
        tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSSA, partner_address, qnic_type, qnic_index, shared_tag++));
      }
    } else if (purification_type == 1021) {  // Fujii-san's Double selection purification
      /// # Purification_type 1021: #
      /// - name: Ds-Sp: Fujii-san's Double selection purification (alternating)
      /// - rounds: n
      /// - input Bell pairs per round: 3
      /// - total Bell pairs: 3^n
      /// - circuit: *almost* Fig. 13 in arXiv:1904.08605, except that
      /// the order of the CNOTs alternates between rounds
      /// - scheduling: symmetric tree
      /// ## description: ##
      /// Similar to 1011, almost corresponding to Fujii-san's paper (PRA 80,
      /// 042308). Note there is no basis change between rounds, but that the
      /// first round is XZ, second is ZX.
      /// ![](../img/arxiv.1904.08605-Fig13.png)
      for (int i = 0; i < num_purification; i++) {
        std::unique_ptr<Rule> rule;
        if (i % 2 == 0) {
          rule_name = "Double selection with: " + std::to_string(partner_address);
          rule = constructPurifyRule(my_address, rule_name, PurType::DSSA, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSSA, partner_address, qnic_type, qnic_index, shared_tag++));
        } else {
          rule_name = "Double selection Inverse with: " + std::to_string(partner_address);
          rule = constructPurifyRule(my_address, rule_name, PurType::DSSA_INV, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSSA_INV, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }
    } else if (purification_type == 1031) {
      /// # Purification_type 1031: #
      /// - name: Ds-Dp: full double selection purification (alternating)
      /// - rounds: n
      /// - input Bell pairs per round: 5
      /// - total Bell pairs: 5^n
      /// - circuit: Fig. 14 in arXiv:1904.08605, except that
      /// the order of the CNOTs alternates between rounds
      /// - scheduling: symmetric tree
      /// ## description: ##
      /// A combination of 1001 and 1011 (Figs. 12 & 13).  Resource requirements
      /// are high; two rounds of this requires 25 Bell pairs.  With a low base
      /// Bell pair generation rate and realistic memory decoherence, this will
      /// be impractical.
      /// ![](../img/arxiv.1904.08605-Fig14.png)
      for (int i = 0; i < num_purification; i++) {
        std::unique_ptr<Rule> rule;
        if (i % 2 == 0) {
          rule_name = "Double selection Dual action with: " + std::to_string(partner_address);
          rule = constructPurifyRule(my_address, rule_name, PurType::DSDA, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSSA, partner_address, qnic_type, qnic_index, shared_tag++));
        } else {
          rule_name = "Double selection Dual action Inverse with: " + std::to_string(partner_address);
          rule = constructPurifyRule(my_address, rule_name, PurType::DSDA_INV, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSSA_INV, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }
    } else if (purification_type == 1061) {
      /// # Purification_type 1061: #
      /// - name: half double selection, half single selection
      /// - rounds: n
      /// - input Bell pairs per round: 4
      /// - total Bell pairs: 4^n
      /// - circuit: no figure available
      /// - scheduling: symmetric tree
      /// ## description: ##
      /// Does double selection on X, single selection on Z
      /// Switches bases between rounds.
      /// Investigated for possibly highly asymmetric X/Z error rates in base
      /// Bell pairs. Initial results weren't very promised, not extensively
      /// used.
      for (int i = 0; i < num_purification; i++) {
        std::unique_ptr<Rule> rule;
        if (i % 2 == 0) {
          rule_name = "Double selection Dual action second with: " + std::to_string(partner_address);
          rule = constructPurifyRule(my_address, rule_name, PurType::DSDA_SECOND, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSDA_SECOND, partner_address, qnic_type, qnic_index, shared_tag++));
        } else {
          rule_name = "Double selection Dual action second inverse with: " + std::to_string(partner_address);
          rule = constructPurifyRule(my_address, rule_name, PurType::DSDA_SECOND_INV, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(
              constructCorrelationCheckRule("purification correlation check", PurType::DSDA_SECOND_INV, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }
    } else if (purification_type == 5555) {  // Predefined purification method
      /// # Purification_type 5555: #
      /// - name: Switching (B)
      /// - rounds: n
      /// - input Bell pairs per round: 3 in first two rounds, then 2
      /// - total Bell pairs: (complicated)
      /// - circuit: Fig. 21, case B in arXiv:1904.08605
      /// - scheduling: symmetric tree (*)
      /// ## description: ##
      /// Two rounds of Ds-Sp, then Ss-Sp.
      /// The point of this was to show that you don't have to stick with one
      /// scheme, but can use different schemes in different rounds.
      for (int i = 0; i < 2; i++) {
        if (i % 2 == 0) {
          rule_name = "Double selection action with: " + std::to_string(partner_address);
        } else {
          rule_name = "Double selection action inverse with: " + std::to_string(partner_address);
        }
        auto rule = std::make_unique<Rule>(my_address, shared_tag, shared_tag);
        rule->setName(rule_name);
        auto condition = std::make_unique<Condition>();
        auto resource_clause = std::make_unique<EnoughResourceConditionClause>(3, partner_address);
        condition->addClause(std::move(resource_clause));
        rule->setCondition(std::move(condition));
        if (i % 2 == 0) {
          auto purify_action = std::make_unique<Purification>(PurType::DSSA, partner_address, shared_tag);
          rule->setAction(std::move(purify_action));
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSSA, partner_address, qnic_type, qnic_index, shared_tag++));
        } else {
          auto purify_action = std::make_unique<Purification>(PurType::DSDA_INV, partner_address, shared_tag);
          rule->setAction(std::move(purify_action));
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSDA_INV, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }

      for (int i = 0; i < num_purification; i++) {
        std::unique_ptr<Rule> rule;
        if (i % 2 == 0) {
          rule_name = "X Purification with: " + std::to_string(partner_address);
          rule = constructPurifyRule(my_address, rule_name, PurType::SINGLE_X, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::SINGLE_X, partner_address, qnic_type, qnic_index, shared_tag++));
        } else {
          rule_name = "Z Purification with: " + std::to_string(partner_address);
          rule = constructPurifyRule(my_address, rule_name, PurType::SINGLE_Z, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::SINGLE_Z, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }
    } else if (purification_type == 5556) {
      /// # Purification_type 5556: #
      /// - name: Switching (A)
      /// - rounds: n
      /// - input Bell pairs per round: 3 in first round, then 2
      /// - total Bell pairs: (complicated)
      /// - circuit: Fig. 21, case A in arXiv:1904.08605
      /// - scheduling: symmetric tree (*)
      /// ## description: ##
      /// One round of Ds-Sp, then Ss-Sp.
      /// The point of this was to show that you don't have to stick with one
      /// scheme, but can use different schemes in different rounds.
      rule_name = "Double selection action with: " + std::to_string(partner_address);
      auto rule = constructPurifyRule(my_address, rule_name, PurType::DSSA, partner_address, qnic_type, qnic_index, shared_tag);
      tomography_ruleset->addRule(std::move(rule));
      tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::DSSA, partner_address, qnic_type, qnic_index, shared_tag++));

      for (int i = 0; i < num_purification; i++) {
        std::unique_ptr<Rule> rule;
        if (i % 2 == 0) {
          rule_name = "Z purification with: " + std::to_string(partner_address);
          rule = constructPurifyRule(my_address, rule_name, PurType::SINGLE_Z, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::SINGLE_Z, partner_address, qnic_type, qnic_index, shared_tag++));
        } else {
          rule_name = "X purification with: " + std::to_string(partner_address);
          rule = constructPurifyRule(my_address, rule_name, PurType::SINGLE_X, partner_address, qnic_type, qnic_index, shared_tag);
          tomography_ruleset->addRule(std::move(rule));
          tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", PurType::SINGLE_X, partner_address, qnic_type, qnic_index, shared_tag++));
        }
      }
    } else if ((x_purification && !z_purification) || (!x_purification && z_purification)) {
      /// # Purification_type default: #
      /// - name: Boolean-driven (obsolete)
      /// - rounds: 1
      /// - input Bell pairs: 2 or 3
      /// - total Bell pairs: 2 or 3
      /// - circuit: <reference a figure>
      /// - scheduling: (commonly pumping, symmetric tree, or banded)
      /// ## description: ##
      /// uses X_Purification and Z_purification booleans, but is obsolete.
      /// Creates a single purification only, or a single round of double
      /// purification. Use of this for new work is deprecated.
      rule_name = "Single purification with: " + std::to_string(partner_address);
      auto rule = constructPurifyRule(my_address, rule_name, (x_purification ? PurType::SINGLE_X : PurType::SINGLE_Z), partner_address, qnic_type, qnic_index, shared_tag);
      tomography_ruleset->addRule(std::move(rule));
      tomography_ruleset->addRule(constructCorrelationCheckRule("purification correlation check", (x_purification ? PurType::SINGLE_X : PurType::SINGLE_Z), partner_address,
                                                                qnic_type, qnic_index, shared_tag++));
    } else {
      throw cRuntimeError("Invalid purification type.");
    }

    // Let's make nodes select measurement basis randomly, because it it easier.
    auto rule = std::make_unique<Rule>(my_address, shared_tag, shared_tag);
    rule->setName("tomography");

    auto condition = std::make_unique<Condition>();

    // 1 qubit resource required to perform tomography action
    auto res_check_clause = std::make_unique<EnoughResourceConditionClause>(1, partner_address);
    condition->addClause(std::move(res_check_clause));

    // 3000 measurements in total. There are 3*3 = 9 patterns of measurements.
    // So each combination must perform 3000/9 measurements.
    auto measure_count_clause = std::make_unique<MeasureCountConditionClause>(num_measure, partner_address);
    condition->addClause(std::move(measure_count_clause));
    rule->setCondition(std::move(condition));

    // Measure the local resource between it->second.neighborQNode_address.
    auto measure_action = std::make_unique<Tomography>(num_measure, my_address, partner_address);
    measure_action->start_time = simTime();
    rule->setAction(std::move(measure_action));

    tomography_ruleset->addRule(std::move(rule));
  } else {
    // RuleSet with no purification. Pure measurement only link level tomography.

    auto rule = std::make_unique<Rule>(my_address, shared_tag, shared_tag);
    auto condition = std::make_unique<Condition>();
    auto res_check_clause = std::make_unique<EnoughResourceConditionClause>(1, partner_address);
    auto measure_count_clause = std::make_unique<MeasureCountConditionClause>(num_measure, partner_address);
    condition->addClause(std::move(res_check_clause));
    condition->addClause(std::move(measure_count_clause));
    rule->setCondition(std::move(condition));

    // Measure the local resource between it->second.neighborQNode_address.
    auto measure = std::make_unique<Tomography>(num_measure, my_address, partner_address);
    measure->start_time = simTime();
    rule->setAction(std::move(measure));

    tomography_ruleset->addRule(std::move(rule));
  }
  return tomography_ruleset;
}

std::unique_ptr<Rule> TomographyManager::constructPurifyRule(int my_address, const std::string &rule_name, const rules::PurType pur_type, const int partner_address,
                                                             const QNIC_type qnic_type, const int qnic_index, const int send_tag) const {
  int required_qubits = 0;
  switch (pur_type) {
    case PurType::SINGLE_X:
    case PurType::SINGLE_Z:
    case PurType::SINGLE_Y:
      required_qubits = 2;
      break;
    case PurType::DOUBLE:
    case PurType::DOUBLE_INV:
    case PurType::DSSA:
    case PurType::DSSA_INV:
      required_qubits = 3;
      break;
    case PurType::DSDA:
    case PurType::DSDA_INV:
      required_qubits = 5;
      break;
    case PurType::DSDA_SECOND:
    case PurType::DSDA_SECOND_INV:
      required_qubits = 4;
      break;
    case PurType::INVALID:
    default:
      throw cRuntimeError("got invalid purification type");
  }
  auto rule = std::make_unique<Rule>(my_address, send_tag, -1);
  rule->setName(rule_name);
  auto condition = std::make_unique<Condition>();
  auto resource_clause = std::make_unique<EnoughResourceConditionClause>(required_qubits, partner_address);
  condition->addClause(std::move(resource_clause));
  rule->setCondition(std::move(condition));
  auto purify_action = std::make_unique<Purification>(pur_type, partner_address, send_tag);
  rule->setAction(std::move(purify_action));
  return rule;
}

std::unique_ptr<Rule> TomographyManager::constructCorrelationCheckRule(const std::string &rule_name, const rules::PurType pur_type, const int partner_address,
                                                                       const QNIC_type qnic_type, const int qnic_index, const int receive_tag) const {
  auto correlation_rule = std::make_unique<Rule>(partner_address, -1, receive_tag);

  auto condition = std::make_unique<Condition>();
  auto correlation_clause = std::make_unique<PurificationCorrelationClause>(partner_address, receive_tag);
  condition->addClause(std::move(correlation_clause));

  auto action = std::make_unique<PurificationCorrelation>(partner_address, receive_tag);

  correlation_rule->setCondition(std::move(condition));
  correlation_rule->setAction(std::move(action));
  return correlation_rule;
}
}  // namespace quisp::utils
