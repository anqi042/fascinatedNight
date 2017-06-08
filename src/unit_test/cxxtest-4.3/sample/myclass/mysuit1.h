#include <cxxtest/TestSuite.h>
#include "myclass1.h"

class MySuit1: public CxxTest::TestSuite
{
    public:
        void test_comp(void)
        {
            MyClass1 a(1);
            TS_ASSERT_EQUALS(0, a.big_than_ten());
            MyClass1 b(11);
            TS_ASSERT_EQUALS(0, b.big_than_ten());
            MyClass1 c(12);
            TS_ASSERT_EQUALS(0, c.big_than_ten());
        }
};
