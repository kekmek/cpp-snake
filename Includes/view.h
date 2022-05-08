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
  virtual void PrintSnake(const std::vector<std::pair<int, int>>& snake_body) = 0;
  virtual void CleanScreen() = 0;
  virtual ~View() {}
  std::pair<int, int> RandCooord(const size_t length_x, const size_t length_y, const std::string& window_type);

 private:

  static View* obj;

};

#endif //VIEW