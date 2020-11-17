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
    Robot(const Robot& c);
    virtual ~Robot();

    virtual unsigned getCollisionCount();
    virtual void draw(QGraphicsScene* scene) const;
    Robot* clone() const override;

private:
    //Robot& operator= (const Robot&) = delete;
};

#endif // ROBOT_H
