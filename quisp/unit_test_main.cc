#include <gtest/gtest.h>
#include <omnetpp.h>

int main(int argc, char **argv) {
  /** DO NOT delete this _flag variable.
  * The variable declares that we are in the main function to omnetpp runtime.
  * This ensures the initialization of the omnetpp::cDefaultList which contains
  * whole cObjects. Sometime it causes segmentation fault without the _flag var.
  */
  omnetpp::cStaticFlag _flag;
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
