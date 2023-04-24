#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cmath>
#include <iostream>
#include <math.h>

#include "GameArea.hpp"

int main() {
  std::srand(time(nullptr));

  uint sx, sy, m;
  std::cout << "X: ";
  std::cin >> sx;

  std::cout << "Y: ";
  std::cin >> sy;

  std::cout << "Mines: ";
  std::cin >> m;

  GameArea area(sx, sy, m);

  area.debug_print();

  sf::RenderWindow window(sf::VideoMode(sx * 30, sy * 30), "Saper");

  sf::Font font;
  if (!font.loadFromFile("font.ttf"))
    std::cerr << "Can't load font" << std::endl;

  sf::Text number;
  number.setFont(font);
  number.setCharacterSize(24);
  number.setFillColor(sf::Color::Black);

  sf::RectangleShape mine(sf::Vector2f(24.0, 24.0));
  mine.setFillColor(sf::Color(255, 100, 100));
  mine.setOutlineThickness(3.);
  mine.setFillColor(sf::Color(235, 80, 80));

  sf::RectangleShape clicked(sf::Vector2f(24.0, 24.0));
  clicked.setFillColor(sf::Color(160, 160, 160));
  clicked.setOutlineThickness(3.);
  clicked.setOutlineColor(sf::Color(140, 140, 140));

  sf::RectangleShape unclicked(sf::Vector2f(24.0, 24.0));
  unclicked.setFillColor(sf::Color(80, 80, 80));
  unclicked.setOutlineThickness(3.);
  unclicked.setOutlineColor(sf::Color(60, 60, 60));

  sf::RectangleShape flag(sf::Vector2f(24.0, 24.0));
  flag.setFillColor(sf::Color(150, 255, 150));
  flag.setOutlineThickness(3.);
  flag.setOutlineColor(sf::Color(130, 235, 130));

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::MouseButtonReleased) {
        auto mouse_pos = sf::Mouse::getPosition(window);
        uint x = floor(mouse_pos.x / 30);
        uint y = floor(mouse_pos.y / 30);
        if (event.mouseButton.button == sf::Mouse::Left) {
          if (!area.get(x, y).is_flagged())
            area.click(x, y);
        } else {
          if (!area.get(x, y).is_clicked())
            area.flag(x, y);
        }
      }
    }

    window.clear(sf::Color(0, 0, 0));

    for (uint y = 0; y < area.size_y(); y++) {
      for (uint x = 0; x < area.size_x(); x++) {
        auto field = area.get(x, y);
        sf::Vector2f pos(x * 30. + 3, y * 30. + 3);

        if (field.is_mine() && field.is_clicked()) {
          mine.setPosition(pos);
          window.draw(mine);
        } else if (field.is_clicked()) {
          clicked.setPosition(pos);
          window.draw(clicked);

          if (field.get_amount_of_mines() > 0) {
            number.setString(std::to_string(field.get_amount_of_mines()));
            number.setPosition(sf::Vector2f(x * 30. + 10., y * 30.));
            window.draw(number);
          }
        } else if (field.is_flagged()) {
          flag.setPosition(pos);
          window.draw(flag);
        } else {
          unclicked.setPosition(pos);
          window.draw(unclicked);
        }
      }
    }

    window.display();
  }

  return 0;
}
