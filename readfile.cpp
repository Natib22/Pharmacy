#include <iostream>
#include <fstream>
#include <sstream>

// Example structure
struct MyStruct
{
    int intValue;
    double doubleValue;
    std::string stringValue;
};

int main()
{
    // Open a text file for reading
    std::ifstream inputFile("data.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    // Read each line from the file
    std::string line;
    std::getline(inputFile, line);

    // Create a stringstream to parse the line
    std::istringstream iss(line);

    // Create a structure to store the parsed data
    MyStruct myData;

    // Parse data from the stringstream into the structure
    iss >> myData.intValue >> myData.doubleValue >> myData.stringValue;

    // Display the data
    std::cout << "intValue: " << myData.intValue << std::endl;
    std::cout << "doubleValue: " << myData.doubleValue << std::endl;
    std::cout << "stringValue: " << myData.stringValue << std::endl;

    // Close the file
    inputFile.close();

    return 0;
}
