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
};

// Function to read data from a file and store it in a vector of vectors
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

// Function to extract links from HTML content
vector<string> extractLinksFromHTML(const string& fileContent) {
    vector<string> links;
    // Regular expression to match href attributes in anchor tags
    regex linkRegex("<a\\s+[^>]*href\\s*=\\s*['\"]([^'\"]+)['\"][^>]*>");
    smatch match;

    // Search for links in the HTML content
    string::const_iterator start = fileContent.cbegin();
    while (regex_search(start, fileContent.cend(), match, linkRegex)) {
        if (match.size() > 1) {
            links.push_back(match[1].str());
        }
        start = match.suffix().first;
    }
    return links;
}

// Function to read content from a file
string readFile(const string& filePath){
    ifstream fileStream(filePath);
    string fileContent;
    if (fileStream.is_open()) {
        fileContent.assign((istreambuf_iterator<char>(fileStream)), istreambuf_iterator<char>());
        return fileContent;
    }
    return fileContent;
}

// Function to check if a word contains a double quote
bool checkComp(const string& word){
    return word.find("\"") != string::npos;
}

// Function to check if a word exists in the file content
bool dataCheckComp(const string& word, const string& fileContent){
    string hold = word + " ";
    size_t found = fileContent.find(hold);
    return found != string::npos;
}

// Function to check if all words in a vector exist in the file content
bool dataCheckSep(vector<string>& words, const string& fileContent){
    for (string word : words){
        if (fileContent.find(word) == string::npos){
            return false;
        }
    }
    return true;
}

// Function to concatenate all words in a vector into a single string
string merge(vector<string>& words){
    string result;
    for (const string& word : words) {
        result += word;
    }
    return result;
}

// Function to remove occurrences of "../" from a link
string removeDots(string link) {
    size_t pos = link.find("../");
    while (pos != string::npos) {
        link.erase(pos, 3); // Erase the "../" substring
        pos = link.find("../"); // Find the next occurrence
    }
    return link;
}

// Recursive function to crawl web pages and extract data
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

// Function to count occurrences of a word in a string
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

// Comparator function for sorting pairs in descending order based on their first element
bool comparePairs(const pair<double, string>& a, const pair<double, string>& b) {
    return a.first > b.first; // Sort in descending order
}

// Function to sort values in a map of doubles and strings
vector<string> sortedVector(map<double, string>& htmlHold) {
    // Create a vector of pairs from the map
    vector<pair<double, string>> tempVec(htmlHold.begin(), htmlHold.end());

    // Sort the vector based on the keys in descending order
    sort(tempVec.begin(), tempVec.end(), comparePairs);

    // Create a vector to store the values sorted by keys
    vector<string> sortedValues;

    // Extract values from the sorted vector
    for (const auto& pair : tempVec) {
        sortedValues.push_back(pair.second);
    }

    return sortedValues;
}

// Function to split a string into words and store them in a vector
void splitWord(vector<string>& vec, const string& word) {
    istringstream iss(word);
    string subword;
    while (iss >> subword) {
        vec.push_back(subword);
    }
}

// Function to process a vector of strings by splitting words containing spaces
void processVector(std::vector<std::string>& vec) {
    std::vector<std::string> result;
    for (const std::string& word : vec) {
        if (word.find(' ') != std::string::npos) {
            splitWord(result, word); // Split words containing spaces
        } else {
            result.push_back(word);
        }
    }
    vec = result; // Update the original vector
}

// Function to score documents based on relevance and backlink density
map<vector<string>, vector<string>> score(map<vector<string>,vector<string>>& invIndex, vector<vector<string>>& search, BacklinksManager& backlinksManager){
    double apper;
    double docLen;
    double keyDens;
    map<vector<string>,vector<string>> tempMap;

    // Iterating through each search query
    for(size_t i = 0; i < search.size(); ++i){
        map<double, string> htmlHold;
        apper = 0;
        docLen = 0;
        // Calculating appearance of each query term in documents
        for(size_t j = 0; j < invIndex[search[i]].size(); ++j){
            string fileContent = readFile(invIndex[search[i]][j]);
            docLen += fileContent.length(); // Accumulate document length
            for(size_t z = 0; z < search[i].size(); ++z){
                vector<string> keysEdit = search[i];
                processVector(keysEdit); // Process the query terms
                for(size_t p = 0; p < keysEdit.size(); ++p){
                    apper += instCheck(keysEdit[p], fileContent);
                }   
            }
        }

        // Calculate key density if document length is not zero
        if (docLen != 0){
            keyDens = apper / docLen;
        }

        double docAp = 0;
        double docLen = 0;
        double docDen = 0.0;
        double backDen = 0.0;
        // Scoring documents based on appearance and backlink density
        for(size_t j = 0; j < invIndex[search[i]].size(); ++j){
            string fileContent = readFile(invIndex[search[i]][j]);
            docLen = fileContent.length();
            docAp = 0;

            vector<string> keysEdit = search[i];
            processVector(keysEdit); // Process the query terms
            // Calculate appearance of processed query terms in document
            for(size_t z = 0; z < keysEdit.size(); ++z){
                docAp += instCheck(keysEdit[z], fileContent);
            }

            // Calculate document density if document length is not zero
            if (docLen != 0){
                docDen = docAp / (docLen * keyDens);
            }

            // Accumulate backlink density for the document
            vector<string> backlinksStored = backlinksManager.getBacklinks(invIndex[search[i]][j]);
            for(size_t y = 0; y < backlinksStored.size(); ++y){
                vector<string> outerLinks = extractLinksFromHTML(readFile(backlinksStored[y]));
                backDen += 1.0 / (1 + outerLinks.size());
            }

            // Calculate document score based on document density and backlink density
            double DocScore = (0.5 * docDen + 0.5 * backDen);

            htmlHold[DocScore] = invIndex[search[i]][j]; // Store document score
        }
        for (const auto& pair : htmlHold) {
            cout << "Key: " << pair.first << ", Value: " << pair.second << endl;
        }
        vector<string> sortedValues = sortedVector(htmlHold); // Sort documents by score

        tempMap[search[i]] = sortedValues; // Store sorted documents for each search query

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
// Function to process and print the matching documents along with their metadata
void dataPR(map<vector<string>, vector<string>>& invIndex, vector<vector<string>>& search){
    for (size_t i = 0; i < search.size(); ++i){
        ofstream out("out" + to_string(i+1) + ".txt"); // Create an output file for each search query

        out << "Matching documents: " << endl; // Print header for matching documents

        // Iterate through each document matching the current search query
        for(size_t j = 0; j < invIndex[search[i]].size(); ++j){
            string fileContent = readFile(invIndex[search[i]][j]); // Read the content of the current document
            string title = extractTitle(fileContent); // Extract the title from the document
            string url = extractURL(fileContent); // Extract the URL from the document
            string description = extractDescription(fileContent); // Extract the description from the document
            string snippet = extractSnippet(fileContent, search[i]); // Extract a snippet containing the search keywords
            out << endl;
            // Print metadata of the document
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

    // Read input file and create map of search queries
    readAndStore(input_filename, search);  

    map<vector<string>,vector<string>> invIndex;
    vector<string> usedHtml;

    // Perform web crawling to populate the inverted index
    webCrawl(argv[1], invIndex, usedHtml, search, manager);

    // Score the documents based on relevance and backlink density
    map<vector<string>,vector<string>> invIndexSorted = score(invIndex, search, manager);

    // Process and print the matching documents along with their metadata
    dataPR(invIndexSorted, search);

    return 0;
}
