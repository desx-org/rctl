#pragma once

#include <string>
#include "fmt/format.h"
#include "fmt/color.h"
#include <vector>
#include <limits>

std::string do_thing(int num);

void bound(int &v,int a,int b)
{
         if (v < a) v = a;
    else if (v > b) v = b; 
}

struct box_t ;


struct point_t
{
    //point_t(int _x, int _y):x(_x),y(_y){}
    int x;
    int y;


    bool operator == (const point_t & o) const
    {
        return (o.x == x) && (o.y == y);
    }
    bool operator != (const point_t & o) const
    {
        return !(*this == o);
    }
    bool operator > (const point_t & o)
    {
        return (y > o.y) || ((y == o.y) && (x > o.x));
    }
    bool operator < (const point_t & o)
    {
        return !(*this > o) && !(*this == o);
    }

    bool h_in(const box_t & box);
    bool v_in(const box_t & box);
    bool in(const box_t & box);

    bool l_edge(const box_t & box);
    bool r_edge(const box_t & box);

    using lim = std::numeric_limits<int>;

    bool null() const
    {
        return ((x == lim::max()) && (y == lim::max()));
    }

    void set_null() 
    {
        x = lim::max();
        y = lim::max();
    }
};

struct box_t 
{
    point_t a;
    point_t b;

    //point_t tl(){return point_t{.x,.y}};
    //point_t tr(){return point_t{.x,.y}};
    //point_t bl(){return point_t{.x,.y}};
    //point_t br(){return point_t{.x,.y}};

};
struct shell_color{
    enum class M {C8,C256,CRGB};
    M type;
    uint32_t v;
};

struct theme_t
{
    fmt::v10::color fg_color     = fmt::color::red; 
    fmt::v10::color bg_color     = fmt::color::black;
    fmt::v10::color canvas_color = fmt::color::dark_violet;
};

bool point_t::h_in(const box_t & box){return (box.a.x <= x) && (x < box.b.x);}
bool point_t::v_in(const box_t & box){return (box.a.y <= y) && (y < box.b.y);}
bool point_t::in(const box_t & box){return h_in(box) && v_in(box);}
bool point_t::l_edge(const box_t & box){return (box.a.x == x) && h_in(box);}
bool point_t::r_edge(const box_t & box){return (box.b.x == (x+1)) && h_in(box);}

template<typename C>
struct gui
{
    gui(std::string s):curser(s){}
    C curser;

    enum class M {CMD,INS,VIS};
    const char * Ms(M v){
        switch(v){
            case M::CMD: return "CMD";
            case M::INS: return "INS";
            case M::VIS: return "VIS";
        }
        return "ERR";
    }

    M mode = M::CMD;

    //std::vector<std::wstring> text = {{L"abc"},{L"xyz"}};

    theme_t theme;

    fmt::memory_buffer buff;

    point_t w = {0,0};//window size
    point_t c = {0,0};//cursur position
    point_t r = {0,0};//render position

    box_t canvas;

    int last_key;

    void fg_set(fmt::v10::color color)
    {
        auto foreground = fmt::detail::make_foreground_color<char>(color);
        buff.append(foreground.begin(), foreground.end());
    }

    void bg_set(fmt::v10::color color)
    {
        auto background = fmt::detail::make_background_color<char>(color);
        buff.append(background.begin(), background.end());
    }

    template <typename... T>
    int pnt(T&&... args) {
        auto sz = fmt::formatted_size(std::forward<T>(args)...);
        fmt::format_to(std::back_inserter(buff), std::forward<T>(args)...);
        r.x += sz;
        return sz;
    }

    template <typename... T>
    void log(int lvl,T&&... args) {
        (void)lvl;
        auto f = std::fopen("text.log","a");
        fmt::print(f,std::forward<T>(args)...);
        std::fclose(f);
    }

    void set_mode(M new_mode)
    {
        if(new_mode != mode)
        {
            log(0,"new mode: {}\n",Ms(new_mode));
            mode = new_mode;
        }
    }
    void set_curser(point_t _c)
    {
        if(_c != c)
        {
            if(     _c.y <    0){log(0,"limit up\n"   );}
            else if(_c.y >= w.y){log(0,"limit down\n" );}
            else if(_c.x >= w.x){log(0,"limit right\n");}
            else if(_c.x    < 0){log(0,"limit left\n" );}
            else{c = _c; }
        }
    }
    void key_press(int key)
    {
        last_key = key;
        //Mode-independant modes
        switch(key)
        {
            case 0x415b1b:set_curser({c.x   ,c.y-1});break;//UP
            case 0x425b1b:set_curser({c.x   ,c.y+1});break;//DN
            case 0x435b1b:set_curser({c.x+1 ,c.y  });break;//RT
            case 0x445b1b:set_curser({c.x-1 ,c.y  });break;//LT
        }
        if(mode == M::CMD)
        {
            switch(key)
            {
                case 'k':set_curser({c.x  ,c.y-1});break;//UP
                case 'j':set_curser({c.x  ,c.y+1});break;//DN
                case 'l':set_curser({c.x+1,c.y  });break;//RT
                case 'h':set_curser({c.x-1,c.y  });break;//LT
                case 'i':set_mode(M::INS);break;
            }
        }
        else if(mode == M::INS)
        {
            switch(key)
            {
                case 0x1b:set_mode(M::CMD);break;//ESC key pressed
                default:
                    log(0,"insert: {}\n",(char)key);
                    curser.insert(key,c);
                break;
            }
        }
    }

    void new_size(int x, int y)
    {
        w.x = x-2;
        w.y = y-2;
    }

    std::string render()
    {
        buff.clear();
        
        auto v = "";

        fg_set(theme.fg_color);
        bg_set(theme.bg_color);

        pnt("\n┌{0:─^{1}}┐\n",v,w.x);
        canvas.a = {1,1};
        canvas.b = {w.x,w.y}; 

        for(r = {0,0};r.y < w.y;++r.y)
        {
            pnt("│");
            r.x = 0;
            while(r.x < w.x)
            {
                //set inverted colors for curser 
                if (r == c)
                {
                    fg_set(theme.bg_color);
                    bg_set(theme.fg_color);
                }
                //return to normal colors after curser
                if ((r.y == c.y) && (r.x == c.x+1))
                {
                    fg_set(theme.fg_color);
                    bg_set(theme.bg_color);
                }

                if ((r.y == (w.y-1)) && (r.x == 0))
                {
                    switch(mode)
                    {
                        case M::VIS:pnt("VIS");break;
                        case M::INS:pnt("INS");break;
                        case M::CMD:pnt("CMD");break;
                    }
                }
                else
                {
                    auto c = curser.val(r);
                    buff.push_back(c);
                    ++r.x;
                }
            }
            pnt("│\n");
        }
        pnt("└{0:─^{1}}┘\e[0m",v,w.x);
        return std::string(buff.begin(),buff.end());
    }
};

bool printable(char c)
{
    switch(c)
    {
        case '\n': return false;
        case '\0': return false;
        case '\r': return false;
        default:return true;
    }
}

struct text_editor_box 
{

};

struct mega_curser
{
    mega_curser(std::string  _s):v(_s){
        reset();
        adv_next_printable();
        t = c;
    }
    template <typename... T>
    void log(int lvl,T&&... args) {
        (void)lvl;
        auto f = std::fopen("text.log","a");
        fmt::print(f,std::forward<T>(args)...);
        std::fclose(f);
    }
    shell_color text_color(){
        return shell_color{shell_color::M::C256,1};
    }
    shell_color bg_color(){
        return shell_color{shell_color::M::C256,1};
    }
    bool bold(){
        return false;
    }
    bool underline(){
        return false;
    }
    void reset(){
        c = {0,0};
        i = 0;
        if(i == v.size())
           c.set_null();
    }

    bool null(){return i == v.size();}


    point_t loc(){
        return c;
    }

    void advance()
    {
        ++i;
        if(printable(v[i])) ++c.x;
        else adv_next_printable();
    }

    void adv_next_printable() 
    {
        while(1)
        {
            if(i == v.size()){
                c.set_null();
                return;
            } 
            if(printable(v[i])) {
                return;
            }
            else if(v[i] == '\n'){
                c.x = 0;
                ++c.y;
            }
            ++i;
        }
    } 
    void insert(char c)
    {
        v.insert(v.begin() + i,c);
    }
    void insert(char ch,point_t l)
    {
        go_to(l);
        if(c == t)
            v.insert(v.begin() + i,ch);
        else
            log(0,"cant insert\n");
    }

    void go_to(point_t _t)
    {
        t = _t;
        if (c > t) reset();

        while((c < t) && !null())
        {
            advance();
        }
        if((c != t) || !printable(v[i]))
        {
            c.set_null();
        }
    }
    char c_val(){
        return null() ? fill:v[i];
    }
    char val(){
        return t == c ? v[i]:fill;
    }
    char val(point_t _t)
    {
        go_to(_t);
        return val();
    }

    private:
    char fill = L'-';
    std::string v;
    size_t i;//current index

    size_t t_c;//foreground color index
    size_t b_c;//background color index
    size_t u_c;//underline color index

    point_t c;//curretn
    point_t t;//target
};

template<typename T>
std::string render(T v, box_t box) 
{
    std::string ret = "";

    for(point_t c = {0,box.a.y};c.y != box.b.y; ++c.y)
    {
        for (c.x = box.a.x; c.x < box.b.x;++c.x)
            ret.push_back(v.val(c));

        if ((c.y + 1) != box.b.y) 
            ret.push_back(L'\n');
    }
    return ret;
}