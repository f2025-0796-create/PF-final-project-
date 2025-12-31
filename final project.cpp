#include <iostream>
#include <string>
#include <iomanip>

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
int findAccount(int accNum);

int main() {
    int choice;

    do {
        cout << "\n--- BANKING & ATM MANAGEMENT SYSTEM ---";
        cout << "\n1. Create New Account";
        cout << "\n2. Deposit Money (ATM)";
        cout << "\n3. Withdraw Money (ATM)";
        cout << "\n4. Check Balance";
        cout << "\n5. Print Bank Statement";
        cout << "\n6. Exit";
        cout << "\nSelect Option: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: displayStatement(); break;
            case 6: cout << "Thank you for using our service!"; break;
            default: cout << "Invalid choice!";
        }
    } while (choice != 6);

    return 0;
}

int findAccount(int accNum) {
    for (int i = 0; i < totalAccounts; i++) {
        if (accountNumbers[i] == accNum) {
            return i;
        }
    }
    return -1; // Not found
}

void createAccount() {
    if (totalAccounts >= MAX_ACCOUNTS) {
        cout << "\n[Error] Bank database full!\n";
        return;
    }

    int tempAccNum;
    bool alreadyExists;

    
    do {
        alreadyExists = false;
        cout << "\nEnter New Account Number: ";
        cin >> tempAccNum;

        if (findAccount(tempAccNum) != -1) {
            cout << "[Error] Account Number " << tempAccNum << " already exists! Please enter a unique ID.\n";
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
    cout << "\nAccount Successfully Created!\n";
}
void deposit() {
    int accNum;
    double amount;
    cout << "Enter Account Number: ";
    cin >> accNum;
    int index = findAccount(accNum);

    if (index != -1) {
        cout << "Enter Amount to Deposit: $";
        cin >> amount;
        balances[index] += amount;
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
        cout << "Enter Amount to Withdraw: $";
        cin >> amount;
        if (amount <= balances[index]) {
            balances[index] -= amount;
            cout << "Withdrawal successful. Remaining Balance: $" << balances[index] << endl;
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
        cout << "Current Balance: $" << balances[index] << endl;
    } else {
        cout << "Account not found!\n";
    }
}

void displayStatement() {
    int accNum;
    cout << "Enter Account Number for Statement: ";
    cin >> accNum;
    int index = findAccount(accNum);

    if (index != -1) {
        cout << "\n------- FINAL BANK STATEMENT -------";
        cout << "\nAccount Number: " << accountNumbers[index];
        cout << "\nAccount Holder: " << accountNames[index];
        cout << "\nTotal Balance:  $" << balances[index];
        cout << "\n------------------------------------\n";
    } else {
        cout << "Account not found!\n";
    }
}
