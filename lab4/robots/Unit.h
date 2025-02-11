/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef UNIT_H
#define UNIT_H

#include "utilities.h"
#include <QGraphicsScene>


/* Root class for all pieces on the board.
 * Subclasses are Robot, Hero and Junk.
 */
class Unit {
public:
    Unit();
    Unit(const Unit& u);
    Unit(const Point& p);

    /*
    * Return Point representation of Unit
    */
    Point asPoint() const;

    /*
    * Am I in the same square as u?
    */
    bool at(const Unit& u) const;

    /*
    * Can I catch u in one move?
    */
    virtual bool attacks(const Unit& u) const;

    /*
    * Take one step closer to u
    */
    virtual void moveTowards(const Unit& u);

    virtual void draw(QGraphicsScene* scene);

    /*
    * Teleport. Does not check for collision
    */
    void teleport();

    /*
    * Euclidean distance to u
    */
    double distanceTo(const Unit& u) const;

    /*
     * Polymorphic clone function. Clones "this" Unit. (this->clone..)
     */
    virtual Unit* clone() const;

private:
    int x;  // x position of this unit
    int y;  // y position of this unit

    // private helpers
    void checkBounds();

};

#endif // UNIT_H
