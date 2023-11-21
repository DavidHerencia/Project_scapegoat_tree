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

    //For running in background
    bool focus = true,running = false,inSearch = false;
    ScgNode<int>* found = nullptr;

    //Create root node
    TreeHandler<int> treeHandler(window);
    ScgTree<int> tree(treeHandler);
    std::mutex mtx;
    //Create hud
    //HUD hud(window, font);
    HUD hud(window);

    //Set lambdas 
    std::function<void(int)> insertFunction = [&tree, &running, &found](int value){
        if(running)
            return;

        //CLEAR FOUND
        if(found != nullptr){
            found->graphic->select(false);
            found = nullptr;
        }

        running = true;
        tree.insert(value);
        running = false;
    };
    std::function<void(int)> removeFunction = [&tree,&running,&found](int value){
        if(running)
            return;

        //CLEAR FOUND
        if(found != nullptr){
            found->graphic->select(false);
            found = nullptr;
        }

        running = true;
        tree.remove(value);
        running = false;
    };
    std::function<void(int)> findFunction = [&tree,&running,&found,&view,&inSearch](int value){
        if (running)
            return;

        running = true;

        //Remove found
        if(found != nullptr){
            found->graphic->select(false);
            found = nullptr;
        }

        std::thread t([&tree, value, &found, &running,&view,&inSearch](){
            found = tree.getRoot();
            inSearch = true;
            ScgNode<int>* prev = nullptr; // start at root
            while (found != nullptr) {
            
                if(prev != nullptr)
                    prev->graphic->setBorder(false);


                if (value == found->data)
                    break;

                found->graphic->setBorder(true);  
                sf::sleep(sf::milliseconds(900));
  
                
                prev = found;
                if (value < found->data) {
                    found = found->left;
                } else {
                    found = found->right;
                }

            }

            if(found != nullptr)
                found->graphic->select(true);

            //Find node and center
            running = false;
            inSearch = false;
        });
        t.detach();
    };

    hud.assignFunction(insertFunction, removeFunction, findFunction);

    //Asign values;
    tree.setSleepTime(0);
    for(int i = 0; i < 999; i++){
        tree.insert(i);
    }
    tree.setSleepTime(1000);

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
            if(!inSearch){
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
            }else if (found != nullptr) {
                //Calculate distance to next node

                auto center = found->graphic->getTarget();
                auto viewCenter = view.getCenter();
                auto distance = sqrt(pow(center.x - viewCenter.x, 2) + pow(center.y - viewCenter.y, 2));
                if(distance > 1){
                    auto direction = center - viewCenter;
                    auto movement = direction * 0.1f;
                    view.move(movement);
                }
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