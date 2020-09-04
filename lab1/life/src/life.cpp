// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include <fstream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
using namespace std;

int main() {
    string filename;
    string line;

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
        while (getline(myfile, line))
        {
           cout << line << '\n';
        }
        /*int row;
        int column;
        for (int i = 0; i<2; i++)
        {
            if (i == 0)
            {
                row =
            }
            else
            {

            }
        }*/
        //cout << "Hello :)" << endl;

        myfile.close();
    }



    return 0;
}


