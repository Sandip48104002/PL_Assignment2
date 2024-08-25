#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>

using namespace std;

// Base class for Account
class Account {
protected:
    string accountNumber;
    double balance;

public:
    Account(const string& accountNumber, double balance)
        : accountNumber(accountNumber), balance(balance) {}

    string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    virtual string getAccountType() const = 0; // Pure virtual function

    virtual void deposit(double amount) {
        if (amount <= 0) throw runtime_error("Deposit amount must be positive.");
        balance += amount;
    }

    virtual void withdraw(double amount) {
        if (amount <= 0) throw runtime_error("Withdraw amount must be positive.");
        if (amount > balance) throw runtime_error("Insufficient funds.");
        balance -= amount;
    }
};

// Derived classes for different types of accounts
class SavingsAccount : public Account {
public:
    SavingsAccount(const string& accountNumber, double balance)
        : Account(accountNumber, balance) {}

    string getAccountType() const override {
        return "Savings Account";
    }
};

class CurrentAccount : public Account {
public:
    CurrentAccount(const string& accountNumber, double balance)
        : Account(accountNumber, balance) {}

    string getAccountType() const override {
        return "Current Account";
    }
};

// Customer class
class Customer {
    string id;
    string name;

public:
    Customer(const string& id, const string& name) : id(id), name(name) {}

    string getId() const { return id; }
    string getName() const { return name; }
};

// Bank class
class Bank {
    vector<Account*> accounts;

    void saveBankData() {
        ofstream file("bank_data.txt");
        for (auto account : accounts) {
            file << account->getAccountNumber() << " " << account->getBalance() << " " << account->getAccountType() << endl;
        }
        file.close();
    }

public:
    void createAccount(Account* account) {
        accounts.push_back(account);
        saveBankData();
    }

    Account* findAccount(const string& accountNumber) {
        for (auto account : accounts) {
            if (account->getAccountNumber() == accountNumber) {
                return account;
            }
        }
        throw runtime_error("Account not found.");
    }

    void deposit(const string& accountNumber, double amount) {
        Account* account = findAccount(accountNumber);
        account->deposit(amount);
        saveBankData();
    }

    void withdraw(const string& accountNumber, double amount) {
        Account* account = findAccount(accountNumber);
        account->withdraw(amount);
        saveBankData();
    }

    void transfer(const string& fromAccountNumber, const string& toAccountNumber, double amount) {
        Account* fromAccount = findAccount(fromAccountNumber);
        Account* toAccount = findAccount(toAccountNumber);
        fromAccount->withdraw(amount);
        toAccount->deposit(amount);
        saveBankData();
    }
};

// Main Function
int main() {
    Bank bank;
    int choice;
    string accountNumber, customerId, customerName, fromAccountNumber, toAccountNumber;
    double amount, initialBalance;

    do {
        cout << "\nBanking System";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit";
        cout << "\n3. Withdraw";
        cout << "\n4. Transfer";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\nEnter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Initial Balance: ";
                cin >> initialBalance;
                cout << "Select Account Type (1 for Savings, 2 for Current): ";
                int accountType;
                cin >> accountType;

                try {
                    if (accountType == 1) {
                        bank.createAccount(new SavingsAccount(accountNumber, initialBalance));
                        cout << "Savings Account created successfully." << endl;
                    } else if (accountType == 2) {
                        bank.createAccount(new CurrentAccount(accountNumber, initialBalance));
                        cout << "Current Account created successfully." << endl;
                    } else {
                        cout << "Invalid account type selected." << endl;
                    }
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case 2: {
                cout << "\nEnter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Amount to Deposit: ";
                cin >> amount;

                try {
                    bank.deposit(accountNumber, amount);
                    cout << "Amount deposited successfully." << endl;
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case 3: {
                cout << "\nEnter Account Number: ";
                cin >> accountNumber;
                cout << "Enter Amount to Withdraw: ";
                cin >> amount;

                try {
                    bank.withdraw(accountNumber, amount);
                    cout << "Amount withdrawn successfully." << endl;
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case 4: {
                cout << "\nEnter From Account Number: ";
                cin >> fromAccountNumber;
                cout << "Enter To Account Number: ";
                cin >> toAccountNumber;
                cout << "Enter Amount to Transfer: ";
                cin >> amount;

                try {
                    bank.transfer(fromAccountNumber, toAccountNumber, amount);
                    cout << "Amount transferred successfully." << endl;
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case 5: {
                cout << "Exiting the system..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice! Please choose again." << endl;
                break;
            }
        }
    } while (choice != 5);

    return 0;
}

