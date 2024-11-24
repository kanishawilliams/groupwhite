#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;

// Function to convert a letter to its corresponding ICAO word
string getICAOWord(char letter) {
    switch (toupper(letter)) {
        case 'A': return "Alpha";
        case 'B': return "Bravo";
        case 'C': return "Charlie";
        case 'D': return "Delta";
        case 'E': return "Echo";
        case 'F': return "Foxtrot";
        case 'G': return "Golf";
        case 'H': return "Hotel";
        case 'I': return "India";
        case 'J': return "Juliett";
        case 'K': return "Kilo";
        case 'L': return "Lima";
        case 'M': return "Mike";
        case 'N': return "November";
        case 'O': return "Oscar";
        case 'P': return "Papa";
        case 'Q': return "Quebec";
        case 'R': return "Romeo";
        case 'S': return "Sierra";
        case 'T': return "Tango";
        case 'U': return "Uniform";
        case 'V': return "Victor";
        case 'W': return "Whiskey";
        case 'X': return "X-ray";
        case 'Y': return "Yankee";
        case 'Z': return "Zulu";
        default: throw invalid_argument(string(1, letter));
    }
}

// Function to process a string and output its phonetic version
void processString(const string& input) {
    cout << "Phonetic version is: ";
    for (char letter : input) {
        if (!isalpha(letter)) { // Skip non-alphabetic characters gracefully
            cout << "\nInvalid letter: " << letter << endl;
            continue;
        }
        try {
            cout << getICAOWord(letter) << " ";
        } catch (const invalid_argument& e) {
            cout << "\nInvalid letter: " << e.what() << endl;
        }
    }
    cout << endl;
}

int main() {
    string userInput;

    // Input prompt
    cout << "Enter a string: ";
    getline(cin, userInput);

    // Process the input string
    processString(userInput);

    return 0;
}
