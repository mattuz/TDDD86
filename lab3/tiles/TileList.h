// This is the .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef TILELIST_H
#define TILELIST_H

#include <QGraphicsScene>
#include "Tile.h"

class TileList {
public:
    TileList();
    ~TileList();
    void addTile(const Tile tile);
    void drawAll(QGraphicsScene* scene);
    int indexOfTopTile(const int x, const int y);
    void lower(const int x, const int y);
    void raise(const int x, const int y);
    void remove(const int x, const int y);
    void removeAll(const int x, const int y);

private:
    void loopThroughList(const string direction, const int tileIndex);
    void resize();
    int t_size = 0;
    int t_capacity = 10;
    Tile* t_array = new Tile[t_capacity];

};

#endif // TILELIST_H
