#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum Side{
    LEFT,
    RIGHT
};

//Node that contains ONLY INT data
class GFXNode{
    
    private:
        //Logical data
        int data;
        sf::VertexArray leftChildLine;
        sf::VertexArray rightChildLine;

        //SFML specific data
        sf::CircleShape shape; //GRAPHIC REPRESENTATION OF THE NODE
        sf::Text text;         //Position is based on the shape 

        void setLabel(){
            this->text.setString(std::to_string(this->data));
            //Set origin to center
            this->setLabelPosition();
        }

        void setLabelPosition(){
            //Get shape position
            auto shapePosition = this->shape.getPosition();

            //Get shape size
            auto shapeSize = this->shape.getRadius();
            //std::cout << shapeSize << std::endl;
            
            //Text bounds
            auto textBounds = this->text.getLocalBounds();
            //std::cout << "Text bounds: " << textBounds.width << " " << textBounds.height << std::endl;
            //Set text position
            this->text.setPosition(int(shapePosition.x + shapeSize - textBounds.width * 0.5 ) - 1, int(shapePosition.y + shapeSize - textBounds.height * 0.5 ) - 1);
        }

    public:
        GFXNode(sf::Font& ttf, int data) : shape(20,10), text("", ttf, 16), leftChildLine(sf::Lines, 2), rightChildLine(sf::Lines, 2){
            this->data = data;

            //Set shape properties
            this->shape.setFillColor(sf::Color::White);

            //Set text properties
            this->text.setColor(sf::Color::Black);
            this->setLabel();
        }
        
        void draw(sf::RenderWindow &window){
            window.draw(this->leftChildLine);
            window.draw(this->shape);
            window.draw(this->text);
        }

        void setPosition(float x, float y){
            this->shape.setPosition(x, y);
            this->setLabelPosition();
        }
        

        void connectTo(Side s, GFXNode* node){
            sf::VertexArray& line = s == LEFT ? this->leftChildLine : this->rightChildLine;

            auto thisCenter = this->getCenter();
            auto leftCenter = node->getCenter();
            line[0].position = thisCenter;
            line[1].position = leftCenter;
        }

        void connectToRight(GFXNode* right){
            auto thisCenter = this->getCenter();
            auto rightCenter = right->getCenter();
            this->rightChildLine[0].position = thisCenter;
            this->rightChildLine[1].position = rightCenter;
        }


        sf::Vector2f getCenter(){
            auto shapePosition = this->shape.getPosition();
            auto shapeSize = this->shape.getRadius();
            return sf::Vector2f(shapePosition.x + shapeSize, shapePosition.y + shapeSize);
        }

        void setData(int data){
            this->data = data;
        }
};