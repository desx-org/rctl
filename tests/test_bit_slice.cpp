#include "catch.hpp"
#include "fmt/format.h"

#include "rctl/bit_slice.hpp"

struct action_message:public generic_message<0xbe01,9>
{
   action_message():generic_message(){}
   action_message(uint8_t *data_):generic_message(data_){}

   auto lights(){return binary_slice<uint8_t,0,1>(payload());}
   auto camera(){return binary_slice<uint8_t,1,1>(payload());}
   auto action(){return binary_slice<uint8_t,2,6>(payload());}
   auto name()  {return fixed_string<1,8>(payload());}
};

struct curtain_message:public generic_message<0xbe02,10>
{
   curtain_message():generic_message(){}
   curtain_message(uint8_t *data_):generic_message(data_){}

   auto left_curtain_pos(){return binary_slice<uint8_t,0>(payload());}
   auto right_curtain_pos(){return binary_slice<uint8_t,8>(payload());}
   auto riggers_name()    {return fixed_string<2,8>(payload());}
};

TEST_CASE("IP ADDRESS STORAGE TEST", "") 
{
   uint8_t msg_data[100];

   uint8_t * write_ptr = msg_data;

   {
      action_message f1; 
      f1.source_id()      = 0x0f;
      f1.destination_id() = 0xd1;
      f1.lights()         = 0b1;
      f1.camera()         = 0b1;
      f1.action()         = 0b111111;
      f1.name()           = "Mr Bean";
        
      REQUIRE(f1.message_id()     ==    0xbe01);
      REQUIRE(f1.payload_length() ==         9);
      REQUIRE(f1.name()           == "Mr Bean");

      write_ptr += f1.write_to(write_ptr, sizeof(msg_data));
   }
   {
      curtain_message msg; 
      msg.source_id()            = 0x0f;
      msg.destination_id()       = 0xd1;
      msg.left_curtain_pos()     = 50;
      msg.right_curtain_pos()    = 99;
      msg.riggers_name()         = "Bob";

      write_ptr += msg.write_to(write_ptr,sizeof(msg_data) - (write_ptr- msg_data));
   }

   uint8_t * read_ptr = msg_data;
   while(1)
   {
      if(action_message::check(read_ptr))
      {
         action_message f2(read_ptr);

         REQUIRE(f2.source_id()      == 0x0f);
         REQUIRE(f2.destination_id() == 0xd1);
         REQUIRE(f2.lights()         == 0b1);
         REQUIRE(f2.camera()         == 0b1);
         REQUIRE(f2.action()         == 0b000000);
         REQUIRE(f2.name()           == "Mr Bean");

         read_ptr += action_message::i_message_length;
      }
      else if(curtain_message::check(read_ptr))
      {
         read_ptr += curtain_message::i_message_length;
      }
      else
      {
        break; 
      }
   }
}