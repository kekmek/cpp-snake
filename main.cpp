#include <iostream>
#include <list>
#include <map>
#include <vector>

#include "gview.h"
#include "tview.h"
#include "human.h"
#include "model.h"


int main(int argc, char** argv) {

    View* view = View::Get(argv[1]);   
    view->Draw();
    
}