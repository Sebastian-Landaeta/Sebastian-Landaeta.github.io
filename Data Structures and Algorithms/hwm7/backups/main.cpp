#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <algorithm>
#include <regex>
#include <map>
#include <sstream>
#include <list>

using namespace std;


// DELETE THIS BEFORE SUBMITTING *********************************************************************************************************************
void printMapToFile(const map<vector<string>, vector<string>>& myMap, ofstream& output) {
    for (const auto& pair : myMap) {
        output << "Key: [";
        for (const string& keyElement : pair.first) {
            output << keyElement << ", ";
        }
        output << "], ";

        output << "Value: [";
        for (const string& valueElement : pair.second) {
            output << valueElement << ", ";
        }
        output << "]" << endl;
    }
}
// DELETE THIS BEFORE SUBMITTING *********************************************************************************************************************


// DELETE THIS BEFORE SUBMITTING *********************************************************************************************************************
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
// DELETE THIS BEFORE SUBMITTING *********************************************************************************************************************

// DELETE THIS BEFORE SUBMITTING *********************************************************************************************************************
template<typename T>
void printVector1D(const std::vector<T>& vec) {
    std::cout << "Vector Contents:" << std::endl;
    for (const T& element : vec) {
        std::cout << element << " ";
    }
    std::cout << endl;
}
// DELETE THIS BEFORE SUBMITTING *********************************************************************************************************************

class BacklinksManager {
private:
    map<string, vector<string>> backlinks; // Map to store backlinks for each link

public:
    // Constructor
    BacklinksManager() {}

    // Function to add a backlink for a given link
    void addBacklink(const string& link, const string& backlink) {
        backlinks[link].push_back(backlink);
    }

    // Function to get backlinks for a given link
    vector<string> getBacklinks(const string& link) {
        if (backlinks.find(link) != backlinks.end()) {
            return backlinks[link];
        }
        return {}; // Return empty vector if link not found
    }


// DELETE THIS BEFORE SUBMITTING *********************************************************************************************************************
    // Function to display all backlinks
    void displayBacklinks() {
        ofstream output_file3("output BackLinks.txt");
        if (!output_file3.is_open()) {
            cerr << "Failed to open the output file." << endl;
            exit(1);
        }
        output_file3 << "Backlinks:" << endl;
        for (const auto& pair : backlinks) {
            output_file3 << "Link: " << pair.first << endl;
            output_file3 << "Backlinks: ";
            for (const auto& backlink : pair.second) {
                output_file3 << backlink << " ";
            }
            output_file3 << endl;
        }
    }
// DELETE THIS BEFORE SUBMITTING *********************************************************************************************************************


    // Function to get the number of backlinks for a specific link
    int getNumBacklinks(const string& link) {
        vector<string> backlinksStored = backlinks[link];
        if (backlinksStored.size() != 0) {
            return backlinksStored.size();
        }
        return 0; // Return 0 if the link has no backlinks
    }
};

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

// function to parse an HTML file and extract links to local files
std::vector<std::string> extractLinksFromHTML(const std::string& fileContent) {
    std::vector<std::string> links;
    // regular expression to match href attributes in anchor tags
    std::regex linkRegex("<a\\s+[^>]*href\\s*=\\s*['\"]([^'\"]+)['\"][^>]*>");
    std::smatch match;

    // search for links in the HTML content
    std::string::const_iterator start = fileContent.cbegin();
    while (std::regex_search(start, fileContent.cend(), match, linkRegex)) {
        if (match.size() > 1) {
            links.push_back(match[1].str());
        }
        start = match.suffix().first;
    }
    return links;
}

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

bool checkComp(const string& word){
    if (word.find("\"") != string::npos) {
        return true;
    } 
    else {
        return false;
    }
}

bool dataCheckComp(const string& word, const string& fileContent){
    string hold = word + " ";
    size_t found = fileContent.find(hold);
    if (found != string::npos) {
        return true;
    } 
    else {
        return false;
    }
}

bool dataCheckSep(vector<string>& words, const string& fileContent){
    bool check = true;
    for (string word : words){
        size_t found = fileContent.find(word);
        if (found != string::npos){
        }
        else{
            check = false;
        }
    }
    if (check){
        return true;
    }
    else{
        return false;
    }
}

string murge(vector<string>& words){
    string hold;
    for (const string& word : words) {
        hold += word;
    }
    return hold;
}

string removeDots(string link) {
    size_t pos = link.find("../");
    while (pos != string::npos) {
        link.erase(pos, 3); // Erase the "../" substring
        pos = link.find("../"); // Find the next occurrence
    }

    return link;
}

void webCrawl(const string& html, map<vector<string>, vector<string>>& invIndex, vector<string>& usedHtml, vector<vector<string>>& search, BacklinksManager& backlinksManager) {
    for (size_t i = 0; i < usedHtml.size(); ++i) {
        if (usedHtml[i] == html) {
            return;
        }
    }

    usedHtml.push_back(html);

    string fileContent = readFile(html);

    for (size_t line = 0; line < search.size(); ++line) {
        if (search[line].size() == 1) {
            if (dataCheckComp(search[line][0], fileContent)) {
                invIndex[search[line]].push_back(html);
            }
        } else if (dataCheckSep(search[line], fileContent)) {
            invIndex[search[line]].push_back(html);
        }
    }

    vector<string> nextLinks = extractLinksFromHTML(fileContent);

    // Add backlinks for the current page
    for (size_t link = 0; link < nextLinks.size(); ++link) {
        
        string nextLink = removeDots(nextLinks[link]);
        backlinksManager.addBacklink(nextLink, html);
    }

    for (size_t link = 0; link < nextLinks.size(); ++link) {
        string newLink = html.substr(0, html.rfind("/") + 1) + nextLinks[link];
        newLink = removeDots(newLink);
        webCrawl(newLink, invIndex, usedHtml, search, backlinksManager);
    }
}

int instCheck(const string& word, const string& data) {
    int count = 0;
    size_t pos = 0;
    
    // Find the first occurrence of the substring
    while ((pos = data.find(word, pos)) != string::npos) {
        // Increment count and move to the next position after the current occurrence
        ++count;
        pos += word.length();
    }
    
    return count;
}

bool comparePairs(const pair<double, string>& a, const pair<double, string>& b) {
    return a.first > b.first; // Sort in descending order
}

vector<string> sortedVector(map<double, string>& htmlHold) {
    // Create a vector of pairs from the map
    vector<pair<double, string>> tempVec(htmlHold.begin(), htmlHold.end());

    // Sort the vector based on the keys in descending order
    sort(tempVec.begin(), tempVec.end(), comparePairs);

    // Create a vector to store the values sorted by keys
    vector<string> sortedValues;

    // Extract values from the sorted vector
    for (vector<pair<double, string>>::const_iterator it = tempVec.begin(); it != tempVec.end(); ++it) {
        sortedValues.push_back(it->second);
    }

    return sortedValues;
}

map<vector<string>, vector<string>> score(map<vector<string>,vector<string>>& invIndex, vector<vector<string>>& search, BacklinksManager& backlinksManager){
    double apper;
    double docLen;
    double keyDens;
    map<vector<string>,vector<string>> tempMap;

    for(size_t i = 0; i < search.size(); ++i){
        map<double, string> htmlHold;
        apper = 0;
        docLen = 0;
        for(size_t j = 0; j < invIndex[search[i]].size(); ++j){
            string fileContent = readFile(invIndex[search[i]][j]);
            docLen += fileContent.length();
            for(size_t z = 0; z < search[i].size(); ++z){
                apper += instCheck(search[i][z], fileContent);
            }
        }
        if (docLen != 0){
            keyDens = apper / docLen;
        }

        double docAp = 0;
        double docLen = 0;
        double docDen = 0.0;
        double backDen = 0.0;
        for(size_t j = 0; j < invIndex[search[i]].size(); ++j){
            string fileContent = readFile(invIndex[search[i]][j]);
            docLen = fileContent.length();
            docAp = 0;
            for(size_t z = 0; z < search[i].size(); ++z){
                docAp = instCheck(search[i][z], fileContent);
            }
            if (docLen != 0){
                docDen = docAp / (docLen * keyDens);
            }

            vector<string> backlinksStored = backlinksManager.getBacklinks(invIndex[search[i]][j]);
            for(size_t y = 0; y < backlinksStored.size(); ++y){
                vector<string> outerLinks = extractLinksFromHTML(readFile(backlinksStored[y]));
                backDen += 1.0 / (1 + outerLinks.size());
            }

            double DocScore = (0.5 * docDen + 0.5 * backDen);

            htmlHold[DocScore] = invIndex[search[i]][j];
        }
        vector<string> sortedValues = sortedVector(htmlHold);

        tempMap[search[i]] = sortedValues;

    }
    return tempMap;
}

// Function to extract the title from HTML content
string extractTitle(const string& fileContent) {
    string title;
    size_t startPos = fileContent.find("<title>");
    size_t endPos = fileContent.find("</title>");
    if (startPos != string::npos && endPos != string::npos) {
        title = fileContent.substr(startPos + 7, endPos - startPos - 7);
    }
    return title;
}

// Function to extract the URL from HTML content
string extractURL(const string& fileContent) {
    string url;
    size_t startPos = fileContent.find("<h1>");
    size_t endPos = fileContent.find("</h1>");
    if (startPos != string::npos && endPos != string::npos) {
        url = fileContent.substr(startPos + 4, endPos - startPos - 4);
    }
    return url;
}

// Function to extract the description from HTML content
string extractDescription(const string& fileContent) {
    string description;
    size_t startPos = fileContent.find("content=");
    if (startPos != string::npos) {
        startPos = fileContent.find("\"", startPos + 8); // Move startPos to the beginning of the description
        size_t endPos = fileContent.find("\"", startPos + 1); // Find the closing quote
        if (endPos != string::npos) {
            description = fileContent.substr(startPos + 1, endPos - startPos - 1);
        }
    }
    return description;
}

string extractSnippet(const string& fileContent, const vector<string>& search) {
    string snippet;
    string compleateWord;
    for (size_t i = 0; i < search.size(); ++i) {
        compleateWord += search[i];
        if (i < search.size() - 1) {
            compleateWord += " "; // Add space between words except for the last word
        }
    }
    
    size_t startPos = fileContent.find("<body>");
    if (startPos != string::npos) {
        size_t pos = fileContent.find(compleateWord, startPos); // Find the position of the keyword after <body>
        if (pos != string::npos) { // If keyword found
            // Search backward for the nearest period before the start position
            size_t periodPos = fileContent.rfind(".", pos);
            if (periodPos != string::npos) {
                // Find the position of the first non-space character after the period
                size_t afterPeriodPos = fileContent.find_first_not_of(" \t\n", periodPos + 1);
                if (afterPeriodPos != string::npos) {
                    startPos = afterPeriodPos; // Adjust the start position
                }
                snippet = fileContent.substr(startPos, 120); // Extract the next 120 characters
            }
        } else {
            // Find the position of the simple keyword after <body>
            size_t pos = fileContent.find(search[0], startPos);
            if (pos != string::npos) {
                // Search backward for the nearest period before the start position
                size_t periodPos = fileContent.rfind(".", pos);
                if (periodPos != string::npos) {
                    // Find the position of the first non-space character after the period
                    size_t afterPeriodPos = fileContent.find_first_not_of(" \t\n", periodPos + 1);
                    if (afterPeriodPos != string::npos) {
                        startPos = afterPeriodPos; // Adjust the start position
                    }
                    snippet = fileContent.substr(startPos, 120); // Extract the next 120 characters
                }
            }
        }
    }
    return snippet;
}

void dataPR(map<vector<string>, vector<string>>& invIndex, vector<vector<string>>& search){
    for (size_t i = 0; i < search.size(); ++i){
        ofstream out("out" + to_string(i+1) + ".txt");

        out << "Matching documents: " << endl;

        for(size_t j = 0; j < invIndex[search[i]].size(); ++j){
            string fileContent = readFile(invIndex[search[i]][j]);
            string title = extractTitle(fileContent);
            string url = extractURL(fileContent);
            string description = extractDescription(fileContent);
            string snippet = extractSnippet(fileContent, search[i]);
            out << endl;
            out << "Title: " << title << endl;
            out << "URL: " << url << endl;
            out << "Description: " << description << endl;
            out << "Snippet: " << snippet << endl;
        }
    }
}

int main(int argc, char *argv[]) {
    BacklinksManager manager;
    // Check if the required number of command-line arguments is provided
    if (argc < 3) {
        cout << "Usage: argument count < 3" << endl;
        exit(1);
    }

    // Open input files
    string input_filename = std::string(argv[2]);

    vector<vector<string>> search;

    // Read input file and create map
    readAndStore(input_filename, search);  

    //printVector(search);

    map<vector<string>,vector<string>> invIndex;
    vector<string> usedHtml;

    webCrawl(argv[1], invIndex, usedHtml, search, manager);

    map<vector<string>,vector<string>> invIndexSorted = score(invIndex, search, manager);


    // DELETE THIS BEFORE SUBMITTING *********************************************************************************************************************
    ofstream output_file1("output unsorted.txt");

    if (!output_file1.is_open()) {
        cerr << "Failed to open the output file." << endl;
        exit(1);
    }

    printMapToFile(invIndex, output_file1);

    ofstream output_file2("output sorted.txt");

    if (!output_file2.is_open()) {
        cerr << "Failed to open the output file." << endl;
        exit(1);
    }

    printMapToFile(invIndexSorted, output_file2);

    // Display all backlinks
    manager.displayBacklinks();
    // DELETE THIS BEFORE SUBMITTING *********************************************************************************************************************

    dataPR(invIndexSorted, search);




    return 0;

}