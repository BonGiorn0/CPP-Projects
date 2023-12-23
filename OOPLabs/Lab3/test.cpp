#include <gtest/gtest.h>
#include <climits>
#include "BigNumber.h"

TEST(int128, Adding){
    CBigNumber b, a(1, LLONG_MAX);
    long long l, h;

    b = a.operator+(CBigNumber(1, 10));
    b.getNum(h, l);
    EXPECT_EQ(h, 3);
    EXPECT_EQ(l, 9);

    b = a + 10;
    b.getNum(h, l);
    EXPECT_EQ(h, 2);
    EXPECT_EQ(l, 9);

    b = a + CBigNumber(LLONG_MAX, 1);
    b.getNum(h, l);
    EXPECT_EQ(h, -LLONG_MAX);
    EXPECT_EQ(l, 0);

}

TEST(int128, dis){
    CBigNumber b, a;
    long long l, h;

    a.setNum(1, -2);
    b = a - LLONG_MAX;
    b.getNum(h, l);
    EXPECT_EQ(h, 0);
    EXPECT_EQ(l, 0);

    b = a - CBigNumber(0, LLONG_MAX);
    b.getNum(h, l);
    EXPECT_EQ(h, 0);
    EXPECT_EQ(l, 0);
     
     
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
