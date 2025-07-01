#include <iostream>
#include <string>
#include <vector>

#include "drivers2.h"

using namespace std;

Driver::Driver(string line){
    std::vector<string> data;  // create vector to hold data lines 
    int i = 0;
    string hold = ""; // string holder
    while(i!= line.length()){ // loop through line and split on " " to get every word or data line to a vector
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
    first_n = data[0];
    last_n = data[1];
    gender = data[2];
    age = data[3];
    phone = data[4];
    rating = data[5];
    latitude = data[6];
    longitude = data[7];
    vehicle_type = data[8];
    state = data[9];
    rider_first_n = data[10];
    rider_last_n = data[11];
    rider_phone = data[12];
}

std::string Driver::getFirstName() const{
    return first_n;
}

std::string Driver::getLastName() const{
    return last_n;
}

std::string Driver::getGender() const{
    return gender;
}

std::string Driver::getAge() const{
    return age;
}

std::string Driver::getPhone() const{
    return phone;
}

std::string Driver::getRating() const{
    return rating;
}

std::string Driver::getLatitude() const{
    return latitude;
}

std::string Driver::getLongitude() const{
    return longitude;
}

std::string Driver::getVehicleType() const{
    return vehicle_type;
}

std::string Driver::getState() const{
    return state;
}

std::string Driver::getRidersFirstName() const{
    return rider_first_n;
}

std::string Driver::getRidersLastName() const{
    return rider_last_n;
}

std::string Driver::getRidersPhone() const{
    return rider_phone;
}


void Driver::setFirstName(std::string fn){
    first_n = fn;
}

void Driver::setLastName(std::string ln){
    last_n = ln;
}

void Driver::setGender(std::string g){
    gender = g;
}

void Driver::setAge(std::string a){
    age = a;
}

void Driver::setPhone(std::string p){
    phone = p;
}

void Driver::setRating(std::string rate){
    rating = rate;
}

void Driver::setLatitude(std::string lat){
    latitude = lat;
}

void Driver::setLongitude(std::string lon){
    longitude = lon;
}

void Driver::setVehicleType(std::string vt){
    vehicle_type = vt;
}

void Driver::setState(std::string st){
    state = st;
}

void Driver::setRidersFirstName(std::string rfn){
    rider_first_n = rfn;
}

void Driver::setRidersLastName(std::string rln){
    rider_last_n = rln;
}

void Driver::setRidersPhone(std::string rp){
    rider_phone = rp;
}
