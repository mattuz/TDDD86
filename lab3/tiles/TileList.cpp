// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "TileList.h"
//Tile* array[10];
//int x = 0;

TileList::TileList()
{
}

TileList::~TileList()
{
    delete [] t_array;
}

void TileList::addTile(Tile tile)           //Här behöver vi skapa något som kollar om den är full (om size == capacity). Isf dubbla capacity och kopiera in allt.
{
    if (t_size == t_capacity)
    {
        Tile* tempArray = new Tile[t_capacity*2];
        copy(t_array, t_array+t_capacity, tempArray);       //Flytta ut denna till en resize()?
        t_capacity *=2;
        delete [] t_array;
        t_array = tempArray;
    }
    t_array[t_size] = tile;
    t_size++;
}

void TileList::drawAll(QGraphicsScene* scene)
{
    for (int i = 0; i < t_size; i++) {
        t_array[i].draw(scene);
    }
}

int TileList::indexOfTopTile(int x, int y)
{
    for (int i = t_size-1; i >= 0; i--)
    {
        if (t_array[i].contains(x, y))
        {
            return i;
        }
    }
    return -1;
}

void TileList::raise(int x, int y)
{
    int k = indexOfTopTile(x, y);
    if (k != -1)
    {
        Tile tempTile = t_array[k];
        for (int i = k; i < t_size; i++)
        {
            t_array[i] = t_array[i+1];
        }
        t_array[t_size-1] = tempTile;
    }


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
