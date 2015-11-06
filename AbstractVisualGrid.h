//
//  AbstractVisualGrid.h
//  GraphTools
//
//  Created by VL-Impact on 04.11.15.
//

#ifndef GraphTools_AbstractVisualGrid_h
#define GraphTools_AbstractVisualGrid_h

#pragma once

#include "VisualisationParameters.h"
#include "Grid.h"
#include "IVisualGrid.h"

namespace ggt {
    

class AbstractVisualGrid : public IVisualGrid, public Grid {
public:
    AbstractVisualGrid(unsigned int width, unsigned int heigth, AbstractPainter* painter=nullptr, VisualisationParameters _params = DEFAULT_VISUALIZATION_PARAMETERS)
    : Grid(width, heigth)
    , params(_params)
    , painter_(painter)
    {
    }
    
    
    void setPainter(AbstractPainter* painter) {
        painter_ = painter;
    }
    void setVisualizationParams(VisualisationParameters params) {
        this->params = params;
        precachePixelData();
    }
    
    virtual void precachePixelData() {
        colRow2CellCenter.resize(Grid::width);
        for(int col = 0; col < Grid::width; ++col) {
            colRow2CellCenter[col].resize(Grid::heigth);
            
            for(int row = 0; row < Grid::heigth; ++row)
                colRow2CellCenter[col][row] = getCentralPixel4Cell(col, row);
        }
    }
    
    virtual void drawGrid() {
        assert(painter_ && "Painter is not set");
        if(!painter_)
            return;
        
        //Cells borders
        if(params.drawGrid) {
            for(int col = 0; col < Grid::width; ++col)
                for(int row = 0; row < Grid::heigth; ++row)
                    drawCell(col, row);
        }
        
        //connections in graph
        if(params.drawConnections) {
            for(int col = 0; col < Grid::width; ++col)
                for(int row = 0; row < Grid::heigth; ++row) {
                    Coordinate thatCell(col, row);
                    for(auto otherCell : Grid::getConnectedCells(col, row) ) {
                        IVisualGrid::drawCellsConnection(thatCell, otherCell);
                    }
                }
        }
        
        //markers in cell-centers
        if(params.drawCellCenterMarkers) {
            for(int col = 0; col < Grid::width; ++col)
                for(int row = 0; row < Grid::heigth; ++row) {
                    auto thatCell = getCentralPixel4Cell(col, row);
                    painter_->marker(thatCell, params.markerColor);
                }
        }
    }
    
    virtual void highlightCell(int col, int row) { }
    
    virtual void drawCellsConnection(int col1, int row1, int col2, int row2) {
        auto cell1 = getCentralPixel4Cell(col1, row1);
        auto cell2 = getCentralPixel4Cell(col2, row2);
        
        painter_->line(cell1, cell2, params.connectionColor);
        painter_->marker(cell1, params.markerColor);
        painter_->marker(cell2, params.markerColor);
    }
    
    virtual void drawPath(const Graph::Path& path) {
        bool firstStep = true;
        Point2Df previous;
        for(ID id : path) {
            Coordinate cell = coordinateFromId(id);
            Point2Df cellCenter = getCentralPixel4Cell(cell);
            painter_->marker(cellCenter, params.pathColor);
            if(firstStep) {
                previous = cellCenter;
                firstStep = false;
                continue;
            }
            painter_->line(previous, cellCenter, params.pathColor);
            previous = cellCenter;
        }
    }
    
    //			virtual void drawCell(int col, int row) = 0;
    //			virtual Coordinate getCellByPixel(int x, int y) = 0;
protected:
    Graph& _getGraph() {
        return Grid::graph;
    }
    
//    Grid& grid_;
    VisualisationParameters params;
    AbstractPainter* painter_;
    std::vector< std::vector<Point2Df> > colRow2CellCenter;
};
    
}

#endif
