/******************************************************************************
Instructor: Prof. Charlesvester Wims
Course: CS 109
Assignment: Module 6-7 Lab (Final) -- Chapter 14, Problem 2
Date: November 23, 2024
Group White (Bruce D., Mikaela P., Savalas P., Kanisha W.)
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <sstream>

using namespace std;

struct LicenseRecord {
    int licenseNumber;
    string details;
};

class SortedList {
public:
    void addRecord(const LicenseRecord& record) {
        auto result = records.insert(record.licenseNumber);
        if (!result.second) {
            duplicates.push_back(record);
        }
        else {
            uniqueRecords.push_back(record);
        }
    }

    void writeDuplicatesToFile(const std::string& filename) {
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const auto& record : duplicates) {
                outFile << record.licenseNumber << " " << record.details << endl;
            }
            outFile.close();
        }
        else {
            cerr << "Unable to open file " << filename << endl;
        }
    }

private:
    set<int> records;
    vector<LicenseRecord> uniqueRecords;
    vector<LicenseRecord> duplicates;
};

int main() {
    ifstream inFile("licensesa.dat");
    string line;
    SortedList sortedList;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            int licenseNumber;
            string details;
            istringstream iss(line);
            iss >> licenseNumber;
            getline(iss >> ws, details); // Using ws to skip leading whitespace
            if (iss.fail()) {
                cerr << "Error reading license number or details from line: " << line << endl;
                continue;
            }
            LicenseRecord record = { licenseNumber, details };
            sortedList.addRecord(record);
        }
        inFile.close();
    }
    else {
        cerr << "Unable to open file licensesa.dat" << endl;
    }

    sortedList.writeDuplicatesToFile("duplicates.dat");

    return 0;
}
