#include <string>


class Rider{
public:
    Rider(std::string line);\

    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getGender() const;
    std::string getAge() const;
    std::string getPhone() const;
    std::string getRating() const;
    std::string getPickup() const;
    std::string getLatitudePickup() const;
    std::string getLongitudePickup() const;
    std::string getDropoff() const;
    std::string getLatitudeDropoff() const;
    std::string getLongitudeDropoff() const;
    std::string getVehicleType() const;
    std::string getState() const;
    std::string getDriversFirstName() const;
    std::string getDriversLastName() const;
    std::string getDriversPhone() const;

    void setFirstName(std::string fn);
    void setLastName(std::string ln);
    void setGender(std::string g);
    void setAge(std::string a);
    void setPhone(std::string p);
    void setRating(std::string rate);
    void setPickup(std::string pick);
    void setLatitudePickup(std::string latp);
    void setLongitudePickup(std::string lonp);
    void setDropoff(std::string drop);
    void setLatitudeDropoff(std::string latd);
    void setLongitudeDropoff(std::string lond);
    void setVehicleType(std::string vt);
    void setState(std::string st);
    void setDriversFirstName(std::string rfn);
    void setDriversLastName(std::string rln);
    void setDriversPhone(std::string rp);
    
private:
    std::string first_n;
    std::string last_n;
    std::string gender;
    std::string age;
    std::string phone;
    std::string rating;
    std::string pickup;
    std::string latitude_pick;
    std::string longitude_pick;
    std::string dropoff;
    std::string latitude_drop;
    std::string longitude_drop;
    std::string vehicle_type;
    std::string state;
    std::string driver_first_n;
    std::string driver_last_n;
    std::string driver_phone;
};
