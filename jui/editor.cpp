#include "fmt/format.h"
#include <string>

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include <signal.h>
#include <stdlib.h>

struct winsize window_size()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w;
}
bool keepRunning = true;
struct u_event{
    int cnt;
    int ack;
    void trigger(){
        ++cnt;
        fmt::print("t\n");
    }
    bool handle()
    {
        if(cnt > ack)
        {
            ++ack;
            return true;
        }
        return false;
    }
};
static u_event resize_event = {};

void intHandler(int) {
    keepRunning = false;
    fmt::print("ctrl-c\n");
}
//void resizeHandler(int) {resize_event.trigger();}
void resizeHandler(int) {resize_event.trigger();}

std::string do_thing(int num)
{
    struct sigaction act;
    act.sa_handler = intHandler;
    sigaction(SIGINT, &act, NULL);

    struct sigaction act2;
    act2.sa_handler = resizeHandler;
    sigaction(SIGWINCH, &act2, NULL);

    while(1)
    {
        if(!keepRunning) break;
        if(resize_event.handle())
        {
            auto w = window_size();
            fmt::print("{}x{}\n",w.ws_col,w.ws_row);
            /*
            fmt::print(
                "┌{0:─^{2}}┐\n"
                "│{1: ^{2}}│\n"
                "└{0:─^{2}}┘\n", "", "Hello, world!", w.ws_col-2);
            */
        }
        sleep(0.01);
    }
    return fmt::format("do thing: {}",num);
}