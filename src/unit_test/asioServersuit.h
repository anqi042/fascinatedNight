#include <cxxtest/TestSuite.h>
#include "msgStruct.hpp"

class AsioServerSuit1: public CxxTest::TestSuite
{
     public:
         void test_encode()
         {
             BigDickMsg bdmsg;
             TS_ASSERT_EQUALS(0, bdmsg.encode(2, NULL, 512, 1234));    
         }
};
