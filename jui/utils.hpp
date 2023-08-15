#pragma once

template<typename T,size_t POW>
struct jfifo
{
    T sigs[1<<POW] = {};

    uint32_t cnt = 0;
    uint32_t ack = 0;

    void push(T v){sigs[(cnt++)%5] = v;}
    bool get(T & v)
    {
        if((cnt - ack)==0) return false;
        v = sigs[(ack++)%5];
        return true;
    }
};