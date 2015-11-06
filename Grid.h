//
//  Grid.h
//  GraphTools
//
//  Created by VL-Impact on 04.11.15.
//

#ifndef GraphTools_Grid_h
#define GraphTools_Grid_h

#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>

#include "Graph.h"

namespace ggt
{


     //For now for simplicity we will have only positive X,Y coordinates.
    typedef struct Coordinate {
        Coordinate(unsigned int _x, unsigned int _y) : x(_x), y(_y) {}
        unsigned int x;
        unsigned int y;
    } Coordinate ;
    
    //For simplicity let's limit grid size with 65535 cells in every dimension.
    const unsigned int MAX_GRID_WIDTH = 65535;
    const unsigned int MAX_GRID_HEIGTH = 65535;

    //We need some means to convert an (X,Y) pair to single node ID and back
    const unsigned int C_SHIFT = 100000;
    ID idFromCoordinate(const Coordinate& c) { return c.x*C_SHIFT + c.y; }
    ID idFromCoordinate(unsigned int x, unsigned int y) { return x*C_SHIFT + y; }
    Coordinate coordinateFromId(ID id) { return Coordinate(id / C_SHIFT, id % C_SHIFT); }
    
/**
 * In terms of 2D games the one most useful graph is grid - a field of adjanced cells.
 * Every cell has X & Y coordinates. Any cell may contain link to some user data.
 * 
 * This Grid class is a wrapper around Graph, with awareness about its properties.
 *
 */
struct Grid {
    friend class AbstractPainter;
    friend class AbstractVisualGrid;

    Grid(unsigned int width, unsigned int heigth)
    : width(width), heigth(heigth)
    {
        assert(width <= MAX_GRID_WIDTH);
        assert(heigth <= MAX_GRID_HEIGTH);
    }
    
    void setData(unsigned int x, unsigned int y, void* data) {
        assert(x < width);
        assert(y < heigth);
        setData(idFromCoordinate(x,y), data);
    }
    void setData(ID id, void* data) {
        nodesData[id] = data;
    }
    
    void* getData(unsigned int x, unsigned int y) {
        assert(x < width);
        assert(y < heigth);
        return getData(idFromCoordinate(x,y));
    }
    void* getData(ID id) {
        std::map<ID, void*>::iterator it = nodesData.find(id);
        if(it == nodesData.end())
            return nullptr;
        
        return it->second;
    }
    
    void connect(Coordinate c1, Coordinate c2) {
        connect(c1.x, c1.y, c2.x, c2.y);
    }
    
    void connect(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
        graph.addEdge(idFromCoordinate(x1,y1), idFromCoordinate(x2,y2));
    }
    
    template<typename Checker>
    void connect2Checked(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Checker& checker) {
        if(   x1 <0 || x2 <0 || y1 <0 || y2 <0
           || x1 >= width || x2 >= width
           || y1 >= heigth || y2 >= heigth ) return; //ignore out-of-bounds requests
        
        Graph::Weight weigth = checker( Coordinate(x1,y1), Coordinate(x2,y2),
                                       getData(x1,y1), getData(x2,y2) );
        if(weigth > 0)
        {
            graph.addEdge(idFromCoordinate(x1,y1), idFromCoordinate(x2,y2), weigth);
        }
    }
    
    template<typename Checker>
    void initGridConnectionsByData(Checker& checker) {
        //STAR
        unsigned int X_START = 0;
        unsigned int Y_START = 0;
        unsigned int X_END = width ;
        unsigned int Y_END = heigth ;
        for(unsigned int x=X_START; x < X_END; ++x)
            for(unsigned int y=Y_START; y < Y_END; ++y)
            {
                void* node1 = getData(x,y);
                connect2Checked(x,y,	x-1,	y-1, checker);
                connect2Checked(x,y,	x,		y-1, checker);
                connect2Checked(x,y,	x+1,	y-1, checker);
                
                connect2Checked(x,y,	x-1,	y+1, checker);
                connect2Checked(x,y,	x,		y+1, checker);
                connect2Checked(x,y,	x+1,	y+1, checker);
                
                connect2Checked(x,y,	x-1,	y, checker);
                connect2Checked(x,y,	x+1,	y, checker);
            }
    };
    
    std::list<Coordinate> getConnectedCells(unsigned int x, unsigned int y) {
        assert(x < width);
        assert(y < heigth);
        
        std::list<Coordinate> result;
        Graph::Node& thatNode = graph.nodes[idFromCoordinate(x,y)];
        for(Graph::Edge edge : thatNode) {
            result.push_back(coordinateFromId(edge.node));
        }
        
        return result;
    }
    
    unsigned int width;
    unsigned int heigth;
    
protected:
    Graph graph; //public for tests
    std::map<ID, void*> nodesData;
};

}
#endif
