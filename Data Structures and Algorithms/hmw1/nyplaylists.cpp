#include <iostream>  
#include <iterator>    
#include <cstdlib>   
#include <vector> 
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// Function to print the playlist
void pr_playlist(const vector<string> &songs, const vector<string> &artists, ofstream& output){
    for(int i=0; i < songs.size(); i++){
        output << songs[i] << " " << artists[i] << endl;
    }
}

// Song addition function
void add_song(vector<string> &songs, vector<string> &artists, string target, ifstream& library){
    songs.push_back(target);

    string line;
    while (getline(library, line)){  // while loop to locate the requested song and its data on the library
        int separation = line.find("\"", 2);

        // devide the data into song title and artists
        string song = line.substr(0, separation+1);
        string artist = line.substr(separation+2, line.length());
        
        if (song == target){   //recognize if it finds the song and ends the loop to avoid craching
            artists.push_back(artist);
            break;
        }
    }
}

// Song remuval function 
void remove_song(vector<string> &songs, vector<string> &artists, string target){
    for(int i=0; i < songs.size(); i++){  //pinpoint the requested song in the vector and remuve it
        if (songs[i] == target){
            songs.erase(songs.begin()+i);
            artists.erase(artists.begin()+i);
        }
    }
}

// Song movement function 
void move_song(vector<string> &songs, vector<string> &artists, string target, int position, ifstream& library){
    auto search = find(songs.begin(), songs.end(), target); 
    int index = distance(songs.begin(), search); // find the index of the song to recognize its pair in artists vector
    string artist = artists[index]; // get the artists data before remuving it

    remove_song(songs, artists, target); // remuve the target song from its original position 

    songs.insert(songs.begin() + position-1, target); //insert the song in the song vector using insert
    artists.insert(artists.begin() + position-1, artist); //insert song info into the artists vector using insert
}

int main(int argc, char *argv[]) {
    if(argc<3){  // recognize if their isnt enough arguments to run program
        cout << "Usage: argument count < 3" << std::endl;
        exit(1);
    }

    // initilizing files
    string playlist_filename = std::string(argv[1]);
    string library_filename = std::string(argv[2]);
    string output_fielname = std::string(argv[3]);

    ifstream playlist(playlist_filename);
    ifstream library(library_filename);
    ofstream output(output_fielname);


    // Error display for playlist opening failure
    if (!playlist.is_open()) {
                std::cerr << "Failed to open the input file." << std::endl;
                exit(1);
        }

     //Error display for library opening failure
    if (!library.is_open()) {
                std::cerr << "Failed to open the librery file." << std::endl;
                exit(1);
        }

    // Error display for output opening failure
    if (!output.is_open()) {
                std::cerr << "Failed to open the output file." << std::endl;
                exit(1);
        }


    string line;
    vector<string> songs; //songs vector   
    vector<string> artists; //artist vector
    //made two different vectors instead of a 2d for simplicity

    while(getline(playlist, line)){ // while loop to get every song data in the given playlist to create the playlist data in vectors
        int separation = line.find("\"", 2); 

        // devide the data into song title and artists
        string song = line.substr(0, separation+1);
        string artist = line.substr(separation+2, line.length());
        
        songs.push_back(song); //add song  to songs vector
        artists.push_back(artist); //add song data to artists vector
    }

    string command = std::string(argv[4]); // recognize command 
    string target; // create the song variable argument
    string extra;

    if (command == "add"){ // addition command eccecution
        target = std::string(argv[5]); // recognize song to be used
        for(int i=6; i < argc; i++){ //filter the data in order to get every word of the song title
            extra = std::string(argv[i]);
            target += " ";
            target += extra;
        }
        add_song(songs, artists, target, library);
    }
    else if (command == "remove"){
        target = std::string(argv[5]); // recognize song to be used
        for(int i=6; i < argc; i++){  //filter the data in order to get every word of the song title
            extra = std::string(argv[i]);
            target += " ";
            target += extra;
        }
        remove_song(songs, artists, target);
    }
    else if (command == "move"){
        target = std::string(argv[5]); // recognize song to be used
        for(int i=6; i < argc-1; i++){ //filter the data in order to get every word of the song title
            extra = std::string(argv[i]); 
            target += " ";
            target += extra;
        }
        int position = std::atoi(argv[argc-1]); // recognize the index to be moved to
        move_song(songs, artists, target, position, library);
    }
    else{ // recognize that no command was recognized and exit program
        cout << "ERROR: Command not recognized" << std::endl;
        exit(1);
    }

    pr_playlist(songs, artists, output); // print the finnal playlist

    output.close();
    return 0; 
}
