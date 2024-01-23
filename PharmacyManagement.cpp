#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
using namespace std;

struct Medicine
{
    string medicineName;
    string medicineType;
    int price;
};
void display();

int main()
{
    display();
    return 0;
}

void display()
{
    ifstream inputFile("Medicines.txt");
    Medicine medicine;
    string line;
    if (!inputFile.is_open())
    {
        cout << "Error opening file." << endl;
    }

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        iss >> medicine.medicineName >> medicine.medicineType >> medicine.price;
        cout << medicine.medicineName << "\t" << medicine.medicineType << "\t" << medicine.price << endl;
    }

    inputFile.close();
}