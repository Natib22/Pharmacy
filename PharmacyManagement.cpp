#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <ctime>
#include <iomanip>
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
void searchMedicine();
void addMedicine();

int main()
{
    int choice;
    cout << right << setw(40) << "Pharmacy Management System\n";
    cout << "-------------------------------------------------" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << setw(36) << "Welcome to E-Pharmacy\n";
    cout << "Menu\n";
    cout << "choose from the given options:\n";
    cout << "1. Buy a medicine\n";
    cout << "2. Display medicine price list\n";
    cout << "3. Search for available medicine\n";
    cout << "4. To add medicine to the inventory(authorized user only)\n";
    cout << "5. To exit from the system\n\n";
    cout << "-------------------------------------------------" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Enter your choice from the menu: ";
    cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
        buyMedicine();
        break;
    case 2:
        display();
        break;
    case 3:
        searchMedicine();
        break;
    case 4:
        // authorized section
        addMedicine();
        break;
    case 5:
    exit_menu:
        exit(0);
        break;
    default:
        break;
    }
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
    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << "  Drugs Name"
         << "   \t\tDrug Type"

         << "\t\t\tDRUGS PRICE(Birr)" << endl;
    cout << "---------------------------------------------------------------------------------------------------------\n";
    while (getline(inputFile, line))
    {
        istringstream iss(line);
        iss >> medicine.medicineName >> medicine.medicineType >> medicine.price;
        cout << i << "  "
             << "." << medicine.medicineName << "\t\t" << medicine.medicineType << "\t\t\t" << medicine.price << endl;
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
        cin.ignore();
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

void searchMedicine()
{
    string searchMedicine;
    string line;
    int length;

    bool flag = false;
    int choice;
    ifstream inputFile("medicines.txt");

    if (!inputFile.is_open())
    {
        cerr << "Error opening file." << endl;
    }

    cout << "Enter the name of the name of the medicine you want to search from the store " << endl;
    cin >> searchMedicine;
    length = searchMedicine.size();

    searchMedicine[0] = toupper(searchMedicine[0]); // to convert user input string to first letter capital and the rest to lower
    for (int i = 1; i < length; i++)
        searchMedicine[i] = tolower(searchMedicine[i]);

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        Medicine medicine;

        iss >> medicine.medicineName >> medicine.medicineType >> medicine.price;

        if (medicine.medicineName == searchMedicine)
        {
            flag = true;
            cout << "---------------------------------------" << endl;
            cout << "---------------------------------------" << endl;
            cout << "Medicine found:" << endl;
            cout << "Name: " << medicine.medicineName << endl;
            cout << "Category: " << medicine.medicineType << endl;
            cout << "Price: " << medicine.price << endl;
            cout << "---------------------------------------" << endl;
            cout << "---------------------------------------" << endl;
            break;
        }
    }
    inputFile.close();
    if (flag == true)
    {
        cout << "If you want to buy " << searchMedicine << " from the pharmacy" << endl;
        cout << "(press 1 for Yes) or any other key to exit the system" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << searchMedicine << " is found in the medicine list below" << endl;
            buyMedicine();
            break;

        default:
            return;
        }
    }
    if (flag == false)
    {
        cout << "Medicine not found." << endl;
    }
}

void addMedicine()
{
    Medicine medicine;
    fstream myfile;
    myfile.open("Medicines.txt", ios::out | ios::app);
    if (myfile.is_open())
    {
        cout << "Enter the name of the medicine you want to add to the store\n";
        cin >> medicine.medicineName;
        cout << endl;
        medicine.medicineName[0] = toupper(medicine.medicineName[0]); // to convert user input string to first letter capital and the rest to lower
        for (int i = 1; i < medicine.medicineName.size(); i++)
            medicine.medicineName[i] = tolower(medicine.medicineName[i]);
        myfile << medicine.medicineName << " ";

        cout << "Enter the drug type of " << medicine.medicineName << endl;
        cin >> medicine.medicineType;
        myfile << medicine.medicineType << " ";
        cout << endl;

        cout << " Enter " << medicine.medicineName << " current price you want the store to sell" << endl;
        cin >> medicine.price;
        myfile << medicine.price;
        myfile << "\n";
    }
    myfile.close();
}