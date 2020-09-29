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
    void addTile(Tile tile);
    void drawAll(QGraphicsScene* scene);
    int indexOfTopTile(int x, int y);
    void lower(int x, int y);
    void raise(int x, int y);
    void remove(int x, int y);
    void removeAll(int x, int y);

private:
    int t_size = 0;
    int t_capacity = 10;
    Tile* t_array = new Tile[t_capacity];

};

#endif // TILELIST_H
