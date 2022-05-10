#ifndef VIEW
#define VIEW

#include <string>
#include <list>
#include <map>
#include <vector>
#include <set>
#include "model.h"

class View{
 public:
  static View* Get(const std::string& type);
  virtual size_t Draw() = 0;
  virtual void DrawRabits(const std::map<int, int>& rabits) = 0;
  virtual void PrintSnake(const std::vector<std::pair<int, int>>& snake_body, Direction dir) = 0;
  virtual void CleanScreen() = 0;
  virtual void IsGrow(std::map<int, int>& rabits, Snake& snake) = 0;
  virtual ~View() {}
  std::pair<int, int> RandCooord(const size_t length_x, const size_t length_y);

 private:

  static View* obj;

};

#endif //VIEW