#ifndef MODEL
#define MODEL

#include <iostream>
#include <vector>
#include <utility>
#include <map>

enum class Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class Snake {
 public:
    Snake(const size_t start_x, const size_t start_y, const size_t length_x, const size_t length_y);
    bool IsAlive(const std::map<int, int>& stones) const;
    bool Move(const std::map<int, int>& stones);
    void ChangeDirection(Direction dir);
    void SnakeGrow(std::pair<int, int> head_coord);
    std::vector<std::pair<int, int>> snake_body;
    size_t GetScore() const;
    Direction GetDirection() const;
    ~Snake();

 private:
    Direction dir_;
    size_t start_x_, start_y_;
    size_t length_x_, length_y_;
    size_t score_;
};


#endif //MODEL