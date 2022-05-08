#ifndef GVIEW
#define GVIEW

#include <iostream>
#include <array>

#include "view.h"
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>

class Gview : public View {

 public:

    Gview();
    size_t Draw() override;
    void DrawRabits(const std::map<int, int>& rabits) override;
    void CleanScreen() override {}
    void PrintSnake(const std::vector<std::pair<int, int>>& snake_body) override;
    ~Gview();

 private:
    void DrawBoundary();
    void DrawRectangles(const double pos_x, const double pos_y, const double length_x, const double length_y);
    void DrawRectangles(sf::RectangleShape& rectangle);

    sf::RenderWindow* window_;
    sf::Texture texture_rabit_;
    sf::Texture texture_snake_head_;
};

#endif // GVIEW