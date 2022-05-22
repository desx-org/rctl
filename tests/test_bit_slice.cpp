
template<typename...slices>
struct parent_msg
{
parent_msg()
  template<typename T,size_t index>
  bit_slice<T> get_val
  {

  }
  template<typename T,size_t index>
  char * get_str
  {

  }
buffer_index_ref buff_;
};
struct stage_status:
  public parent_msg<1,1,6,9*8>
{
  stage_status(buffer_index_ref buff_):parent_msg(buff_){}

  auto lights() {return get_val<uint8_t,0>();}
  auto camera() {return get_val<uint8_t,1>();}
  auto action() {return get_val<uint8_t,2>();}
  auto name()   {return get_str<uint8_t,3>();}
};



TEST_CASE("circular buffer test","")
{
  circular_buffer<uint8_t,100> tx_buff;
  SECTION("basice circular buffer test")
  {
    {
      stage_status s1(tx_buff.end().view());

      s1.lights() = 1;
      s1.camera() = 2;
      s1.action() = 99;
      s1.name() = "dave";

      tx_buff.push(s1.size());
    }
    auto inp_rear = tx_buf.begin();

    circular_buffer<uint8_t,100> rx_buff;
    rx_buf.intrusive_copy_from(inp_rear);
    auto rx_rear = rx_buf.end();
    {
      while(1)
      {
        stage_status ::process(rx_rear,[](){
          REQUIRE(m1.lights() == 1);
          REQUIRE(m1.camera() == 2);
          REQUIRE(m1.action() == 99);
          REQUIRE(m1.name() == "dave");
        });

        if(stage_status m1{rx_rear.view()};m1.valid())
        {
          REQUIRE(m1.lights() == 1);
          REQUIRE(m1.camera() == 2);
          REQUIRE(m1.action() == 99);
          REQUIRE(m1.name() == "dave");
          rx_rear.push(m1.size());
        }
        else if(curtain_status::valid(rx_rear.view()))
        {
        }
        else
        {
          //more conditions....
        }
      }


    }

  }
}