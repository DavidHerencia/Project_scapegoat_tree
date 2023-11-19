#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Node.h"

#define MIN_NODE_SEP 15.0f

//This class is responsible for handling the drawing and positioning of the nodes
template <typename T>
class TreeHandler {
    //SFML specific data
    sf::Font font;
    sf::RenderTarget& target;
    std::list<ScgNode<T>*> nodes;
    ScgNode<T>* root = nullptr;

    public:
        TreeHandler(sf::RenderTarget& _target): target(_target){
            if(!font.loadFromFile("assets/font.ttf"))
                std::cout << "Error loading font" << std::endl;
            else
                std::cout << "Font loaded" << std::endl;   
        }

        void addNode(ScgNode<T>* &node){
            node->graphic = new GFXNode<T>(this->font, node->data);
            if(this->root == nullptr){
                this->root = node;
                this->root->graphic->setPosition(this->target.getSize().x/2, 50);
            }

            this->nodes.push_back(node);
            reArrange(this->root);
        }
        
        void draw(){
            for(auto node : nodes){
                target.draw(*(node->graphic));
                node->graphic->updateChildrenLines((node->left != nullptr) ? node->left->graphic->getCenter() : node->graphic->getCenter(), (node->right != nullptr) ? node->right->graphic->getCenter() : node->graphic->getCenter());
            }
        }

    private:
        void reArrange(ScgNode<T>* node){
            //Find most left leaf
            if(node == nullptr)
                return;

            long offsetLeft = 12.5 * ((!node->left) ? 0 : getWeight(node->left->right)) + 12.5;
            long offsetRight = 12.5 * ((!node->right) ? 0 : getWeight(node->right->left)) + 12.5;

            std::cout << "Node: " << node->data << " offsetLeft: " << offsetLeft << " offsetRight: " << offsetRight << std::endl;

            auto center = node->graphic->getCenter();

            if(node->left != nullptr)
                node->left->graphic->setPosition(center.x - offsetLeft, center.y + 50);
            
            if(node->right != nullptr)
                node->right->graphic->setPosition(center.x + offsetRight, center.y + 50);

            reArrange(node->left);
            reArrange(node->right);
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


/*

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
*/