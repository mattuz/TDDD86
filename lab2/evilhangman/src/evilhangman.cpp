#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

int main() {
    map<int, set<string>> dictionary;
    string line;
    int wordLenght;
    int guesses;
    string answer;

    cout << "Welcome to Hangman." << endl;

    ifstream dictFile("dictionary.txt");

    if(dictFile.is_open())
    {
        while(getline(dictFile, line))
        {
            int lineLenght = line.size();

            if (dictionary.find(lineLenght) != dictionary.end())
            {
                dictionary[lineLenght].insert(line);
            }
            else
            {
                set<string> words;
                words.insert(line);
                dictionary[lineLenght] = words;
            }
        }
        dictFile.close();
    }

    cout << "Please insert word lenght: ";
    cin >> wordLenght;

    while (dictionary[wordLenght].empty())
    {
        cout << "Please insert a valid word lenght: ";
        cin >> wordLenght;
    }

    cout << "Insert the number of guesses you would like: ";
    cin >> guesses;

    while (guesses < 1)
    {
        cout << "Please insert a valid number of guesses: ";
        cin >> guesses;
    }

    cout << "Would you like to see the amount of remaining words? (y/n): ";
    cin >> answer;
    while (answer != "y" && answer != "n")
    {
        cout << "Please insert a valid option: ";
        cin >> answer;
    }



    return 0;
}
