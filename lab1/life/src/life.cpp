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

int main() {
    string filename;
    string line;
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
                 "Grid input file name? "
                 << endl;
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
            cout << '\n';
        }
    }

    cout << row << '\n' << column << '\n';

    cout << myGrid.toString() << '\n';

    return 0;
}

void setGridValue(Grid<char>& grid, int row, int column, string line) {
    for (int i = 0; i < column; i ++)
    {
        char symbol = line[i];
        cout << symbol;
        grid.set(row, i, symbol);
    }
}



