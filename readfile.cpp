#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
using namespace std;
// Example structure
struct MyStruct
{
    int intValue;
    string doubleValue;
    string stringValue;
};

int main()
{
    // Open a text file for reading
    ifstream inputFile("nati.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    string line;
    getline(inputFile, line);

    // Create a stringstream to parse the line
    istringstream iss(line);

    // Create a structure to store the parsed data
    MyStruct myData;

    // Parse data from the stringstream into the structure
    iss >> myData.intValue >> myData.doubleValue >> myData.stringValue;

    // Display the data
    cout << "intValue: " << myData.intValue << endl;
    cout << "doubleValue: " << myData.doubleValue << endl;
    cout << "stringValue: " << myData.stringValue << endl;

    // Close the file
    inputFile.close();

    return 0;
}
