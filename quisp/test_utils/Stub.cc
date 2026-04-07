#include "Stub.h"

Stub::Stub() {
  setComponentType(new TestModuleType("stub"));
  auto *sim = quisp_test::utils::getTestSimulation();
  sim->registerComponent(this);
}
