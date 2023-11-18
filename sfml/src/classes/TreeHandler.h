#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "GFXNode.h"

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
                rearrange();
                this->nodes.push_back(temp);

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
    void rearrange() {
        std::cout << "Rearranging" << std::endl;
        // Setea la posición inicial y el espacio horizontal
        float initialX = target.getSize().x / 2;
        float horizontalSpace = 10.0f;

        rearrangeNodes(root, initialX, 50.0f, horizontalSpace);
        }

    void rearrangeNodes(GFXNode* node, float x, float y, float horizontalSpace) {
        if (node == nullptr)
            return;

        // Calcular el espacio necesario para los hijos
        float spaceNeeded = horizontalSpace * pow(2, (maxDepth - node->depth) + 1);

        // Ajustar la posición para evitar colisiones
        if (node->leftChild != nullptr) {
            float childX = x - spaceNeeded / 2;
            node->leftChild->setPosition(childX, y + 60.0f);
            rearrangeNodes(node->leftChild, childX, y + 60.0f, horizontalSpace / 2);
        }

        if (node->rightChild != nullptr) {
            float childX = x + spaceNeeded / 2;
            node->rightChild->setPosition(childX, y + 60.0f);
            rearrangeNodes(node->rightChild, childX, y + 60.0f, horizontalSpace / 2);
        }
    }
};