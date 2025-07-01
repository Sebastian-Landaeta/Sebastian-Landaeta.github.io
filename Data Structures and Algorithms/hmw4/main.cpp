#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "yelp.h" 

using namespace std;

// Function to filter Yelp data based on specified categories and zipcode
void data_sorter(list<Yelp>& data, const string& zipcode_input, vector<string> &cat) {
    list<Yelp>::iterator it = data.begin();

    while (it != data.end()) {
        int check = -1;
        for (int i = 0; i < cat.size(); ++i){ // parse through every categorie to compare to the yelp categories and see if present
            if (it->getBussinessCategories().find(cat[i]) != string::npos){
                check = 1; // make check = 1 if it finds a match
            }
        }
        if (check == -1 || it->getBussinessZipCode() != zipcode_input) { // recognize if ither no categorie match or no zip match
            it = data.erase(it); // Erase the current element and get the iterator to the next
        } 
        else {
            ++it;
        }
    }
}

// Function to print filtered Yelp data with additional formatting
void pr_data(ofstream& output, list<Yelp>& data){
    data.sort();  // Sorting data
    if (data.empty()) { // recognize if their is no objects present
        output << "Sorry, we couldn't find any results" << std::endl;
    } 
    else { // if their is objects present print formatting 
        int count = 1; // formatting count
        output << "=====================" << endl;
        for (list<Yelp>::iterator it = data.begin(); it != data.end(); ++it) {
            output << count << ". " << it->getBussinessName() << endl;

            if (it->getBussinessRating() != std::floor(it->getBussinessRating())){
                int stars = std::floor(it->getBussinessRating());
                for ( int i = 0; i < stars; ++i){
                    output << "\u2605";
                }
                output << "\u00BD" << " " << it->getBussinessRating() << " (" << it->getBussinessRevewCount() << " reviews)" << endl;
            }
            else {
                int stars = std::floor(it->getBussinessRating());
                for ( int i = 0; i < stars; ++i){
                    output << "\u2605";
                }
                output << " " << it->getBussinessRating() << " (" << it->getBussinessRevewCount() << " reviews)" << endl;
            }

            output << it->getBussinessCity() << " ";
            for (int i = 0; i < it->getBussinessPrice(); ++i){
                output << "$";
            }
            output << endl;
            output << it->getBussinessCategories() << endl;
            output << "=====================" << endl;
            ++count;
        }
    }
}

int main(int argc, char *argv[]) {
    // Check if the required number of command-line arguments is provided
    if (argc < 4) {
        cout << "Usage: argument count < 4" << endl;
        exit(1);
    }

    // Initializing file names from command-line arguments
    string input_filename = std::string(argv[1]);
    string output_filename = std::string(argv[2]);

    // Open input and output files
    ifstream input_file(input_filename);
    ofstream output_file(output_filename);

    // Display an error message if opening the input file fails
    if (!input_file.is_open()) {
        cerr << "Failed to open the input file." << endl;
        exit(1);
    }

    // Display an error message if opening the output file fails
    if (!output_file.is_open()) {
        cerr << "Failed to open the output file." << endl;
        exit(1);
    }

    // Get zipcode and categories from command-line arguments
    string zipcode_input = std::string(argv[3]);

    vector<string> categories; // place categories in a vector for latter parse and use
    for( int i = 4; i < argc; ++i){
        categories.push_back(argv[i]);
    }

    // Create a list to store Yelp data
    list<Yelp> data;

    // Read input file and create Yelp objects
    string line;
    while (getline(input_file, line)) {
        data.push_back(Yelp(line));
    }

    // Filter Yelp data based on categories and zipcode
    data_sorter(data, zipcode_input, categories);

    // Call the function to print filtered data to the output file
    pr_data(output_file, data);

    // Close files
    input_file.close();
    output_file.close();

    return 0;
}