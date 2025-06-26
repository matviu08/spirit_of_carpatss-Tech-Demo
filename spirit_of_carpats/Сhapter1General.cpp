#include "location.h"
#include "chapter1_house.h"

void Generation_of_chapter1(sf::RenderWindow& window, sf::Sprite& background, sf::Text& backButtonWithSetings, Player& pl, sf::Font font, const std::optional<sf::Event>& event, Menu& menu) {

    scene_home(window, background, backButtonWithSetings, pl, font, event, menu);
}
