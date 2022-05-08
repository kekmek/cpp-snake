#include "model.h"
#include "gview.h"

const int boundary_width = 10;
const int rabits_quan = 20;

Gview::Gview() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window_ = new sf::RenderWindow(sf::VideoMode(1920, 1080), "", sf::Style::Fullscreen, settings);
    window_->setVerticalSyncEnabled(true);

    if(!texture_rabit_.loadFromFile("Images/Rabit.png")) {
        delete window_;
        exit(-1);
    }
    texture_rabit_.setSmooth(true);

    if(!texture_snake_head_.loadFromFile("Images/SnakeHead.png")) {
        delete window_;
        exit(-1);
    }
    texture_snake_head_.setSmooth(true);
}

size_t Gview::Draw() {
    
    sf::Music music;
    if(!music.openFromFile("Sounds/SnakeTheme-Song.wav")) {
        return -1;
    }
    music.play();
    music.setLoop(true);

    std::map<int, int> rabits;

    for(int i = 0; i < rabits_quan; ++i) {
        std::pair<int, int> tmp = View::RandCooord(1920, 1080, "Gview");
        rabits[tmp.first] = tmp.second;
    }

    Snake snake(1920/2, 1080/2, 1920, 1080);

    while(window_->isOpen()) {
        DrawBoundary();
        sf::Event event;
        while (window_->pollEvent(event)) {
            
            switch (event.type) {
                case sf::Event::Closed :
                    window_->close();
                    break;

                case sf::Event::KeyPressed :
                    switch (event.key.code) {
                    case sf::Keyboard::Escape : 
                        window_->close();
                        break;
                    
                    case sf::Keyboard::D :
                        snake.ChangeDirection(Direction::RIGHT);
                        break;
                    
                    case sf::Keyboard::W :
                        snake.ChangeDirection(Direction::UP);
                        break;

                    case sf::Keyboard::S :
                        snake.ChangeDirection(Direction::DOWN);
                        break;
                    
                    case sf::Keyboard::A :
                        snake.ChangeDirection(Direction::LEFT);
                        break;

                    default:
                        break;

                    }

                    break;

                default:  
                    break;
            }

        }

        DrawRabits(rabits);
        PrintSnake(snake.snake_body);

        window_->display();
        window_->clear();
    }
    return snake.GetScore();
}

void Gview::DrawBoundary() {
    std::array<sf::RectangleShape, 2> boundary;
    boundary.at(0) = sf::RectangleShape(sf::Vector2f(window_->getSize().x, boundary_width)); // horizontal
    boundary.at(1) = sf::RectangleShape(sf::Vector2f(boundary_width, window_->getSize().y)); //  vertical

    boundary.at(0).setFillColor(sf::Color::Blue);
    boundary.at(1).setFillColor(sf::Color::Blue);
    
    boundary.at(0).setPosition(0, 0);
    boundary.at(1).setPosition(0, 0);
    DrawRectangles(boundary.at(0));
    DrawRectangles(boundary.at(1));


    boundary.at(0).setPosition(0, window_->getSize().y - boundary_width);
    boundary.at(1).setPosition(window_->getSize().x - boundary_width, 0);
    DrawRectangles(boundary.at(0));
    DrawRectangles(boundary.at(1));
}

void Gview::PrintSnake(const std::vector<std::pair<int, int>>& snake_body) {
    sf::RectangleShape rectangle(sf::Vector2f(50.f, 50.f));

    for(int i = 0; i < snake_body.size(); ++i) {
        if(i == 0) {
            rectangle.setTexture(&texture_snake_head_);
        }else {

        }
        rectangle.setPosition(sf::Vector2f(snake_body.at(i).first, snake_body.at(i).second));
        window_->draw(rectangle);
    }
}

void Gview::DrawRectangles(const double pos_x, const double pos_y, const double length_x, const double length_y) {
    sf::RectangleShape rectangle(sf::Vector2f(length_x, length_y));
    rectangle.setPosition(pos_x, pos_y);
    
    window_->draw(rectangle);
}

void Gview::DrawRectangles(sf::RectangleShape& rectangle) {
    window_->draw(rectangle);
}

void Gview::DrawRabits(const std::map<int, int>& rabits) {

    sf::RectangleShape rectangle(sf::Vector2f(50.f, 50.f));
    rectangle.setTexture(&texture_rabit_);

    for(const auto el : rabits) {
        rectangle.setPosition(sf::Vector2f(el.first, el.second));
        window_->draw(rectangle);
    }
}

Gview::~Gview() {
    delete window_;
}