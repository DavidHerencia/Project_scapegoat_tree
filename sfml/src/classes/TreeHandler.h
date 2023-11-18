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
                    else
                        temp = temp->rightChild;
                }

                if(depth > this->maxDepth){
                    this->maxDepth = depth;
                }

                temp = new GFXNode(this->font, data);
                temp->depth = depth;
                temp->parent = parent;
                parent->connectTo((data < parent->data) ? LEFT : RIGHT, temp);
                this->nodes.push_back(temp);
                rearrange();
            }
        }

        void draw(){
            for(auto node : nodes){
                target.draw(*node);
                node->updateChildrenLines();
            }
            
        }

    private:
    void rearrange() {
        std::cout << "Rearranging" << std::endl;
        // Setea la posición inicial y el espacio horizontal

        rearrangeNodes(root);
        }

    void rearrangeNodes(GFXNode* node) {
        if (node == nullptr)
            return;

        //Set children positions
        float offsetX = MIN_NODE_SEP * pow(2,(this->maxDepth - node->depth));

        if(node->leftChild != nullptr){
            node->leftChild->setPosition(node->getCenter().x - offsetX, node->getCenter().y + 100);
        }
        if(node->rightChild != nullptr){
            node->rightChild->setPosition(node->getCenter().x + offsetX, node->getCenter().y + 100);
        }

        rearrangeNodes(node->leftChild);
        rearrangeNodes(node->rightChild);
    }
};