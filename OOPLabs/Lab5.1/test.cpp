#include "googletest/"

#include "CSet.hpp"

TEST(CSet, all){
    CSet a, b, c;

    a.Add(5);
    a.Add(3);
    a.Add(1);
    a.Add(4);

    EXPECT_TRUE(a.Has(5)):
    EXPECT_TRUE(a.Has(3)):
    EXPECT_TRUE(a.Has(1)):
    EXPECT_TRUE(a.Has(4)):

    a.Add(-96);
    a.Add(-333);
    a.Delete(-96);
    a.Delete(-333);

    EXPECT_FALSE(a.Has(-96))
    EXPECT_FALSE(a.Has(-333))

    b.Add(3);
    b.Add(1);
    b.Add(104);

    c = a + b;
    EXPECT_TRUE(c.Has(5)):
    EXPECT_TRUE(c.Has(3)):
    EXPECT_TRUE(c.Has(1)):
    EXPECT_TRUE(c.Has(4)):
    EXPECT_TRUE(c.Has(104)):

}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
