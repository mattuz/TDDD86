// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "TileList.h"
Tile* array[10];
int x = 0;
TileList::TileList()
{
    // TODO: write this member
    //arrayPointer = new Tile[10];
}

TileList::~TileList()
{
    // TODO: write this member
   // delete [] arrayPointer;
}

void TileList::addTile(Tile tile)
{
    // TODO: write this member
    x++;
    cout << x <<endl;
    //Tile t = new Tile();
    //arrayPointer[0] = t;
}

void TileList::drawAll(QGraphicsScene* scene)
{
    // TODO: write this member
}

int TileList::indexOfTopTile(int x, int y)
{
    // TODO: write this member
}

void TileList::raise(int x, int y)
{
    // TODO: write this member
}

void TileList::lower(int x, int y)
{
    // TODO: write this member
}

void TileList::remove(int x, int y)
{
    // TODO: write this member
}

void TileList::removeAll(int x, int y)
{
    // TODO: write this member
}
