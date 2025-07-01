#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <algorithm>

#include "users.h"

using namespace std;

double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double radiusOfEarth = 6371.0; // Earth's radius in kilometers

    // convert latitude and longitude from degrees to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // Haversine formula
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    // distance in kilometers
    double distanceKM = radiusOfEarth * c;
    // convert it to distance in miles
    double distanceMiles = distanceKM * 0.621371;

    return distanceMiles;
}

// Define the linked list node
class Node {
public:
    Users data;
    Node* next;

    // constructor
    Node(Users user) : data(user), next(nullptr) {}
};

class LinkedList {
public:
    LinkedList() : head(nullptr) {}

    // method to add a user to the linked list
    void addUser(const Users& user) {
    Node* newNode = new Node(user);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    

    // Add a destructor to clean up memory
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    void showProfile(const string& phoneNum, ofstream& output) {
        // Initialize a pointer to the head of the linked list
        Node* current = head;

        // Variables to store user preference criteria
        int UPreffminAge;
        int UPreffmxnAge;
        string UPreffGender;
        double UPreffDistance;
        double ULat;
        double ULon;
        int found = -1;

        // Iterate through the linked list to find the user with the given phone number
        while (current != nullptr) {
            if (current->data.getPhone() == phoneNum) {
                // User found, set preferences based on user data
                found = 1;
                UPreffminAge = current->data.getMinAge();
                UPreffmxnAge = current->data.getMaxAge();
                UPreffGender = current->data.getSexPreferens();
                UPreffDistance = current->data.getMaxDistance();
                ULat = current->data.getLat();
                ULon = current->data.getLon();
            }
            current = current->next;
        }
        // If the user is not found, display an error message and exit
        if (found == -1) {
            cout << "User not found" << endl;
            exit(1);
        }

        current = head;
        found = -1;
        int spacing = 0;
        // Iterate through the linked list to find matching users based on preferences
        while (current != nullptr) {
            // Boolean variables to check if the user matches preference criteria
            bool age, gender, distance;
            // Check age criteria
            age = UPreffminAge <= current->data.getAge() && current->data.getAge() <= UPreffmxnAge;
            // Check gender criteria
            gender = current->data.getGender() == UPreffGender;
            if (UPreffGender == "Both") {
                gender = true;
            }
            // Check distance criteria using the Haversine formula
            distance = UPreffDistance >= calculateDistance(ULat, ULon, current->data.getLat(), current->data.getLon());
            // Display user information if all criteria are met and not the same user
            if (age && gender && distance && current->data.getPhone() != phoneNum) {
                found = 1;
                if (spacing >= 1) {
                    output << endl;
                }
                ++spacing;
                output << current->data.getName() << " " << current->data.getAge() << endl;
                // Display user's profession, replacing underscores with spaces
                string profession = current->data.getProfession();
                replace(profession.begin(), profession.end(), '_', ' ');
                if (current->data.getProfession() != "Undisclosed") {
                    output << profession << endl;
                }
                // Display user's school, replacing underscores with spaces
                string school = current->data.getSchool();
                replace(school.begin(), school.end(), '_', ' ');
                if (current->data.getSchool() != "Undisclosed") {
                    output << school << endl;
                }
            }
            current = current->next;
        }
        // If no matching users are found, display a message
        if (found == -1) {
            output << "There are no users matching with your preference at this moment." << endl;
        }
    }

    void showMatch(const string& phoneNum, ofstream& output) {
        Node* current = head;
        string UserLikes;
        int found = -1;

        // Iterate through the linked list to find the user with the given phone number
        while (current != nullptr) {
            if (current->data.getPhone() == phoneNum) {
                // User found, set UserLikes based on liked information
                found = 1;
                UserLikes = current->data.getLiked();
            }
            current = current->next;
        }
        // If the user is not found, display an error message and exit
        if (found == -1) {
            cout << "User not found" << endl;
            exit(1);
        }

        current = head;
        found = -1;
        string targetPH;
        string targetLikes;
        int spacing = 0;

        // Iterate through the linked list to find matching users based on mutual likes
        while (current != nullptr) {
            // Retrieve target user's phone number and liked information
            targetPH = current->data.getPhone();
            targetLikes = current->data.getLiked();
            // Check if there is a mutual like between the users
            if (UserLikes.find(targetPH) != string::npos && targetLikes.find(phoneNum) != string::npos) {
                found = 1;
                // Display matching user information
                if (spacing >= 1) {
                    output << endl;
                }
                ++spacing;
                output << current->data.getName() << " " << current->data.getAge() << endl;
                // Display user's profession, replacing underscores with spaces
                string profession = current->data.getProfession();
                replace(profession.begin(), profession.end(), '_', ' ');
                if (current->data.getProfession() != "Undisclosed") {
                    output << profession << endl;
                }
                // Display user's school, replacing underscores with spaces
                string school = current->data.getSchool();
                replace(school.begin(), school.end(), '_', ' ');
                if (current->data.getSchool() != "Undisclosed") {
                    output << school << endl;
                }
            }
            current = current->next;
        }
        // If no matches are found, display a message
        if (found == -1) {
            output << "You do not have any matches at this moment." << endl;
        }
    }

    void showLike(const string& phoneNum, ofstream& output) {
        Node* current = head;
        string UserPremium;
        int found = -1;

        // Iterate through the linked list to find the user with the given phone number
        while (current != nullptr) {
            if (current->data.getPhone() == phoneNum) {
                // User found, set premium status based on user data
                found = 1;
                UserPremium = current->data.getPremium();
            }
            current = current->next;
        }
        // If the user is not found, display an error message and exit
        if (found == -1) {
            cout << "User not found" << endl;
            exit(1);
        }
        current = head;
        found = -1;
        string targetLikes;
        int spacing = 0;

        // Check if the user is a premium user
        if (UserPremium == "true") {
            // Iterate through the linked list to find users who liked the current user
            while (current != nullptr) {
                // Retrieve liked information of the target user
                targetLikes = current->data.getLiked();
                // Check if the target user liked the current user
                if (targetLikes.find(phoneNum) != string::npos) {
                    found = 1;
                    // Display information of the user who liked the current user
                    if (spacing >= 1) {
                        output << endl;
                    }
                    ++spacing;
                    output << current->data.getName() << " " << current->data.getAge() << endl;
                    // Display user's profession, replacing underscores with spaces
                    string profession = current->data.getProfession();
                    replace(profession.begin(), profession.end(), '_', ' ');
                    if (current->data.getProfession() != "Undisclosed") {
                        output << profession << endl;
                    }
                    // Display user's school, replacing underscores with spaces
                    string school = current->data.getSchool();
                    replace(school.begin(), school.end(), '_', ' ');
                    if (current->data.getSchool() != "Undisclosed") {
                        output << school << endl;
                    }
                }
                current = current->next;
            }
            // If no likes are found, display a message
            if (found == -1) {
                output << "You have not received any likes so far." << endl;
            }
        } else {
            // Display a message if the user is not a premium user
            output << "Only premium users can view who liked you." << endl;
        }
    }

    void showUnmatch(const string& phoneNum, ofstream& output, const string& targetNum) {
        Node* current = head;
        string holder;
        int found1 = -1;
        int found2 = -1;

        // Iterate through the linked list to find the first user with the given phone number
        while (current != nullptr) {
            if (current->data.getPhone() == phoneNum) {
                found1 = 1;
                holder = current->data.getLiked();
                // Remove targetNum from the liked list of User1
                size_t pos = holder.find(targetNum);
                if (pos != string::npos) {
                    holder.erase(pos, targetNum.length());
                    if (holder.find("__") != string::npos) {
                        holder.erase(holder.find("__"), 1);
                    }
                    holder = holder.substr(holder.find_first_not_of('_'), holder.find_last_not_of('_') - holder.find_first_not_of('_') + 1);
                    current->data.setLiked(holder);
                }
                // Display User1's updated match list
                output << current->data.getName() << "'s match list:" << endl;
                output << endl;
                showMatch(phoneNum, output);
            }
            current = current->next;
        }  
        output << endl;
        output << "======" << endl;
        output << endl;
        current = head;

        // Iterate through the linked list to find the second user with the given phone number
        while (current != nullptr) {          
            if (current->data.getPhone() == targetNum) {
                found2 = 1;
                holder = current->data.getLiked();
                // Remove phoneNum from the liked list of User2
                size_t pos = holder.find(phoneNum);
                if (pos != string::npos) {
                    holder.erase(pos, phoneNum.length());
                    if (holder.find("__") != string::npos) {
                        holder.erase(holder.find("__"), 1);
                    }
                    holder = holder.substr(holder.find_first_not_of('_'), holder.find_last_not_of('_') - holder.find_first_not_of('_') + 1);
                    current->data.setLiked(holder);
                }
                // Display User2's updated match list
                output << current->data.getName() << "'s match list:" << endl;
                output << endl;
                showMatch(targetNum, output);
            }
            current = current->next;   
        }
        // If User1 is not found, display an error message and exit
        if (found1 == -1) {
            cout << "User1 not found" << endl;
            exit(1);
        }
        // If User2 is not found, display an error message and exit
        if (found2 == -1) {
            cout << "User2 not found" << endl;
            exit(1);
        }
    }

    void showBlock(const string& phoneNum, ofstream& output, const string& targetNum) {
        Node* current = head;

        int UPreffminAge;
        int UPreffmxnAge;
        string UPreffGender;
        double UPreffDistance;
        double ULat;
        double ULon;

        int found = -1;   
        while (current != nullptr) {
            // Find the user with the given phone number
            if (current->data.getPhone() == phoneNum) {
                // User found, set found flag and retrieve user's preferences
                found = 1;
                UPreffminAge = current->data.getMinAge();
                UPreffmxnAge = current->data.getMaxAge();
                UPreffGender = current->data.getSexPreferens();
                UPreffDistance = current->data.getMaxDistance();
                ULat = current->data.getLat();
                ULon = current->data.getLon();
                // Display a header for the profiles shown to the user
                output <<  "profiles shown to " << current->data.getName() << ":" << endl;
                output << endl;
            }
            current = current->next;
        }
        // If the user is not found, display an error message and exit
        if (found == -1) {
            cout << "User not found" << endl;
            exit(1);
        }
        Node* current1 = head;
        found = -1;    
        int spacing = 0;    

        // Iterate through the linked list to find potential matches based on preferences
        while (current1 != nullptr) {
            // Variables to check matching criteria
            bool age, gender, distance, blockCheck;
            age = UPreffminAge <= current1->data.getAge() && current1->data.getAge() <= UPreffmxnAge;
            gender = current1->data.getGender() == UPreffGender;
            if (UPreffGender == "Both") {
                gender = true;
            }
            distance = UPreffDistance >= calculateDistance(ULat, ULon, current1->data.getLat(), current1->data.getLon());
            blockCheck = current1->data.getPhone() != targetNum;
            // Check if the user meets all criteria and is not blocked
            if (age && gender && distance && blockCheck && current1->data.getPhone() != phoneNum) {
                found = 1;
                // Display matched profile information
                if (spacing >= 1) {
                    output << endl;
                }
                ++spacing;
                output << current1->data.getName() << " " << current1->data.getAge() << endl;
                string profession = current1->data.getProfession();
                replace(profession.begin(), profession.end(), '_', ' ');
                if (current1->data.getProfession() != "Undisclosed") {
                    output << profession << endl;
                }
                string school = current1->data.getSchool();
                replace(school.begin(), school.end(), '_', ' ');
                if (current1->data.getSchool() != "Undisclosed") {
                    output << school << endl;
                }
            }
            current1 = current1->next;
        }
        // Display a message if no matching profiles are found
        if (found == -1) {
            output << "There are no users matching with your preference at this moment." << endl;
        }
        output << endl;
        output << "======" << endl;
        output << endl;
        current = head;
        found = -1;   
        spacing = 0;
        while (current != nullptr) {
            if (current->data.getPhone() == targetNum) {
                // Target user found, set found flag and retrieve user's preferences
                found = 1;
                UPreffminAge = current->data.getMinAge();
                UPreffmxnAge = current->data.getMaxAge();
                UPreffGender = current->data.getSexPreferens();
                UPreffDistance = current->data.getMaxDistance();
                ULat = current->data.getLat();
                ULon = current->data.getLon();

                // Display a header for the profiles shown to the target user
                output <<  "profiles shown to " << current->data.getName() << ":" << endl;
                output << endl;
            }
            current = current->next;
        }
        // If the target user is not found, display an error message and exit
        if (found == -1) {
            cout << "User not found" << endl;
            exit(1);
        }

        // Reset current1 pointer to the beginning of the list
        current1 = head;

        // Reset found flag
        found = -1;        
        // Iterate through the linked list to find potential matches based on preferences for the target user
        while (current1 != nullptr) {
            // Variables to check matching criteria for the target user
            bool age, gender, distance, blockCheck;
            age = UPreffminAge <= current1->data.getAge() && current1->data.getAge() <= UPreffmxnAge;
            gender = current1->data.getGender() == UPreffGender;
            if (UPreffGender == "Both") {
                gender = true;
            }
            distance = UPreffDistance >= calculateDistance(ULat, ULon, current1->data.getLat(), current1->data.getLon());
            blockCheck = current1->data.getPhone() != phoneNum;

            // Check if the target user meets all criteria and is not blocked
            if (age && gender && distance && blockCheck && current1->data.getPhone() != targetNum) {
                found = 1;
                // Display matched profile information for the target user
                if (spacing >= 1) {
                    output << endl;
                }
                ++spacing;
                output << current1->data.getName() << " " << current1->data.getAge() << endl;
                string profession = current1->data.getProfession();
                replace(profession.begin(), profession.end(), '_', ' ');
                if (current1->data.getProfession() != "Undisclosed") {
                    output << profession << endl;
                }
                string school = current1->data.getSchool();
                replace(school.begin(), school.end(), '_', ' ');
                if (current1->data.getSchool() != "Undisclosed") {
                    output << school << endl;
                }
            }
            current1 = current1->next;
        }
        // Display a message if no matching profiles are found for the target user
        if (found == -1) {
            output << "There are no users matching with your preference at this moment." << endl;
        }
    }

private:
    Node* head;
};

int main(int argc, char *argv[]) {
    // Check if the required number of command-line arguments is provided
    if (argc < 4) {
        cout << "Usage: argument count < 4" << endl;
        exit(1);
    }

    // Initializing file names from command-line arguments
    string users_filename = std::string(argv[1]);
    string output_filename = std::string(argv[2]);

    // Open input and output files
    ifstream users_file(users_filename);
    ofstream output_file(output_filename);

    // Display an error message if opening the usres file fails
    if (!users_file.is_open()) {
        cerr << "Failed to open the users file." << endl;
        exit(1);
    }

    // Display an error message if opening the output file fails
    if (!output_file.is_open()) {
        cerr << "Failed to open the output file." << endl;
        exit(1);
    }

    LinkedList userList;

    // Read input file and create Yelp objects
    string line;
    while (getline(users_file, line)) {
        Users newUser(line);
        userList.addUser(newUser);
    }

    // Get zipcode and categories from command-line arguments
    string phoneNum = std::string(argv[3]);
    string command = std::string(argv[4]);
    string target;

    // command recognition statements
    if (command == "profile") {
        userList.showProfile(phoneNum, output_file);
    }
    else if (command == "match") {
        userList.showMatch(phoneNum, output_file);
    }
    else if (command == "like") {
        userList.showLike(phoneNum, output_file);
    }
    else if (command == "unmatch") {
        target = std::string(argv[5]);
        userList.showUnmatch(phoneNum, output_file, target);
    }
    else if (command == "block") {
        target = std::string(argv[5]);
        userList.showBlock(phoneNum, output_file, target);
    }
    else {
        cerr << "Command not recognized" << endl;
        exit(1);
    }

    // Close files
    users_file.close();
    output_file.close();

    return 0;
}