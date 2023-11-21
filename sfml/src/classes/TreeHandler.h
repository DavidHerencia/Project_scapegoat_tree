#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <mutex>
#include "Node.h"

#define MIN_NODE_SEP 15.0f

#define INITIAL_X 20
#define INITIAL_Y 20

//This class is responsible for handling the drawing and positioning of the nodes
template <typename T>
class TreeHandler {
    //SFML specific data
    sf::Font font;
    sf::RenderWindow& target;
    std::list<ScgNode<T>*> nodes;

    public:
        TreeHandler(sf::RenderWindow& _target): target(_target){
            if(!font.loadFromFile("assets/font.ttf"))
                std::cout << "Error loading font" << std::endl;
            else
                std::cout << "Font loaded" << std::endl;   
        }

        void addNode(ScgNode<T>* &node){
            node->graphic = new GFXNode<T>(this->font, node->data);
            node->graphic->setPosition(INITIAL_X, INITIAL_Y);
            this->nodes.push_back(node);
        }

        void removeNode(ScgNode<T>* &node){
            this->nodes.remove(node);
            delete node->graphic;
            delete node;
        }
        
        void draw(){
            //Draw all LINES
            for(auto node : nodes){
                if(node == nullptr)
                    continue;
                
                node->graphic->drawLines(this->target, sf::RenderStates::Default);
            }

            //Draw all NODES
            for(auto node : nodes){
                 if(node == nullptr)
                    continue;
                node->graphic->drawMain(this->target, sf::RenderStates::Default);
            }
        }

        void update(float dt){
            for (auto node : nodes){
                if(node == nullptr)
                    continue;
                node->graphic->update(dt);
                node->graphic->updateChildrenLines((!node->left) ? node->graphic->getCenter() : node->left->graphic->getCenter(), (!node->right) ? node->graphic->getCenter() : node->right->graphic->getCenter());
            }
        }

        void arrangeNodes(ScgNode<T>* node, bool forceUpdate = false){
            std::cout << "Re arranging" << std::endl;
            //First node is always the "root"
            node->graphic->setPosition(this->target.getSize().x/2, 50);   
            reArrange(node);
            std::cout << "Re arranged" << std::endl;
        }

    private:
        void reArrange(ScgNode<T>* node){
            //Find most left leaf
            if(node == nullptr)
                return;

            long offsetLeft = 12.5 * ((!node->left) ? 0 : getWeight(node->left->right)) + 12.5;
            long offsetRight = 12.5 * ((!node->right) ? 0 : getWeight(node->right->left)) + 12.5;

            //std::cout << "Node: " << node->data << " offsetLeft: " << offsetLeft << " offsetRight: " << offsetRight << std::endl;

            auto center = node->graphic->getTarget();

            if(node->left != nullptr){
                node->left->graphic->setTarget(center.x - offsetLeft, center.y + 50);
                reArrange(node->left);
            }
            
            if(node->right != nullptr){
                node->right->graphic->setTarget(center.x + offsetRight, center.y + 50);
                reArrange(node->right);
            }
            

        }

        float getWeight(ScgNode<T>* node){
            if(node == nullptr)
                return 0.75;
            else if(node->isLeaf())
                return getWeight(node->left) + getWeight(node->right) +  1;
            else if (node->left != nullptr && node->right == nullptr)
                return getWeight(node->left) + getWeight(node->right) +  1;
            else 
                return getWeight(node->left) + getWeight(node->right) + 1;

        }
};