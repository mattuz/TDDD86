/*
 * This file contains the declaration of the Tour class.
 * See Tour.cpp for implementation of each member.
 */
#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:
    /*
     * Creates a tour using 4 points. (Mainly used for testing)
     */
    Tour(Point a, Point b, Point c, Point d);

    /*
     * Constructor.
     */
    Tour();

    /*
     * Destructor.
     */
    ~Tour();

    /*
     * Prints all the points in a tour, in order first to last.
     */
    void show();

    /*
     * Draws graphic lines representing the tour (in a new window), using the Point function drawTo().
     */
    void draw(QGraphicsScene* scene);

    /*
     * Returns the number of Points a tour contains.
     */
    int size();

    /*
     * Returns the distance traveled when a tour is completed. I.e the distance from the first to the last point.
     */
    double distance();

    /*
     * Inserts the Point p in a tour, right after the already existing point that is closest to p.
     */
    void insertNearest(const Point p);

    /*
     * Inserts the Point p in the position in the tour that makes the distance added as small as possible.
     */
    void insertSmallest(const Point p);

private:
    Node* m_front = nullptr;    //Pointer to the first element in a tour.
    Node* m_current = nullptr;  //Pointer used when traversing a tour.
    //Node* nodeP;
};

#endif // TOUR_H
