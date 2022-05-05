#include "model.h"
#include <vector>

Snake::Snake(const size_t start_x, const size_t start_y, const size_t length_x, const size_t length_y) {
    start_x_ = start_x;
    start_y_ = start_y;
    length_x_ = length_x;
    length_y_ = length_y;
    score_ = 0;
    snake_body.push_back(std::pair<int, int>(start_x, start_x));
    dir_ = Direction::RIGHT;
}

bool Snake::IsAlive() const {
    if(snake_body.at(0).first == length_x_ || snake_body.at(0).first == 1 || snake_body.at(0).second == length_y_ || snake_body.at(0).second == 1) {
        return false;
    }else {
        for(int i = 1; i < snake_body.size(); ++i) {
            if(snake_body.at(i) == snake_body.at(0)) return false;
        }    
    }
    return true;
}

Snake::~Snake() {};