#ifndef TVIEW
#define TVIEW

#include <string>
#include <list>
#include <map>
#include <vector>

#include "view.h"

class Tview : public View{
 public:

    void Draw() override;
    void DrawRabits(std::vector<std::pair<int, int>>& rabits) override;
    void CleanScreen() override;

 private:

    void GoCoord(int x, int y);
    void SetColor(int color);
    void SetColor(int f_color, int b_color);
};


#endif // TVIEW