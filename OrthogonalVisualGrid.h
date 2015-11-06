//
//  RectVisualGrid.h
//  GraphTools
//
//  Created by VL-Impact on 04.11.15.
//

#ifndef GraphTools_RectVisualGrid_h
#define GraphTools_RectVisualGrid_h

#include "AbstractVisualGrid.h"

namespace ggt {
    
class OrthogonalVisualGrid : public AbstractVisualGrid {
public:
    OrthogonalVisualGrid(unsigned int width, unsigned int heigth, AbstractPainter* painter=nullptr, VisualisationParameters params = DEFAULT_VISUALIZATION_PARAMETERS)
    : AbstractVisualGrid(width, heigth, painter, params) {
        precachePixelData();
    }
    
    virtual Coordinate getCellByPixel(int x, int y) {
        x -= params.gridOrigin.x;
        y -= params.gridOrigin.y;
        
        int col = (x) /  params.gridCellWidth;
        int row = (y) / params.gridCellHeigth;
        
        return Coordinate(col, row);
    }
    virtual Point2Df getCentralPixel4Cell(int col, int row) {
        float x_center = (params.gridCellWidth/2) + params.gridCellWidth*col +params.gridOrigin.x;
        float y_center = (params.gridCellHeigth/2) + params.gridCellHeigth*row +params.gridOrigin.y;
        return Point2Df(x_center, y_center);
    }
    
    virtual void drawCell(int col, int row) {
        painter_->rect4Center(colRow2CellCenter[col][row],
                              params.gridCellWidth, params.gridCellHeigth,
                              params.gridColor);
    }		
};

}

#endif
