#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

class sfTextBox : public sf::Drawable, public sf::Transformable {
    bool active = true;
    std::string content;
    sf::RectangleShape shape;
    sf::Text text;
    sf::RenderWindow& target;   

    public:
        sfTextBox(sf::RenderWindow& target, sf::Font& font, sf::Vector2f position, std::string text, int textSize) : target(target){
            //Setup box
            this->shape.setFillColor(sf::Color(0xA4AEBDFF));
            this->shape.setOutlineColor(sf::Color::Black);
            this->shape.setOutlineThickness(1);

            //Setup text
            this->text.setFont(font);
            this->text.setColor(sf::Color::Black);
            this->text.setCharacterSize(textSize);
            this->text.setString(text);

            int width = (textSize * text.size()/ 2) + 10;
            int height = textSize + 5;

            //Set box size to acomodate text
            this->shape.setSize(sf::Vector2f(width, height));

            //Set position
            this->setPosition(position);
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

        std::string getText(){
            std::string temp = this->content;
            this->content = "";
            this->text.setString(content);
            return temp;
        }

        void setPosition(sf::Vector2f position){
            this->shape.setPosition(position);
            this->text.setPosition(position.x + 5, position.y - 1);
        }

        bool isValid(){
            return content.size() > 0;
        }

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override{
            target.draw(this->shape);
            target.draw(this->text);
        }

        void update(sf::Event& event){

            if (event.type == sf::Event::TextEntered && active)
            {

                //DEL key
                if(event.text.unicode == 8 && content.size() > 0){
                    content.pop_back();
                    text.setString(content);
                }
                //ASCII character
                else
                if (event.text.unicode >= 48 && event.text.unicode <= 57 && content.size() < 3)
                {
                    content += static_cast<char>(event.text.unicode);
                    text.setString(content);
                }
            }
        }

};