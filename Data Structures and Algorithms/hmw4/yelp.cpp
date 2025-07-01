#include <iostream>

#include "yelp.h"

Yelp::Yelp(std::string& line){
    name = getName(line);
    categories = getCategories(line);
    city = getCity(line);
    rating = getRating(line);
    price = getPrice(line);
    zipCode = getZipcode(line);
    revewCount = getRevewCount(line);
}


string Yelp::getName(std::string& line){
        int start = 0;
        // starting from the position start, and search the string variable line,
        // to find the first name string.
        int key_start = line.find("name", start);
        int value_start = key_start + 7;
        // remember to use escape.
        int value_end = line.find("\"", value_start);
        int len = value_end - value_start;
        // go from start to end, but exclude the character at end.
        // when we use the substr(start, length) function on a std::string,
        // the substring includes the character at the start position,
        // and the length of the substring is length.
        // It does not include the character at the position start + length.
        std::string name = line.substr(value_start, len);
        return name;
}

string Yelp::getCategories(std::string& line){
        int start = 0;
        // starting from the position start, and search the string variable line,
        // to find the first categories string.
        int key_start = line.find("categories", start);
        int value_start = key_start + 13;
        // remember to use escape.
        int value_end = line.find("\"", value_start);
        int len = value_end - value_start;
        // go from start to end, but exclude the character at end.
        // when we use the substr(start, length) function on a std::string,
        // the substring includes the character at the start position,
        // and the length of the substring is length.
        // It does not include the character at the position start + length.
        std::string categories = line.substr(value_start, len);
        return categories;
}

string Yelp::getCity(std::string& line){
        int start = 0;
        // starting from the position start, and search the string variable line,
        // to find the first name string.
        int key_start = line.find("city", start);
        int value_start = key_start + 7;
        // remember to use escape.
        int value_end = line.find("\"", value_start);
        int len = value_end - value_start;
        // go from start to end, but exclude the character at end.
        // when we use the substr(start, length) function on a std::string,
        // the substring includes the character at the start position,
        // and the length of the substring is length.
        // It does not include the character at the position start + length.
        std::string city = line.substr(value_start, len);
        return city;
}

double Yelp::getRating(std::string& line){
        int start = 0;
        // starting from the position start, and search the string variable line,
        // to find the first stars string.
        int key_start = line.find("stars", start);
        int value_start = key_start + 7;
        // remember to use escape.
        int value_end = line.find("\"", value_start);
        // -1 here because this is not a string.
        int len = value_end - value_start - 1;
        // go from start to end, but exclude the character at end.
        // when we use the substr(start, length) function on a std::string,
        // the substring includes the character at the start position,
        // and the length of the substring is length.
        // It does not include the character at the position start + length.
        // convert this string to a double
        double stars = stod(line.substr(value_start, len));
        return stars;
}

int Yelp::getPrice(std::string& line){
        int start = 0;

        int key_start = line.find("RestaurantsPriceRange2", start);

        if(key_start == std::string::npos){
                return -1;
        }
        int value_start = key_start + 25;

        int value_end = line.find("\"", value_start);
        int len = value_end - value_start;

        try {
                int price = stoi(line.substr(value_start, len));
                return price;
        } 
        catch (const std::invalid_argument& e) {
        // Handle the case where stoi conversion fails
                return -1;
        }
}

string Yelp::getZipcode(std::string& line) {
    int start = 0;

    int key_start = line.find("postal_code", start);
    int value_start = key_start + 14;

    int value_end = line.find("\"", value_start);
    int len = value_end - value_start;
    std::string zip = line.substr(value_start, len);
    return zip;
}

int Yelp::getRevewCount(std::string& line){
        int start = 0;
        int key_start = line.find("review_count", start);

        if(key_start == std::string::npos){
                return -1;
        }
        int value_start = key_start + 14;
        int value_end = line.find("\"", value_start);

        int len = value_end - value_start;

        try {
                int revCount = stoi(line.substr(value_start, len));
                return revCount;
        } 
        catch (const std::invalid_argument& e) {
        // Handle the case where stoi conversion fails
                return -1; 
        }
}

bool Yelp::operator<(const Yelp& other){
        return other.rating<rating;
}

// getters

string Yelp::getBussinessName() const{
        return name;
}

string Yelp::getBussinessCategories() const{
        return categories;
}

string Yelp::getBussinessCity() const{
        return city;
}

double Yelp::getBussinessRating() const{
        return rating;
}

int Yelp::getBussinessPrice() const{
        return price;
}

string Yelp::getBussinessZipCode() const{
        return zipCode;
}

int Yelp::getBussinessRevewCount() const{
        return revewCount;
}