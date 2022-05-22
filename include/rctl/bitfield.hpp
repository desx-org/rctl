#include <iostream>
using namespace std;

template<typename T,size_t... vals>
struct bitfield;

template<typename T,size_t val>
struct bitfield<T,val>
{
    static size_t last()    
    {
        return val;
    }
    static size_t sum()    
    {
        return val;
    }
    static size_t first()    
    {
        return val;
    }
    static size_t size()
    {
        return 1;
    }
    static size_t nth(int n)
    {
        if (n == 0)
            return val;
        else 
            return 0;
    }
    static size_t nth_sum(int n)
    {
        if (n == 0)
            return val;
        else 
            return 0;
    }
};

template<typename T,size_t val,size_t... vals>
struct bitfield<T,val,vals...>
{
    using this_t = bitfield<T,val,vals...>;
    using curr= bitfield<T,val>; 
    using next = bitfield<T,vals...>; 

    static size_t size()
    {
        return 1 + next::size(); 
    }
    static size_t last()    
    {
        return next::last(); 
    }
    static size_t first()    
    {
        return curr::first(); 
    }
    static size_t sum()
    {
        return curr::sum() + next::sum(); 
    }
    static size_t nth(int n)
    {
        if (n == 0)
            return val;
        else 
        {
            return next::nth(n-1);
        }
    }
    static size_t nth_sum(int n)
    {
        if (n == 0)
            return val;
        else 
        {
            return val + next::nth_sum(n-1);
        }
    }
    static size_t shift_a(int n)
    {
        return n ==0?0:nth_sum(n-1);
    }

    static size_t nth_raw_mask(int n)
    {
        return (~((T)0)) << nth_sum(n);
    }

    static size_t nth_mask(int n)
    {
        if(n==0) return ~nth_raw_mask(n);
        return nth_raw_mask(n-1) & ~nth_raw_mask(n);
    }

    struct ref 
    {
        ref(this_t & p_,int n_):p(p_),n(n_){}

        bool operator == (T other)
        {
            return static_cast<T>(*this) == static_cast<T>(other);
        }
        T operator = (T other)
        {
            p.raw_val = ((other << shift_a(n)) & nth_mask(n)) | (p.raw_val & ~nth_mask(n));
            return other;
        }
        operator T() const
        {
            return (p.raw_val & nth_mask(n))>>shift_a(n);
        }


        friend std::ostream &operator<<(std::ostream &os, this_t::ref const &m) 
        { 
            return os << static_cast<T>(m);
        }

        this_t &p;
        int n;
    };
    struct iterator
    {
        iterator(this_t & p_,int n_):r(p_,n_){}
        ref operator *()
        {
            return r;
        }
        bool operator !=(const iterator & other)
        {
            return r.n != other.r.n;
        }
        iterator operator ++()
        {
            ++r.n; 
            return  *this;
        }
        ref r;
    };
    ref operator[](int index)
    {
        return ref{*this,index};
    }
    iterator begin()
    {
        return iterator(*this,0);
    }
    iterator end()
    {
        return iterator(*this,size());
    }
    T raw_val;
};