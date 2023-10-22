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

abcd
efgh
)";
//RED text,black BG
//#define A "\e[38;2;255;000;000m\e[48;2;000;000;000m"
//BLACK text,RED BG
//#define B "\e[38;2;000;000;000m\e[48;2;255;000;000m"

#define A "\e[38;2;255;000;000m\e[48;2;000;000;000m"
#define B "\e[38;2;000;000;000m\e[48;2;255;000;000m"

#define Z "\e[0m"
auto edit_1=A"\n"
"┌────┐\n"
"│" B "h" A "ell│\n"
"│----│\n"
"│CMD-│\n"
"└────┘" Z;

auto edit_2=A"\n"
"┌────┐\n"
"│h" B "e" A "ll│\n"
"│----│\n"
"│CMD-│\n"
"└────┘" Z;

auto edit_3=A"\n"
"┌────┐\n"
"│he" B "l" A "l│\n"
"│----│\n"
"│CMD-│\n"
"└────┘" Z;

auto edit_4=Z A"\n"
"┌────┐\n"
"│" B "h" A "ell│\n"
"│----│\n"
"│CMD-│\n"
"└────┘" Z;

void render_tst(const char * inp, const char *ans, box_t loc) 
{
    auto c = mega_curser(inp);
    auto r = render(c,loc);
    REQUIRE(r == ans);
}

TEST_CASE("aix buffer test","foo")
{

#if 1
    std::string s = "ab\nef\n\nx";
    auto l = mega_curser(s);
    REQUIRE(l.c_val() == 'a');
    REQUIRE(l.loc() == point_t{0,0});
    REQUIRE(!l.null());
    REQUIRE(!l.loc().null());
    l.advance();
    REQUIRE(l.c_val() == 'b');
    REQUIRE(l.loc() == point_t{1,0});
    REQUIRE(!l.null());
    REQUIRE(!l.loc().null());
    l.advance();
    REQUIRE(l.c_val() == 'e');
    REQUIRE(l.loc() == point_t{0,1});
    REQUIRE(!l.null());
    REQUIRE(!l.loc().null());
    l.advance();
    REQUIRE(l.c_val() == 'f');
    REQUIRE(l.loc() == point_t{1,1});
    REQUIRE(!l.null());
    REQUIRE(!l.loc().null());
    l.advance();
    REQUIRE(l.c_val() == 'x');
    REQUIRE(l.loc() == point_t{0,3});
    REQUIRE(!l.null());
    REQUIRE(!l.loc().null());
    l.advance();
    REQUIRE(l.null());
    REQUIRE(l.loc().null());
    l.reset();
    l.insert('x');
    REQUIRE(l.c_val() == 'x');
    
    //render_tst(box0,"abcd-\nefgh-"    ,{{0,0},{5,2}});
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

    render_tst(box0d,"----\nabcd"  ,{{0,0},{4,2}});

    gui<mega_curser> g("hello");
    g.theme = {fmt::color::red,fmt::color::black};

    g.new_size(6,5);
    auto v = g.render();
    REQUIRE(v == edit_1);
    g.set_curser({1,0});
    v = g.render();
    REQUIRE(v == edit_2);
    g.set_curser({2,0});
    v = g.render();
    REQUIRE(v == edit_3);
    g.set_curser({3,0});
    v = g.render();
    //REQUIRE(v == edit_4);

    

    //printf("%s\n", "\e[0maaa\e[31mbbb\e[0mccc");

    {
        point_t a = {0,0};
        point_t b = {1,0};
        REQUIRE(b > a);
        b = {1,0};
        REQUIRE(b > a);
        a = {1,1};
        b = {0,2};
        REQUIRE(b > a);
        b = {2,0};
        REQUIRE(a > b);
        b = {2,1};
        REQUIRE(b > a);
    }
#endif
    REQUIRE((1 + 1) == 2);
}
