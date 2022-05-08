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
  virtual void Draw() = 0;
  virtual void DrawRabits(const std::map<int, int>& rabits) = 0;
  virtual void CleanScreen() = 0;
  virtual void PrintSnake(const std::vector<std::pair<int, int>>& snake_body) = 0;
  virtual ~View() {}
    
 private:

  static View* obj;

};

#endif //VIEW