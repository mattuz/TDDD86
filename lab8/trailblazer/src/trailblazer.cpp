
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

vector<Node *> constructPath(map<Node*, Node*> nodeMap, Vertex* node, Vertex* originNode){
    Vertex* currentNode = node;
    vector<Node*> path;
    path.push_back(currentNode);
    while(nodeMap.at(currentNode) != originNode){
        path.insert(path.begin(), nodeMap.at(currentNode));
        currentNode = nodeMap.at(currentNode);
    }
    path.insert(path.begin(), originNode);

    return path;
}


vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();

    queue<Node *> nodeQueue;
    nodeQueue.push(start);
    map<Node*, Node*> nodeMap;
    Vertex* neighbour;
    vector<Vertex*> path;

    while(!nodeQueue.empty()){
        Vertex* node = nodeQueue.front();
        nodeQueue.pop();
        node->visited = true;
        node->setColor(GREEN);
        if(node == end){
            path = constructPath(nodeMap, node, start);
            break;
        } else {
            for(auto arc : node->arcs){
                if(!arc->visited){
                    arc->visited = true;
                    if(arc->finish != start){
                        neighbour = arc->finish;
                    }else{
                        neighbour = arc->start;
                    }
                    if(!neighbour->visited){
                        neighbour->setColor(YELLOW);
                        nodeQueue.push(neighbour);
                        nodeMap.insert(pair<Node*, Node*>(neighbour, node));
                    }
                }
            }

        }
    }    return path;
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
