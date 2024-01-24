#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <ctime>
using namespace std;

struct Medicine
{
    string medicineName;
    string medicineType;
    int price;
};
void display();
void buyMedicine();
void displayReceipt(vector<int> whichMedicine, vector<int> quantities, string name);

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

        buyer.close();
        cout << "here is ur receipt" << endl;
        displayReceipt(whichMedicine, quantities, name);
    }
    else
    {
        cout << "Error opening file";
        cout << endl;
    }
}

void displayReceipt(vector<int> whichMedicine, vector<int> quantities, string name)
{

    Medicine medicine;
    string line;
    int totalPrice = 0;
    // time_t now = time(0);
    // char *dt = ctime(&now);
    time_t now = time(0);
    struct tm *timeinfo = localtime(&now);

    char dt[20];
    strftime(dt, sizeof(dt), "%Y-%m-%d %H:%M:%S", timeinfo);

    cout << "\t-------------------------------------------------------------------------\n";
    cout << "\t                       Pharmacy Receipt                                  \n";
    cout << "\t-------------------------------------------------------------------------\n";
    cout << "\tName: " << name << "                                 Date: " << dt << endl;
    cout << "\t-------------------------------------------------------------------------\n";
    cout << "\tNo.\tMedicine name\tprice\tquantity\ttotal price\n";
    for (int i = 0, j = 0; i < whichMedicine.size(); i++)
    {
        ifstream inputFile("Medicines.txt");
        if (inputFile.is_open())
        {
            while (j < whichMedicine[i] && getline(inputFile, line))
            {
                j++;
            }
            istringstream iss(line);
            iss >> medicine.medicineName >> medicine.medicineType >> medicine.price;
            cout << "\t" << i + 1 << ".\t" << medicine.medicineName << "\t" << medicine.price << "\t" << quantities[i] << "\t\t" << quantities[i] * medicine.price << endl;
            totalPrice += quantities[i] * medicine.price;
            j = 0;
            inputFile.close();
        }
        else
        {
            cout << " error opening the file" << endl;
        }
    }

    cout << endl;
    cout << "\t\t\t\t\tGrand total: " << totalPrice << endl;
    cout << "\t-------------------------------------------------------------------------\n";
}