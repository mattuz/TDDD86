/*
 * TDDD86 Trailblazer
 * This file declares the functions you will write in this assignment.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Author: Marty Stepp
 * Slight modifications by Tommy Farnqvist
 */

#ifndef _trailblazer_h
#define _trailblazer_h

#include <vector>
#include "BasicGraph.h"

/*
 * Searches through the graph using the DFS algorithm.
 */
vector<Node*> depthFirstSearch(BasicGraph& graph, Node* start, Node* end);

/*
 * Performs the DFS recursion that is used to construct a path from start to end.
 */
vector<Node*> DFSRecursion(BasicGraph& graph, Vertex* start, Vertex* end);

/*
 * Returns a path for the BFS algorithm.
 */
vector<Node*> constructPath(map<Node*, Node*> nodeMap, Vertex* node);

/*
 * Searches through the graph using the BFS algorithm.
 */
vector<Node*> breadthFirstSearch(BasicGraph& graph, Node* start, Node* end);

/*
 * Searches through the graph using Dijkstras search algorithm.
 */
vector<Node*> dijkstrasAlgorithm(BasicGraph& graph, Node* start, Node* end);

/*
 * Searches through the graph using the A* search algorithm.
 */
vector<Node*> aStar(BasicGraph& graph, Node* start, Node* end);

/*
 * Constructs a path given the end and start node. Goes from end->previous
 * to start, then returns the path.
 */
vector<Node*> backtrackPath(Vertex* start, Vertex* end);


#endif
