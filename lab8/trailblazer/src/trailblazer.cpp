
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include <queue>
#include "pqueue.h"

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
                        //neighbour->previous = node;
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
    graph.resetData();
    Vertex* neighbour;
    PriorityQueue<Vertex*> pqueue;

    for (auto node : graph.getNodeSet()) {
        node->cost = POSITIVE_INFINITY;
    }
    start->cost = 0;
    pqueue.enqueue(start, start->cost);

    while(!pqueue.isEmpty()) {
        Vertex* node = pqueue.dequeue();
        node->visited = true;
        node->setColor(GREEN);
        if (node == end) {
            break;
        }
        for (auto arc : node->arcs) {
            if(!arc->visited){
                arc->visited = true;
                if(arc->finish != start){
                    neighbour = arc->finish;
                } else {
                    neighbour = arc->start;
                }
                double cost = node->cost + arc->cost;

                if (cost < neighbour->cost) {
                    if (neighbour->cost == POSITIVE_INFINITY) {
                        neighbour->setColor(YELLOW);
                        neighbour->cost = cost;
                        neighbour->previous = node;
                        pqueue.enqueue(neighbour, neighbour->cost);

                    } else {
                        neighbour->cost = cost;
                        neighbour->previous = node;
                        pqueue.changePriority(neighbour, neighbour->cost);
                    }
                }
            }
        }
    }
    return backtrackPath(start, end);
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Vertex* neighbour;
    PriorityQueue<Vertex*> pqueue;

    for (auto node : graph.getNodeSet()) {
        node->cost = POSITIVE_INFINITY;
    }
    start->cost = 0;
    pqueue.enqueue(start, start->heuristic(end));

    while(!pqueue.isEmpty()) {
        Vertex* node = pqueue.dequeue();
        node->visited = true;
        node->setColor(GREEN);
        if (node == end) {
            break;
        }
        for (auto arc : node->arcs) {
            if(!arc->visited){
                arc->visited = true;
                if(arc->finish != start){
                    neighbour = arc->finish;
                } else {
                    neighbour = arc->start;
                }
                double cost = node->cost + arc->cost;

                if (cost < neighbour->cost) {
                    double h = neighbour->heuristic(end);
                    if (neighbour->cost == POSITIVE_INFINITY) {
                        neighbour->setColor(YELLOW);
                        neighbour->cost = cost;
                        neighbour->previous = node;
                        pqueue.enqueue(neighbour, neighbour->cost + h);

                    } else {
                        neighbour->cost = cost;
                        neighbour->previous = node;
                        pqueue.changePriority(neighbour, neighbour->cost + h);
                    }


                }
            }
        }
    }

    return backtrackPath(start, end);
}

vector<Node*> backtrackPath(Vertex* start, Vertex* end) {
    vector<Node*> path;
    Vertex* previousNode = end->previous;
    path.push_back(end);
    while(previousNode != start) {
        path.push_back(previousNode);
        previousNode = previousNode->previous;
    }
    path.push_back(start);
    return path;
}
