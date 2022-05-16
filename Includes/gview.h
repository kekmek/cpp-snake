#ifndef GVIEW
#define GVIEW

#include <iostream>
#include <array>
#include <unistd.h>

#include "view.h"
#include "model.h"
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>

class Gview : public View {

 public:

   Gview();
   size_t Draw() override;
   void DrawRabits(const std::map<int, int>& rabits) override;
   void CleanScreen() override {}
   void PrintSnake(const std::vector<std::pair<int, int>>& snake_body, Direction dir) override;
   void IsGrow(std::map<int, int>& rabits, Snake& snake) override;
   //void DrawStones(std::map<int, int>& stones, const size_t length_x, const size_t length_y) override{}
   ~Gview();

 private:
   void DrawBoundary();
   void DrawRectangles(const double pos_x, const double pos_y, const double length_x, const double length_y);
   void DrawRectangles(sf::RectangleShape& rectangle);
   sf::RenderWindow* window_;
   sf::Texture texture_rabit_;
   sf::Texture texture_snake_head_right_;
   sf::Texture texture_snake_head_left_;
   sf::Texture texture_snake_head_up_;
   sf::Texture texture_snake_head_down_;
};

#endif // GVIEW