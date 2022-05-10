#include "gview.h"

const size_t boundary_width_x = 20;
const size_t boundary_width_y = 30;
const size_t rabits_quan = 30;

const size_t screen_resolution_x = 1920;
const size_t screen_resolution_y = 1080;

const size_t model = 50;

const size_t x_blocks = (screen_resolution_x - boundary_width_x) / model;
const size_t y_blocks = (screen_resolution_y - boundary_width_y) / model;

Gview::Gview() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    window_ = new sf::RenderWindow(sf::VideoMode(screen_resolution_x, screen_resolution_y), "", sf::Style::Fullscreen, settings);
    window_->setVerticalSyncEnabled(true);

    if(!texture_rabit_.loadFromFile("Images/Rabit.png")) {
        delete window_;
        exit(-1);
    }
    texture_rabit_.setSmooth(true);


    if(!texture_snake_head_right_.loadFromFile("Images/SnakeHeadRight.png")) {
        delete window_;
        exit(-1);
    }
    texture_snake_head_right_.setSmooth(true);

    if(!texture_snake_head_up_.loadFromFile("Images/SnakeHeadUp.png")) {
        delete window_;
        exit(-1);
    }
    texture_snake_head_up_.setSmooth(true);

    if(!texture_snake_head_left_.loadFromFile("Images/SnakeHeadLeft.png")) {
        delete window_;
        exit(-1);
    }
    texture_snake_head_left_.setSmooth(true);

    if(!texture_snake_head_down_.loadFromFile("Images/SnakeHeadDown.png")) {
        delete window_;
        exit(-1);
    }
    texture_snake_head_down_.setSmooth(true);
}

size_t Gview::Draw() {
    
    sf::Music music;
    // if(!music.openFromFile("Sounds/SnakeTheme-Song.wav")) {
    //     return -1;
    // }
    if(!music.openFromFile("Sounds/INSTASAMKA.wav")) {
        return -1;
    }
    music.play();
    music.setLoop(true);

    std::map<int, int> rabits;

    for(int i = 0; i < rabits_quan; ++i) {
        std::pair<int, int> tmp = View::RandCooord(x_blocks, y_blocks);
        rabits[tmp.first] = tmp.second;
    }
    
    Snake snake(x_blocks/2, y_blocks/2, x_blocks, y_blocks);
    while(window_->isOpen()) {
        if(snake.IsAlive()) {
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
                            snake.Move();
                            break;
                        
                        case sf::Keyboard::W :
                            snake.ChangeDirection(Direction::DOWN);
                            snake.Move();
                            break;

                        case sf::Keyboard::S :
                            snake.ChangeDirection(Direction::UP);
                            snake.Move();
                            break;
                        
                        case sf::Keyboard::A :
                            snake.ChangeDirection(Direction::LEFT);
                            snake.Move();
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
            PrintSnake(snake.snake_body, snake.GetDirection());
            snake.Move();
            IsGrow(rabits, snake);

            window_->display();
            window_->clear();
            usleep(500000);
        }else {
            return snake.GetScore();;
        }
    }
    return snake.GetScore();
}

void Gview::DrawBoundary() {
    std::array<sf::RectangleShape, 2> boundary;
    boundary.at(0) = sf::RectangleShape(sf::Vector2f(window_->getSize().x, boundary_width_y)); // horizontal
    boundary.at(1) = sf::RectangleShape(sf::Vector2f(boundary_width_x, window_->getSize().y)); //  vertical

    boundary.at(0).setFillColor(sf::Color::Blue);
    boundary.at(1).setFillColor(sf::Color::Blue);
    
    boundary.at(0).setPosition(0, 0);
    boundary.at(1).setPosition(0, 0);
    DrawRectangles(boundary.at(0));
    DrawRectangles(boundary.at(1));


    boundary.at(0).setPosition(0, window_->getSize().y - boundary_width_y);
    boundary.at(1).setPosition(window_->getSize().x - boundary_width_x, 0);
    DrawRectangles(boundary.at(0));
    DrawRectangles(boundary.at(1));
}

void Gview::PrintSnake(const std::vector<std::pair<int, int>>& snake_body, Direction dir) {
    sf::RectangleShape rectangle(sf::Vector2f(model, model));

    for(int i = 0; i < snake_body.size(); ++i) {
        if(i == 0) {
            switch (dir) {
            case Direction::UP :
                rectangle.setTexture(&texture_snake_head_up_);
                break;

            case Direction::DOWN :
                rectangle.setTexture(&texture_snake_head_down_);
                break;

            case Direction::LEFT :
                rectangle.setTexture(&texture_snake_head_left_);
                break;

            case Direction::RIGHT :
                rectangle.setTexture(&texture_snake_head_right_);
                break;
            
            default:
                break;
            }
            
        }else {
            rectangle.setFillColor(sf::Color::Blue);
        }
        rectangle.setPosition(sf::Vector2f(snake_body.at(i).first * model, snake_body.at(i).second * model));
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

    sf::RectangleShape rectangle(sf::Vector2f(model, model));
    rectangle.setTexture(&texture_rabit_);
    for(const auto el : rabits) {
        rectangle.setPosition(sf::Vector2f(el.first * model, el.second * model));
        window_->draw(rectangle);
    }
}

void Gview::IsGrow(std::map<int, int>& rabits, Snake& snake) {
    if(rabits.count(snake.snake_body.at(0).first) && rabits.at(snake.snake_body.at(0).first) == snake.snake_body.at(0).second) {
        auto tmp = snake.snake_body.at(0).first;
        snake.SnakeGrow(std::pair<float, float>(snake.snake_body.at(0).first, rabits.at(snake.snake_body.at(0).first)));
        rabits.erase(tmp);
    }
}

Gview::~Gview() {
    delete window_;
}