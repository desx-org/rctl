#pragma once

#include <array>
#include <cstddef>

#include "modulo_int.hpp"
#include "span_array.hpp"
namespace rctl
{
template<typename T, size_t S,typename idx_t = uint32_t>
class circular_buffer_base;


template<typename T, size_t S,typename idx_t >
class circular_buffer_base 
{
   public:

   size_t size(){return S;}

   using idx = rctl::mod_index<idx_t,S>;

   using dta2x = mdata_view<T,2>;

   using this_t = circular_buffer_base<T,S,idx_t>;

   struct iterator;
   struct iterator_ro;

   struct iterator_ro:public idx
   {
      iterator_ro(iterator & base_,idx_t start):base_it(base_),idx(base_it.val()){}
      iterator & base_it;
      T & operator *()
      {
         return base_it.base_buffer.buffer[idx::index()];
      }
      iterator begin()
      {
         return iterator(base_it.base_buffer,base_it.val());
      }
      iterator end()
      {
         return base_it;
      }
   };

   struct iterator:public idx
   {
      iterator(this_t & base_,idx_t start):base_buffer(base_),idx(start){}

      this_t & base_buffer;

      T & operator *()
      {
         return base_buffer.buffer[idx::index()];
      }

      iterator_ro new_reader()
      {
         return iterator_ro(*this,idx::val());
      }
   };

   iterator begin()
   {
      return iterator(*this,0);
   }
   iterator end()
   {
      return iterator(*this,(idx_t)S);
   }

   constexpr static idx first_index() {return 0;}
   dta2x get_dataview(idx begin ,idx end)
   {
      dta2x ret;
      if(begin.index() <= end.index())
      {
         ret[0] = {buffer.data() + begin.index(),buffer.data() + end.index()};
      }
      else
      {
         ret[0] = {buffer.data() + begin.index(),buffer.data() + size()};
         ret[1] = {buffer.data()                ,buffer.data() + end.index()};
      }
      return ret;
   }
   void insert(T * itm, size_t cnt, idx pos)
   {
      buffer[pos.index()] = itm;
   }
   T & operator[](idx pos)
   {
      return buffer[pos.index()];
   }
   T & get(idx pos)
   {
      return buffer[pos.index()];
   }
   dta2x  get(idx a,idx b)
   {
      dta2x ret;

      if ((b - a) > size())
      {
         a = b - size();
      }

      if(a == b) 
      {
         return ret; 
      }
      else if(a.index() < b.index())
      {
         ret[0] = {&buffer[a.index()],&buffer[b.index()]}; 
      }
      else
      {

         ret[0] = {&buffer[a.index()],&buffer[size()]}; 
         ret[1] = {&buffer[        0],&buffer[b.index()]}; 

      }
      return ret;
   }

   std::array<T, S> buffer;

};

template<typename T,size_t S>
class buffer_loc
{
   using base_buff_t = circular_buffer_base<T,S>;
   //buffer_loc(base_buff_t & buff_):buff(buff_){}

   //base_buff_t & buff;
};

template<typename T, size_t S, typename idx_t = uint32_t>
class circular_buffer:public circular_buffer_base<T, S>
{
   using cir_buff =  circular_buffer<T,S,idx_t>;
   public:
   circular_buffer():circular_buffer_base<T,S,idx_t>()
   {

   }
   using idx = rctl::mod_index<idx_t,S>;

   //T & location(int location)
   //{
   //   return buffer[(added + location).index()];
   //}

   //template<typename T, size_t S,typename idx_t>
   class iterator:public idx
   {
      public:
      iterator(cir_buff & p_):p(p_),idx(p.added){}
      iterator(cir_buff & p_, idx idx_in):p(p_),idx(idx_in){}

      T & operator *()
      {
         return p.buffer[idx::index()];
      } 
      iterator operator ++(){idx::operator++();return *this;}
      iterator operator ++(int){auto tmp = *this;idx::operator++();return tmp;}
      private:
      cir_buff & p;
   };

   iterator current()
   {
      return iterator(*this);
   }


   idx added;
};

}