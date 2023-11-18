#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
//Line with thickness

namespace sf {
    class Line : public sf::Drawable {
    public:

        Line(sf::Color col): color(col), thickness(5.f){}

        void update_point(const sf::Vector2f& point1,const sf::Vector2f& point2){
            m_point1 = point1;
            m_point2 = point2;
            update();
            updateColor();
        }

        void draw(sf::RenderTarget &target, sf::RenderStates states) const
        {
            target.draw(vertices,4,sf::Quads);
        }

        void changeColor(sf::Color newColor){
            color = newColor;
            updateColor();

        }

    private:

        void update()
        {
            sf::Vector2f direction = m_point2 - m_point1;
            sf::Vector2f unitDirection = direction / std::sqrt(direction.x*direction.x+direction.y*direction.y);
            sf::Vector2f unitPerpendicular(-unitDirection.y,unitDirection.x);

            sf::Vector2f offset = (thickness/2.f)*unitPerpendicular;

            vertices[0].position = m_point1 + offset;
            vertices[1].position = m_point2 + offset;
            vertices[2].position = m_point2 - offset;
            vertices[3].position = m_point1 - offset;
        }

        void updateColor(){
            for (int i=0; i<4; ++i)
                vertices[i].color = color;
        }




        sf::Vector2f m_point1, m_point2;
        sf::Vertex vertices[4];
        float thickness;
        sf::Color color;
    };
}