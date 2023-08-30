#pragma once

namespace quisp::utils {

/**
 * @brief The TomographyManager interface
 *
 * This interface is used to store tomography results and calcualte fidelity
 * The subclass of this interface provides a general way to access the tomography results.
 */
class ITomographyManager {
 public:
  virtual ~ITomographyManager(){};
  virtual void addLocalResult(int qnic_id, int partner, int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean) = 0;
  virtual void addPartnerResult(int self_qnic_id, int partner, int tomography_round, char measurement_basis, bool is_plus, char my_GOD_clean) = 0;
};
}  // namespace quisp::utils
