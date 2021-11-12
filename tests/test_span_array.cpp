#include "rctl/span_array.hpp"
#include "fmt/format.h"
#include <catch.hpp>
#include <vector>

TEST_CASE("aix buffer test","")
{
   SECTION("mdata_view test")
   {
      mdata_view<uint8_t,2> f;
      std::vector<uint8_t> tst_set = {0,1,2,3,4,5,6,7,8,9};
   }
   SECTION("data view tests")
   {
#if 0
      {

      mdata_view<char,2> d1;

      char a[5] = {'a','b','c','d','e'};
      char b[3] = {'f','g','h'};

      d1[0] = {a, sizeof(a)};
      d1[1] = {b, sizeof(b)};

      REQUIRE(d1.to_vec() == std::vector<char>{'a','b','c','d','e','f','g','h'});

      mdata_view<char,3> d2;

      char c[2];
      char d[3];
      char e[3];

      d2[0] = {c,sizeof(c)};
      d2[1] = {d,sizeof(d)};
      d2[2] = {e,sizeof(e)};
      d1.copy_to(d2);

      REQUIRE(d2.to_vec() == std::vector<char>{'a','b','c','d','e','f','g','h'});

      mdata_view<char,1> d3;

      char f[3];
      d3[0] = {f,sizeof(f)};

      d1.copy_to(d3);
      REQUIRE(d3.to_vec() == std::vector<char>{'a','b','c'});
      }
#endif
      {
         mdata_view<char,3> d1;
   
         char a[] = {'a','b'};
         char b[] = {'c','d','e'};
         char c[] = {'f','g','h'};
   
         d1[0] = {a,sizeof(a)};
         d1[1] = {b,sizeof(b)};
         d1[2] = {c,sizeof(c)};
   
         char v[] = {'x','y','z'};
         d1.copy_tx({{v,sizeof(v)}});
         
         //REQUIRE(std::to_array(v) == std::to_array<char>({'a','b','c'}));
      }
   }
}
