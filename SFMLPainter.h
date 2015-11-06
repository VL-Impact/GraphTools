//
//  SFMLPainter.h
//  GraphTools
//
//  Created by VL-Impact on 04.11.15.
//

#ifndef GraphTools_SFMLPainter_h
#define GraphTools_SFMLPainter_h

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "AbstractPainter.h"

namespace ggt{

struct SFMLPainter : AbstractPainter
{
    SFMLPainter(sf::RenderWindow& _window)
    : window(_window)
    {
    }
    
    virtual void setColor (Color color) {
        currentColor = color;
    }
    
    sf::Color getColor() {
        return getColor(currentColor);
    }
    sf::Color getColor(Color intColor) {
        char red = ((intColor & 0xFF0000) >> 16);
        char green = ((intColor & 0x00FF00) >> 8);
        char blue = (intColor & 0x0000FF) ;
        
        return sf::Color(red, green, blue);
    }
    
    virtual void line (float x1, float y1, float x2, float y2) {
        line(x1,y1, x2,y2, currentColor);
    }
    
    virtual void line (float x1, float y1, float x2, float y2, Color c) {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(x1, y1), getColor(c)),
            sf::Vertex(sf::Vector2f(x2, y2), getColor(c))
        };
        
        window.draw(line, 2, sf::Lines);
    }
    
    virtual void rect4Center (float x, float y, float width, float heigth, Color color)
    {
        setColor(color);
        float ax = x - width/2;
        float ay = y - heigth/2;
        float bx = ax + width;
        float by = ay + heigth;
        
        line(ax, ay, bx, ay);
        line(ax, by, bx, by);
        line(ax, ay, ax, by);
        line(bx, ay, bx, by+1);// not sure, if it's SFML or some rounding error, but bottom-right pixel is missing in rectangle without that "+1" thing
    }
    
    sf::RenderWindow& window;
};

}

#endif
