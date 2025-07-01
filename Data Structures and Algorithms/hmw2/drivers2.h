#include <string>


class Driver{
public:
    Driver(std::string line);

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getGender() const;
    std::string getAge() const;
    std::string getPhone() const;
    std::string getRating() const;
    std::string getLatitude() const;
    std::string getLongitude() const;
    std::string getVehicleType() const;
    std::string getState() const;
    std::string getRidersFirstName() const;
    std::string getRidersLastName() const;
    std::string getRidersPhone() const;

    void setFirstName(std::string fn);
    void setLastName(std::string ln);
    void setGender(std::string g);
    void setAge(std::string a);
    void setPhone(std::string p);
    void setRating(std::string rate);
    void setLatitude(std::string lat);
    void setLongitude(std::string lon);
    void setVehicleType(std::string vt);
    void setState(std::string st);
    void setRidersFirstName(std::string rfn);
    void setRidersLastName(std::string rln);
    void setRidersPhone(std::string rp);
    
private:
    std::string first_n;
    std::string last_n;
    std::string gender;
    std::string age;
    std::string phone;
    std::string rating;
    std::string latitude;
    std::string longitude;
    std::string vehicle_type;
    std::string state;
    std::string rider_first_n;
    std::string rider_last_n;
    std::string rider_phone;
};
