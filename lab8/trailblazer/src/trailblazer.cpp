
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include <queue>

using namespace std;

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    return DFSRecursion(graph, start, end);
}

vector<Node*> DFSRecursion(BasicGraph& graph, Vertex* start, Vertex* end){
    vector<Vertex*> path;
    Vertex* node;
    start->setColor(GREEN);
    start->visited = true;


    if(start == end){
        path.push_back(start);
    }else{
        for(auto arc : start->arcs){
            if(!arc->visited){
                arc->visited = true;
                if(arc->finish != start){
                    node = arc->finish;
                }else{
                    node = arc->start;
                }
                if(!node->visited){
                    vector<Vertex*> tempPath = DFSRecursion(graph, node, end);
                    if(!tempPath.empty()){
                        path = tempPath;
                        path.insert(path.begin(), start);
                        return path;
                    } else {
                        node->setColor(GRAY);
                    }

                }

            }
        }
    }

    return path;
}


vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    queue nodeQueue;
    nodeQueue.push(start);
    start->visited = True;

    while(!nodeQueue.empty()){
        Vertex* node = nodeQueue.front();
        nodeQueue.pop();
        //kolla om det är end, annars ->
        //lägg till dess grannar i kön
    }

    for(auto arc : start->arcs){
        if(!arc->visited){
            arc->visited = true;
            if(arc->finish != start){
                node = arc->finish;
            }else{
                node = arc->start;
            }
        }
    }


    vector<Vertex*> path;
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}
