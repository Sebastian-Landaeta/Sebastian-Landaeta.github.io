#include <string>

using namespace std;

class Users{
public:
    // constructor
    Users(std::string& line);

    //getters
    string getName() const;
    int getAge() const;
    string getGender() const;
    string getPhone() const;
    string getProfession() const;
    string getSchool() const;
    double getLat() const;
    double getLon() const;
    string getPremium() const;
    int getMinAge() const;
    int getMaxAge() const;
    double getMaxDistance() const;
    string getSexPreferens() const;
    string getLiked() const;

    //setters
    void setLiked(std::string update);

private:
    // class variables
    string name;
    int age;
    string gender;
    string phone;
    string profession;
    string school;
    double lat;
    double lon;
    string premium;
    int minAge;
    int maxAge;
    double maxDistance;
    string sexPreferens;
    string liked;
};