#pragma once

#include <type_traits>
#include <arpa/inet.h>

using namespace fmt;

template<typename T>
static T constexpr mask(size_t dbits)
{
   using UT = typename std::make_unsigned<T>::type;
   return static_cast<T>( (static_cast<UT>(1) << dbits) -1);
}

template<typename T>
static T gen_ntoh(T val)
{
   if constexpr (sizeof(T) == 1) 
      return val ;
   else if constexpr (sizeof(T) == 2) 
      return ntohs(val);
   else if constexpr (sizeof(T) == 4) 
      return ntohl(val);
   else if constexpr (sizeof(T) == 8) 
      return ntohll(val);
   else
      return 0;
}

template<typename T>
static T gen_hton(T val)
{
   if constexpr (sizeof(T) == 1) 
      return val ;
   else if constexpr (sizeof(T) == 2) 
      return htons(val);
   else if constexpr (sizeof(T) == 4) 
      return htonl(val);
   else if constexpr (sizeof(T) == 8) 
      return htonll(val);
   else 
      return 0;
}

template<size_t dst_offset, size_t src_offset, size_t bits>
struct binary_copy
{
   template<typename dst_t,  typename src_t> 
   static void rcopy(dst_t * dst, const src_t * src)
   {
      binary_copy<src_offset,dst_offset,bits>::copy(dst,src);
   }
   
   template<typename dst_t,  typename src_t>
   static void copy(dst_t * dst, const src_t * src)
   {
      static constexpr size_t src_sz = sizeof(src_t) * 8;
      static constexpr size_t dst_sz = sizeof(dst_t) * 8; 
      static constexpr auto end_offset = src_offset + bits;

      size_t src_loc = src_offset;
      size_t dst_loc = dst_offset;

      while(src_loc < end_offset)
      {
         auto src_bits = src_loc%src_sz;
         auto dst_bits = dst_loc%dst_sz;

         auto mv_bits = std::min(src_sz - src_bits, dst_sz - dst_bits);
         mv_bits = std::min(mv_bits, end_offset - src_loc);

         const 
         src_t * src_ptr = src + src_loc / src_sz; 
         dst_t * dst_ptr = dst + dst_loc / dst_sz; 

         auto src_val = static_cast<dst_t>(((*src_ptr >> src_bits) & mask<src_t>(mv_bits)));

         *dst_ptr &= (mask<dst_t>(dst_bits)  | ~mask<dst_t>(dst_bits+mv_bits)); 
         *dst_ptr |= (src_val << dst_bits); 

         src_loc += mv_bits;
         dst_loc += mv_bits;
      }
   }
};

template<typename T,size_t offset, size_t bits=sizeof(T)*8>
struct binary_slice
{
    binary_slice(uint8_t* data_):data(data_){}

    T operator = (T val)
    {
        T tmp_val = gen_hton(val);
        binary_copy<offset,0,bits>::copy(data,&tmp_val);
        return val;
    }
    template<typename U>
    bool operator == (U other) const
    {
      return operator T() == static_cast<T>(other);
    }

    template<typename U>
    bool operator != (U other) const
    {
      return operator T() != static_cast<T>(other);
    }

    operator T() const
    {
        T ret = 0;
        binary_copy<0,offset,bits>::copy(&ret,data);
        return gen_ntoh(ret);
    }

    private:

    uint8_t * data; 
};

template <size_t offset, size_t size>
class fixed_string
{
    public:
    fixed_string(uint8_t * val_):val((char*)val_)
    {
    }

    char * operator()() const { return begin(); }
    char * begin()      const { return val+offset;  }
    char * end()        const { return val+offset+size; }
    char * back()       const { return end() - 1;}
    operator char*()          { return begin();}

    const char * operator = (const char* str_in)
    {
        strncpy(begin(),str_in,size);
        *back() = '\0';
        return begin();
    }
    bool operator == (const char* str_in) const
    {
        return strncmp(begin(),str_in,size) == 0;
    }

    char * val;
};

struct generic_header 
{
   generic_header(uint8_t *data_):data(data_){}

   static constexpr size_t i_header_length = 8;

   auto message_id()    {return binary_slice<uint16_t , 0>(data);}
   auto source_id()     {return binary_slice<uint8_t  ,16>(data);}
   auto destination_id(){return binary_slice<uint8_t  ,24>(data);}
   auto payload_length(){return binary_slice<uint32_t ,32>(data);}

   uint8_t * data;
};

template<uint16_t message_id_ ,uint32_t payload_length_>
struct generic_message:public generic_header
{
   static constexpr size_t   i_payload_length  = payload_length_;
   static constexpr size_t   i_message_length  = i_header_length + i_payload_length;
   static constexpr uint16_t i_message_id      = message_id_;

   generic_message():generic_header(i_data)
   {
      memset(i_data,0,i_message_length);
      message_id()      = i_message_id ;
      payload_length()  = i_payload_length;
   }

   generic_message(uint8_t*data_):generic_header(data_)
   {
      std::copy(data_,data_+i_message_length,i_data);
   }

   static bool check(uint8_t* data_,size_t size_ = i_message_length)
   {
      if(size_ < i_header_length) return false;
      
      generic_header h1(data_);
      return (h1.message_id() == i_message_id)&&(h1.payload_length() == i_payload_length);
   }

   uint8_t i_data[i_message_length];
   uint8_t * payload(){return i_data + i_header_length; }

   size_t write_to(uint8_t * buffer,size_t size_)
   {
      if(size_ >= i_message_length)
      {
         std::copy(buffer,buffer + i_message_length, i_data);
         return i_message_length;
      }
      return 0;
   }
};
