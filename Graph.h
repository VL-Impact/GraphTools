//
//  Graph.h
//  GraphTools
//
//  Created by VL-Impact on 04.11.15.
//

#ifndef GraphTools_Graph_h
#define GraphTools_Graph_h

#pragma once

#include <set>
#include <map>
#include <deque>
#include <climits>

namespace ggt
{
    
typedef unsigned long long ID;
    
/**
 * A very simple implementation of Graph structure.
 * This class doesn't store any user data at nodes - it is designed to store only graph topology,
 * i.e. some node IDs and connections between them.
 *
 * Currently this Graph has API only for creation of nodes/edges;
 */
struct Graph {
    typedef int Weight;
    static const Weight ZERO_W = 0;
    static const Weight W_ONE = 1;
    
    typedef struct Edge {
        Edge(ID node, Weight weight = W_ONE) : node(node), weight(weight) {}
        
        ID node;
        Weight weight;
        bool operator==(const Edge& other) const { return node == other.node; }
        bool operator<(const Edge& other) const { return node < other.node; }
    } Edge;
    
    typedef std::set<Edge> Node;
    typedef std::map<ID, Node> Nodes;
    typedef Nodes::iterator NodeIterator;
    typedef std::deque<ID> Path;
    
    //Connects NodeA & NodeB with bidirectional edge;
    //If either NodeA or NodeB not exist, it will be created
    void addEdge(ID nodeA, ID nodeB, Weight weight = W_ONE) {
        _forceInsertEdge(nodeA, nodeB, weight);
        _forceInsertEdge(nodeB, nodeA, weight);
    }
    
    void addDirectedEdge(ID from, ID to, Weight weight = W_ONE) {
        _forceInsertEdge(from, to, weight);
    }
    
    bool isConnected(ID nodeA, ID nodeB) const {
        if(nodes.count(nodeA) == 0)
            return false;
        
        const Node& node = nodes.at(nodeA);
        for(const Edge& edge : node) {
            if(edge.node == nodeB)
                return true;
        }
        
        return false;
    }
    
    Nodes nodes;
    
protected:
    inline void _forceInsertEdge(ID from, ID to, Weight weight) {
        Edge edge(to, weight);
        if(!nodes[from].insert(edge).second) {
            nodes[from].erase(edge);
            nodes[from].insert(edge);
        }
    }
};

}//namespace ggt

#endif
