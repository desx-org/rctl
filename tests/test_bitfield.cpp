#include "rctl/bitfield.hpp"
#include "catch.hpp"

TEST_CASE("Bitfield test", "") 
{
    bitfield<int,2,3,4,5> f1 = {0b0'00001'0001'001'01};

    REQUIRE(f1.raw_val ==  0b00001'0001'001'01);
    //using ranged for loop
    { 

        for(auto i:f1)
        {
            REQUIRE(i == 1);
            i = 2;
            REQUIRE(i == 2);
        }
    
        REQUIRE(f1.raw_val ==  0b00010'0010'010'10);
    
        for(auto i:f1)
        {
            i = 3;
            REQUIRE(i ==  3);
        }    

        REQUIRE(f1.raw_val ==  0b00011'0011'011'11);
    }
    //using normal for loop
    {
        for(int i = 0;i< f1.size();++i)
        {
            REQUIRE(f1[i] == 3);
            f1[i] = 2;
        }
        REQUIRE(f1.raw_val ==  0b00010'0010'010'10);
    }
}
