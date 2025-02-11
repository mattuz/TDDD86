
#include "TileList.h"

TileList::TileList()
{
}

TileList::~TileList()
{
    delete [] t_array;
}


void TileList::addTile(const Tile tile)
{
    if (t_size == t_capacity)
    {
        resize();

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

int TileList::indexOfTopTile(const int x, const int y)
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

void TileList::raise(const int x, const int y)
{
    int tileIndex = indexOfTopTile(x, y);
    if (tileIndex != -1)
    {
        Tile tempTile = t_array[tileIndex];
        loopThroughList("forwards", tileIndex);
        t_array[t_size-1] = tempTile;
    }
}

void TileList::lower(const int x, const int y)
{
    int tileIndex = indexOfTopTile(x, y);
    if(tileIndex != -1)
    {
        Tile tempTile = t_array[tileIndex];
        loopThroughList("backwards", tileIndex);
        t_array[0] = tempTile;
    }
}

void TileList::remove(const int x, const int y)
{
    int tileIndex = indexOfTopTile(x,y);
    if(tileIndex != -1)
    {
        loopThroughList("forwards", tileIndex);
    }
}

void TileList::removeAll(const int x, const int y)
{
    int tileIndex = indexOfTopTile(x,y);
    while(tileIndex != -1)
    {
        loopThroughList("forwards", tileIndex);
        tileIndex = indexOfTopTile(x,y);
    }
}

void TileList::resize()
{
    Tile* tempArray = new Tile[t_capacity*2];
    copy(t_array, t_array+t_capacity, tempArray);
    t_capacity *=2;
    delete [] t_array;
    t_array = tempArray;
}

void TileList::loopThroughList(const string& direction, const int tileIndex)
{
    if(direction == "forwards"){
        for(int i = tileIndex; i < t_size; i++)
        {
            t_array[i] = t_array[i+1];
        }
    }
    else if(direction == "backwards")
    {
        for (int i = tileIndex; i > 0; i--)
        {
            t_array[i] = t_array[i-1];
        }

    }

}
