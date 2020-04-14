#include<iostream>
#include<fstream>
#include<gtest/gtest.h>


TEST(NoError, Test){
float fidelity;
fidelity = 1.0;
EXPECT_EQ(fidelity, 1.0);
}

// int main(){
//     std::ifstream ifs("./testresult.txt");
//     int line_num = 1;
//     std::string line;
//     while (getline(ifs,line)){
//         std::cout << line_num << ":" << line << std::endl;
//         line_num += 1;
//   }
// }
