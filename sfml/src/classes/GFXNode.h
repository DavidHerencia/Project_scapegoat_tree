#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "sfLine.h"

enum Side{
    LEFT,
    RIGHT
};

//Node that contains ONLY INT data
class GFXNode : public sf::Drawable {

    sf::Line leftChildLine, rightChildLine;
    //SFML specific data
    sf::CircleShape shape; //GRAPHIC REPRESENTATION OF THE NODE
    sf::Text text;         //Position is based on the shape 

    public:
        GFXNode* leftChild{}, *rightChild{}, *parent{};
        int data,depth{};
    public:
        GFXNode(sf::Font& ttf, int data) : shape(20,10), text("", ttf, 16), leftChildLine(sf::Color::Green), rightChildLine(sf::Color::Blue){
            this->data = data;
            
            //Set shape properties
            this->shape.setFillColor(sf::Color::White);

            //Set text properties
            this->text.setColor(sf::Color::Black);
            this->setLabel();


            //Set center origin of shape
            this->shape.setOrigin(this->shape.getRadius(), this->shape.getRadius());

            this->setPosition(20,20);

            leftChildLine.update_point(this->getCenter(), this->getCenter());
            rightChildLine.update_point(this->getCenter(), this->getCenter());
        }
        
        void draw(sf::RenderTarget &target, sf::RenderStates states) const {
            target.draw(this->leftChildLine);
            target.draw(this->rightChildLine);
            target.draw(this->shape);
            target.draw(this->text);
        }

        void setPosition(float x, float y){
            this->shape.setPosition(x, y);
            this->setLabelPosition();

            //Update lines
            if(this->leftChild != nullptr)
                this->leftChildLine.update_point(this->getCenter(), this->leftChild->getCenter());
            
            if(this->rightChild != nullptr)
                this->rightChildLine.update_point(this->getCenter(), this->rightChild->getCenter());
        }
        

        void connectTo(Side s, GFXNode* node){
            sf::Line& line = (s == LEFT) ?  (this->leftChildLine) : (this->rightChildLine);
            if(s == LEFT)
                this->leftChild = node;
            else
                this->rightChild = node;

            auto thisCenter = this->getCenter();
            auto otherCenter = node->getCenter();
            line.update_point(this->getCenter(),otherCenter);
            //std::cout << "Connected " << this->data << " to " << node->data << "FROM SIDE" << ((s == LEFT) ? "LEFT" : "RIGHT") << std::endl;
        }

        void updateChildrenLines() {
            if(this->leftChild != nullptr)
                this->leftChildLine.update_point(this->getCenter(), this->leftChild->getCenter());
            
            if(this->rightChild != nullptr)
                this->rightChildLine.update_point(this->getCenter(), this->rightChild->getCenter());
        }

        sf::Vector2f getCenter(){
            auto shapePosition = this->shape.getPosition();
            return sf::Vector2f(shapePosition.x , shapePosition.y);
        }

        void setData(int data){
            this->data = data;
            this->setLabel();
        }

        int getRadius(){
            return this->shape.getRadius();
        }

        void select(bool val){
            this->shape.setFillColor((val) ? sf::Color::Red : sf::Color::White);
        }

    private:
        void setLabel(){
            this->text.setString(std::to_string(this->data));
            //Set origin to center
            this->setLabelPosition();
        }
        void setLabelPosition(){
            //Get shape position
            auto shapePosition = this->shape.getPosition();
            //Text bounds
            auto textBounds = this->text.getLocalBounds();
            //Set text position
            this->text.setPosition(int(shapePosition.x - textBounds.width * 0.5 ) - 1, int(shapePosition.y - textBounds.height * 0.5 ) - 1);
        }
};