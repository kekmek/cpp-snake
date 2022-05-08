#ifndef GVIEW
#define GVIEW

#include <iostream>

#include "view.h"

class Gview : public View {

    size_t Draw() override {}
    void DrawRabits(const std::map<int, int>& rabits) {}
    void CleanScreen() override {}
    void PrintSnake(const std::vector<std::pair<int, int>>& snake_body) override {}

 private:
    
};

#endif // GVIEW