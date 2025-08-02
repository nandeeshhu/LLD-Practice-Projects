#include <iostream>
#include<vector>
#include <ctime>
#include <string>
#include <iomanip>
#include<queue>
#include<unordered_set>
#include <sstream>
#include<unordered_map>
#include <random>

using namespace std;
enum Type {
    twoWheeler,
    threeWheeler,
    fourWheeler,
    fourWheelerHeavy
};

class Vehicle {
public:
    string plateNo;
    string color;
    Type type;

    Vehicle(string plateNo, string color, Type type) {
        this->plateNo = plateNo;
        this->color = color;
        this->type = type;
    }
};

class Ticket {
    string getTime() {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
        auto str = oss.str();

        return str;
    }
    string getID(string &plateNo, string &time) {
        string ticketID = plateNo;
        for(auto c:time) {
            if(c>='0' && c<='9') ticketID.push_back(c);
        }
        return ticketID;
    }
    public:
    string ticketID;
    string plateNo;
    string Time;
    string spot;
    Ticket(Vehicle vehicle, int position) {
        this->plateNo = vehicle.plateNo;
        this->Time = getTime();
        this->ticketID = getID(this->plateNo, this->Time);
        this->spot = to_string(vehicle.type)+"/"+to_string(position);
    }
};

class ParkingLot {
    unordered_map<Type, queue<int>> availablePosition;
    unordered_map<string, Type> stringToEnum;
    unordered_map<Type, int> rate;
    unordered_map<string, string> vehicleParked;

    Ticket getTicket(Vehicle vehicle, int type_) {
        Type type = static_cast<Type>(type_);
        int availableSpot = availablePosition[type].front();
        availablePosition[type].pop();
        Ticket ticket = Ticket(vehicle, availableSpot);
        return ticket;
    }

    Type getType(Ticket ticket) {
        string tp;
        int i = 0, len = ticket.spot.length();

        while(i<len && ticket.spot[i]!='/') tp.push_back(ticket.spot[i++]);
        return stringToEnum[tp];
    }
    string getTime() {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
        auto str = oss.str();

        return str;
    }

    int getSpot(Ticket ticket) {
        int i = 0, len = ticket.spot.length();

        while(i<len && ticket.spot[i]!='/') i++;
        i++;
        return stoi(ticket.spot.substr(i));
    }
    ParkingLot(unordered_map<Type, int> pltCounts,unordered_map<Type, int> rate) {
        for(auto & plt: pltCounts) {
            for(int position=1;position<=plt.second;position++) {
                this->availablePosition[plt.first].push(position);
            }
            this->stringToEnum[to_string(plt.first)] = plt.first;
        }
        this->rate = rate;
    }
    int getDuration(const string& entryTimeStr, const string& exitTimeStr) {
        tm entryTm = {}, exitTm = {};
        istringstream issEntry(entryTimeStr);
        istringstream issExit(exitTimeStr);

        issEntry >> get_time(&entryTm, "%d-%m-%Y %H-%M-%S");
        issExit >> get_time(&exitTm, "%d-%m-%Y %H-%M-%S");

        time_t entryTime = mktime(&entryTm);
        time_t exitTime = mktime(&exitTm);

        double seconds = difftime(exitTime, entryTime);
        int days = (seconds + 24 * 60 * 60 - 1) / (24 * 60 * 60);  // round up
        return max(1, days);
    }


    ParkingLot(const ParkingLot&) = delete;
    ParkingLot& operator=(const ParkingLot&) = delete;

    // Singleton instance
    static ParkingLot* instance;

    public:
    static ParkingLot* getInstance(unordered_map<Type, int> pltCounts = {}, unordered_map<Type, int> rate = {}) {
        if (!instance) {
            instance = new ParkingLot(pltCounts, rate);
        }
        return instance;
    }

    Ticket park(Vehicle vehicle) {
        int type_ = vehicle.type;
        while(type_<5) {
            if(!availablePosition[static_cast<Type>(type_)].empty()) break;
            type_++;
        }
        if(type_==5) throw runtime_error("No available spot for this vehicle type.");
        Ticket ticket = getTicket(vehicle, type_);
        vehicleParked[vehicle.plateNo] = ticket.spot;
        return ticket;
    }

    int Unpark(Ticket ticket) {
        Type type = getType(ticket);
        int spot = getSpot(ticket);
        string presetTime = getTime();
        int parkingDays = getDuration(ticket.Time, presetTime);
        availablePosition[type].push(spot);
        vehicleParked.erase(ticket.plateNo);
        return parkingDays*rate[type];
    }

    string searchParkingLot(string plateNo) {
        if(vehicleParked.find(plateNo)==vehicleParked.end()) return "Null";
        return vehicleParked[plateNo];
    }
};

ParkingLot* ParkingLot::instance = nullptr;
int main() {
    // Define number of parking spots for each type
    unordered_map<Type, int> pltCounts = {
        {twoWheeler, 30},
        {threeWheeler, 20},
        {fourWheeler, 40},
        {fourWheelerHeavy, 10}
    };

    unordered_map<Type, int> rate = {
        {twoWheeler, 20},
        {threeWheeler, 40},
        {fourWheeler, 50},
        {fourWheelerHeavy, 100}
    };

    ParkingLot* lot = ParkingLot::getInstance(pltCounts, rate);

    // Vehicle pool for simulation
    vector<Vehicle> allVehicles;
    vector<Ticket> issuedTickets;

    // Generate vehicles (100 total: 25 each)
    int count = 0;
    for (int i = 0; i < 25; ++i) {
        allVehicles.push_back(Vehicle("KA" + to_string(1000 + count++), "Red", twoWheeler));
        allVehicles.push_back(Vehicle("KA" + to_string(1000 + count++), "Blue", threeWheeler));
        allVehicles.push_back(Vehicle("KA" + to_string(1000 + count++), "White", fourWheeler));
        allVehicles.push_back(Vehicle("KA" + to_string(1000 + count++), "Black", fourWheelerHeavy));
    }

    // Park all vehicles
    for (auto &v : allVehicles) {
        try {
            Ticket t = lot->park(v);
            issuedTickets.push_back(t);
            cout << "Parked: " << v.plateNo << " -> Spot: " << t.spot << ", Time: " << t.Time << "\n";
        } catch (...) {
            cout << "Parking failed for: " << v.plateNo << endl;
        }
    }

    cout << "\n--------- RANDOM UNPARKING ----------\n";

    // Randomly unpark 30 vehicles
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, issuedTickets.size() - 1);

    unordered_set<int> usedIndices;
    int unparkCount = 0;

    while (unparkCount < 30) {
        int index = dist(gen);
        if (usedIndices.count(index)) continue;
        usedIndices.insert(index);

        Ticket t = issuedTickets[index];
        int cost = lot->Unpark(t);
        cout<<"PAY THE PARKING AMOUNT RS."<<cost<<"."<<endl;
        cout << "Unparked: " << t.plateNo << " from Spot: " << t.spot << " at Time: " << t.Time << "\n";
        unparkCount++;
    }

    // Search for 10 random parked vehicles
    for (int i = 0; i < 10; ++i) {
        string plate = issuedTickets[i].plateNo;
        string result = lot->searchParkingLot(plate);
        cout << "Search: " << plate << " -> Spot: " << result << endl;
    }

    // Search for vehicles that were never parked (simulate invalid searches)
    vector<string> invalidPlates = {"KA9999", "MH1234", "DL4321"};
    for (const auto& plate : invalidPlates) {
        string result = lot->searchParkingLot(plate);
        cout << "Search: " << plate << " -> Spot: " << result << endl;
    }

    return 0;
}

