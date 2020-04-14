#include<gtest/gtest.h>

TEST(NoError, Test){
    float fidelity;
    fidelity = 1.0;
    EXPECT_EQ(fidelity, 1.0);
}