#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "GFXNode.h"

#define MIN_NODE_SEP 15.0f

class TreeHandler {
    //SFML specific data
    sf::Font font;
    sf::RenderTarget& target;
    std::list<GFXNode*> nodes;
    GFXNode* root{};

    

    //Logical data
    int maxDepth{};
    int maxNodeCount{};

    public:
        TreeHandler(sf::RenderTarget& _target): target(_target){
            if(!font.loadFromFile("assets/font.ttf"))
                std::cout << "Error loading font" << std::endl;
            else
                std::cout << "Font loaded" << std::endl;   
            
            maxDepth = 0;
            maxNodeCount = 0;
        }

        void addNode(int data){
            if(this->root == nullptr){
                this->root = new GFXNode(this->font, data);
                this->root->setPosition(this->target.getSize().x/2, 50);
                this->root->depth = 0;
                this->nodes.push_back(this->root);
            }
            else{

                GFXNode* temp, *parent;
                temp = parent = this->root;
                int depth = 0;
                while(temp != nullptr){
                    depth++;
                    parent = temp;
                    if(data < temp->data)
                        temp = temp->leftChild;
                    else if (data > temp->data)
                        temp = temp->rightChild;
                    else
                        return;
                    
                }

                if(depth > this->maxDepth){
                    this->maxDepth = depth;
                }

                temp = new GFXNode(this->font, data);
                temp->depth = depth;
                temp->parent = parent;
                parent->connectTo((data < parent->data) ? LEFT : RIGHT, temp);
                this->nodes.push_back(temp);
                reArrange(this->root);

                std::cout << "VALUE INSERTED: " << data << " SIDE: " << (depth) << "maxDepth" << maxDepth << "\n";   
            }
        }

        void draw(){
            for(auto node : nodes){
                target.draw(*node);
                node->updateChildrenLines();
            }
        }

    private:
        void reArrange(GFXNode* node){
            //sf::sleep(sf::milliseconds(100));
            //Arrange nodes based on weight
            //Find most left leaf
            if(node == nullptr)
                return;


            long offsetLeft = 25 * ((!node->leftChild) ? 0 : getWeight(node->leftChild->rightChild)) + 5;
            long offsetRight = 25 * ((!node->rightChild) ? 0 : getWeight(node->rightChild->leftChild)) + 5;

            std::cout << "Node: " << node->data << " offsetLeft: " << offsetLeft / 30 << " offsetRight: " << offsetRight / 30 << std::endl;

            auto center = node->getCenter();

            if(node->leftChild != nullptr)
                node->leftChild->setPosition(center.x - offsetLeft, center.y + 50);
            
            if(node->rightChild != nullptr)
                node->rightChild->setPosition(center.x + offsetRight, center.y + 50);

            reArrange(node->leftChild);
            reArrange(node->rightChild);
        }

        float getWeight(GFXNode* node){
            if(node == nullptr)
                return 0.75;
            else if(node->isLeaf())
                return getWeight(node->leftChild) + getWeight(node->rightChild) +  1;
            else if (node->leftChild != nullptr && node->rightChild == nullptr)
                return getWeight(node->leftChild) + getWeight(node->rightChild) +  1;
            else 
                return getWeight(node->leftChild) + getWeight(node->rightChild) + 1;

        }

};