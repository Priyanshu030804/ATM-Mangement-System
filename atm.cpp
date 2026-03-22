#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Account {
private:
    int accountNumber;
    string name;
    int pin;
    double balance;

public:
    Account() {}

    Account(int accNo, string n, int p, double b) {
        accountNumber = accNo;
        name = n;
        pin = p;
        balance = b;
    }

    int getAccountNumber() { return accountNumber; }
    int getPin() { return pin; }
    double getBalance() { return balance; }
    string getName() { return name; }

    void deposit(double amount) {
        balance += amount;
        cout << "Amount Deposited Successfully!\n";
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient Balance!\n";
            return false;
        }
        balance -= amount;
        cout << "Please Collect Your Cash.\n";
        return true;
    }

    void display() {
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nName: " << name;
        cout << "\nBalance: " << balance << endl;
    }

    void saveToFile(ofstream &out) {
        out << accountNumber << " "
            << name << " "
            << pin << " "
            << balance << endl;
    }

    void loadFromFile(ifstream &in) {
        in >> accountNumber >> name >> pin >> balance;
    }
};

vector<Account> accounts;

void loadAccounts() {
    ifstream file("accounts.txt");
    while (!file.eof()) {
        Account acc;
        acc.loadFromFile(file);
        if (file)
            accounts.push_back(acc);
    }
    file.close();
}

void saveAccounts() {
    ofstream file("accounts.txt");
    for (auto &acc : accounts) {
        acc.saveToFile(file);
    }
    file.close();
}

int findAccount(int accNo) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].getAccountNumber() == accNo)
            return i;
    }
    return -1;
}

void createAccount() {
    int accNo, pin;
    string name;
    double balance;

    cout << "Enter Account Number: ";
    cin >> accNo;

    if (findAccount(accNo) != -1) {
        cout << "Account already exists!\n";
        return;
    }

    cout << "Enter Name: ";
    cin >> name;
    cout << "Set PIN: ";
    cin >> pin;
    cout << "Enter Initial Balance: ";
    cin >> balance;

    Account newAcc(accNo, name, pin, balance);
    accounts.push_back(newAcc);
    saveAccounts();

    cout << "Account Created Successfully!\n";
}

void login() {
    int accNo, enteredPin;
    cout << "Enter Account Number: ";
    cin >> accNo;

    int index = findAccount(accNo);
    if (index == -1) {
        cout << "Account not found!\n";
        return;
    }

    cout << "Enter PIN: ";
    cin >> enteredPin;

    if (accounts[index].getPin() != enteredPin) {
        cout << "Incorrect PIN!\n";
        return;
    }

    int choice;
    do {
        cout << "\n1. Check Balance\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            accounts[index].display();
            break;

        case 2: {
            double amount;
            cout << "Enter Amount: ";
            cin >> amount;
            accounts[index].deposit(amount);
            saveAccounts();
            break;
        }

        case 3: {
            double amount;
            cout << "Enter Amount: ";
            cin >> amount;
            if (accounts[index].withdraw(amount))
                saveAccounts();
            break;
        }

        case 4:
            cout << "Thank You!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }
    } while (choice != 4);
}

void adminPanel() {
    cout << "\n---- Admin Panel ----\n";
    for (auto &acc : accounts) {
        acc.display();
        cout << "------------------\n";
    }
}

int main() {
    loadAccounts();
    int choice;

    do {
        cout << "\n===== ATM Banking System =====\n";
        cout << "1. Create Account\n";
        cout << "2. Login\n";
        cout << "3. Admin Panel\n";
        cout << "4. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createAccount();
            break;
        case 2:
            login();
            break;
        case 3:
            adminPanel();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 4);

    return 0;
}