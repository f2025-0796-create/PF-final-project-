#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

const int MAX_ACCOUNTS = 100;

int accountNumbers[MAX_ACCOUNTS];
string accountNames[MAX_ACCOUNTS];
double balances[MAX_ACCOUNTS];
int totalAccounts = 0;

void createAccount();
void deposit();
void withdraw();
void checkBalance();
void displayStatement();
void transfer();
int findAccount(int accNum);
void saveToFile();
void loadFromFile();

int main() {
    loadFromFile();
    int choice;

    do {
        cout << " BANKING & ATM MANAGEMENT SYSTEM "<< endl;
        cout << "1. Create New Account"<< endl;
        cout << "2. Deposit Money"<< endl;
        cout << "3. Withdraw Money"<< endl;
        cout << "4. Check Balance"<< endl;
        cout << "5. Print Bank Statement"<< endl;
        cout << "6. Transfer Funds"<< endl;
        cout << "7. Exit"<< endl;
        cout << "Select Option: "<< endl;
        cin >> choice;

        switch (choice) {
         case 1: createAccount(); break;
          case 2: deposit(); break;
            case 3: withdraw(); break;
              case 4: checkBalance(); break;
               case 5: displayStatement(); break;
                 case 6: transfer(); break;
                   case 7: cout << "come back again soon"; break;
                     default: cout << "option dosen't match";
        }
    } while (choice != 7);

    return 0;
}

void saveToFile() {
    ofstream outFile("bnu_bank.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < totalAccounts; i++) {
            outFile << accountNumbers[i] << endl;
            outFile << accountNames[i] << endl;
            outFile << balances[i] << endl;
        }
        outFile.close();
    }
}

void loadFromFile() {
    ifstream inFile("bnu_bank.txt");
    if (inFile.is_open()) {
        totalAccounts = 0;
        while (totalAccounts < MAX_ACCOUNTS && inFile >> accountNumbers[totalAccounts]) {
            inFile.ignore();
            getline(inFile, accountNames[totalAccounts]);
            inFile >> balances[totalAccounts];
            totalAccounts++;
        }
        inFile.close();
    }
}

int findAccount(int accNum) {
    for (int i = 0; i < totalAccounts; i++) {
        if (accountNumbers[i] == accNum) {
            return i;
        }
    }
    return -1;
}

void createAccount() {
    if (totalAccounts >= MAX_ACCOUNTS) {
        cout << "\n[Error] accounts are full ";
        return;
    }

    int tempAccNum;
    bool alreadyExists;

    do {
        alreadyExists = false;
        cout << "Enter New Account Number: ";
        cin >> tempAccNum;
        if (findAccount(tempAccNum) != -1) {
            cout << "[Error] Account Number already exists!";
            alreadyExists = true;
        }
    } while (alreadyExists);

    accountNumbers[totalAccounts] = tempAccNum;
    cout << "Enter Account Holder Name: ";
    cin.ignore();
    getline(cin, accountNames[totalAccounts]);
    cout << "Enter Initial Balance: $";
    cin >> balances[totalAccounts];

    totalAccounts++;
    saveToFile();
    cout << "Account is created";
}

void deposit() {
    int accNum;
    double amount;
    cout << "Enter Account Number: ";
    cin >> accNum;
    int index = findAccount(accNum);

    if (index != -1) {
        cout << "Enter Amount: $";
        cin >> amount;
        balances[index] += amount;
        saveToFile();
        cout << "Deposit successful. New Balance: $" << fixed << setprecision(2) << balances[index] << endl;
    } else {
        cout << "Account not found!\n";
    }
}

void withdraw() {
    int accNum;
    double amount;
    cout << "Enter Account Number: ";
    cin >> accNum;
    int index = findAccount(accNum);

    if (index != -1) {
        cout << "Enter Amount: $";
        cin >> amount;
        if (amount <= balances[index]) {
            balances[index] -= amount;
            saveToFile();
            cout << "Withdrawal successful. Remaining Balance: $" << fixed << setprecision(2) << balances[index] << endl;
        } else {
            cout << "Insufficient funds!\n";
        }
    } else {
        cout << "Account not found!\n";
    }
}

void checkBalance() {
    int accNum;
    cout << "Enter Account Number: ";
    cin >> accNum;
    int index = findAccount(accNum);

    if (index != -1) {
        cout << "Account Holder: " << accountNames[index] << endl;
        cout << "Current Balance: $" << fixed << setprecision(2) << balances[index] << endl;
    } else {
        cout << "Account not found!\n";
    }
}

void displayStatement() {
    int accNum;
    cout << "Enter Account Number: ";
    cin >> accNum;
    int index = findAccount(accNum);

    if (index != -1) {
        cout << "- FINAL BANK STATEMENT -";
        cout << "Account Number: " << accountNumbers[index];
        cout << "Account Holder: " << accountNames[index];
        cout << "Total Balance:  $" << fixed << setprecision(2) << balances[index];
       
    } else {
        cout << "Account not present";
    }
}

void transfer() {
    int senderAcc, receiverAcc;
    double amount;

    cout << "Enter Your Account Number: ";
    cin >> senderAcc;
    int senderIdx = findAccount(senderAcc);

    if (senderIdx == -1) {
        cout << "Sender account not found!\n";
        return;
    }

    cout << "Enter Receiver Account Number: ";
    cin >> receiverAcc;
    int receiverIdx = findAccount(receiverAcc);

    if (receiverIdx == -1) {
        cout << "Receiver account not found";
        return;
    }

    cout << "Enter Amount to Transfer: $";
    cin >> amount;

    if (amount > 0 && amount <= balances[senderIdx]) {
        balances[senderIdx] -= amount;
        balances[receiverIdx] += amount;
        saveToFile();
        cout << "Transfer done";
    } else {
        cout << "Transaction failed.";
    }
}
