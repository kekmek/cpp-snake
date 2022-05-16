#ifndef TVIEW
#define TVIEW

#include <string>
#include <list>
#include <map>
#include <vector>

#include "view.h"
#include "model.h"

void SignHandler(int n);

class Tview : public View{
 public:
  Tview();
  size_t Draw() override;
  void DrawRabits(const std::map<int, int>& rabits) override;
  void CleanScreen() override;  
  void PrintSnake(const std::vector<std::pair<int, int>>& snake_body, Direction dir) override;
  void IsGrow(std::map<int, int>& rabits, Snake& snake) override;
  void DrawStones(std::map<int, int>& stones, const size_t length_x, const size_t length_y);
  ~Tview();

 private:   
  void GoCoord(int x, int y);
  void SetColor(int color);
  void DrawBoundary(const size_t length_x, const size_t length_y);
};

#endif // TVIEW