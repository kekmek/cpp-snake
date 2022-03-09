#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <ctime>
#include <termios.h>
#include <signal.h>
#include <sys/poll.h>
#include <string>

#include "tview.h"

//Foreground Colors
#define FOREGROUND_COL_BLACK 30
#define FOREGROUND_COL_RED 31
#define FOREGROUND_COL_GREEN 32
#define FOREGROUND_COL_YELLOW 33
#define FOREGROUND_COL_BLUE 34
#define FOREGROUND_COL_MAGENTA 35
#define FOREGROUND_COL_CYAN 36
#define FOREGROUND_COL_WHITE 37

//Background Colors
#define BACKGROUND_COL_BLACK 40
#define BACKGROUND_COL_RED 41
#define BACKGROUND_COL_GREEN 42
#define BACKGROUND_COL_YELLOW 43
#define BACKGROUND_COL_BLUE 44
#define BACKGROUND_COL_MAGENTA 45
#define BACKGROUND_COL_CYAN 46
#define BACKGROUND_COL_WHITE 47

struct termios old_term;
bool final = false;

void SignHandler(int n) {
    final = true;
}

Tview::Tview() {
    struct termios term;
    tcgetattr(0, &term);
    
    old_term = term;

    cfmakeraw(&term);
    term.c_lflag |= ISIG; 
    tcsetattr(0, TCSANOW, &term);
    signal(SIGINT, SignHandler);

}

Tview::~Tview() {
    tcsetattr(0, TCSANOW, &old_term);
}


void Tview::CleanScreen() {
    printf("\e[H\e[J");
}

void Tview::GoCoord(int x, int y) {
    printf("\e[%d;%dH", y, x);
}

void Tview::SetColor(int color) {
    printf("\e[%dm", color);
}

void Tview::SetColor(int f_color, int b_color) {
    printf("\e[%d;%dm", f_color, b_color);
}

void Tview::Draw(){
    
    struct winsize w;
    ioctl(1, TIOCGWINSZ, &w);

    const size_t length_x  = w.ws_col;
    const size_t length_y  = w.ws_row;


    while(!final) {

    struct pollfd arr;
    arr.fd = 0;
    arr.events = POLLIN;

    int n = poll(&arr, 1, 500);
    if( n == 1) {

        char c;
        scanf("%c", &c);

        if( c == 'q') {
            break;
        }

        // std::string str;
        // getline(cin, str);

        // if(str == "quit") {
        //     break;
        // }
    }

    SetColor(FOREGROUND_COL_YELLOW, BACKGROUND_COL_BLACK);
    CleanScreen();

    GoCoord(1, 1);
    for(int i = 1; i < length_x; ++i) {
        printf("*");
    }

    GoCoord(1, length_y);
    for(int i = 1; i < length_x; ++i) {
        printf("*");
    }
    
    for(int i = 1; i < length_y; ++i) {
        GoCoord(1, i);
        printf("*");
        GoCoord(length_x, i);
        printf("*");
    }

    std::vector<std::pair<int, int>> rabits = { {15, 18}, {12, 14}, {22, 18} , {44, 16}};

    usleep(1000);
    DrawRabits(rabits);

    }


}

void Tview::DrawRabits(std::vector<std::pair<int, int>>& rabits) {
    SetColor(FOREGROUND_COL_WHITE, BACKGROUND_COL_BLACK);
    for(const auto& [x, y]: rabits) {
        GoCoord(x, y);
        printf("@");
        fflush(stdout);        
    }
}