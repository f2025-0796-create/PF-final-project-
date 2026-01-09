#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

struct Account {
    int id;
    string holder;
    double balance;
};

vector<Account> bank;
const string DATA_FILE = "bnu_bank.txt";

void save() {
    ofstream out(DATA_FILE);
    for (const auto& acc : bank) {
        out << acc.id << endl << acc.holder << endl << acc.balance << endl;
    }
}

void load() {
    ifstream in(DATA_FILE);
    Account temp;
    while (in >> temp.id) {
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(in, temp.holder);
        in >> temp.balance;
        bank.push_back(temp);
    }
}

int findIdx(int id) {
    for (int i = 0; i < bank.size(); i++) {
        if (bank[i].id == id) return i;
    }
    return -1;
}

void createAccount() {
    int id;
    cout << "Assign Account Number: ";
    cin >> id;

    if (findIdx(id) != -1) {
        cout << "That ID is already taken." << endl;
        return;
    }

    Account newAcc;
    newAcc.id = id;
    cout << "Name: ";
    cin.ignore();
    getline(cin, newAcc.holder);
    cout << "Initial Deposit: $";
    cin >> newAcc.balance;

    bank.push_back(newAcc);
    save();
    cout << "Account created successfully!" << endl;
}

void deposit() {
    int id;
    double amt;
    cout << "Account Number: ";
    cin >> id;
    int idx = findIdx(id);

    if (idx != -1) {
        cout << "Amount to Deposit: $";
        cin >> amt;
        bank[idx].balance += amt;
        save();
        cout << "Done. New Balance: $" << bank[idx].balance << endl;
    } else {
        cout << "Account not found." << endl;
    }
}

void withdraw() {
    int id;
    double amt;
    cout << "Account Number: ";
    cin >> id;
    int idx = findIdx(id);

    if (idx != -1) {
        cout << "Amount to Withdraw: $";
        cin >> amt;
        if (amt <= bank[idx].balance) {
            bank[idx].balance -= amt;
            save();
            cout << "Withdrawal complete." << endl;
        } else {
            cout << "Insufficient funds." << endl;
        }
    } else {
        cout << "Account not found." << endl;
    }
}

void checkBalance() {
    int id;
    cout << "Account Number: ";
    cin >> id;
    int idx = findIdx(id);

    if (idx != -1) {
        cout << "Holder: " << bank[idx].holder << endl;
        cout << "Balance: $" << fixed << setprecision(2) << bank[idx].balance << endl;
    } else {
        cout << "Account not found." << endl;
    }
}

void transfer() {
    int fromId, toId;
    double amt;
    cout << "Your Account Number: ";
    cin >> fromId;
    int fromIdx = findIdx(fromId);

    if (fromIdx == -1) {
        cout << "Sender not found." << endl;
        return;
    }

    cout << "Receiver Account Number: ";
    cin >> toId;
    int toIdx = findIdx(toId);

    if (toIdx == -1) {
        cout << "Receiver not found." << endl;
        return;
    }

    cout << "Amount to Transfer: $";
    cin >> amt;

    if (amt > 0 && amt <= bank[fromIdx].balance) {
        bank[fromIdx].balance -= amt;
        bank[toIdx].balance += amt;
        save();
        cout << "Transfer successful." << endl;
    } else {
        cout << "Invalid." << endl;
    }
}

int main() {
    load();
    int choice;

    while (true) {
        cout << " BANKING SYSTEM" << endl;
        cout << "1. New Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Balance" << endl;
        cout << "5. Transfer" << endl;
        cout << "6. Exit" << endl;
        cout << "Select: ";
        cin >> choice;

        if (choice == 1) 
        createAccount();
         else if (choice == 2) 
         deposit();
           else if (choice == 3)
           withdraw();
              else if (choice == 4) 
              checkBalance();
                 else if (choice == 5) 
                 transfer();
                     else if (choice == 6) {
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice." << endl;
        }
    }
    return 0;
}
