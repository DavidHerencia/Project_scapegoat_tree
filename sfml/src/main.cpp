#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

#include "classes/GFXNode.h"
#include "classes/TreeHandler.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;

    sf::RenderWindow window(sf::VideoMode(1000, 600), "Scapegoat-tree Visualizer", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect(0, 0, 1000, 600));
    window.setView(view);

    //Create root node
    TreeHandler tree(window);

    std::thread t([&tree](){
            //Insert random values
            tree.addNode(50);
            tree.addNode(25);
            tree.addNode(75);
            tree.addNode(12);
            tree.addNode(37);
            tree.addNode(62);
            tree.addNode(87);
            tree.addNode(6);
            tree.addNode(18);
            tree.addNode(31);
            tree.addNode(43);
            tree.addNode(56);
            tree.addNode(68);
            tree.addNode(81);
            tree.addNode(93);
            tree.addNode(3);
            tree.addNode(9);
            tree.addNode(15);
            tree.addNode(21);
            tree.addNode(28);
            tree.addNode(34);
            sf::sleep(sf::milliseconds(500));


            std::cout << "Done!" << std::endl;
    });

    t.detach();
    

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            view.move(-10, 0);;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            view.move(10, 0);;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            view.move(0, -10);;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            view.move(0, 10);;
        }

        window.setView(view);


        window.clear();
        tree.draw();
        window.display();
    }
}