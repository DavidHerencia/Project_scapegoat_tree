#pragma once
#include <SFML/Graphics.hpp>

//Node that contains ONLY INT data
class GFXNode{
    
    private:
        //Logical data
        int data;
        GFXNode *left;
        GFXNode *right;


        //SFML specific data
        sf::CircleShape shape; //GRAPHIC REPRESENTATION OF THE NODE
        sf::Text text;         //Position is based on the shape 

        void setLabel(){
            this->text.setString(std::to_string(this->data));
            //Set origin to center
            this->text.setOrigin(this->text.getLocalBounds().width/2, this->text.getLocalBounds().height/2);
            this->setLabelPosition();
        }

        void setLabelPosition(){
            //Get shape position
            auto shapePosition = this->shape.getPosition();

            //Get shape size
            auto shapeSize = this->shape.getRadius();
            
            //Text bounds
            auto textBounds = this->text.getLocalBounds();
            //Set text position
            this->text.setPosition(int(shapePosition.x + shapeSize - 2 ), int(shapePosition.y + shapeSize - 1));
        }

    public:
        GFXNode(sf::Font& ttf, int data) : shape(24,16),text("", ttf, 16){
            this->data = data;
            this->left = nullptr;
            this->right = nullptr;

            //Set shape properties
            this->shape.setFillColor(sf::Color::White);
        
            //Set text properties
            this->text.setColor(sf::Color::Black);
            this->setLabel();
        }
        
        void draw(sf::RenderWindow &window){
            window.draw(this->shape);
            window.draw(this->text);
        }

        void setPosition(float x, float y){
            this->shape.setPosition(x, y);
            this->setLabelPosition();
        }


        /*
        *   Getters and setters
        */

        int getData(){
            return this->data;
        }

        GFXNode* getLeft(){
            return this->left;
        }

        GFXNode* getRight(){
            return this->right;
        }

        void setLeft(GFXNode* left){
            this->left = left;
        }

        void setRight(GFXNode* right){
            this->right = right;
        }

        void setData(int data){
            this->data = data;
        }
};