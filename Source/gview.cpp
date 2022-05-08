#include "model.h"
#include "gview.h"

size_t Gview::Draw() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "", sf::Style::Fullscreen, settings);

    window.SetVerticalSyncEnabled(true);
}