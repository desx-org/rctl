#pragma once
// Type your code here, or load an example.
#include <array>
#include <cstddef>
#include <vector>

#include "fmt/format.h"

template<typename T>
class data_view
{
   public:
   data_view()
   {

   }
   data_view(T*a,size_t s)
   {
      begin_ = a; 
      end_ = a + s;
   }

   data_view(T*a,T*b)
   {
      begin_ = a; 
      end_ = b;
   }
    
   size_t size()
   {
      if(end_ && begin_)
         return end_ - begin_;
      else
         return 0;
   }
   T * begin(){return begin_;}
   T * end(){return end_;}

   private:
   T* begin_ = nullptr;
   T* end_ = nullptr;
};

template<typename T,size_t s>
class mdata_view 
{
   public:
   mdata_view(){}
   mdata_view(std::array<data_view<T>,s> v):data_(v)
   {

   }
   size_t size()
   {
      size_t sum = 0;
      for(auto i:data_)sum+=i.size();
      return sum;
   }
   size_t block_cnt()
   {
      return data_.size();
   } 
   data_view<T>& operator[](int i)
   {
      return data_[i];
   }
   std::vector<T> to_vec()
   {
      std::vector<T> ret((int)size());
      auto tmp = ret.begin();
      for(auto i :data_)
      {
         tmp = std::copy(i.begin(),i.end(),tmp);
      }
      return ret;
   }

   size_t copy_to(T * data)
   {
      mdata_view<T,1> tmp;
      tmp[0] = {data,size()};
      return copy_to(tmp);
   }
   void pnt()
   {
      fmt::print("mdata:\n");
      for(auto i :data_)
      {
         fmt::print("{}\n",i.size());
      }
   }
   template<size_t S2>
   size_t copy_to(mdata_view<T,S2> & dst)
   {

      size_t src_index= 0;
      size_t src_offset = 0;
      size_t dst_index = 0;
      size_t dst_offset = 0;
      

      while((src_index != block_cnt()) &&  (dst_index != dst.block_cnt()))
      {
         size_t src_size  = data_[src_index].size() - src_offset;
         size_t dst_size  = dst[dst_index].size() - dst_offset;

         //fmt::print("SRC idx: {} offset: {} size: {}\n",src_index, src_offset, src_size);
         //fmt::print("DST idx: {} offset: {} size: {}\n",dst_index, dst_offset, dst_size);
         if(src_size >= dst_size)
         {
            std::copy
            (
               data_[src_index].begin() + src_offset,
               data_[src_index].begin() + src_offset + dst_size,
               dst[dst_index].begin() + dst_offset
            );
            ++dst_index; 
            dst_offset = 0;
            if(src_size == dst_size)
            {
               ++src_index; 
               src_offset = 0;
            }
            else
            {
               src_offset += dst_size;  
            }
         }
         else
         {
            std::copy
            (
               data_[src_index].begin() + src_offset,
               data_[src_index].end(),
               dst[dst_index].begin() + dst_offset
            );
            dst_offset = data_[src_index].size();
            ++src_index; 
            src_offset = 0;
         }
      }

      size_t written = 0;
      #if 0
      for(auto i:data_)
      {
         auto res = std::copy(i.begin(),i.end(),dst+written);
         written += (res - i.begin());
      }
      #endif
      return written;
   }
   data_view<T> & operator[](size_t v)
   {
      return data_[v]; 
   }

   template <class U , std::size_t N, std::size_t... I> 
   constexpr std::array<std::remove_cv_t<U>, N> to_array_impl(U (&&a)[N], std::index_sequence<I...>)
   {
      return { {std::move(a[I])...} };
   }
   
   template <class U = data_view<T>, std::size_t N>
   constexpr std::array<std::remove_cv_t<U>, N> copy_tx(U (&&a)[N])
   {
      auto ret = to_array_impl(std::move(a), std::make_index_sequence<N>{});

      mdata_view<T,N> alt(ret);

      fmt::print("s:{}:{}\n",alt.block_cnt(), alt[0].size());

      copy_to(alt);

      return ret;
   }

   private:

   std::array<data_view<T>,s> data_;
};


