#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>

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
            getline(iss, details);
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
