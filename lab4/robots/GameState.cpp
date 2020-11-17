/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>
#include <typeinfo>

GameState::GameState(){}

GameState::GameState(int numberOfRobots) { // Ska man lägga delete här? Hur? Var?
    std::cout << "In i vanliga konstruktorn \n";
    for (int i = 0; i < numberOfRobots; i++) {
        Robot* robot;
        do {robot = new Robot();}
        while (!isEmpty (*robot));
        robots.push_back(robot);
    }
    teleportHero();
}

GameState::GameState(const GameState& other) {
    std::cout << "In i copy constr. \n";
    for (unsigned int i = 0; i < other.robots.size(); i++) {
       robots.push_back(other.robots[i]->clone());
   }
    hero = other.hero;
}

GameState::~GameState(){
    std::cout << "In i destruktor \n";
    for(auto x : robots){
        delete x;
    }
}

GameState& GameState::operator=(const GameState& other) {
    std::cout << "In i operator= \n";
    if (this != &other){
        for (unsigned int i=0; i < robots.size(); i++) {
                delete robots[i];
        }
        robots.clear();

        for (unsigned int i=0; i < other.robots.size(); i++) {
            robots.push_back(other.robots[i]->clone());
        }
        hero = other.hero;
    }
    return *this;
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    for (size_t i = 0; i < robots.size(); ++i)
        robots[i]->draw(scene);
    hero.draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for (unsigned int i = 0; i < robots.size(); i++){
        robots[i]->moveTowards(hero);
    }
}

int GameState::countCollisions() {
    int numberDestroyed = 0;
    unsigned int i = 0;
    while (i < robots.size()) {
        bool hitJunk = junkAt (*robots[i]);
        bool collision = (countRobotsAt (*robots[i]) > 1);
        if (hitJunk || collision) {
            robots.push_back (new Junk(*robots[i])); //Kanske ska vara såhär sen
            Robot* p = robots[i];
            delete p;
            robots[i] = robots[robots.size()-1];
            robots.pop_back();
            numberDestroyed++;
            i++;
        } else i++;
    }
    return numberDestroyed;
}

bool GameState::anyRobotsLeft() const {
    for (unsigned int i = 0; i < robots.size(); i++) {
        if (typeid(*robots[i]) == typeid(Robot)) {
            return true;
        }
    }
    return false;
}

bool GameState::heroDead() const {
    return !isEmpty(hero);
}

bool GameState::isSafe(const Unit& unit) const {
    for (unsigned int i = 0; i < robots.size(); i++)
        if (robots[i]->attacks(unit)) return false;
    if (junkAt(unit)) return false;
    return true;
}

void GameState::moveHeroTowards(const Unit& dir) {
    hero.moveTowards(dir);
}

Hero GameState::getHero() const {return hero;}

/*
 * Free of robots and junk only
 */
bool GameState::isEmpty(const Unit& unit) const {
    return (countRobotsAt(unit) == 0 && !junkAt(unit));

}

/*
 * Is there junk at unit?
 */

bool GameState::junkAt(const Unit& unit) const {
    for (size_t i = 0; i < robots.size(); ++i)
        if (typeid(*robots[i]) == typeid(Junk) && typeid(unit) == typeid(Robot)) {
            if (robots[i]->at(unit)) return true;
        }
    return false;
}

/*
 * How many robots are there at unit?
 */
int GameState::countRobotsAt(const Unit& unit) const {
    int count = 0;
    if (typeid(unit) != typeid(Junk)){
        for (size_t i = 0; i < robots.size(); ++i) {
            if (robots[i]->at(unit) && typeid(*robots[i]) == typeid(Robot))
                count++;
        }
    }
    return count;
}
