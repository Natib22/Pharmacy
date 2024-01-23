#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
using namespace std;

struct Medicine
{
    string medicineName;
    string medicineType;
    int price;
};
void display();
void buyMedicine();

int main()
{
    buyMedicine();
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
    int i = 1;
    while (getline(inputFile, line))
    {
        istringstream iss(line);
        iss >> medicine.medicineName >> medicine.medicineType >> medicine.price;
        cout << i << ". " << medicine.medicineName << "\t" << medicine.medicineType << "\t" << medicine.price << endl;
        i++;
    }

    inputFile.close();
}

void buyMedicine()
{
    fstream buyer;
    int choice;
    string name;
    vector<int> whichMedicine;
    vector<int> quantities;

    buyer.open("drugHistory.txt", ios::app);
    if (buyer.is_open())
    {
        cout << "Enter your fullname: ";
        getline(cin, name);
        cout << endl;

        display();
        do
        {
            buyer << name << " ";
            cout << "Which medicine do you want to buy bases on Inventory Id: ";
            cin >> choice;
            whichMedicine.push_back(choice);
            buyer << choice << " ";
            cout << endl;

            cout << "Enter how many Medicines you want to buy /quantities: ";
            cin >> choice;
            buyer << choice << endl;
            quantities.push_back(choice);
            cout << endl;

            cout << "If you want to buy more press 1 (else any key) ";
            cin >> choice;
            cout << endl;
        } while (choice == 1);

        // buyer << "\n";
    }
    else
    {
        cout << "Error opening file";
        cout << endl;
    }
}