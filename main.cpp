#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

// reads in a given file and returns a vector of each line contained in the file
vector<string> getWordsFromLibrary(string file);

// main function, prompts user for a int and outputs a string of words from a provided library
int main()
{
    vector<string> library = getWordsFromLibrary("library.txt");
    string phrase{};
    string input{};
    
    int length = 0;
    bool exit = false;
    
    // prompts user for input and retrys if the input isn't a int
    cout << "Please enter the number of words in the phrase: ";
    while (!exit)
    {
        cin >> input;
        try
        {
            length = stoi(input);

            if (length < 1)
            {
                cout << "Number to small, please enter a integer greater than 0: ";
                continue;
            }
            exit = true;
        }
        catch (invalid_argument e)
        {
            cout << "Improper format, please enter a an integer: ";
        }
        catch (exception e)
        {
            cout << "\nunknown error: ";
            cout << '"' << e.what() << '"' << endl;
            cout << "Please enter the number of words in the phrase: ";
        }
    }

    bool removeIndex = length > library.size() ? false : true;
    srand(int(time(0)));

    // create a loop for the amount of words wanted in the phrase
    for (int i = 0; i < length; i++)
    {
        // get a random position inside the library and add it to the phrase
        int index = rand() % (library.size());
        phrase += library[index];

        // if the length is less than the library size we can remove it to prevent duplicates
        if (removeIndex)
        {
            library.erase(library.begin() + index, library.begin() + index + 1);
        }
    }

    
    cout << phrase << endl;
}

vector<string> getWordsFromLibrary(string file)
{
    // initalize strings and open the provided file
    string currentLine{};
    vector<string> output{};
    ifstream in;
    in.open(file);

    // if the file failed to open, then exit program
    if (in.fail())
    {
        cerr << "Failed to open file: \"" << file << "\"" << endl;
        exit(EXIT_FAILURE);
    }

    // loop through the whole file until the end is hit
    while (true)
    {
        if (in.fail()) break;
        getline(in, currentLine);
        output.push_back(currentLine);
    }

    return output;  
}
