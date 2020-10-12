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
    /*
     * Default constructor
     */
    TileList();

    /*
     * Default desctuctor
     */
    ~TileList();

    /*
     * Checks if the array has enough capacity to add a tile.
     * If it does, the tile is added to the array. If not,
     * it will double the current capacity then add the tile.
     */
    void addTile(const Tile tile);

    /*
     * Traverses the array and calls the .draw() method for
     * each tile.
     */
    void drawAll(QGraphicsScene* scene);

    /*
     * Traverses the array searching for the first tile containing
     * a specific x- y- coordinate. Returns the index of that tile.
     */
    int indexOfTopTile(const int x, const int y);

    /*
     * Lowers the chosen tile by moving it to the bottom of the list.
     * Also moves all the other tiles (if necessary) by decreasing
     * their index by one.
     */
    void lower(const int x, const int y);

    /*
     * Raises the chosen tile by moving it to the top of the list.
     * Also moves all the other tiles (if necessary) by increasing
     * their index by one.
     */
    void raise(const int x, const int y);

    /*
     * Removes the tile with the lowest index (for those coordinates)
     * from the array by overwriting it.
     */
    void remove(const int x, const int y);

    /*
     * Removes all the tiles that contain a certain coordinate by overwriting
     * them all. Works the same way as remove, but does it for every tile containing
     * the given coordinate.
     */
    void removeAll(const int x, const int y);

private:

    /*
     * Traverses the list in a given direction and either increases or decreases
     * each tiles index (given the direction), starting from the given tileIndex.
     */
    void loopThroughList(const string direction, const int tileIndex);

    /*
     * Increases the capacity of the array by x2. Creates a new array (B) with x2
     * the capacity of the original array (A). Copies A into B, then deletes A and sets
     * A = B.
     */
    void resize();

    int t_size = 0;
    int t_capacity = 10;
    Tile* t_array = new Tile[t_capacity];

};

#endif // TILELIST_H
