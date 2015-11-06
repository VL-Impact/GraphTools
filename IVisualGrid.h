//
//  IVisualGrid.h
//  GraphTools
//
//  Created by VL-Impact on 04.11.15.
//

#ifndef GraphTools_IVisualGrid_h
#define GraphTools_IVisualGrid_h

namespace ggt {
    
class IVisualGrid {
public:
    virtual ~IVisualGrid(){}
    
    virtual void drawGrid() = 0;
    virtual void drawCell(int col, int row) = 0;
    virtual void drawCellsConnection(int col1, int row1, int col2, int row2) = 0;
            void drawCellsConnection(const Coordinate& cell1, const Coordinate& cell2) { return drawCellsConnection(cell1.x, cell1.y, cell2.x, cell2.y); }
    virtual void highlightCell(int col, int row) = 0;
    virtual Coordinate getCellByPixel(int x, int y) = 0;
            Coordinate getCellByPixel(Point2Df pixel) { return getCellByPixel(pixel.x, pixel.y); }
    
    virtual Point2Df getCentralPixel4Cell(int col, int row) = 0;
            Point2Df getCentralPixel4Cell(Coordinate cell) { return getCentralPixel4Cell(cell.x, cell.y); }
				
    virtual void drawPath(const Graph::Path& path) = 0;
};
    
}

#endif
