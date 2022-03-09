#ifndef VIEW
#define VIEW

#include <cstring>
#include <list>
#include <map>
#include <vector>

class View{
 public:
    static View* Get(const std::string& type);
    virtual void Draw() = 0;
    virtual void DrawRabits(std::vector<std::pair<int, int>>& rabits) = 0;
    virtual void CleanScreen() = 0;

 private:

    static View* obj;

};

#endif //VIEW