//
//  InteractiveGridMixin.h
//  GraphTools
//
//  Created by VL-Impact on 04.11.15.
//

#ifndef GraphTools_InteractiveGridMixin_h
#define GraphTools_InteractiveGridMixin_h

#pragma once

#include "Grid.h"

namespace ggt {
    
template<class BaseGrid>
struct InteractiveGridMixin : BaseGrid {
    template<typename... Args>
    InteractiveGridMixin(Args... args)
    : BaseGrid(args...)
    , selectedCell_{Coordinate(-1,-1), Coordinate(-1,-1)}
    {
        ///todo:	static_assert(BaseGrid is inherited from AbstractField)
    }
    
    virtual void drawGrid() {
        BaseGrid::drawGrid();
        drawSelection();
    }
    
    void onGridClicked(sf::Mouse::Button button, float xPixel, float yPixel) {
        Coordinate cell = BaseGrid::getCellByPixel(xPixel, yPixel);
        onCellClicked(button, cell.x, cell.y);
    }
    void setClickHandle(std::function<void(sf::Mouse::Button, int, int)> handle) {
        clickHandle_ = handle;
    }
    
    virtual void onCellClicked(sf::Mouse::Button button, int col, int row) {
        int i = button == sf::Mouse::Button::Left ? 0 : 1;
        selectedCell_[i].x = col;
        selectedCell_[i].y = row;
        
        ///
        if(clickHandle_)
            clickHandle_(button, col, row);
    }
    
protected:
    bool cellIsValid(Coordinate cell) {
        if(cell.x < 0 || cell.y < 0 || cell.x >= BaseGrid::width || cell.y >= BaseGrid::heigth)
            return false;
        return true;
    }
    
    
    void drawSelection() {
        
        for(auto cell : selectedCell_) {
            if(cellIsValid(cell)) {
                BaseGrid::painter_->marker(IVisualGrid::getCentralPixel4Cell(cell), 0xFFFFFF, 3);//white marker
                BaseGrid::highlightCell(cell.x, cell.y);
            }
        }
        
    }
    Coordinate selectedCell_[2];
    
    std::function<void(sf::Mouse::Button, int, int)> clickHandle_;
};

}

#endif
