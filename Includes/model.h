#ifndef MODEL
#define MODEL

#include <vector>

enum class Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class Snake {
 public:
    Snake(const size_t start_x, const size_t start_y, const size_t length_x, const size_t length_y);

    bool IsAlive() const;
    bool Move();
    void ChangeDirection(Direction dir);
    std::vector<std::pair<int, int>> snake_body;
    Direction GetDirection() const;
    size_t GetScore() const;
    ~Snake();

 private:
    Direction dir_;
    size_t start_x_, start_y_;
    size_t length_x_, length_y_;
    size_t score_;
    
};


#endif //MODEL