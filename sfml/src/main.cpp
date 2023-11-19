#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

#include "classes/GFXNode.h"
#include "classes/TreeHandler.h"
#include "structures/Scgtree.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;

    sf::RenderWindow window(sf::VideoMode(640, 480), "Scapegoat-tree Visualizer", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    sf::View view(sf::FloatRect(0, 0, 640, 480));
    window.setView(view);

    //Create root node
    TreeHandler<int> treeHandler(window);
    ScgTree<int> tree(treeHandler);

    std::thread t([&tree](){
        for(int i = 0; i < 100; i++){
            tree.insert(rand() % 100);
            sf::sleep(sf::milliseconds(10));
            std::cout << "POS: " << i << std::endl;
        }
    });
    

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if(event.type == sf::Event::Resized){
                view.setSize(event.size.width, event.size.height);
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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            view.zoom(0.99f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            view.zoom(1.01f);
        }

        window.setView(view);


        window.clear();
        treeHandler.draw();
        window.display();
    }
}