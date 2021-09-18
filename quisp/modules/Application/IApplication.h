#ifndef MODULES_IAPPLICATION_H_
#define MODULES_IAPPLICATION_H_

#include <omnetpp.h>

using namespace omnetpp;

namespace quisp {
namespace modules {

class IApplication : public cSimpleModule {
 public:
  virtual ~IApplication(){};
};

}  // namespace modules
}  // namespace quisp

#endif /* MODULES_IAPPLICATION_H_ */
