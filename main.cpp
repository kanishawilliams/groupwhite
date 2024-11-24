/******************************************************************************
Instructor: Prof. Charlesvester Wims
Course: CS 109
Assignment: Module 6-7 Lab (Final)
Date: November 23, 2024
Group White (Bruce D., Mikaela P., Savalas P., Kanisha W.)
*******************************************************************************/

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// Define an enum for the months
enum monthOn { January, February, March, April, May, June, 
                July, August, September, October, November, December };

// Class to represent a network access point
class NetworkAccessPoint {
private:
    bool status;
    monthOn monthTurnedOn;

public:
    // Constructor
    NetworkAccessPoint() : status(false), monthTurnedOn(January) {}

    // Accessor methods
    bool isOn() const { return status; }
    monthOn getMonthTurnedOn() const { return monthTurnedOn; }

    // Mutator methods
    void turnOn(monthOn month) {
        if (!status) {
            status = true;
            monthTurnedOn = month;
        } else {
            throw runtime_error("Access point is already on.");
        }
    }

    void turnOff() {
        if (status) {
            status = false;
            monthTurnedOn = January; // Reset month when turning off
        } else {
            throw runtime_error("Access point is already off.");
        }
    }
};

// Class to represent a room
class Room {
private:
    NetworkAccessPoint* accessPoints;
    int numAccessPoints;

public:
    // Constructor
    Room(int numAccessPoints) : numAccessPoints(numAccessPoints) {
        accessPoints = new NetworkAccessPoint[numAccessPoints];
    }

    // Destructor
    ~Room() {
        delete[] accessPoints;
    }

    // Accessor methods
    int getNumAccessPoints() const { return numAccessPoints; }
    NetworkAccessPoint& getAccessPoint(int index) {
        if (index >= 0 && index < numAccessPoints) {
            return accessPoints[index];
        } else {
            throw out_of_range("Invalid access point index.");
        }
    }

    // Mutator methods
    void addAccessPoint() {
        NetworkAccessPoint* temp = new NetworkAccessPoint[numAccessPoints + 1];
        for (int i = 0; i < numAccessPoints; ++i) {
            temp[i] = accessPoints[i];
        }
        delete[] accessPoints;
        accessPoints = temp;
        accessPoints[numAccessPoints] = NetworkAccessPoint();
        numAccessPoints++;
    }
};

// Class to represent a floor
class Floor {
private:
    Room* rooms;
    int numRooms;

public:
    // Default constructor
    Floor() : numRooms(0) {
        rooms = nullptr; 
    }

    // Constructor
    Floor(int numRooms, int accessPointsPerRoom) : numRooms(numRooms) {
        rooms = new Room[numRooms];
        for (int i = 0; i < numRooms; ++i) {
            rooms[i] = Room(accessPointsPerRoom);
        }
    }

    // Destructor
    ~Floor() {
        delete[] rooms;
    }

    // Accessor methods
    int getNumRooms() const { return numRooms; }
    Room& getRoom(int index) {
        if (index >= 0 && index < numRooms) {
            return rooms[index];
        } else {
            throw out_of_range("Invalid room index.");
        }
    }

};

// Class to represent a building
class Building {
private:
    Floor* floors;
    int numFloors;

public:
    // Constructor
    Building(int numFloors, int numRoomsPerFloor, int accessPointsPerRoom) :
        numFloors(numFloors) {
        floors = new Floor[numFloors];
        for (int i = 0; i < numFloors; ++i) {
            floors[i] = Floor(numRoomsPerFloor, accessPointsPerRoom);
        }
    }

    // Destructor
    ~Building() {
        delete[] floors;
    }

    // Accessor methods
    int getNumFloors() const { return numFloors; }
    Floor& getFloor(int index) {
        if (index >= 0 && index < numFloors) {
            return floors[index];
        } else {
            throw out_of_range("Invalid floor index.");
        }
    }

    // Mutator methods
    void addFloor(int numRooms, int accessPointsPerRoom) {
        Floor* temp = new Floor[numFloors + 1];
        for (int i = 0; i < numFloors; ++i) {
            temp[i] = floors[i];
        }
        delete[] floors;
        floors = temp;
        floors[numFloors] = Floor(numRooms, accessPointsPerRoom);
        numFloors++;
    }
};

int main() {
    try {
        // Create a building with 3 floors, each with 2 rooms and 3 access points per room
        Building building(3, 2, 3); 

        // Turn on the first access point on the first floor
        building.getFloor(0).getRoom(0).getAccessPoint(0).turnOn(May);

        // Check if the first access point is on
        if (building.getFloor(0).getRoom(0).getAccessPoint(0).isOn()) {
            cout << "Access point is on, turned on in " 
                 << building.getFloor(0).getRoom(0).getAccessPoint(0).getMonthTurnedOn()
                 << endl;
        }

        // Turn on another access point
        building.getFloor(0).getRoom(0).getAccessPoint(1).turnOn(June);

        // Add another floor
        building.addFloor(3, 4);

        // Turn on access points on the new floor
        building.getFloor(3).getRoom(0).getAccessPoint(0).turnOn(July);
    } catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
