#include <iostream>
#include <string>

#include "view.h"
#include "gview.h"
#include "tview.h"


View* View::obj = nullptr;
View* View::Get(const std::string& type) {
    const std::string text = "Tview";
    const std::string goi  = "Gview";

    if(!obj){
        if(type == text){
            obj = new Tview;
        }else if(type == goi){
            //obj = new Gview;
        }
    }
    return obj;
}