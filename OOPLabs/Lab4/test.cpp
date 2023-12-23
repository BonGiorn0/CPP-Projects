#include <gtest/gtest.h>
#include <climits>
#include "BigNumber.h"

TEST(int128, Adding){
    CBigNumber b, a(1, ULLONG_MAX);
    long long h;
    unsigned long long l;

    b = a + CBigNumber(1, 10);
    b.getNum(h, l);
    EXPECT_EQ(h, 3);
    EXPECT_EQ(l, 9);

    b = a + 10;
    b.getNum(h, l);
    EXPECT_EQ(h, 2);
    EXPECT_EQ(l, 9);

    b = a + CBigNumber(ULLONG_MAX, 1);
    b.getNum(h, l);
    EXPECT_EQ(h, 1);
    EXPECT_EQ(l, 0);

}

TEST(int128, dis){
    CBigNumber b, a;
    long long h;
    unsigned long long l;

    a.setNum(1, 0);
    b = a - ULLONG_MAX - 2;
    b.getNum(h, l);
    EXPECT_EQ(h, 0);
    EXPECT_EQ(l, ULLONG_MAX);

    b = a - CBigNumber(0, ULLONG_MAX);
    b.getNum(h, l);
    EXPECT_EQ(h, 1);
    EXPECT_EQ(l, 1);
     
     
}

TEST(int128, compare){
    CBigNumber c(0, ULLONG_MAX), b(1, 0), 
                a(1, ULLONG_MAX), a1(1, ULLONG_MAX);

    EXPECT_TRUE(a > b);
    EXPECT_TRUE(a > c);
    
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(a < c);

    EXPECT_TRUE(a == a1);
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(a == c);

}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
