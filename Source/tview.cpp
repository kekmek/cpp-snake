#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <ctime>
#include <termios.h>
#include <signal.h>
#include <sys/poll.h>
#include <string>
#include <random>
#include <algorithm>
#include <curses.h>
// /#include <conio.h>

#include "tview.h"
#include "game.h"

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

Snake snake;
const size_t rabits_quan = 20;
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

    size_t start_x = length_x / 2;
    size_t start_y = length_y / 2;

    std::vector<std::pair<int, int>> rabits;

    for(int i = 0; i < rabits_quan; ++i) {
        std::pair<int, int> tmp = RandCooord(length_x, length_y);
        rabits.push_back(tmp);
    }
    
    while(!final) {

        struct pollfd arr;
        arr.fd = 0;
        arr.events = POLLIN;

        int n = poll(&arr, 1, 500);
        if( n == 1 ) {
            
            char c;
            scanf("%c", &c);

            if( c == 'q') break;

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
    
        DrawRabits(rabits);

        int dx = 1, dy = 1;
        if(length_y > length_x) {
            dx += length_y / length_x;
        }else if(length_y < length_x) {
            dy += length_x / length_y;
        }

        if(snake.Dir.UP)         start_y -= dy; 
        else if(snake.Dir.DOWN)  start_y += dy;
        else if(snake.Dir.RIGHT) start_x += dx;
        else if(snake.Dir.LEFT)  start_x -= dx;

        PrintSnake(start_x, start_y);
        usleep(10);
    
    }


}

std::pair<int, int> Tview::RandCooord(const size_t length_x, const size_t length_y) {

    std::pair<int, int> rand_coord;
    
    std::random_device random_device; 
    std::mt19937 generator(random_device());

    std::uniform_int_distribution<> distribution_x(1, length_x);
    std::uniform_int_distribution<> distribution_y(1, length_y);

    int x = distribution_x(generator);
    int y = distribution_y(generator); 

    rand_coord.first  = x;
    rand_coord.second = y;
    
    return rand_coord;
}

void Tview::DrawRabits(const std::vector<std::pair<int, int>>& rabits) {
    SetColor(FOREGROUND_COL_WHITE, BACKGROUND_COL_BLACK);
    for(const auto [x, y]: rabits) {
        GoCoord(x, y);
        printf("R");
        fflush(stdout);        
    }
}

void Tview::PrintSnake(const size_t start_x, const size_t start_y) {

    
    GoCoord(start_x, start_y);
    SetColor(FOREGROUND_COL_RED, BACKGROUND_COL_BLACK);
    printf("S");
    fflush(stdout);

    struct pollfd arr;
    arr.fd = 0;
    arr.events = POLLIN;
    //snake.Dir.UP = true;
    int n = poll(&arr, 1, 100);
    if( n == 1 ) {

        switch(getchar()) {
            case 'a' :
                snake.Dir.UP    = false;
                snake.Dir.DOWN  = false;
                snake.Dir.RIGHT = false;
                snake.Dir.LEFT  = true;
                break;

            case 's' :
                snake.Dir.UP    = false;
                snake.Dir.DOWN  = true;
                snake.Dir.RIGHT = false;
                snake.Dir.LEFT  = false;
                break;
        
            case 'd' :
                snake.Dir.UP    = false;
                snake.Dir.DOWN  = false;
                snake.Dir.RIGHT = true;
                snake.Dir.LEFT  = false;
                break;

            case 'w' :
                snake.Dir.UP    = true;
                snake.Dir.DOWN  = false;
                snake.Dir.RIGHT = false;
                snake.Dir.LEFT  = false;
                break;
        }
    }
}