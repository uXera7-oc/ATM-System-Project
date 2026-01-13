// =====================================================================
// ATM System Project
// Program: Client ATM Interface for Banking Operations
// This program simulates an ATM system allowing clients to perform
// basic banking operations after authentication
// =====================================================================



#include <iostream>       
#include <string>       
#include <cctype>         
#include <vector>         
#include <fstream>        
#include <iomanip>        


using namespace std;



// Global constant for the clients data file name
const string FileName = "ClientsRecords.txt";

// Structure to store client data - contains all client information
struct stClientData
{
    string PinCode;           
    string AccountNumber;     
    string Name;              
    string Phone;             
    float AccountBalance;     
};

// Global variable to store currently logged-in client data
stClientData CurrentClient;

// Enumeration for ATM main menu options
enum eATM { eQuickWithdraw = 1, eNormalWithdraw, eDeposit, eCheckBalance, eLogout };

// Enumeration for quick withdraw amount options
enum eQuickWithDraw { Twenty = 1, Fifty, Hundred, TwoHundred, FourHundred, SixHundred, EightHundred, Thousand, Exit };

// Function to split a string into parts based on a delimiter
// Example: "User#//#123" becomes ["User", "123"]
vector <string> SplitString(string S1, string Delim)
{
    vector <string> vString;
    short pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); //Store the Word
        if (sWord != Delim)
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());//Erasing until position and move to the next word

    }

    if (S1 != Delim)
    {
        vString.push_back(S1);
    }

    return  vString;
}

// Function to read account number from user input
// Prompts user to enter account number and returns it as string
string ReadAccountNumber()
{
    string AccountNumber;

    cout << "Enter Account Number? ";
    getline(cin, AccountNumber);

    return AccountNumber;
}

// Function to read PIN code from user input
// Prompts user to enter PIN and returns it as string
string ReadPin()
{
    string Pin;

    cout << "Enter Pin? ";
    getline(cin, Pin);

    return Pin;
}

// Function to convert a text line from file into organized client data
stClientData ConvertLineToRecord(string Line, string Delim = "#//#")
{
    stClientData ClientData;
    vector <string> vClientData;

    vClientData = SplitString(Line, Delim);

    if (vClientData.size() >= 5)
    {
        ClientData.AccountNumber = vClientData[0];
        ClientData.PinCode = vClientData[1];
        ClientData.Name = vClientData[2];
        ClientData.Phone = vClientData[3];
        ClientData.AccountBalance = stof(vClientData[4]);
    }

    return ClientData;

}

// Function to read all clients data from file and store them in a list
vector<stClientData> LoadClientDataFromFile(string FileName)
{
    vector <stClientData> vClients;

    fstream ClientsRecords;

    ClientsRecords.open(FileName, ios::in);

    if (ClientsRecords.is_open())
    {
        string Line;
        stClientData Client;

        while (getline(ClientsRecords, Line))
        {
            Client = ConvertLineToRecord(Line);

            vClients.push_back(Client);
        }
        ClientsRecords.close();
    }

    return vClients;

}

// Function to convert client record to text line for saving in file
// Formats client data with delimiters for consistent file storage
string ConvertRecordToLine(stClientData Client, string Delim = "#//#")
{
    return Client.AccountNumber + Delim
        + Client.PinCode + Delim
        + Client.Name + Delim
        + Client.Phone + Delim
        + to_string(Client.AccountBalance);
}

// Function to save clients data to file
// Overwrites entire file with updated client information
void SaveClientsDataToFile(string FileName, vector<stClientData> vClients)
{
    fstream File;
    File.open(FileName, ios::out);

    if (File.is_open())
    {
        for (stClientData& Client : vClients)
        {
            File << ConvertRecordToLine(Client) << endl;
        }
        File.close();
    }
}

// Function to authenticate client login credentials
// Checks if account number and PIN match any client record
bool CheckClientLogin(string AccountNumber, string Pin)
{
    vector <stClientData> vClients = LoadClientDataFromFile(FileName);

    for (stClientData& Client : vClients)
    {
        if (AccountNumber == Client.AccountNumber && Pin == Client.PinCode)
        {
            CurrentClient = Client;
            return true;
        }
    }
    return false;

}

// Function to update current client's balance in the file
// Synchronizes in-memory client data with persistent storage
void UpdateCurrentClientInFile()
{
    vector<stClientData> vClients = LoadClientDataFromFile(FileName);

    for (stClientData& Client : vClients)
    {
        if (Client.AccountNumber == CurrentClient.AccountNumber)
        {
            Client.AccountBalance = CurrentClient.AccountBalance;
            break;
        }
    }

    SaveClientsDataToFile(FileName, vClients);
}

// Function to ask user to press any key to return to main menu
// Provides pause functionality for better user experience
void PressAnyKeyFunction()
{

    cout << "Press Any Key to go back to Main Menu...";
    system("pause>0");

}

// Function to ask Client to choose an option from the menu
// Prompts user to enter a number between 1 and 5
short AskForOperation()
{
    short Number;
    cout << "Choose What Do you Want to do ? [1 to 5] ?";
    cin >> Number;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return Number;
}

// Function to display the main menu of the program
// Shows all available ATM operations in formatted interface
void ATMMainMenuScreen()
{
    system("cls");
    cout << "================================================\n";
    cout << "\t\tATM Main Menu Screen\n";
    cout << "================================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "================================================\n";

}

// Function to convert menu choice number to enumeration value
// Maps numerical input to corresponding ATM operation enum
eATM MenuOperation(short Number)
{
    switch (Number)
    {
    case 1:  return eQuickWithdraw;

    case 2:  return eNormalWithdraw;

    case 3:  return eDeposit;

    case 4:  return eCheckBalance;

    case 5:  return eLogout;

    default:
        return eLogout;
    }
}

// Function to display login screen and authenticate user
// Continues prompting until valid credentials are entered
void LoginScreen()
{
    string AccountNumber, Pin;

    vector <stClientData> vClients = LoadClientDataFromFile(FileName);

    cout << "\n------------------------------------\n";
    cout << "\tLogin Screen";
    cout << "\n------------------------------------\n";

    while (true)
    {
        AccountNumber = ReadAccountNumber();
        Pin = ReadPin();

        if (!(CheckClientLogin(AccountNumber, Pin)))
        {
            system("cls");
            cout << "\n------------------------------------\n";
            cout << "\tLogin Screen";
            cout << "\n------------------------------------\n";
            cout << "Invalid Account Number/PinCode!\n";
        }
        else
        {
            break;
        }
    }
}

// Function to get current client's account balance
// Returns the balance of the currently logged-in client
float GetCurrentClientBalance()
{
    return CurrentClient.AccountBalance;
}

// Function to perform quick withdraw operation
// Provides predefined withdrawal amounts for fast transactions
void QuickWithdraw()
{
    vector <stClientData> vClients;
    short OpNumber;
    char Answer;
    float NewBalance = 0;

    cout << "\n================================================\n";
    cout << "\t\tQuick Withdraw\n";
    cout << "================================================\n\n";
    cout << "\t[1] 20\t\t[2] 50\n\n";
    cout << "\t[3] 100\t\t[4] 200\n\n";
    cout << "\t[5] 400\t\t[6] 600\n\n";
    cout << "\t[7] 800\t\t[8] 1000\n\n";
    cout << "\t[9] Exit\n\n";
    cout << "================================================\n";
    cout << "Your Balance is : " << GetCurrentClientBalance() << endl;
    cout << "Choose What to Withdraw from [1] to [8]";
    cin >> OpNumber;
    if (OpNumber == 9)
    {
        return;
    }

    cout << "\nAre You sure you want perform this transaction? (y/n) ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        switch ((eQuickWithDraw)OpNumber)
        {
        case 1:
            CurrentClient.AccountBalance -= 20;
            UpdateCurrentClientInFile();
            break;
        case 2:
            CurrentClient.AccountBalance -= 50;
            UpdateCurrentClientInFile();
            break;
        case 3:
            CurrentClient.AccountBalance -= 100;
            UpdateCurrentClientInFile();
            break;
        case 4:
            CurrentClient.AccountBalance -= 200;
            UpdateCurrentClientInFile();
            break;
        case 5:
            CurrentClient.AccountBalance -= 400;
            UpdateCurrentClientInFile();
            break;
        case 6:
            CurrentClient.AccountBalance -= 600;
            UpdateCurrentClientInFile();
            break;
        case 7:
            CurrentClient.AccountBalance -= 800;
            UpdateCurrentClientInFile();
            break;
        case 8:
            CurrentClient.AccountBalance -= 1000;
            UpdateCurrentClientInFile();
            break;
        }

        cout << "Withdraw Done Successfully , New Balance is : " << CurrentClient.AccountBalance << endl;
    }
    else
    {
        cout << "Withdraw Cancelled ! " << endl;
    }
    vClients = LoadClientDataFromFile(FileName);
}

// Function to perform normal withdraw operation
// Allows custom withdrawal amounts in multiples of 5
void NormalWithdraw()
{
    int Amount;
    char Answer;
    vector <stClientData> vClients;

    cout << "\n================================================\n";
    cout << "\t\tNormal Withdraw \n";
    cout << "================================================\n\n";
    do
    {
        cout << "\n\nEnter an Amount multiple of 5's ?";
        cin >> Amount;
    } while (Amount % 5 != 0);

    if (Amount > GetCurrentClientBalance())
    {
        cout << "Amount Exceeds the balance, You can withdraw up to : " << CurrentClient.AccountBalance << endl;
        cout << "\nPlease Enter Another Amount? ";
        cin >> Amount;
    }
    else
    {
        CurrentClient.AccountBalance -= Amount;
        UpdateCurrentClientInFile();
    }

    cout << "\nAre you sure you want perform this transaction? (y/n)";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        vClients = LoadClientDataFromFile(FileName);
        cout << "Done Successfully. New Balance is : " << CurrentClient.AccountBalance << endl;
    }
    else
    {
        cout << "Withdraw Cancelled ! " << endl;
    }
}

// Function to perform deposit operation
// Allows client to add funds to their account with validation
void Deposit()
{
    vector <stClientData> vClients;
    float Amount;
    char Answer;

    cout << "\n================================================\n";
    cout << "\t\tDeposit\n";
    cout << "================================================\n\n";

    do
    {
        cout << "Enter a positive Deposit Amount? ";
        cin >> Amount;
    } while (Amount <= 0);

    cout << "\n\nAre you sure you want perform this transaction [Y/N] ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        CurrentClient.AccountBalance += Amount;
        UpdateCurrentClientInFile();
        cout << "Deposit Done Successfully , New Balance is : " << CurrentClient.AccountBalance << endl << endl;
    }
    else
    {
        cout << "Deposit Cancelled ! " << endl;
    }
    vClients = LoadClientDataFromFile(FileName);
}

// Function to display current account balance
// Shows client's available funds without performing transactions
void CheckBalance()
{
    cout << "\n================================================\n";
    cout << "\t\tCheck Balance Screen\n";
    cout << "================================================\n\n";
    cout << "\nYour Balance is : " << CurrentClient.AccountBalance << endl << endl;
}

// Main controller function for ATM operations
// Manages the complete ATM session flow and menu navigation
void PerformATMMainMenu()
{
    eATM Operation;

    while (true)
    {
        LoginScreen();

        do
        {
            ATMMainMenuScreen();
            Operation = (eATM)AskForOperation();

            switch (Operation)
            {
            case eQuickWithdraw:
                system("cls");
                QuickWithdraw();
                PressAnyKeyFunction();
                break;

            case eNormalWithdraw:
                system("cls");
                NormalWithdraw();
                PressAnyKeyFunction();
                break;

            case eDeposit:
                system("cls");
                Deposit();
                PressAnyKeyFunction();
                break;

            case eCheckBalance:
                system("cls");
                CheckBalance();
                PressAnyKeyFunction();
                break;

            case eLogout:
                system("cls");
                break;

            default:
                system("cls");
                cout << "\nError: Invalid Option! Please enter a number between 1 and 5.\n";
                PressAnyKeyFunction();
                break;
            }

        } while (Operation != eLogout);
    }
}

// Main function - entry point of the ATM program
// Initializes and runs the ATM system
int main()
{

    //You must have ClientsRecords.txt in Containing Folder of This Code
    PerformATMMainMenu();
  
    
    
    return 0;
}