/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
public:
    Robot();

    /*
     * Creates a Unit with the same properties as a given Robot.
     */
    Robot(const Robot& c);
    virtual ~Robot();

    /*
     * Returns 1. Used to check if, for example, a robot has collided.
     */
    virtual unsigned getCollisionCount();
    virtual void draw(QGraphicsScene* scene) const;

    /*
     * Polymorphic clone function. Clones "this" Robot. (this->clone..)
     */
    Robot* clone() const override;

private:

};

#endif // ROBOT_H
