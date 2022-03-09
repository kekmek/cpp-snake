#ifndef GVIEW
#define GVIEW

#include <iostream>

#include "view.h"

class Gview : public View {
    void Draw() override {}
    void DrawRabits(std::vector<std::pair<int, int>>& rabits) {}
    void CleanScreen() override {}

 private:
    
};

#endif // GVIEW