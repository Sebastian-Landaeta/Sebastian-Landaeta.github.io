#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;


vector<vector<string>> createEmpMatrix(int row, int col) {
    vector<vector<string >> temp;
    for (int i = 0; i < row; i++) {
        vector<string> tempRow(col, "0");
        temp.push_back(tempRow);
    }
    return temp;
}

void addWordDriver(std::list<std::string> &reqWord, int colNum, int rowNum,
                   std::vector<std::vector<std::vector<std::string>>> &res) {
    std::vector<std::vector<std::string>> tempMatrix = createEmpMatrix(rowNum, colNum);
    addWordRec(reqWord, colNum, rowNum, res, 0, 0, tempMatrix);
}

int main(int argc, char *argv[]) {
    // Check if the required number of command-line arguments is provided
    if (argc < 3) {
        cout << "Usage: argument count < 3" << endl;
        exit(1);
    }

    // Initializing file names from command-line arguments
    string puzzle_filename = std::string(argv[1]);
    string output_filename = std::string(argv[2]);

    // Open input and output files
    ifstream puzzle_file(puzzle_filename);
    ofstream output_file(output_filename);

    // Display an error message if opening the puzzle file fails
    if (!puzzle_file.is_open()) {
        cerr << "Failed to open the users file." << endl;
        exit(1);
    }

    // Display an error message if opening the output file fails
    if (!output_file.is_open()) {
        cerr << "Failed to open the output file." << endl;
        exit(1);
    }

    // get collum length
    string col = "0";
    puzzle_file >> col;
    int colNum = stoi(col);

    // get row length
    string row = "0";
    puzzle_file >> row;
    int rowNum = stoi(row);

    // list to store the allowed words
    list<string> goodWord;
    // list to store the unallowed words
    vector<string> badWord;

    string holder;
    string word;
    while (puzzle_file >> holder) {
        puzzle_file >> word;
        if (holder == "+") {
            goodWord.push_back(word);
        } else {
            badWord.push_back(word);
        }
    }
    


    // close files
    puzzle_file.close();
    output_file.close();
}