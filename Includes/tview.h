#ifndef TVIEW
#define TVIEW

#include <string>
#include <list>
#include <map>
#include <vector>

#include "view.h"

void SignHandler(int n);

class Tview : public View{
 public:
    Tview();
    void Draw() override;
    void DrawRabits(const std::vector<std::pair<int, int>>& rabits) override;
    void CleanScreen() override;  
    void PrintSnake(const size_t length_x, const size_t length_y) override;
    ~Tview();

 private:   
    void GoCoord(int x, int y);
    void SetColor(int color);
    void SetColor(int f_color, int b_color);
    void SetTerminalConfig();
    std::vector<std::pair<int, int>> RandCooord(const size_t length_x, const size_t length_y);
};

#endif // TVIEW