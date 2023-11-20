#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <functional>

class sfButton : public sf::Drawable, public sf::Transformable
{
    public:
        sfButton(sf::RenderWindow& target, sf::Font& font, sf::Vector2f position, std::string text, int textSize) : target(target), font(font){
            //Setup box
            this->shape.setFillColor(sf::Color::White);
            this->shape.setOutlineColor(sf::Color::Black);
            this->shape.setOutlineThickness(1);

            //Setup text
            this->text.setFont(font);
            this->text.setColor(sf::Color::Black);
            this->text.setCharacterSize(textSize);
            this->text.setString(text);

            this->width = (textSize * text.size()/ 2) + 10;
            this->height = textSize + 5;

            //Set box size to acomodate text
            this->shape.setSize(sf::Vector2f(this->width, this->height));

            //Set position
            this->setPosition(position);
        }

        int getRightMostX(){
            return this->width + this->shape.getPosition().x;
        }

        bool isClicked(){
            return sf::Mouse::isButtonPressed(sf::Mouse::Left) && isOver();
        }

        bool isOver(){
            sf::Vector2i mousePos = sf::Mouse::getPosition(target);
            sf::Vector2f worldPos = target.mapPixelToCoords(mousePos);
            sf::Vector2f mousePosF(worldPos.x, worldPos.y);
            
            return this->shape.getGlobalBounds().contains(mousePosF);
        }

        void setPosition(sf::Vector2f position){
            this->shape.setPosition(position);
            this->text.setPosition(position.x + 5, position.y - 1);
        }

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override{
            target.draw(this->shape);
            target.draw(this->text);
        }

        void update(){
            //Check if mouse is hovering over button
            if(isOver()){
                this->shape.setFillColor(sf::Color::Black);
                this->text.setColor(sf::Color::White);
            }else{
                this->shape.setFillColor(sf::Color::White);
                this->text.setColor(sf::Color::Black);
            }

            //Check if button is clicked
            if(isClicked() && this->clickFunction && !press){
                press = true;
                this->clickFunction();
            }
            //Check if button is released
            if(!isClicked()){
                press = false;
            }
        }

        void setOnClick(std::function<void()> onClick){
            this->clickFunction = onClick;
        }

    private:
        sf::RenderWindow& target;
        sf::Font& font;
        sf::Text text;
        sf::RectangleShape shape;
        int width, height;
        std::function<void()> clickFunction;
        bool press = false;
};