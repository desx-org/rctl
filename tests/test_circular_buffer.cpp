#include "rctl/modulo_int.hpp"
#include "rctl/circular_buffer.hpp"

#include "fmt/format.h"
#include "catch.hpp"

#include <experimental/array>
#include <vector>

using namespace rctl;

TEST_CASE("circular buffer test","")
{
  SECTION("basice circular buffer test")
  {
      circular_buffer<uint8_t,2> b1;
      auto t1 = b1.current();

      b1.buffer[0] = 100;
      b1.buffer[1] = 101;

      REQUIRE(*t1 == 100);
      REQUIRE(*++t1 == 101);
      REQUIRE(*t1++ == 101);
      REQUIRE(*t1 == 100);
  }
  SECTION("basice circular buffer test size 8")
  {
      circular_buffer<uint8_t,8> b1 = {};
      auto t1 = b1.current();

      b1.buffer[0] = 100;
      b1.buffer[1] = 101;
      b1.buffer[2] = 102;
      b1.buffer[3] = 103;
      b1.buffer[4] = 104;
      b1.buffer[5] = 105;
      b1.buffer[6] = 106;
      b1.buffer[7] = 107;

      //REQUIRE((int)*t1 == 100);
      //REQUIRE((int)*++t1 == 101);
      //REQUIRE((int)*t1++ == 101);
      //REQUIRE((int)*t1 == 102);
  }
}