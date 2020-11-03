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
    //virtual ~Robot() = default;
    void moveTowards(const Unit& u) override;
    bool attacks(const Unit& u) const override;
    void draw(QGraphicsScene* scene) const;
private:
};

#endif // ROBOT_H
