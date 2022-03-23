#ifndef GVIEW
#define GVIEW

#include <iostream>

#include "view.h"

class Gview : public View {
    void Draw() override {}
    void DrawRabits(const std::vector<std::pair<int, int>>& rabits) {}
    void CleanScreen() override {}
    void PrintSnake(const size_t length_x, const size_t length_y) override {}

 private:
    
};

#endif // GVIEW