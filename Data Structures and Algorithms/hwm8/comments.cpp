#include <iostream>
#include <string>
#include <vector>

#include "comments.h"

using namespace std;

Comments::Comments(std::string& line){
    std::vector<string> data;  // create vector to hold data lines 
    int i = 0;
    string hold = ""; // string holder
    while(i != line.length()){ // loop through line and split on " " to get every word or data line to a vector
        if (line[i]== ' '){ // had to be ' ' and not " " due to comparison between pointer and integer error
            data.push_back(hold);
            hold = "";
            i++;
        }
        else{
            hold += line[i];
            i++;
        }
    }
    data.push_back(hold); // add the last data line stored 
    //store data
    name = data[0];
    age = stoi(data[1]);
    gender = data[2];
    phone = data[3];
    profession = data[4];
    school = data[5];
    lat = stod(data[6]);
    lon = stod(data[7]);
    premium = data[8];
    minAge = stoi(data[9]);
    maxAge = stoi(data[10]);
    maxDistance = stod(data[11]);
    sexPreferens = data[12];
    liked = data[13];
}

// getters

string Users::getName() const{
        return name;
}

int Users::getAge() const{
        return age;
}

string Users::getGender() const{
        return gender;
}

string Users::getPhone() const{
        return phone;
}

string Users::getProfession() const{
        return profession;
}

string Users::getSchool() const{
        return school;
}

double Users::getLat() const{
        return lat;
}

double Users::getLon() const{
        return lon;
}

string Users::getPremium() const{
        return premium;
}

int Users::getMinAge() const{
        return minAge;
}

int Users::getMaxAge() const{
        return maxAge;
}

double Users::getMaxDistance() const{
        return maxDistance;
}

string Users::getSexPreferens() const{
        return sexPreferens;
}

string Users::getLiked() const{
        return liked;
}

//setters

void Users::setLiked(std::string update){
    liked = update;
}

