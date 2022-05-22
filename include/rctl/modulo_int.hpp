#pragma once

#include <limits>
#include <type_traits>
#include <cstddef>
namespace rctl
{

template<typename T>
constexpr T max_multiple_inv(const T v,const T limit = std::numeric_limits<T>::max())
{
   auto ret = (limit - v + 1)%v;
 
   return ret==0?v:ret;
}
template<typename T>
constexpr bool is_power_of_2(const T val) 
{
   #if 0
   return false;
   #else
   if(val == 1) return true;
   else if((val == 0) || (val & 1)) return false; 
   else return is_power_of_2(val >> 1);
   #endif
}

//*****************************************************************************
///\brief The max multiple of a number within the valid range for an integer 
/// arithmetic type. 
//*****************************************************************************
template<typename T>
constexpr T max_multiple(const T v,const T limit = std::numeric_limits<T>::max())
{
   if (is_power_of_2(v)) 
      return 0;
   else
      return limit - max_multiple_inv(v,limit) + 1;
}
template<typename T>
constexpr T max_multiple_div2(const T v)
{
      return max_multiple(v,(T)(std::numeric_limits<T>::max()>>1));
}


//*****************************************************************************
///\defgroup mod_int modulo integer 
/// An integer where operations are performed modulo a compile time value   
//*****************************************************************************

template<typename INT_TYPE ,INT_TYPE mod_val,bool mark = false>
class mod_int
{
   public:

   using this_t = mod_int<INT_TYPE, mod_val>;

   static constexpr size_t bits = sizeof(INT_TYPE)*8;

   static constexpr INT_TYPE mark_mask = 1 << (bits -1);
   static constexpr INT_TYPE val_mask = static_cast<INT_TYPE>(~mark_mask); 
   
   mod_int():val_(0){};

   INT_TYPE get_mod_val() const
   {
      return mod_val;
   }

   mod_int(INT_TYPE val_in)
   {
      if(!mod_val)
         val_ = val_in;
      else
         val_ = val_in%mod_val;
   };

   enum class mark_t{none,roll,iroll};

   template<mark_t d_mark>
   mod_int adder(this_t incr_val) const
   {
      mod_int ret;

      if constexpr (!mod_val)
      {
         ret = val() + incr_val.val();
      }
      else
      {
         INT_TYPE new_val = (val() + incr_val.val());

         if constexpr(!is_power_of_2(mod_val)) 
         {
            if(new_val < val())
            { 
               new_val += max_multiple_inv(mod_val);
            }
         }

         ret = new_val%mod_val;
      }

      if constexpr (d_mark != mark_t::none)
      {
         ret.val_ |= (val_ & mark_mask);
      }

      if constexpr (d_mark == mark_t::roll)
      {
         if(ret.val() < val())
         { 
            ret.val_ |= mark_mask;
         }
      }
      else if constexpr (d_mark == mark_t::iroll)
      {
         if(ret.val() > val())
         { 
            ret.val_ |= mark_mask;
         }
      }
      return ret;
   }

   mod_int operator + (this_t incr_val) const
   {
      if constexpr (mark)
         return adder<mark_t::roll>(incr_val);
      else
         return adder<mark_t::none>(incr_val);
   }

   mod_int operator - (this_t incr_val) const 
   {
      if constexpr (mark)
         return adder<mark_t::iroll>(-incr_val);
      else
         return adder<mark_t::none>(-incr_val);
   }

   mod_int operator ++ (int)
   {
      auto tmp = *this;
      operator++();
      return tmp;
   }

   mod_int operator -- (int)
   {
      auto tmp = *this;
      operator--();
      return tmp;
   }

   INT_TYPE val() const 
   {
      if constexpr (mark)
         return val_ & val_mask;
      else
         return val_;
   }
   bool rollover_marked()
   {
      if constexpr (mark)
         return (val_ & mark_mask)?true:false;
      else
         return false;

   }

   mod_int operator += (this_t incr_val){return (*this = *this + incr_val);}
   mod_int operator -= (this_t incr_val){ return operator+=(-incr_val);}

   mod_int operator ++ (){return operator+=(1); }
   mod_int operator -- (){return operator-=(1); }

   mod_int operator - () {return mod_val - this->val_;}

   bool operator == (const INT_TYPE val_in) const { return (val_ == val_in); }
   bool operator == (const mod_int val_in) const { return (val_ == val_in.val_);}
   bool operator != (const mod_int val_in) const { return !(val_ == val_in.val_);}
   
   bool operator > (const mod_int val_in) const { return (val_ > val_in.val_);}

   
   private:
   INT_TYPE val_;
};



template<typename T,size_t S>
class mod_index:public mod_int<T,max_multiple_div2<T>(S),true>
{
   public:

   using P = mod_int<T,max_multiple_div2<T>(S),true>;

   mod_index():P(0){}
   mod_index(T v):P(v){}
   mod_index(P v):P(v){}
   using P::val;

   T index()
   {
      return val()%S; 
   }
};
}