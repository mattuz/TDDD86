/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    Junk();
    Junk(const Robot& c);

    void moveTowards(const Unit& u) override;
    bool attacks(const Unit& u) const override;
    unsigned getCollisionCount() override;

    Junk* clone() const override;

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;
private:
    //Junk& operator= (const Junk&) = delete;
};

#endif // JUNK_H
