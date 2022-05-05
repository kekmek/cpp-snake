#ifndef GVIEW
#define GVIEW

#include <iostream>

#include "view.h"

class Gview : public View {
    void Draw() override {}
    void DrawRabits(const std::vector<std::pair<int, int>>& rabits) {}
    void CleanScreen() override {}
    void PrintSnake(const std::vector<std::pair<int, int>>& snake_body) override {}

 private:
    
};

#endif // GVIEW