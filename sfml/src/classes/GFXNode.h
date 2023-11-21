#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../util/sfLine.h"
#include <cmath>

#define PI 3.14159265358979323846

enum Side{
    LEFT,
    RIGHT
};

float noise(float x){
    return sin(2 * x) + sin(PI * x);
}

//Node that contains ONLY INT data
template <typename T>
class GFXNode {

    sf::Line leftChildLine, rightChildLine;
    //SFML specific data
    sf::CircleShape shape; //GRAPHIC REPRESENTATION OF THE NODE
    sf::Text text;         //Position is based on the shape 
    sf::Clock clock;

    sf::Vector2f targetPosition;
    float velocity = 10.0f;

    public:
        T& dataHolder;
    public:
        GFXNode(sf::Font& ttf, T& _holder) : shape(20,10), dataHolder(_holder), text("", ttf, 16), leftChildLine(sf::Color::Green), rightChildLine(sf::Color::Blue){
            
            //Set shape properties
            this->shape.setFillColor(sf::Color::White);

            //Set text properties
            this->text.setColor(sf::Color::Black);
            this->setLabel();


            //Set center origin of shape
            this->shape.setOrigin(this->shape.getRadius(), this->shape.getRadius());
            this->shape.setOutlineColor(sf::Color::Magenta);
            
            this->setPosition(20,20);
            
            leftChildLine.update_point(this->getCenter(), this->getCenter());
            rightChildLine.update_point(this->getCenter(), this->getCenter());

        }
        
        void drawMain(sf::RenderTarget &target, sf::RenderStates states) const {
            target.draw(this->shape);
            target.draw(this->text);
        }

        void drawLines(sf::RenderTarget &target, sf::RenderStates states) const {
            target.draw(this->leftChildLine);
            target.draw(this->rightChildLine);

        }

        
        void update(float dt){
            auto currentPosition = this->getCenter();
            auto direction = this->targetPosition - currentPosition;
            auto distance = sqrt(direction.x * direction.x + direction.y * direction.y);
            if(distance > 1){
                auto movement = direction * velocity * dt;
                this->shape.move(movement);
                this->setLabelPosition();
            }

            float ticks = clock.getElapsedTime().asSeconds() * 0.5;

            //Add noisy movement
            this->shape.move(sf::Vector2f(noise(ticks + targetPosition.x) * 0.25, noise(ticks + targetPosition.y) * 0.25));
        }

        void setPosition(float x, float y){
            this->shape.setPosition(x, y);
            this->setTarget(x,y);
            this->setLabelPosition();
        }

        
        void setTarget(float x, float y){
            this->targetPosition = sf::Vector2f(x,y);
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

        void updateChildrenLines(sf::Vector2f left, sf::Vector2f right) {
            this->leftChildLine.update_point(this->getCenter(), left);
            this->rightChildLine.update_point(this->getCenter(), right);
        }

        void updateLabel(){
            this->setLabel();
        }

        sf::Vector2f getCenter(){
            auto shapePosition = this->shape.getPosition();
            return sf::Vector2f(shapePosition.x , shapePosition.y);
        }

        sf::Vector2f getTarget(){
            return this->targetPosition;
        }
        
        int getRadius(){
            return this->shape.getRadius();
        }

        void select(bool val){
            this->shape.setFillColor((val) ? sf::Color::Red : sf::Color::White);
        }

        void setBorder(bool val, sf::Color color = sf::Color::Magenta){
            this->shape.setOutlineThickness((val) ? 4 : 0);
            this->shape.setOutlineColor(color);
        }

        bool isLeaf(){
            return (this->leftChild == nullptr && this->rightChild == nullptr);
        }

    private:
        void setLabel(){
            this->text.setString(std::to_string(this->dataHolder));
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