#include <iostream>

#include "gview.h"
#include "tview.h"
#include "human.h"
#include "model.h"


int main(int argc, char** argv) {

    View* view = View::Get(argv[1]);   
    auto score = view->Draw();
    delete view;

    std::cout << "GAME IS OVER! YOUR SCORE : " << score << std::endl;
    
}