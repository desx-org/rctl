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

auto box0 = LR"(abcd
efgh)";

auto box0a = 
LR"(bcd
fgh)";
auto box0b = 
LR"(abc
efg)";
auto box0c = LR"(abcd-
efgh-)";

struct mega_curser
{
    mega_curser(std::wstring v_):v(v_)
    {

    }

    bool printable(wchar_t c)
    {
        switch(c)
        {
            case L'\n': return false;
            case L'\r': return false;
            default:return true;
        }
    }
    wchar_t val(int x,int y)
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
    wchar_t fill = L'-';
    std::wstring v;
    int tx = -1;
    int ty = -1;
    std::wstring::iterator i = v.begin();
};

template<typename T>
std::wstring render(T v, box_t box) 
{
    std::wstring ret = L"";

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

void render_tst(const wchar_t * inp, const wchar_t *ans, box_t loc) 
{
    auto c = mega_curser(inp);
    auto r = render(c,loc);
    REQUIRE(r == ans);
}

TEST_CASE("aix buffer test","foo")
{
    render_tst(L"",L""           ,{{0,0},{0,1}});
    render_tst(L"",L""           ,{{0,0},{1,0}});
    render_tst(L"",L"-"          ,{{0,0},{1,1}});
    render_tst(L"",L"--"         ,{{0,0},{2,1}});
    render_tst(L"",L"--\n--"     ,{{0,0},{2,2}});

    render_tst(box0,L"a"         ,{{0,0},{1,1}});
    render_tst(box0,L"ab"        ,{{0,0},{2,1}});
    render_tst(box0,L"abc"       ,{{0,0},{3,1}});
    render_tst(box0,L"abcd"      ,{{0,0},{4,1}});
    render_tst(box0,L"abcd-"     ,{{0,0},{5,1}});
    render_tst(box0,L"abcd--"    ,{{0,0},{6,1}});
    render_tst(box0,L"abcd---"   ,{{0,0},{7,1}});

    render_tst(box0,L""         ,{{1,0},{1,1}});
    render_tst(box0,L"b"        ,{{1,0},{2,1}});
    render_tst(box0,L"bc"       ,{{1,0},{3,1}});
    render_tst(box0,L"bcd"      ,{{1,0},{4,1}});
    render_tst(box0,L"bcd-"     ,{{1,0},{5,1}});
    render_tst(box0,L"bcd--"    ,{{1,0},{6,1}});
    render_tst(box0,L"bcd---"   ,{{1,0},{7,1}});

    render_tst(box0,L"a\ne"            ,{{0,0},{1,2}});
    render_tst(box0,L"ab\nef"          ,{{0,0},{2,2}});
    render_tst(box0,L"abc\nefg"        ,{{0,0},{3,2}});
    render_tst(box0,L"abcd\nefgh"      ,{{0,0},{4,2}});
    render_tst(box0,L"abcd-\nefgh-"    ,{{0,0},{5,2}});
    render_tst(box0,L"abcd--\nefgh--"  ,{{0,0},{6,2}});
    render_tst(box0,L"abcd---\nefgh---",{{0,0},{7,2}});

    render_tst(box0,L"\n"            ,{{1,0},{1,2}});
    render_tst(box0,L"b\nf"          ,{{1,0},{2,2}});
    render_tst(box0,L"bc\nfg"        ,{{1,0},{3,2}});
    render_tst(box0,L"bcd\nfgh"      ,{{1,0},{4,2}});
    render_tst(box0,L"bcd-\nfgh-"    ,{{1,0},{5,2}});
    render_tst(box0,L"bcd--\nfgh--"  ,{{1,0},{6,2}});
    render_tst(box0,L"bcd---\nfgh---",{{1,0},{7,2}});
    render_tst(box0,L"abcd\nefgh",{{0,0},{4,2}});
    render_tst(box0,L"bcd\nfgh"  ,{{1,0},{4,2}});

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
