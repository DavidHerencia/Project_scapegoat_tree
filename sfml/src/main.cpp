#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

#include "classes/GFXNode.h"
#include "classes/TreeHandler.h"
#include "classes/HUD.h"
#include "structures/Scgtree.h"
#include <mutex>

bool running = false;


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;

    sf::RenderWindow window(sf::VideoMode(1280, 480), "Scapegoat-tree Visualizer", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    sf::View view(sf::FloatRect(0, 0, 1280, 480));
    window.setView(view);

    bool focus = true,running = false;

    //Create root node
    TreeHandler<int> treeHandler(window);
    ScgTree<int> tree(treeHandler);
    std::mutex mtx;
    //Create hud
    //HUD hud(window, font);
    HUD hud(window);

    //Set lambdas 
    std::function<void(int)> insertFunction = [&tree, &running, &mtx](int value){
        if(running)
            return;

        running = true;


            tree.insert(value);
            running = false;



    };
    std::function<void(int)> removeFunction = [&tree,&running](int value){
        if(running)
            return;

        running = true;
        tree.remove(value);
        running = false;
    };
    std::function<void(int)> findFunction = [&tree,&running](int value){
        if (running)
            return;

        running = true;
        tree.find(value);
        running = false;
    };

    hud.assignFunction(insertFunction, removeFunction, findFunction);

    sf::Event event;
    while (window.isOpen())
    {
        for (event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::GainedFocus)
				focus = true;
			else if (event.type == sf::Event::LostFocus)
				focus = false;
            else if(event.type == sf::Event::Resized){
                view.setSize(event.size.width, event.size.height);
            }
        }

        //std::cout << "Focus: " << focus << std::endl;
        
        if(focus){
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

            //FORCE TREEHANDLER REARRANGE
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                //treeHandler.reArrange();
                tree.pretty();
            }

            treeHandler.update(0.016f);
            
            if(!running)
                hud.update(event);

        }

        window.clear();
        window.setView(view);
        treeHandler.draw();

        //Set hud text
        window.setView(window.getDefaultView());
        hud.draw();
        window.display();
    }
}