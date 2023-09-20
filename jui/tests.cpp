#include "editor.hpp"

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

auto box00 = R"(a)";

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

auto box0d = R"(
\e
)";

void render_tst(const char * inp, const char *ans, box_t loc) 
{
    auto c = mega_curser(inp);
    auto r = render(c,loc);
    REQUIRE(r == ans);
}

TEST_CASE("aix buffer test","foo")
{

#if 1
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
    render_tst(box0,"abcd----\nefgh----",{{0,0},{8,2}});
    render_tst(box00,"a-\n--",{{0,0},{2,2}});
    render_tst(box00,"-",{{0,1},{1,2}});

    render_tst(box0,"\n"            ,{{1,0},{1,2}});
    render_tst(box0,"b\nf"          ,{{1,0},{2,2}});
    render_tst(box0,"bc\nfg"        ,{{1,0},{3,2}});
    render_tst(box0,"bcd\nfgh"      ,{{1,0},{4,2}});
    render_tst(box0,"bcd-\nfgh-"    ,{{1,0},{5,2}});
    render_tst(box0,"bcd--\nfgh--"  ,{{1,0},{6,2}});
    render_tst(box0,"bcd---\nfgh---",{{1,0},{7,2}});
    render_tst(box0,"abcd\nefgh",{{0,0},{4,2}});
    render_tst(box0,"bcd\nfgh"  ,{{1,0},{4,2}});
#endif
    gui<mega_curser> g("hello");
    
    REQUIRE((1 + 1) == 2);
    printf("%s\n", "\x1b[31mtest\033[0ming");
}
