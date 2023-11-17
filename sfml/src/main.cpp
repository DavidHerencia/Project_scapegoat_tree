#include <SFML/Graphics.hpp>
#include <iostream>

#include "classes/GFXNode.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;


    auto window = sf::RenderWindow(sf::VideoMode(640, 480), "Scapegoat-tree Visualizer", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    //Create text
    sf::Font font;
    if(!font.loadFromFile("assets/font.ttf"))
        std::cout << "Error loading font" << std::endl;
    else
        std::cout << "Font loaded" << std::endl;


    GFXNode node(font, 5);
    GFXNode node2(font, 15);

    node2.setPosition(50, 50);
    node.connectTo(RIGHT,&node2);



    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        node.draw(window);
        node2.draw(window);
        window.display();
    }
}