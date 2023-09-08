//#include "editor.hpp"

#include "fmt/format.h"
#include <iostream>
#include "fmt/core.h"
#include "fmt/xchar.h"
#include <catch2/catch_test_macros.hpp>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <inttypes.h>
#include <locale>
#include "editor.hpp"
using namespace fmt;

#include <list>
#include <vector>

auto box0 = R"(abcd
efgh)";

auto box0a = 
R"(bcd
fgh)";
auto box0b = 
R"(abc
efg)";
auto box0c = R"(abcd-
efgh-)";

struct mega_curser
{
    mega_curser(std::string v_):v(v_)
    {

    }

    bool printable(char c)
    {
        switch(c)
        {
            case L'\n': return false;
            case L'\r': return false;
            default:return true;
        }
    }
    char val(int x,int y)
    {
        if((x > tx) || (y > ty))
        {
            i = v.begin();
            tx = -1;
            ty = -1;
        }

        for(;i != v.end();++i)
        {
            auto c = *i;
            if(printable(c))
            {
                if(tx < 0)++ty;
                ++tx;
                if ((ty == y) && (tx == x))
                {
                    break;
                }
            }
            else if (c == L'\n')
            {
                if (ty == y){
                    break;
                } 
                tx = -1;
            }
        }
        if (tx == x)
            return *i; 
        else
            return fill;
    }

    private:
    char fill = L'-';
    std::string v;
    int tx = -1;
    int ty = -1;
    std::string::iterator i = v.begin();
};

template<typename T>
std::string render(T v, box_t box) 
{
    std::string ret = "";

    int y = box.a.y; 

    while(true)
    {
        if (y == box.b.y) break;
        for (int x = box.a.x; x < box.b.x;++x)
        {
            ret.push_back(v.val(x,y));
        }
        if ((y+1) != box.b.y) 
            ret.push_back(L'\n');
        ++y;
    }
    return ret;
}

void render_tst(const char * inp, const char *ans, box_t loc) 
{
    auto c = mega_curser(inp);
    auto r = render(c,loc);
    REQUIRE(r == ans);
}

TEST_CASE("aix buffer test","foo")
{


    render_tst(box0,"a"         ,{{0,0},{1,1}});
    render_tst(box0,"ab"        ,{{0,0},{2,1}});
    render_tst(box0,"abc"       ,{{0,0},{3,1}});
    render_tst(box0,"abcd"      ,{{0,0},{4,1}});
    render_tst(box0,"abcd-"     ,{{0,0},{5,1}});
    render_tst(box0,"abcd--"    ,{{0,0},{6,1}});
    render_tst(box0,"abcd---"   ,{{0,0},{7,1}});

    render_tst(box0,""         ,{{1,0},{1,1}});
    render_tst(box0,"b"        ,{{1,0},{2,1}});
    render_tst(box0,"bc"       ,{{1,0},{3,1}});
    render_tst(box0,"bcd"      ,{{1,0},{4,1}});
    render_tst(box0,"bcd-"     ,{{1,0},{5,1}});
    render_tst(box0,"bcd--"    ,{{1,0},{6,1}});
    render_tst(box0,"bcd---"   ,{{1,0},{7,1}});

    render_tst(box0,"a\ne"            ,{{0,0},{1,2}});
    render_tst(box0,"ab\nef"          ,{{0,0},{2,2}});
    render_tst(box0,"abc\nefg"        ,{{0,0},{3,2}});
    render_tst(box0,"abcd\nefgh"      ,{{0,0},{4,2}});
    render_tst(box0,"abcd-\nefgh-"    ,{{0,0},{5,2}});
    render_tst(box0,"abcd--\nefgh--"  ,{{0,0},{6,2}});
    render_tst(box0,"abcd---\nefgh---",{{0,0},{7,2}});

    render_tst(box0,"\n"            ,{{1,0},{1,2}});
    render_tst(box0,"b\nf"          ,{{1,0},{2,2}});
    render_tst(box0,"bc\nfg"        ,{{1,0},{3,2}});
    render_tst(box0,"bcd\nfgh"      ,{{1,0},{4,2}});
    render_tst(box0,"bcd-\nfgh-"    ,{{1,0},{5,2}});
    render_tst(box0,"bcd--\nfgh--"  ,{{1,0},{6,2}});
    render_tst(box0,"bcd---\nfgh---",{{1,0},{7,2}});
    render_tst(box0,"abcd\nefgh",{{0,0},{4,2}});
    render_tst(box0,"bcd\nfgh"  ,{{1,0},{4,2}});

    #if 0
    {
        box_t loc = {{1,0},{4,2}};
        auto c = mega_curser(box0);
        auto r = render(c,loc);
        REQUIRE(r == box0a);
    }
    {
        box_t loc = {{0,0},{3,2}};
        auto c = mega_curser(box0);
        auto r = render(c,loc);
        REQUIRE(r == box0b);
    }
    {
        box_t loc = {{0,0},{5,2}};
        auto c = mega_curser(box0);
        auto r = render(c,loc);
        REQUIRE(r == box0c);
    }
    #endif
    REQUIRE((1 + 1) == 2);

}
