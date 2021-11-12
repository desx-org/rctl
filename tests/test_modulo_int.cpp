#include "rctl/modulo_int.hpp"
#include "fmt/format.h"
#include "catch.hpp"

#include <experimental/array>
#include <vector>

using namespace rctl;

TEST_CASE("mod int test","")
{
   SECTION("is power of 2 test")
   {   
      REQUIRE(is_power_of_2<uint8_t>(1 ) == true); 
      REQUIRE(is_power_of_2<uint8_t>(2 ) == true); 
      REQUIRE(is_power_of_2<uint8_t>(4 ) == true); 
      REQUIRE(is_power_of_2<uint8_t>(8 ) == true); 
      REQUIRE(is_power_of_2<uint8_t>(16) == true); 
      REQUIRE(is_power_of_2<uint8_t>(32) == true); 
      REQUIRE(is_power_of_2<uint8_t>(64) == true); 
      REQUIRE(is_power_of_2<uint8_t>(128) == true); 

      REQUIRE(is_power_of_2<uint8_t>(  0) == false); 
      REQUIRE(is_power_of_2<uint8_t>(  3) == false); 
      REQUIRE(is_power_of_2<uint8_t>(  5) == false); 
      REQUIRE(is_power_of_2<uint8_t>(  6) == false); 
      REQUIRE(is_power_of_2<uint8_t>(  7) == false); 
      REQUIRE(is_power_of_2<uint8_t>(  9) == false); 
      REQUIRE(is_power_of_2<uint8_t>( 10) == false); 
      REQUIRE(is_power_of_2<uint8_t>( 11) == false); 
      REQUIRE(is_power_of_2<uint8_t>( 12) == false); 
      REQUIRE(is_power_of_2<uint8_t>( 13) == false); 
      REQUIRE(is_power_of_2<uint8_t>( 14) == false); 
      REQUIRE(is_power_of_2<uint8_t>( 33) == false); 
      REQUIRE(is_power_of_2<uint8_t>(255) == false); 

   }
   SECTION("max multiple test")
   {   
      //REQUIRE(max_multiple<uint8_t>(  0) ==   0);//floating point error signal
      REQUIRE(max_multiple<uint8_t>(  1) ==   0);
      REQUIRE(max_multiple<uint8_t>(  2) ==   0);
      REQUIRE(max_multiple<uint8_t>(  3) == 255);
      REQUIRE(max_multiple<uint8_t>(  4) ==   0);
      REQUIRE(max_multiple<uint8_t>(  5) == 255);
      REQUIRE(max_multiple<uint8_t>(  6) == 252);
      REQUIRE(max_multiple<uint8_t>(  7) == 252);
      REQUIRE(max_multiple<uint8_t>(  8) ==   0);
      REQUIRE(max_multiple<uint8_t>(  9) == 252);
      REQUIRE(max_multiple<uint8_t>( 10) == 250);
      REQUIRE(max_multiple<uint8_t>(100) == 200);
      REQUIRE(max_multiple<uint8_t>(200) == 200);
      REQUIRE(max_multiple<uint8_t>(250) == 250);
      REQUIRE(max_multiple<uint8_t>(255) == 255);
   }
   SECTION("test mod int")
   {   
      mod_int<uint8_t, 10> v = 4;
      auto b = ++v;
      REQUIRE(b == 5); 
      auto c = v++;
      REQUIRE(c == 5); 

      REQUIRE(v == 6); 
      v+=1;
      REQUIRE(v == 7); 
      v+=2;
      REQUIRE(v == 9); 
      v+=1;
      REQUIRE(v == 0); 
      v+=10;
      REQUIRE(v == 0); 
      v=9;
      REQUIRE(v == 9); 
      v+=250;
      REQUIRE(v == 9); 
      v+=255;
      REQUIRE(v == 4); 
      auto y =v + 1;
      REQUIRE(v == 4); 
      REQUIRE(y == 5); 
      v-=1;
      REQUIRE(v.val() == 3); 
      v-=3;
      REQUIRE(v.val() == 0); 
      v-=2;
      REQUIRE(v.val() == 8); 
      v-=10;
      REQUIRE(v.val() == 8); 
      v-=20;
      REQUIRE(v.val() == 8); 
      v-=250;
      REQUIRE(v.val() == 8); 
      mod_int<uint8_t, 0> q = 4;
      REQUIRE(q.val() == 4); 
      q +=251;
      REQUIRE(q.val() == 255);
      q +=1;
      REQUIRE(q.val() == 0); 
      q =1; 
      q += 255;
      REQUIRE(q.val() == 0); 

      mod_int<uint8_t, 10> r = 4;
      r += 255;
      REQUIRE(r.val() == 9);
      REQUIRE(r.val() == 9); 
      r = 9;
      r += 255;
      REQUIRE(r.val() == 4);
      {  
         mod_int<uint8_t, 10> v = 0;
         v-=2;
         REQUIRE(v.val() == 8);
      }
      mod_int<uint32_t, 10> ss = 1;

      REQUIRE(ss.val() == 1);
      ss = -ss;
      REQUIRE(ss.val() == 9);
      ss = 10;
      REQUIRE(ss.val() == 0);

   }
   SECTION("mod index test")
   {
      mod_index<uint8_t,5>  f1 = (uint8_t)22;
      REQUIRE(f1.val() == 22);
      REQUIRE(f1.index() == 2);
      f1++; 
      REQUIRE(f1.val() == 23);
      REQUIRE(f1.index() == 3);
      ++f1; 
      REQUIRE(f1.val() == 24);
      REQUIRE(f1.index() == 4);
      ++f1; 
      REQUIRE(f1.val() == 25);
      REQUIRE(f1.index() == 0);
      f1+=10; 
      REQUIRE(f1.val() == 35);
      REQUIRE(f1.index() == 0);
      f1+=100; 
      REQUIRE(f1.val() == 135);
      REQUIRE(f1.index() == 0);
      f1+=1; 
      REQUIRE(f1.val() == 136);
      REQUIRE(f1.index() == 1);
      f1+=110; 
      REQUIRE(f1.val() == 246);
      REQUIRE(f1.index() == 1);
      f1+=10; 
      REQUIRE(f1.val() ==   1);
      REQUIRE(f1.index() == 1);
      f1-=10; 
      REQUIRE(f1.val() == 246);
      REQUIRE(f1.index() == 1);
   }
}