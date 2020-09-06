// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include <fstream>
#include <sstream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
using namespace std;

void setGridValue(Grid<char>& grid, int row, int column, string line);
void printCurrentGrid(Grid<char>& grid);
void nextAction(string answer, Grid<char> &grid, int row, int column);
void evolve(Grid<char>& grid, int column, int row);
void animate(Grid<char>& grid, int row, int column);
void printWelcome();

int main() {
    string filename;
    string line;
    string option;
    int row = 1;
    int column;
    Grid<char> myGrid;


    cout << "Welcome to the TDDD86  Game of Life, \n"
                 "a simulation of the lifecycle of a bacteria colony. \n"
                 "Cells (X) live and die by the following rules:\n"
                 "- A cell with 1 or fewer neighbours dies :'(.\n"
                 "- Locations with 2 neighbours remain stable. \n"
                 "- Locations with 3 neighbours will create life.\n"
                 "- A cell with 4 or more neighbours dies. \n"
                 "\n"
                 "Grid input file name? ";
    cin >> filename;

    ifstream myfile(filename);

    if (myfile.is_open())
    {
        for (int i = 0; i < 2; i++)             //Reads the first two lines and converts them to row/column integers
        {
            getline(myfile, line);
            if (i == 0)
            {
                stringstream currentline(line);
                currentline >> row;
            }
            else
            {
                stringstream currentline(line);
                currentline >> column;
            }
        }
        myGrid.resize(row, column);             //Resize the grid when we know the amount of rows/columns.
        for (int i = 0; i < row; i++)
        {
            getline(myfile, line);
            setGridValue(myGrid, i, column, line);
        }
    }
    printCurrentGrid(myGrid);

    cout << "a)nimate, t)ick, q)uit? ";
    cin >> option;
    nextAction(option, myGrid, row, column);

    return 0;
}

void setGridValue(Grid<char>& grid, int row, int column, string line) {
    for (int i = 0; i < column; i ++)
    {
        grid.set(row, i, line[i]);
    }
}

void printCurrentGrid(Grid<char>& grid) {           //prints out the current grid withouth changing it.
    for (int row = 0; row < grid.numRows(); row ++)
    {
        if (row > 0)
        {
            cout << '\n';
        }
        for (int column = 0; column < grid.numCols(); column++)
        {
            cout << grid[row][column];
        }
    }
    cout << '\n';
}


void nextAction(string answer, Grid<char>& grid, int row, int column) {
    if (answer == "a") //animate
    {
        animate(grid, row, column);
        cout << "a)nimate, t)ick, q)uit? ";
        cin >> answer;
        nextAction(answer, grid, row, column);
    }
    else if (answer == "t") //tick
    {
        evolve(grid, column, row);
        printCurrentGrid(grid);
        cout << "a)nimate, t)ick, q)uit? ";
        cin >> answer;
        nextAction(answer, grid, row, column);
    }
    else if (answer == "q") //quit
    {
        cout << "Have a nice life :)" << endl;
    }
    else
    {
        cout << "\nPlease enter a valid option: ";
        cin >> answer;
        nextAction(answer, grid, row, column);

    }
}

void evolve(Grid<char>& grid, int column, int row){
    Grid<char>newgrid = Grid<char>(row, column);
    for(int x=0; x<row; x++){
        for(int y=0; y<column; y++){

            int neighbours=0;
            for(int i=-1; i<2; i++){
                for(int j=-1; j<2; j++){
                    if(grid.inBounds(x+i, y+j) && grid.get(x+i,y+j)=='X'){
                        neighbours++;
                    }
                }
            }
            if(grid[x][y] == 'X'){
                neighbours--;}

            if(neighbours == 3){
                newgrid[x][y] = 'X';
            }
            else if(neighbours==2){
                newgrid[x][y] = grid[x][y];
            }
            else if(neighbours<2 || neighbours>3){
                newgrid[x][y] = '-';
            }
        }
    }
    grid = newgrid;
}

void animate(Grid<char>& grid, int row, int column){
    for(int i=0; i<40; i++){
        clearConsole();
        evolve(grid, column, row);
        printCurrentGrid(grid);
        pause(100);
        clearConsole();
    }
}
