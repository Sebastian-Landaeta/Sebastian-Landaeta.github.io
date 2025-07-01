#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
/*
void readAndStore(const string& filename, vector<vector<string>>& storageVec) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.front() == '"' && line.back() == '"') {
            // If the line is enclosed in double quotes, add it as one element
            storageVec.push_back({line.substr(1, line.size() - 2)});
        } else {
            stringstream ss(line);
            string word;
            vector<string> words;

            while (ss >> word) {
                words.push_back(word);
            }

            // Store the vector of words in the storage vector
            storageVec.push_back(words);
        }
    }

    file.close();
}

void printVector(const vector<vector<string>>& vec) {
    for (const auto& innerVec : vec) {
        cout << "[";
        for (size_t i = 0; i < innerVec.size(); ++i) {
            cout << innerVec[i];
            if (i != innerVec.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
}

int main() {
    vector<vector<string>> storageVec;
    readAndStore("input.txt", storageVec);
    printVector(storageVec);
    return 0;
}

*/

#include <iostream>
#include <fstream>
#include <string>

string readFile(const std::string& filePath){
    std::ifstream fileStream(filePath);
    string fileContent;
    if (fileStream.is_open()) {
        std::string fileContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
        // suppose filePath is the string "html_files/subdir1/file3.html", then at this point, the string fileContent will be the full content of this file file3.html.
        // do something with fileContent
        return fileContent;
    }
    return fileContent;
}

int instCheck(const std::string& word, const std::string& data) {
    int count = 0;
    size_t pos = 0;
    
    // Find the first occurrence of the substring
    while ((pos = data.find(word, pos)) != std::string::npos) {
        // Increment count and move to the next position after the current occurrence
        ++count;
        pos += word.length();
    }
    
    return count;
}

int main() {
    std::string data = readFile("html_files/subdir1/subdir2/subdir3/file10.html");
    cout << data << endl;
    //std::cout << instCheck("CNN", data) << std::endl;
    //int i = 1;
    //string file = "out"+ to_string(i)+ ".txt";
    //cout << file << endl;
    return 0;
}
