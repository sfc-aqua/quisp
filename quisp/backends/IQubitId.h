#pragma once
#include <cstddef>
#include <functional>
#include <iostream>

namespace quisp::backends::abstract {
class IQubitId {
 public:
  virtual ~IQubitId() { std::cout << "IQubitId dtor" << std::endl; };
  virtual std::size_t operator()() const { return 0; };
  virtual std::size_t hash() const = 0;
  virtual bool compare(const IQubitId& id) const = 0;
  virtual bool operator==(const IQubitId& id) const { return compare(id); }
  virtual bool operator==(const IQubitId* id) const { return compare(*id); }
  virtual bool operator==(const std::unique_ptr<IQubitId> id) const { return compare(*id); }
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
};
}  // namespace quisp::backends::abstract
