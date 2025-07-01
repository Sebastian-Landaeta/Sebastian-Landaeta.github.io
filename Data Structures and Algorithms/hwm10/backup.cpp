#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <queue>
#include <functional>
#include <utility>

using namespace std;

// Define a class to store relevant data
class TikTokVideo {
public:
    string id;
    string coverUrl;
    string webVideoUrl;
    string musicName;
    string musicArtist;
    string musicID;
    int playCount;
    vector<string> postText;
};

// Function to parse JSON file and store data into class
map<string, TikTokVideo> parseJSON(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        // Return an empty map
        return {};
    }

    map<string, TikTokVideo> videos;

    string line;
    while (getline(file, line)) {
        if (line.find("\"id\":") != string::npos) {
            TikTokVideo video;
            size_t pos = line.find("\"id\":") + 6;
            video.id = line.substr(pos + 1, line.find("\"", pos + 1) - pos - 1);
            
            size_t coverUrlPos = line.find("\"coverUrl\":") + 13;
            video.coverUrl = line.substr(coverUrlPos);
            video.coverUrl = video.coverUrl.substr(0, video.coverUrl.find("\""));

            size_t webVideoUrlPos = line.find("\"webVideoUrl\":") + 16;
            video.webVideoUrl = line.substr(webVideoUrlPos);
            video.webVideoUrl = video.webVideoUrl.substr(0, video.webVideoUrl.find("\""));

            size_t playCountPos = line.find("\"playCount\":") + 12;
            video.playCount = stoi(line.substr(playCountPos));

            size_t musicNamePos = line.find("\"musicName\":") + 14;
            video.musicName = line.substr(musicNamePos);
            video.musicName = video.musicName.substr(0, video.musicName.find("\""));

            size_t musicAuthorPos = line.find("\"musicAuthor\":") + 16;
            video.musicArtist = line.substr(musicAuthorPos);
            video.musicArtist = video.musicArtist.substr(0, video.musicArtist.find("\""));

            size_t musicIDPos = line.find("\"musicId\":") + 12;
            video.musicID = line.substr(musicIDPos);
            video.musicID = video.musicID.substr(0, video.musicID.find("\""));

            string text;
            size_t textPos = line.find("\"text\":") + 9;
            text = line.substr(textPos);
            text = text.substr(0, text.find("\""));
            std::regex hashtagRegex("#([\\w\\u0080-\\uFFFF]+)");
            

            // create an iterator for matching
            std::sregex_iterator hashtagIterator(text.begin(), text.end(), hashtagRegex);
            std::sregex_iterator endIterator;

            // iterate over the matches and extract the hashtags
            while (hashtagIterator != endIterator) {
                std::smatch match = *hashtagIterator;
                std::string hashtag = match.str(1);  // extract the first capturing group
            // this line will print each hash tag
            // if you want to do more with each hash tag, do it here. for example, store all hash tags in your container.
                video.postText.push_back(hashtag);

                ++hashtagIterator;
            }
            

            videos[video.id] = video;
        }
    }

    file.close();
    return videos;
}

map<string, pair<int, int>> countStringOccurrencesWithViews(const map<string, TikTokVideo>& videos) {
    map<string, pair<int, int>> occurrenceAndViewMap;
    
    for (map<string, TikTokVideo>::const_iterator it = videos.begin(); it != videos.end(); ++it) {
        const TikTokVideo& video = it->second;
        for (vector<string>::const_iterator str_it = video.postText.begin(); str_it != video.postText.end(); ++str_it) {
            // Increment occurrences
            occurrenceAndViewMap[*str_it].first++;
            // Add views
            occurrenceAndViewMap[*str_it].second += video.playCount;
        }
    }
    
    return occurrenceAndViewMap;
}

void hashtagFunction(const map<string, pair<int, int>>& occurrenceAndViewMap, const map<string, TikTokVideo>& videos, ofstream& outputFile) {
    // Create a custom comparison function to compare pairs of strings by occurrences, views, and string itself
    struct CustomCompare {
        bool operator()(const pair<string, pair<int, int>>& a, const pair<string, pair<int, int>>& b) const {
            if (a.second.first != b.second.first) // Compare by occurrences
                return a.second.first < b.second.first; // Lower occurrences come first
            else if (a.second.second != b.second.second) // If occurrences are tied, compare by views
                return a.second.second < b.second.second; // Lower views come first
            else // If both occurrences and views are tied, compare by string
                return a.first > b.first; // Strings are compared using the > operator
        }
    };

    // Create a priority queue using custom comparison function
    priority_queue<pair<string, pair<int, int>>, vector<pair<string, pair<int, int>>>, CustomCompare> pq;

    // Push map elements into the priority queue
    for (map<string, pair<int, int>>::const_iterator it = occurrenceAndViewMap.begin(); it != occurrenceAndViewMap.end(); ++it) {
        pq.push(*it);
    }

    outputFile << "trending hashtags:" << endl;
    outputFile << endl;

    // Print the sorted strings to the output file, limit to 10 elements
    int count = 0;
    while (!pq.empty() && count < 10) {
        const pair<string, pair<int, int>>& pair = pq.top();
        outputFile << "========================" << endl;
        outputFile << "#" << pair.first << endl;
        outputFile << "used " << pair.second.first << " times" << endl;
        outputFile << pair.second.second << " views" << endl;
        outputFile << endl;

        // Print cover URL and web video URL of at least 3 videos that contain the string
        map<int, TikTokVideo> holderMap;
        for (map<string, TikTokVideo>::const_iterator it = videos.begin(); it != videos.end(); ++it) {
            const TikTokVideo& video = it->second;
            bool flag = false;
            for (size_t i = 0; i < (video.postText).size(); ++i) {
                if((video.postText)[i] == pair.first){
                    flag = true;
                }
            }       
            if(flag){
                holderMap[video.playCount] = video;
            }
        }
        
        // Reverse iterator to print the map in descending order
        int videoCount = 0;
        map<int, TikTokVideo>::reverse_iterator it;
        for (it = holderMap.rbegin(); it != holderMap.rend(); ++it) {
            outputFile << "cover url: " << it->second.coverUrl << endl;
            outputFile << "web video url: " << it->second.webVideoUrl << endl;
            ++videoCount;
            if (videoCount >= 3) break;
        }
        outputFile << "========================" << endl;
        pq.pop();
        holderMap.clear();
        ++count;
    }
}


// Function to count the occurrences of each unique musicName in the videos map
map<pair<string, string>, pair<pair<int, int>, string>> countMusicOccurrences(const map<string, TikTokVideo>& videos) {
    map<pair<string, string>, pair<pair<int, int>, string>> musicOccurrences;

    // Iterate through the values of the videos map
    for (map<string, TikTokVideo>::const_iterator it = videos.begin(); it != videos.end(); ++it) {
        const TikTokVideo& video = it->second;
        string musicName = video.musicName;
        string musicArtist = video.musicArtist;
        string musicID = video.musicID;
        // If the musicName is "original sound", make it a new key with a number in the string
        if (musicName == "original sound") {
            // Check if "original sound" already exists as a key
            if (musicOccurrences.find(make_pair("original sound", musicArtist)) != musicOccurrences.end()) {
                int number = 1; // Start with 1 as the suffix
                while (musicOccurrences.find(make_pair("original sound " + to_string(number), musicArtist)) != musicOccurrences.end()) {
                    ++number; // Increment the number until finding a unique key
                }
                musicName = "original sound " + to_string(number);
            } else {
                musicName = "original sound"; // Use "original sound" as is
            }
        }
        if (musicName == "sonido original") {
            // Check if "original sound" already exists as a key
            if (musicOccurrences.find(make_pair("sonido original", musicArtist)) != musicOccurrences.end()) {
                int number = 1; // Start with 1 as the suffix
                while (musicOccurrences.find(make_pair("sonido original " + to_string(number), musicArtist)) != musicOccurrences.end()) {
                    ++number; // Increment the number until finding a unique key
                }
                musicName = "sonido original " + to_string(number);
            } else {
                musicName = "sonido original"; // Use "original sound" as is
            }
        }
        // Increment the count for the current musicName or insert it if it doesn't exist
        musicOccurrences[make_pair(musicName, musicArtist)].first.first++; // Increment occurrence count
        musicOccurrences[make_pair(musicName, musicArtist)].first.second += video.playCount; // Add views
        musicOccurrences[make_pair(musicName, musicArtist)].second = musicID; // Store musicID
    }

    return musicOccurrences;
}




// Function to print the top 10 musics based on total views
void printTop10Musics(const map<string, TikTokVideo>& videos, ofstream& outputFile) {
    // Call the countMusicOccurrences function to get the map of music occurrences
    map<pair<string, string>, pair<pair<int, int>, string>> musicOccurrences = countMusicOccurrences(videos);

    // Create a vector of pairs to store the map elements
    vector<pair<pair<string, string>, pair<pair<int, int>, string>>> sortedMusics;
    for (map<pair<string, string>, pair<pair<int, int>, string>>::const_iterator it = musicOccurrences.begin(); it != musicOccurrences.end(); ++it) {
        sortedMusics.push_back(*it);
    }

    // Sort the vector based on total views in descending order
    sort(sortedMusics.begin(), sortedMusics.end(), [](const pair<pair<string, string>, pair<pair<int, int>, string>>& a, const pair<pair<string, string>, pair<pair<int, int>, string>>& b) {
        return a.second.first.second > b.second.first.second;
    });

    // Print the top 10 musics
    outputFile << "trending hashtags:" << endl;
    outputFile << endl;
    int count = 0;
    for (vector<pair<pair<string, string>, pair<pair<int, int>, string>>>::const_iterator it = sortedMusics.begin(); it != sortedMusics.end(); ++it) {
        outputFile << "========================" << endl;
        outputFile << it->first.first << endl;
        outputFile << it->second.first.second << " views" << endl;
        outputFile << it->first.second << endl;
        outputFile << "music id: " << it->second.second << endl;

        


        count++;
        if (count >= 10) {
            break; // Exit the loop once the top 10 musics are printed
        }
    }
}



int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Usage: argument count < 4" << endl;
        exit(1);
    }

    string input_filename = std::string(argv[1]);
    string output_filename = std::string(argv[2]);
    string command = std::string(argv[3]);

    map<string, TikTokVideo> videos = parseJSON(input_filename);

    // Open the output file
    ofstream outputFile(output_filename);
    // Check if the file is successfully opened
    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open output file " << output_filename << endl;
        return 0;
    }

    if(command == "hashtag"){
        map<string, pair<int, int>> occurrenceAndViewMap = countStringOccurrencesWithViews(videos);
        hashtagFunction(occurrenceAndViewMap, videos, outputFile);
    }
    else if(command == "sound"){
        printTop10Musics(videos, outputFile);
    }

    // Close the output file
    outputFile.close();

    return 0;
}
