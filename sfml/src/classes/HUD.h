//GENERATE CLASS HUD THAT SHOW TEXT OF WHAT INSTRUCTION IS EXECUTING
#pragma once
#include <SFML/Graphics.hpp>
#include "../util/sfButton.h"
#include "../util/sfTextBox.h"
#include <functional>

#define HEIGHT_BAR 45

enum class Status{
    INSERT,
    REMOVE,
    FIND,
    NONE
};

class HUD
{
    sf::RenderWindow& target;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape bar;

    sfButton insertButton,removeButton,findButton;
    sfTextBox textBox;

    std::function<void(int)> insertFunction, removeFunction, findFunction;

    public:
        HUD(sf::RenderWindow& target): target(target)
        , insertButton(target, font, sf::Vector2f(0,0), "Insert", 32),
        removeButton(target, font, sf::Vector2f(0,0), "Remove", 32),
        findButton(target, font, sf::Vector2f(0,0), "Find", 32),
        textBox(target, font, sf::Vector2f(50,50), "___", 32)
        {
            if(!font.loadFromFile("assets/font2.ttf"))
                std::cout << "Error loading font" << std::endl;
            else
                std::cout << "Font loaded" << std::endl;   

            //set bar color
            this->bar.setSize(sf::Vector2f(target.getSize().x,HEIGHT_BAR));
            this->bar.setFillColor(sf::Color::White);
            //Set to bottom
            this->bar.setPosition(0, target.getSize().y - HEIGHT_BAR);

            //Set status text
            this->text.setCharacterSize(32);
            this->text.setFillColor(sf::Color::Black);
            this->text.setFont(font);
            this->text.setString("Status: ");

            this->text.setPosition(10, target.getSize().y - HEIGHT_BAR + 2 );
            this->insertButton.setPosition(sf::Vector2f(target.getSize().x / 4, target.getSize().y - HEIGHT_BAR + 4));
            this->removeButton.setPosition(sf::Vector2f(this->insertButton.getRightMostX() + 5, target.getSize().y - HEIGHT_BAR + 4));
            this->findButton.setPosition(sf::Vector2f(this->removeButton.getRightMostX() + 5, target.getSize().y - HEIGHT_BAR + 4));
            this->textBox.setPosition(sf::Vector2f(this->findButton.getRightMostX() + 5, target.getSize().y - HEIGHT_BAR + 4));
        
            //Set button functions
            this->insertButton.setOnClick([&](){assignFunctionInsert();});
            this->removeButton.setOnClick([&](){assignFunctionRemove();});
            this->findButton.setOnClick([&](){assignFunctionFind();});
        }

        

        void updateStatus(std::string text){
            this->text.setString(text);
        }

        void draw(){
            this->target.draw(this->bar);
            this->target.draw(this->text);
            this->target.draw(this->insertButton);
            this->target.draw(this->removeButton);
            this->target.draw(this->findButton);
            this->target.draw(this->textBox);
        }

        void update(sf::Event& event){
            this->insertButton.update();
            this->removeButton.update();
            this->findButton.update();
            this->textBox.update(event);
        }

        void assignFunction(std::function<void(int)> funcI, std::function<void(int)> funcR, std::function<void(int)> funcF){
            this->insertFunction = funcI;
            this->removeFunction = funcR;
            this->findFunction = funcF;
        }

        void assignFunctionInsert(){
            if(this->insertFunction && this->textBox.isValid())
                insertFunction(std::stoi(this->textBox.getText()));
        }

        void assignFunctionRemove(){
            if(this->removeFunction && this->textBox.isValid())
                removeFunction(std::stoi(this->textBox.getText()));
        }

        void assignFunctionFind(){
            if(this->findFunction && this->textBox.isValid())
                findFunction(std::stoi(this->textBox.getText()));
        }
};
