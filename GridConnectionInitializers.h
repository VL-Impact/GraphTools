//
//  GridConnectionInitializers.h
//  GraphTools
//
//  Created by VL-Impact on 04.11.15.
//

#ifndef GraphTools_GridConnectionInitializers_h
#define GraphTools_GridConnectionInitializers_h

namespace ggt {
    //You can pass those functors to Grid::initGridConnectionsByData to setup graph connections for adjancet cells
    
    auto CROSS_CONNECTOR = [](Coordinate c1, Coordinate c2, void* data1, void* data2)->Graph::Weight {
        int x_distance = abs(c1.x-c2.x);
        int y_distance = abs(c1.y-c2.y);
        if(x_distance > 1 || y_distance > 1)
            return 0;
        int total_distance = x_distance + y_distance;
        return  total_distance == 1 ? 1 : 0; // CROSS connections
    };
    
    auto STAR_CONNECTOR = [](Coordinate c1, Coordinate c2, void* data1, void* data2)->Graph::Weight {
        int x_distance = abs(c1.x-c2.x);
        int y_distance = abs(c1.y-c2.y);
        if(x_distance > 1 || y_distance > 1)
            return 0;
        int total_distance = x_distance + y_distance;
        return  total_distance == 1 ? 10 :
        total_distance == 2 ? 12 : 0 ; //Full-Star connections
    };
    
    auto HEX_POINTY_TOPPED_CONNECTOR = [](Coordinate c1, Coordinate c2, void* data1, void* data2)->Graph::Weight {
        int x_distance = abs(c1.x-c2.x);
        int y_distance = abs(c1.y-c2.y);
        if(x_distance > 1 || y_distance > 1)
            return 0;
        int total_distance = x_distance + y_distance;
        bool shift_touch = (c1.y % 2 == 0 && c1.x < c2.x && total_distance == 2)
        ||(c1.y % 2 == 1 && c1.x > c2.x && total_distance == 2);
        return  total_distance == 1 || shift_touch ? 1 : 0; // HEX Pointy-topped connections
    };
    
    
}
#endif
