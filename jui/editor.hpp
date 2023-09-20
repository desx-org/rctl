#pragma once

#include <string>
#include "fmt/format.h"
#include "fmt/color.h"
#include <vector>

std::string do_thing(int num);

void bound(int &v,int a,int b)
{
         if (v < a) v = a;
    else if (v > b) v = b; 
}

struct box_t ;

struct sz2d_t 
{
    int w;
    int h;
};

struct point_t
{
    int x;
    int y;
    bool operator == (const point_t & other)
    {
        return (other.x == x) && (other.y == y);
    }
    bool h_in(const box_t & box);
    bool v_in(const box_t & box);
    bool in(const box_t & box);

    bool l_edge(const box_t & box);
    bool r_edge(const box_t & box);
};

struct box_t 
{
    point_t a;
    point_t b;
};

struct theme_t
{
    fmt::v10::color fg_color     = fmt::color::red; 
    fmt::v10::color bg_color     = fmt::color::black;
    fmt::v10::color canvas_color = fmt::color::dark_violet;
};

struct line_number_box_t:public box_t
{
    int start;
};

struct status_bar_t:public box_t
{

};
struct command_bar_t:public box_t
{

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
    M mode;

    std::vector<std::wstring> text = {{L"abc"},{L"xyz"}};

    theme_t theme;

    fmt::memory_buffer buff;

    point_t w = {0,0};//window size
    point_t c = {0,0};//cursur position
    point_t r = {0,0};

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

    void key_press(int key)
    {
        last_key = key;
        //Mode-independant modes
        switch(key)
        {
            case 0x415b1b:--c.y;break;//UP
            case 0x425b1b:++c.y;break;//DN
            case 0x435b1b:++c.x;break;//RT
            case 0x445b1b:--c.x;break;//LT
            case 'i':mode = M::INS;break;
        }
        if(mode == M::CMD)
        {
            switch(key)
            {
                case 'k':--c.y;break;//UP
                case 'j':++c.y;break;//DN
                case 'l':++c.x;break;//RT
                case 'h':--c.x;break;//LT
            }
        }
        if(mode == M::INS)
        {
            switch(key)
            {
                case 0x1b:mode = M::CMD;break;//ESC key pressed
            }
        }
        bound(c.y,0,w.y-1);
        bound(c.x,0,w.x-1);
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

        for(r= {0,0};r.y < w.y;++r.y)
        {
            pnt("│");
            r.x= 0 ;
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
                    pnt(" {:06x}",last_key);
                }
                else
                {
                    //pnt(" ");
                    auto c = curser.val(r.x,r.y);
                    // pnt("{}",c);
                    //if (s != 1)
                    //{
                    //}
                    buff.push_back(c);
                    ++r.x;
                    //pnt("{}",'s');
                }
            }
            pnt("│\n");
        }
        pnt("└{0:─^{1}}┘",v,w.x);
        return std::string(buff.begin(),buff.end());
    }
};



bool printable(char c)
{
    switch(c)
    {
        case '\n': return false;
        //case '\0': return false;
        case '\r': return false;
        default:return true;
    }
}

struct mega_curser
{
    mega_curser(std::string v_):v(v_){}

    char val(int tx,int ty)
    {
        //if((cx > tx) || (cy > ty))
        {
            i = v.begin();
            cx = -1;
            cy = -1;
        }

        for(;i != v.end();++i)
        {
            auto c = *i;
            if(printable(c))
            {
                if(cx < 0)++cy;
                ++cx;
                if ((cy == ty) && (cx == tx))
                {
                    break;
                }
            }
            else if (c == '\n')
            {
                if (cy == ty){
                    break;
                } 
                cx = -1;
            }
        }
        //if (cx == tx) 
        if ((cx == tx) &&(cy == ty))
            return *i; 
        else
            return fill;
    }

    private:
    char fill = L'-';
    std::string v;
    int cx = -1;
    int cy = -1;
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