#include <iostream>
#include <string>
#include <vector>

#include "riders2.h"

using namespace std;

Rider::Rider(string line){
    std::vector<string> data; // create vector to hold data lines 
    int i = 0;
    string hold = ""; // string holder
    while(i!= line.length()){ // loop through line and split on " " to get every word or data line to a vector
        if (line[i]== ' '){ // had to be ' ' and not " " due to comparison between pointer and integer error
            data.push_back(hold);
            hold = "";
            i++; // advance loop
        }
        else{
            hold += line[i];
            i++; // advance loop
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
    pickup = data[6];
    latitude_pick = data[7];
    longitude_pick = data[8];
    dropoff = data[9];
    latitude_drop = data[10];
    longitude_drop = data[11];
    vehicle_type = data[12];
    state = data[13];
    driver_first_n = data[14];
    driver_last_n = data[15];
    driver_phone = data[16];
}

std::string Rider::getFirstName() const{
    return first_n;
}

std::string Rider::getLastName() const{
    return last_n;
}

std::string Rider::getGender() const{
    return gender;
}

std::string Rider::getAge() const{
    return age;
}

std::string Rider::getPhone() const{
    return phone;
}

std::string Rider::getRating() const{
    return rating;
}

std::string Rider::getPickup() const{
    return pickup;
}

std::string Rider::getLatitudePickup() const{
    return latitude_pick;
}

std::string Rider::getLongitudePickup() const{
    return longitude_pick;
}

std::string Rider::getDropoff() const{
    return dropoff;
}

std::string Rider::getLatitudeDropoff() const{
    return latitude_drop;
}

std::string Rider::getLongitudeDropoff() const{
    return longitude_drop;
}

std::string Rider::getVehicleType() const{
    return vehicle_type;
}

std::string Rider::getState() const{
    return state;
}

std::string Rider::getDriversFirstName() const{
    return driver_first_n;
}

std::string Rider::getDriversLastName() const{
    return driver_last_n;
}

std::string Rider::getDriversPhone() const{
    return driver_phone;
}


void Rider::setFirstName(std::string fn){
    first_n = fn;
}

void Rider::setLastName(std::string ln){
    last_n = ln;
}

void Rider::setGender(std::string g){
    gender = g;
}

void Rider::setAge(std::string a){
    age = a;
}

void Rider::setPhone(std::string p){
    phone = p;
}

void Rider::setRating(std::string rate){
    rating = rate;
}

void Rider::setPickup(std::string pick){
    pickup = pick;
}

void Rider::setLatitudePickup(std::string latp){
    latitude_pick = latp;
}

void Rider::setLongitudePickup(std::string lonp){
    longitude_pick = lonp;
}

void Rider::setDropoff(std::string drop){
    dropoff = drop;
}

void Rider::setLatitudeDropoff(std::string latd){
    latitude_drop = latd;
}

void Rider::setLongitudeDropoff(std::string lond){
    longitude_drop = lond;
}

void Rider::setVehicleType(std::string vt){
    vehicle_type = vt;
}

void Rider::setState(std::string st){
    state = st;
}

void Rider::setDriversFirstName(std::string dfn){
    driver_first_n = dfn;
}

void Rider::setDriversLastName(std::string dln){
    driver_last_n = dln;
}

void Rider::setDriversPhone(std::string dp){
    driver_phone = dp;
}
