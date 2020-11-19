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

    /*
     * Constructs a Junk given a specific Robot.
     * Gives it the same properties (coordinates etc.)
     */
    Junk(const Robot& c);
    ~Junk() = default;

    /*
     * Overrides Unit.moveTowards. Does nothing (Junk cannot move).
     */
    void moveTowards(const Unit& u) override;

    /*
     * Overrides Unit.attacks. Always returns false (Junk cannot attack).
     */
    bool attacks(const Unit& u) const override;

    /*
     * Returns 0.
     */
    unsigned getCollisionCount() override;

    /*
     * Polymorphic clone function. Clones "this" Junk. (this->clone..)
     */
    Junk* clone() const override;

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const override;
private:

};

#endif // JUNK_H
