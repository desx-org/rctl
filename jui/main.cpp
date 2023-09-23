
#include <sys/ioctl.h>
#include <iostream>
#include <termios.h>
#include "fmt/format.h"
#include <signal.h>
#include <stdint.h>
#include <termios.h>
#include <sys/ioctl.h>

//#include <vector>
#include "tlpi_hdr.h"

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <fmt/color.h>
#include "editor.hpp"
#include "utils.hpp"

volatile long long count_major_loop      =0;
volatile long long count_signals_caught  =0;
volatile int       flag_quit             =0;

static jfifo<int,8> sigs;
static jfifo<uint32_t,8> keys;

static void sigwinchHandler(int sig)
{
    sigs.push(sig);
}
template<typename T>
void win_resize(gui<T> & g)
{
    struct winsize ws;
    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
    {
        printf("ioctl error\n");
        exit(0);
    }
    g.new_size(ws.ws_col,ws.ws_row);

    fmt::print("{}",g.render());

    fflush(stdout);

}
auto txt = std::string(R"(AAA
BBB
CCC
DDD
EEE
FFF
GGG
HHH
III
JJJ
KKK
LLL
MMM
NNN
OOO
PPP
QQQ
RRR
SSS
TTT
UUU
VVV
WWW
XXX
YYY
ZZZ
1AA
jkk
1BB
1CC
1DD
1EE
1FF
1GG
1HH
1II
1JJ
1KK
1LL
1MM
1NN
1OO
1PP
1QQ
1RR
1SS
1TT
1UU
1VV
1WW
1XX
)");

void run_loop()
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);

    sa.sa_flags = 0;
    sa.sa_handler = sigwinchHandler;

    if (sigaction(SIGWINCH, &sa, NULL) == -1)
        printf("sigaction");

    gui<mega_curser> g(txt);

    win_resize(g);

    while (!flag_quit) {

        ++count_major_loop;

        pause();

        int sig;
        while(sigs.get(sig))
        {
            switch(sig)
            {
                case SIGWINCH:
                    win_resize(g);
                break;
                case SIGIO://IO RECEIVED
                break;
                default:
                    fmt::print("unexpected signal: {}\n",sig);
                break;
            }
        }
        uint32_t key = 0;
        while(keys.get(key))
        {
            g.key_press(key);
            fmt::print("{}",g.render());
        }
        fflush(stdout);
    }
}
//TEXT IDE
//WEB IDE
//Package Manager
//Unit Test Framework
//Text Documentation Generator
//HTML Documentation Generator
//Single Portable Executable
//Graphics Visualization
//PACKAGE 
//Web Deployment
void sig_io(int signo)
{
    sigs.push(signo);

    char           c_array[1000];
    fd_set         read_set;

    struct timeval timeout_value;

    count_signals_caught++;

    FD_ZERO(&read_set);
    FD_SET(STDIN_FILENO,&read_set);
    timeout_value.tv_sec  = 0;
    timeout_value.tv_usec = 0;


    if(select(STDIN_FILENO + 1, &read_set, NULL, NULL,&timeout_value) > 0)
    {

        auto read_count = read(STDIN_FILENO,c_array,sizeof(c_array));

        if(read_count < 0) {
            fmt::print("got error\n");
            flag_quit = 1;
        }
        else if(read_count == 0)
        {
            fmt::print("got eof\n");
            flag_quit=1;
        }
        else if (c_array[0] == 'q') {
            fmt::print("got quit request\n");
            flag_quit=1;
        }
        else
        {
            uint32_t v = 0;
            if(read_count <= static_cast<decltype(read_count)>(sizeof(uint32_t)))
            {
                memcpy(&v,c_array,read_count);
                keys.push(v);
            }
            else{
                fmt::print("invalid size\n");
            }
        }
    }
}
#include "wchar.h"
int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON|ECHO); // turn off line buffering and echoing
    tcsetattr(0, TCSANOW, &term);

    struct sigaction sa = {};
    sa.sa_handler = sig_io;

    if (sigaction(SIGIO, &sa, NULL) < 0) {
        fmt::print(stderr,"[ERROR]: sigaction error\n");
        exit(1);
    }

    if (fcntl(0, F_SETOWN, getpid()) < 0) {
        fmt::print(stderr,"[ERROR]: fcntl F_SETOWN error\n");
        exit(1);
    }

    if (fcntl(0, F_SETFL, O_NONBLOCK|O_ASYNC) < 0) {
        fmt::print(stderr,"[ERROR]: fcntl error for O_NONBLOCK|O_ASYNC\n");
        exit(1);
    }

    run_loop();

    term.c_lflag |= (ICANON|ECHO); // turn on line buffering and echoing
    tcsetattr(0, TCSANOW, &term);

    fmt::print("major loop count: {}\n",count_major_loop      );
    fmt::print("signals caught  : {}\n",count_signals_caught  );

    return 0;
    #if 0
   #endif
}
