//
//  VisualisationParameters.h
//  GraphTools
//
//  Created by VL-Impact on 04.11.15.
//

#ifndef GraphTools_VisualisationParameters_h
#define GraphTools_VisualisationParameters_h
#pragma once

namespace ggt{
    
//I target SFML as primary platform for work, but I try to keep some platform independency.
//Therefore I will define required types here and then will map them to platform-specific when required.

typedef unsigned int Color;
struct Point2Df {
    Point2Df() : x(0), y(0) {}
    Point2Df(float _x, float _y) : x(_x), y(_y) {}
    float x,y;
};

struct VisualisationParameters {
    Color gridColor;
    Color connectionColor;
    Color markerColor;
    Color pathColor;
    bool drawGrid;
    bool drawConnections;
    bool drawCellCenterMarkers;
    bool drawPaths;
    //bool drawContent;
    union {
        float gridCellWidth;
        float hexSize;
    };
    float normalizedHexSize() const {
        return gridCellWidth / 3.0 * 2.0;
    }
    
    float gridCellHeigth;
    
    Point2Df gridOrigin;
};

static const VisualisationParameters DEFAULT_VISUALIZATION_PARAMETERS =
{
    0x887050,
    0xAA0000,
    0x009900,
    0x00A2E8,
    true,
    true,
    false,
    true,
    //bool drawContent;
    64,//20
    64,
    {0.0, 0.0}
};

}
#endif
