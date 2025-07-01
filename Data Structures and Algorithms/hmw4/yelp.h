#include <string>

using namespace std;

class Yelp{
public:
    // constructor
    Yelp(std::string& line);

    // class functions
    string getName(std::string& line);
    string getCategories(std::string& line);
    string getCity(std::string& line);
    double getRating(std::string& line);
    int getPrice(std::string& line);
    string getZipcode(std::string& line);
    int getRevewCount(std::string& line);
    bool operator<(const Yelp& other);

    // Getters
    string getBussinessName() const;
    string getBussinessCategories() const;
    string getBussinessCity() const;
    double getBussinessRating() const;
    int getBussinessPrice() const;
    string getBussinessZipCode() const;
    int getBussinessRevewCount() const;



private:
    // class variables
    string name;
    string categories;
    string city;
    double rating;
    int price;
    string zipCode;
    int revewCount;
};