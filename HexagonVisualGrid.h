//
//  HexagonVisualField.h
//  GraphTools
//
//  Created by VL-Impact on 04.11.15.
//

#ifndef GraphTools_HexagonVisualField_h
#define GraphTools_HexagonVisualField_h

#pragma once

#include "AbstractVisualGrid.h"

namespace ggt {
    
    class HexagonVisualGrid : public AbstractVisualGrid {
    public:
        HexagonVisualGrid(unsigned int width, unsigned int heigth, AbstractPainter* painter=nullptr, VisualisationParameters params = DEFAULT_VISUALIZATION_PARAMETERS)
        : AbstractVisualGrid(width, heigth, painter, params)
        {
            precachePixelData();
        }

        virtual Coordinate getCellByPixel(int x, int y) {
            
            x -= params.gridOrigin.x;
            y -= params.gridOrigin.y;
            
            
            float aq = (1.0/3.0*sqrt(3) * x - 1.0/3.0 * y) / params.normalizedHexSize();
            float ar = 2.0/3.0 * y / params.normalizedHexSize();
            
            float qx = aq;
            int qz = ar;
            float qy = -qx-qz;
            
            float q = qx + (qz + (qz&1)) / 2.0;
            float r = qz;
            
            return	Coordinate(q,r);
         }
        
        virtual Point2Df getCentralPixel4Cell(int col, int row) {
            float height = params.normalizedHexSize() * 2;
            float vert = 3.0/4.0 * height;
            float width  = sqrt(3.0)/2.0 * height;
            float horiz = width;
            
            float x_center = (row%2 == 1 ? width/2 : width) + (horiz*col) + params.gridOrigin.x;
            float y_center = (height/2) + vert*row +params.gridOrigin.y;
            
            return Point2Df(x_center, y_center);

        }
        
        virtual void drawCell(int col, int row) {
            painter_->hexPointyTopped4Center(colRow2CellCenter[col][row],
                                  params.normalizedHexSize(),
                                  params.gridColor);
        }
        
        virtual void highlightCell(int col, int row) {
            float height = params.normalizedHexSize() * 2;
            float vert = 3.0/4.0 * height;
            float width  = sqrt(3.0)/2.0 * height;
            float horiz = width;
            
            Point2Df p = getCentralPixel4Cell(col, row) ;
            painter_->rect4Center(p, 
                                  width,height,
                                  0xAAAAAA);
        }
    };
    
}

#endif
