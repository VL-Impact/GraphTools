//
//  AbstractPainter.h
//  GraphTools
//
//  Created by VL-Impact on 04.11.15.
//

#ifndef GraphTools_AbstractPainter_h
#define GraphTools_AbstractPainter_h

#pragma once

#include "VisualisationParameters.h"
#include <cmath>

namespace ggt{

// This class supports drawing of different shapes using primitive operations.
// Supported shapes include Rectangle, Rhombus, Hexagon(Flat-topped or Pointy-topped)
// It is used for debug information output.
// To use it on some platfor you have to inherit from it and provide implementation for
//  setColor() and line() functions.
// See SFMLPainter for example.
struct AbstractPainter
{
    Color currentColor;
    
    virtual void setColor (Color color) = 0;
    virtual void line (float x1, float y1, float x2, float y2) = 0;
    virtual void line (float x1, float y1, float x2, float y2, Color c) = 0;
    
    void line (Point2Df point1, Point2Df point2) {
        line(point1.x, point1.y, point2.x, point2.y);
    }
    void line (Point2Df point1, Point2Df point2, Color c) {
        line(point1.x, point1.y, point2.x, point2.y, c);
    }
    
    void marker(Point2Df point, Color c, int size = 3) {
        marker(point.x, point.y, c, size);
    }
    
    void marker(float x, float y, Color c, int size = 3) {
        rect4Center(x,y, size,size, c);
    }
    
    void rect4Center (Point2Df point, float width, float heigth, Color color) {
        rect4Center (point.x, point.y, width, heigth, color);
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
        line(bx, ay, bx, by);
    }
    
    void rhomb4Center (Point2Df point, float width, float heigth, Color color) {
        rhomb4Center (point.x, point.y, width, heigth, color);
    }
    
    virtual void rhomb4Center (float x, float y, float width, float heigth, Color color)
    {
        setColor(color);
        float ax = x - width/2;
        float ay = y - heigth/2;
        float bx = ax + width;
        float by = ay + heigth;
        
        line(ax, y, x, ay);
        line(x, ay, bx, y);
        line(x, by, bx, y);
        line(ax, y, x, by);
    }
    
    void hexPointyTopped4Center (Point2Df point, float size, Color color) {
        hexPointyTopped4Center (point.x, point.y, size, color);
    }
    
    virtual void hexPointyTopped4Center (float center_x, float center_y, float size, Color color) { //pointy-topped
        setColor(color);
        float x0,y0;
        for (int i = 0; i <= 6; ++i) {
            float angle = 2 * M_PI / 6 * (i + 0.5);
            float x_i = center_x + size * cos(angle);
            float y_i = center_y + size * sin(angle);
            if(i == 0) {
                x0 = x_i;
                y0 = y_i;
            }
            else {
                line(x0,y0, x_i, y_i);
                x0 = x_i;
                y0 = y_i;
            }
        }
    }
    
    void hexFlatTopped4Center (Point2Df point, float size, Color color) {
        hexFlatTopped4Center (point.x, point.y, size, color);
    }
    
    virtual void hexFlatTopped4Center (float center_x, float center_y, float size, Color color) {//flat-topped
        setColor(color);
        float x0,y0;
        for (int i = 0; i <= 6; ++i) {
            float angle = 2 * M_PI / 6 * i;
            float x_i = center_x + size * cos(angle);
            float y_i = center_y + size * sin(angle);
            if(i == 0) {
                x0 = x_i;
                y0 = y_i;
            }
            else {
                line(x0,y0, x_i, y_i);
                x0 = x_i;
                y0 = y_i;
            }
        }
    }
};
    
    namespace converters {
        Point2Df getPoint4rhombStyle_RhombField(int col, int row, VisualisationParameters& params) {
            float x_center = (params.gridCellWidth/2) + (params.gridCellWidth/2*col) +params.gridOrigin.x;
            float y_center = (params.gridCellHeigth/2 + col*0.5*params.gridCellHeigth) + params.gridCellHeigth*row +params.gridOrigin.y;
            return Point2Df(x_center, y_center);
        }
        Point2Df getPoint4rhombStyle_RhombField2(int col, int row, VisualisationParameters& params) {
            float x_center = (params.gridCellWidth/2) + (params.gridCellWidth/2*col) - (params.gridCellWidth/2*row) +params.gridOrigin.x;
            float y_center = (params.gridCellHeigth/2 + col*0.5*params.gridCellHeigth) + params.gridCellHeigth*row - (params.gridCellHeigth/2*row) + params.gridOrigin.y;
            return Point2Df(x_center, y_center);
        }
        Point2Df getPoint4HexAStyle_RectField(int col, int row, VisualisationParameters& params) {
            float height = params.hexSize * 2;
            float vert = 3.0/4.0 * height;
            float width  = sqrt(3.0)/2.0 * height;
            float horiz = width;
            
            float x_center = (row%2 == 1 ? width/2 : width) + (horiz*col) + params.gridOrigin.x;
            float y_center = (height/2) + vert*row +params.gridOrigin.y;
            return Point2Df(x_center, y_center);
        }
        
 /*       void drawGrid_rhombStyle_rhombusField(Grid& grid, VisualisationParameters& params) {
            
            for(int col = 0; col < grid.width; ++col) {
                for(int row = 0; row < grid.heigth; ++row) {
                    //------------------------------------
                    rhomb4Center(getPoint4rhombStyle_RhombField(col, row, params),
                                 params.gridCellWidth, params.gridCellHeigth,
                                 params.gridColor);
                }
            }
        }
        
        void drawGrid_rhombStyle_rhombusField2(Grid& grid, VisualisationParameters& params) {
            
            for(int col = 0; col < grid.width; ++col) {
                for(int row = 0; row < grid.heigth; ++row) {
                    //------------------------------------
                    rhomb4Center(getPoint4rhombStyle_RhombField2(col, row, params),
                                 params.gridCellWidth, params.gridCellHeigth,
                                 params.gridColor);
                }
            }
        }
        
        void drawGrid_HexAStyle_RectField(Grid& grid, VisualisationParameters& params) {
            
            for(int col = 0; col < grid.width; ++col) {
                for(int row = 0; row < grid.heigth; ++row) {
                    //------------------------------------
                    hexPointyTopped4Center(getPoint4HexAStyle_RectField(col, row, params),
                                           params.hexSize,
                                           params.gridColor);
                }
            }
        }
    */    

        float distance(float x1, float y1, float x2, float y2){
            float dx = x1-x2;
            float dy = y1-y2;
            return sqrt(dx*dx + dy*dy);
        }
          float distance(Point2Df p1, Point2Df p2){
            return distance(p1.x,p1.y, p2.x, p2.y);
        }
        
        Coordinate pixelToColRowHexA_RectField(float x, float y, VisualisationParameters& params) {
            x-=params.gridOrigin.x;
            y-=params.gridOrigin.y;
            
            float q = (1.0/3.0*sqrt(3) * x - 1.0/3.0 * y) / params.hexSize;
            float r = 2.0/3.0 * y / params.hexSize;
            
            {
                int Qx = q;
                int Qz = r;
                int Qy = -Qx-Qz;
                
                q = Qx + (Qz + (Qz&1)) / 2;
                r = Qz;
            }
            
            {
                int Q=q;
                int R=r;
                for(int i=-1; i<=1; ++i)
                    for(int j=-1; j<=1; ++j)
                    {
                        Point2Df nearest = getPoint4HexAStyle_RectField(q,r, params);
                        Point2Df test = getPoint4HexAStyle_RectField(Q+i, R+j, params);
                        if(distance(x,y, test.x, test.y) < distance(x,y, nearest.x, nearest.y)) {
                            q=Q+i;
                            r=R+j;
                        }
                    }
                
            }
            
            return Coordinate(q, r);
        }
    }
    
}

#endif
