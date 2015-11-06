//
//  IsometricVisualGrid.h
//  GraphTools
//
//  Created by VL-Impact on 04.11.15.
//

#ifndef GraphTools_IsometricVisualGrid_h
#define GraphTools_IsometricVisualGrid_h

#pragma once

#include "AbstractVisualGrid.h"

namespace ggt {
    class IsometricVisualGrid : public AbstractVisualGrid {
    public:
        IsometricVisualGrid(unsigned int width, unsigned int heigth, AbstractPainter* painter=nullptr, VisualisationParameters params = DEFAULT_VISUALIZATION_PARAMETERS)
        : AbstractVisualGrid(width, heigth, painter, params)
        {
            precachePixelData();
        }
        
        virtual void precachePixelData() {
            borderOffsetX_ = params.gridCellWidth * (Grid::heigth-1) / 2.0;
            AbstractVisualGrid::precachePixelData();
        }
        virtual Coordinate getCellByPixel(int x, int y) {

            x -= params.gridOrigin.x;
            y -= params.gridOrigin.y;
            
            x -= params.gridCellWidth/2;
            x -= borderOffsetX_;
            
            float horzScalingFactor = params.gridCellWidth/params.gridCellHeigth;
            
            float tWidthHeigth = sqrt(params.gridCellHeigth*params.gridCellHeigth/2.0);
            
            
            
            float tx = x / horzScalingFactor;
            float ty = y;
            
            float s = sin(- M_PI / 4.0);
            float c = cos(- M_PI / 4.0);
            
            float xnew = tx * c - ty * s;
            float ynew = tx * s + ty * c;
            
            int col = (xnew) /  tWidthHeigth;
            int row = (ynew) / tWidthHeigth;
            
            return Coordinate(col, row);
        }
        
        virtual Point2Df getCentralPixel4Cell(int col, int row) {
            float x_center = borderOffsetX_ + (params.gridCellWidth/2) + (params.gridCellWidth/2*col) - (params.gridCellWidth/2*row) +params.gridOrigin.x;
            float y_center = (params.gridCellHeigth/2 + col*0.5*params.gridCellHeigth) + params.gridCellHeigth*row - (params.gridCellHeigth/2*row) + params.gridOrigin.y;
            return Point2Df(x_center, y_center);
        }
        
        virtual void drawCell(int col, int row) {
            painter_->rhomb4Center(colRow2CellCenter[col][row],
                                  params.gridCellWidth, params.gridCellHeigth,
                                  params.gridColor);
        }
    protected:
        float borderOffsetX_;
    };
}
#endif
