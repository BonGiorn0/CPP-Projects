#include <gtest/gtest.h>
#include <cmath>
#include "function.h"

TEST(LinearEquasion, CommonInput){
    EXPECT_EQ(SolveLinearEquation(5, 10), -2);
    EXPECT_EQ(SolveLinearEquation(5, 6665), -1333);
    EXPECT_EQ(SolveLinearEquation(10, -10), 1);
    EXPECT_EQ(SolveLinearEquation(10, -1), 0.1);
    EXPECT_EQ(SolveLinearEquation(10, 0), 0);
    
}

TEST(Equasion, ZeroA){
    EXPECT_EQ(SolveLinearEquation(0, -10), INFINITY);   
    EXPECT_EQ(SolveLinearEquation(0, 110), -INFINITY);   
    EXPECT_TRUE(
        std::isnan(SolveLinearEquation(0, 0))
    );
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
