#pragma once
#include <cstddef>
#include <functional>

namespace quisp::backends::abstract {

/**
 * @brief a key to identify a qubit in a backend.
 *
 * Inherit this class and add your own fields to it.
 * This class is used like `unoredered_map<const IQubitId*, unique_ptr<SomeQubit>, IQubitId::Hash, IQubitId::Pred>`
 * see also the existing backend implementations.
 */
class IQubitId {
 public:
  virtual ~IQubitId(){};

  class Hash {
   public:
    std::size_t operator()(const IQubitId& id) const { return id.hash(); }
    std::size_t operator()(const IQubitId* id) const { return id->hash(); }
  };
  class Pred {
   public:
    bool operator()(const IQubitId& id1, const IQubitId& id2) const { return id1.compare(id2); }
    bool operator()(const IQubitId* id1, const IQubitId* id2) const { return id1->compare(*id2); }
  };

 protected:
  /**
   * a hash function for unordered_map. this function should return a unique value for each qubit id.
   */
  virtual std::size_t hash() const = 0;

  /**
   * a comparison function for unordered_map.
   */
  virtual bool compare(const IQubitId& id) const = 0;
};
}  // namespace quisp::backends::abstract
