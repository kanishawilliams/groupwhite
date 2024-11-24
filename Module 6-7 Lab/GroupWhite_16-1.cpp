/******************************************************************************
Instructor: Prof. Charlesvester Wims
Course: CS 109
Assignment: Module 6-7 Lab (Final) -- Chapter 16, Problem 1
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

// Overload the extraction operator for monthOn type
istream& operator>>(istream& in, monthOn& month) {
    int monthInt;
    in >> monthInt;
    month = static_cast<monthOn>(monthInt);
    return in;
}

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
    Room** rooms;
    int numRooms;

public:
    // Default constructor
    Floor() : numRooms(0), rooms(nullptr) {}

    // Constructor
    Floor(int numRooms, int accessPointsPerRoom) : numRooms(numRooms) {
        rooms = new Room*[numRooms];
        for (int i = 0; i < numRooms; ++i) {
            rooms[i] = new Room(accessPointsPerRoom);
        }
    }

    // Destructor
    ~Floor() {
        for (int i = 0; i < numRooms; ++i) {
            delete rooms[i];
        }
        delete[] rooms;
    }

    // Accessor methods
    int getNumRooms() const { return numRooms; }
    Room& getRoom(int index) {
        if (index >= 0 && index < numRooms) {
            return *rooms[index];
        } else {
            throw out_of_range("Invalid room index.");
        }
    }

    // Mutator method
    void addRoom(int accessPointsPerRoom) {
        Room** temp = new Room*[numRooms + 1];
        for (int i = 0; i < numRooms; ++i) {
            temp[i] = rooms[i];
        }
        temp[numRooms] = new Room(accessPointsPerRoom);
        delete[] rooms;
        rooms = temp;
        numRooms++;
    }
};

// Class to represent a building
class Building {
private:
    Floor** floors;
    int numFloors;

public:
    // Constructor
    Building(int numFloors, int numRoomsPerFloor, int accessPointsPerRoom) :
        numFloors(numFloors) {
        floors = new Floor*[numFloors];
        for (int i = 0; i < numFloors; ++i) {
            floors[i] = new Floor(numRoomsPerFloor, accessPointsPerRoom);
        }
    }

    // Destructor
    ~Building() {
        for (int i = 0; i < numFloors; ++i) {
            delete floors[i];
        }
        delete[] floors;
    }

    // Accessor methods
    int getNumFloors() const { return numFloors; }
    Floor& getFloor(int index) {
        if (index >= 0 && index < numFloors) {
            return *floors[index];
        } else {
            throw out_of_range("Invalid floor index.");
        }
    }

    // Mutator methods
    void addFloor(int numRooms, int accessPointsPerRoom) {
        Floor** temp = new Floor*[numFloors + 1];
        for (int i = 0; i < numFloors; ++i) {
            temp[i] = floors[i];
        }
        delete[] floors;
        floors = temp;
        floors[numFloors] = new Floor(numRooms, accessPointsPerRoom);
        numFloors++;
    }
};

void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Add Floor\n";
    cout << "2. Add Room to Floor\n";
    cout << "3. Add Access Point to Room\n";
    cout << "4. Turn Access Point On\n";
    cout << "5. Turn Access Point Off\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    try {
        Building building(3, 2, 3);
        int choice;

        while (true) {
            displayMenu();
            cin >> choice;

            if (choice == 6) break;

            int floorIndex, roomIndex, accessPointIndex, numRooms, numAccessPoints;
            monthOn month;

            switch (choice) {
            case 1:
                cout << "Enter number of rooms for the new floor: ";
                cin >> numRooms;
                cout << "Enter number of access points per room: ";
                cin >> numAccessPoints;
                building.addFloor(numRooms, numAccessPoints);
                cout << "New floor added.\n";
                break;
            case 2:
                cout << "Enter floor index to add a room: ";
                cin >> floorIndex;
                cout << "Enter number of access points for the new room: ";
                cin >> numAccessPoints;
                building.getFloor(floorIndex).addRoom(numAccessPoints);
                cout << "New room added to floor " << floorIndex << ".\n";
                break;
            case 3:
                cout << "Enter floor index: ";
                cin >> floorIndex;
                cout << "Enter room index: ";
                cin >> roomIndex;
                building.getFloor(floorIndex).getRoom(roomIndex).addAccessPoint();
                cout << "New access point added to room " << roomIndex << " on floor " << floorIndex << ".\n";
                break;
            case 4:
                cout << "Enter floor index: ";
                cin >> floorIndex;
                cout << "Enter room index: ";
                cin >> roomIndex;
                cout << "Enter access point index: ";
                cin >> accessPointIndex;
                cout << "Enter month turned on (0-11): ";
                cin >> month;
                building.getFloor(floorIndex).getRoom(roomIndex).getAccessPoint(accessPointIndex).turnOn(month);
                cout << "Access point " << accessPointIndex << " in room " << roomIndex << " on floor " << floorIndex << " turned on.\n";
                break;
            case 5:
                cout << "Enter floor index: ";
                cin >> floorIndex;
                cout << "Enter room index: ";
                cin >> roomIndex;
                cout << "Enter access point index: ";
                cin >> accessPointIndex;
                building.getFloor(floorIndex).getRoom(roomIndex).getAccessPoint(accessPointIndex).turnOff();
                cout << "Access point " << accessPointIndex << " in room " << roomIndex << " on floor " << floorIndex << " turned off.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
