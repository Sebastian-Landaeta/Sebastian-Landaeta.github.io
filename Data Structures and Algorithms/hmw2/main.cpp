#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <regex>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

#include "riders2.h"
#include "drivers2.h"

void RiderFilePrint(vector<Rider> &rider_vector, ofstream& output2){

    string fn, ln, gen, age, ph, rt, pick, latp, lonp, drop, latd, lond, vt, st, dfn, dln, dh;

    for(int i=0; i < rider_vector.size(); i++){
        fn = rider_vector[i].getFirstName();
        ln = rider_vector[i].getLastName();
        gen = rider_vector[i].getGender();
        age = rider_vector[i].getAge();
        ph = rider_vector[i].getPhone();
        rt = rider_vector[i].getRating();
        pick = rider_vector[i].getPickup();
        latp = rider_vector[i].getLatitudePickup();
        lonp = rider_vector[i].getLongitudePickup();
        drop = rider_vector[i].getDropoff();
        latd = rider_vector[i].getLatitudeDropoff();
        lond = rider_vector[i].getLongitudeDropoff();
        vt = rider_vector[i].getVehicleType();
        st = rider_vector[i].getState();
        dfn = rider_vector[i].getDriversFirstName();
        dln = rider_vector[i].getDriversLastName();
        dh = rider_vector[i].getDriversPhone();

        output2 << fn << " " << ln << " " << gen << " " << age << " " << ph << " " << rt << " " << pick << " " << latp << " " << \
        lonp << " " << drop << " " << latd << " " << lond << " " << vt << " " << st << " " << dfn << " " << dln << " " << dh << endl; 
        
    }  
}

void driverFilePrint(vector<Driver> &driver_vector, ofstream& output1){

    string fn, ln, gen, age, ph, rt, lat, lon, vt, st, rfn, rln, rp;
    
    for(int i=0; i < driver_vector.size(); i++){
        fn = driver_vector[i].getFirstName();
        ln = driver_vector[i].getLastName();
        gen = driver_vector[i].getGender();
        age = driver_vector[i].getAge();
        ph = driver_vector[i].getPhone();
        rt = driver_vector[i].getRating();
        lat = driver_vector[i].getLatitude();
        lon = driver_vector[i].getLongitude();
        vt = driver_vector[i].getVehicleType();
        st = driver_vector[i].getState();
        rfn = driver_vector[i].getRidersFirstName();
        rln = driver_vector[i].getRidersLastName();
        rp = driver_vector[i].getRidersPhone();

        output1 << fn << " " << ln << " " << gen << " " << age << " " << ph << " " << rt << " " << lat << " " << lon << " " << vt << " " << \
        st << " " << rfn << " " << rln << " " << rp << endl;

    }
}

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

int phoneChecker(string phone){ // function to compare the format of the given number and the requested format
    regex pattern("\\d{3}-\\d{3}-\\d{4}"); // utilize regex to set a string pattern 
    if (regex_match(phone, pattern)){
        return 1; //return 1 if match
    }
    return 0; // return 0 if no match
}

int accountCheckerRider(vector<Rider> &rider_vector, string phone){ // function to check if the account exists (Rider class)
    for(int i=0; i < rider_vector.size(); i++){
        if (rider_vector[i].getPhone() == phone){
            return i;
        }
    }   
    return -1;
}

int accountCheckerDriver(vector<Driver> &driver_vector, string phone){ // function to check if the account exists (Driver class)
    for(int i=0; i < driver_vector.size(); i++){
        if (driver_vector[i].getPhone() == phone){
            return i;
        }
    }   
    return -1;
}

void request(vector<Rider> &rider_vector, vector<Driver> &driver_vector, ofstream& output0, int client){ // request function
    // setting variable that will be needed for the function and for analysis
    string client_fname = rider_vector[client].getFirstName();
    string client_lname = rider_vector[client].getLastName();
    string client_phone = rider_vector[client].getPhone();
    float client_lat = std::stof(rider_vector[client].getLatitudePickup());
    float client_lon = std::stof(rider_vector[client].getLongitudePickup());
    string client_preff = rider_vector[client].getVehicleType();
    string pickup = rider_vector[client].getPickup();
    string dropoff = rider_vector[client].getDropoff();

    string an_or_a;

    if (client_preff == "Economy"){
        an_or_a = "an";
    }
    else if (client_preff == "Luxury"){
        an_or_a = "a";
    }
    else if (client_preff == "Premium"){
        an_or_a = "a";
    }
    else if (client_preff == "Standard"){
        an_or_a = "a";
    }

    output0 <<  "Ride requested for rider " << client_fname <<", looking for " << an_or_a << " " << client_preff << " vehicle." << endl;
    output0 <<  "Pick Up Location: " << pickup << ", Drop Off Location: " << dropoff << "." << endl;
    
    // setting temporary holder variables for the search for loop
    float temp_distance = 0.0;
    float closest_distance = 100000.0;
    int cd = -1;
    float temp_lat = 0.0;
    float temp_lon = 0.0;
    
    for(int i=0; i < driver_vector.size(); i++){ // loop that goes through each Driver and analyses its data to see if it is a vaiable one 
        temp_lat = std::stof(driver_vector[i].getLatitude());
        temp_lon = std::stof(driver_vector[i].getLongitude());

        temp_distance = calculateDistance(client_lat, client_lon, temp_lat, temp_lon); // calculates the distance between Rider and Driver

        if (temp_distance < closest_distance){ // if distance is smaller than the saved "ideal option" then make it the "ideal option"
            if (driver_vector[i].getVehicleType() == client_preff && driver_vector[i].getState() == "Available"){ // make sure the driver is available
                closest_distance = temp_distance;
                cd = i;
            }
        }
    }

    if (cd == -1){ // catcher for the cace in which no driver was found
        output0 <<  "Sorry we can not find a driver for you at this moment." << endl;
    }
    else {
        // update Rider Data
        rider_vector[client].setState("Driver_on_the_way");
        rider_vector[client].setDriversFirstName(driver_vector[cd].getFirstName());
        rider_vector[client].setDriversLastName(driver_vector[cd].getLastName());
        rider_vector[client].setDriversPhone(driver_vector[cd].getPhone());

        string dri_n = driver_vector[cd].getFirstName();
        string dri_r = driver_vector[cd].getRating();

        string f_distance = to_string(closest_distance);

        output0 <<  "We have found the closest driver " << dri_n << "(" << dri_r << ") for you." << endl;
        output0 << dri_n << " is now " << f_distance.substr(0,3) << " miles away from you." << endl;

        // update Driver Data
        driver_vector[cd].setState("On_the_way_to_pickup");
        driver_vector[cd].setRidersFirstName(client_fname);
        driver_vector[cd].setRidersLastName(client_lname);
        driver_vector[cd].setRidersPhone(client_phone);
    }
}

void cancelRider(vector<Rider> &rider_vector, vector<Driver> &driver_vector, string clientPh, int client, ofstream& output0){ // cancel function (Rider scenerio)
    
    int tg = -1;
    for(int i=0; i < driver_vector.size(); i++){ // find the affected user in the Driver vector
        if (driver_vector[i].getRidersPhone() == clientPh){
            tg = i;
        }
    }
    output0 <<  "Ride request for rider " << rider_vector[client].getFirstName() << " is now canceled by the rider." << endl;

    // update Rider Data
    rider_vector[client].setState("Ready_to_request");
    rider_vector[client].setDriversFirstName("null");
    rider_vector[client].setDriversLastName("null");
    rider_vector[client].setDriversPhone("null");

    
    // update Driver Data
    driver_vector[tg].setState("Available");
    driver_vector[tg].setRidersFirstName("null");
    driver_vector[tg].setRidersLastName("null");
    driver_vector[tg].setRidersPhone("null");
    
}

void cancelDriver(vector<Driver> &driver_vector, vector<Rider> &rider_vector, string clientPh, int client, ofstream& output0){ // cancel function (Driver scenerio)
    
    string dn = driver_vector[client].getFirstName(); // get the drivers name
    string rn;
    int tg = -1;
    for(int i=0; i < rider_vector.size(); i++){ // find the affected user in the Rider vector
        if (rider_vector[i].getDriversPhone() == clientPh){
            rn = rider_vector[i].getFirstName();
            tg = i;
        }
    }

    output0 <<  "Your driver " << dn << " has canceled the ride request. We will now find a new driver for you." << endl;

    request(rider_vector, driver_vector, output0, tg); // run request function to give the rider a new ride

    //update driver data
    driver_vector[client].setState("Available");
    driver_vector[client].setRidersFirstName("null");
    driver_vector[client].setRidersLastName("null");
    driver_vector[client].setRidersPhone("null");
}




int main(int argc, char *argv[]){
    if(argc<8){  // recognize if their isnt enough arguments to run program
        cout << "Usage: argument count < 8" << endl;
        exit(1);
    }

    // initilizing files
    string drivers_filename = std::string(argv[1]);
    string riders_filename = std::string(argv[2]);
    string output0_fielname = std::string(argv[3]);
    string output1_fielname = std::string(argv[4]);
    string output2_fielname = std::string(argv[5]);

    ifstream drivers_file(drivers_filename);
    ifstream riders_file(riders_filename);
    ofstream output0(output0_fielname);
    ofstream output1(output1_fielname);
    ofstream output2(output2_fielname);


    // Error display for drivers opening failure
    if (!drivers_file.is_open()) {
                std::cerr << "Failed to open the drivers file." << std::endl;
                exit(1);
        }

     //Error display for riders opening failure
    if (!riders_file.is_open()) {
                std::cerr << "Failed to open the riders file." << std::endl;
                exit(1);
        }

    // Error display for output0 opening failure
    if (!output0.is_open()) {
                std::cerr << "Failed to open the output1 file." << std::endl;
                exit(1);
        }

    // Error display for output1 opening failure
    if (!output1.is_open()) {
                std::cerr << "Failed to open the output2 file." << std::endl;
                exit(1);
        }

    // Error display for output2 opening failure
    if (!output2.is_open()) {
                std::cerr << "Failed to open the output3 file." << std::endl;
                exit(1);
        }

    std::vector<Rider> rider_vector; // create the rider vector to store each rider class data
    std::vector<Driver> driver_vector; // create the driver vector to store each driver class data

    string line;
    while(getline(riders_file, line)){ // fill up the Rider class vector with data from the file
        rider_vector.push_back(Rider(line));
    }
    while(getline(drivers_file, line)){ // fill up the Driver class vector with date from the file
        driver_vector.push_back(Driver(line));
    }


    string phone = argv[6]; // get the phone from the arguments
    string command = argv[7]; // get the comand from the arguments

    if (command == "request"){ // request command recognition
        int client = accountCheckerRider(rider_vector, phone);
    
        int key = 0; 
        if (phoneChecker(phone) == 0){ // make sure the number is valid
            output0 <<  "Phone number is invalid." << endl;
            key = 1;
        }
        else if (client == -1){ // make sure the account exists
            output0 <<  "Account does not exist." << endl;
            key = 1;
        }
        else if (rider_vector[client].getState() == "Driver_on_the_way"){ // make sure the client status can request a new ride
            output0 <<  "You have already requested a ride and your driver is on the way to the pickup location." << endl;
            key = 1;
        }
        else if (rider_vector[client].getState() == "During_the_trip"){ // make sure the client status can request a new ride
            output0 <<  "You can not request a ride at this moment as you are already on a trip." << endl;
            key = 1;
        }
        
        if (key == 0){ // if none of the above gets trigered then client can request ride
            request(rider_vector, driver_vector, output0, client);
        } 
    }
    else if (command == "cancel"){ // cancel command recognition
        
        int client = -1;
        bool rider = false;
        bool driver = false;

        if (accountCheckerRider(rider_vector, phone) > -1 ){ // check if its a rider and store its ID
            client = accountCheckerRider(rider_vector, phone);
            rider = true;
        }
        if (accountCheckerDriver(driver_vector, phone) > -1 ){  // check if its a driver and store its ID
            client = accountCheckerDriver(driver_vector, phone);
            driver = true;
        }

        if (client == -1){ // if not recognized as Rider or Driver then accound does not exist
            output0 <<  "Account does not exist." << endl;
        }
        else if (rider){ // Rider client process
            if (rider_vector[client].getState() != "Driver_on_the_way"){ // recognize if Rider status cant cancel ride
                output0 <<  "You can only cancel a ride request if your driver is currently on the way to the pickup location." << endl;
            }
            else { // if obove is not trigered run Rider cancel function
                cancelRider(rider_vector, driver_vector, phone, client, output0); 
                
            } 
        }
        else if (driver){ // Driver client process
            if (driver_vector[client].getState() != "On_the_way_to_pickup"){ // recognize if Driver status cant cancel ride
                output0 <<  "You can only cancel a ride request if you are currently on the way to the pickup location." << endl;
            }
            else { // if above is not trigered run Driver cance function
                cancelDriver(driver_vector, rider_vector, phone, client, output0);
            }
        }
        else { // ERROR recognition of cancelation process failing to run
            cout << "lost in prossess" << endl;
            exit(1);
        }
    }
    else { // ERROR recognition of command not recognized 
        cout << "command not recognized" << endl;
        exit(1);
    }
    

    RiderFilePrint(rider_vector, output2); // print update rider file to output 2 file
    driverFilePrint(driver_vector, output1); // print updated driver file to output 1 file



    output0.close();
    output1.close();
    output2.close();
    return 0; 

}