#include "rctl/pp_utils.h"
#include "fmt/format.h"
#include <catch.hpp>
#include <vector>
using namespace fmt;
using namespace std;

#define DO_THING(NUM,ITM) val[ITM] = NUM;

#define CNT 64
TEST_CASE("pp utils test","")
{
    int val[CNT];

      int 
      a0=0x00,b0=0x01,c0=0x02,d0=0x03,e0=0x04,f0=0x05,g0=0x06,h0=0x07,
      a1=0x08,b1=0x09,c1=0x0a,d1=0x0b,e1=0x0c,f1=0x0d,g1=0x0e,h1=0x0f,
      a2=0x10,b2=0x11,c2=0x12,d2=0x13,e2=0x14,f2=0x15,g2=0x16,h2=0x17,
      a3=0x18,b3=0x19,c3=0x1a,d3=0x1b,e3=0x1c,f3=0x1d,g3=0x1e,h3=0x1f,
      a4=0x20,b4=0x21,c4=0x22,d4=0x23,e4=0x24,f4=0x25,g4=0x26,h4=0x27,
      a5=0x28,b5=0x29,c5=0x2a,d5=0x2b,e5=0x2c,f5=0x2d,g5=0x2e,h5=0x2f,
      a6=0x30,b6=0x31,c6=0x32,d6=0x33,e6=0x34,f6=0x35,g6=0x36,h6=0x37,
      a7=0x38,b7=0x39,c7=0x3a,d7=0x3b,e7=0x3c,f7=0x3d,g7=0x3e,h7=0x3f 
      ;

    SECTION("basic test")
    {
      #if 0
      FOR_EACH(DO_THING,
      ,a0,b0,c0,d0,e0,f0,g0,h0
      ,a1,b1,c1,d1,e1,f1,g1,h1
      ,a2,b2,c2,d2,e2,f2,g2,h2
      ,a3,b3,c3,d3,e3,f3,g3,h3
      ,a4,b4,c4,d4,e4,f4,g4,h4
      ,a5,b5,c5,d5,e5,f5,g5,h5
      ,a6,b6,c6,d6,e6,f6,g6,h6
      ,a7,b7,c7,d7,e7,f7,g7
      );
      for(int i = 0; i < 24;i++)
      {
        REQUIRE(val[i] == i);
      }
      #endif
    }
}