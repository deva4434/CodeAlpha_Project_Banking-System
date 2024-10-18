#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Transaction Class
class Transaction {
public:
    string type;
    double amount;

    Transaction(string type, double amount) {
        this->type = type;
        this->amount = amount;
    }

    void displayTransaction() const {
        cout << type << ": " << amount << endl;
    }
};

// Account Class
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accountNumber, double initialDeposit) {
        this->accountNumber = accountNumber;
        this->balance = initialDeposit;
        transactions.push_back(Transaction("Initial Deposit", initialDeposit));
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));
        cout << "Deposit successful! New Balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance." << endl;
        } else {
            balance -= amount;
            transactions.push_back(Transaction("Withdrawal", amount));
            cout << "Withdrawal successful! New Balance: " << balance << endl;
        }
    }

    void transfer(double amount, Account &recipient) {
        if (amount > balance) {
            cout << "Insufficient balance for transfer." << endl;
        } else {
            balance -= amount;
            recipient.deposit(amount);
            transactions.push_back(Transaction("Transfer to Account " + to_string(recipient.getAccountNumber()), amount));
            cout << "Transfer successful! New Balance: " << balance << endl;
        }
    }

    void viewAccountInfo() const { // Marking this as a const member function
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << endl;
        cout << "Recent Transactions: " << endl;
        for (const auto &transaction : transactions) {
            transaction.displayTransaction();
        }
    }
};

// Customer Class
class Customer {
private:
    string name;
    vector<Account> accounts;

public:
    Customer(string name) {
        this->name = name;
    }

    string getName() const {
        return name;
    }

    void createAccount(int accountNumber, double initialDeposit) {
        accounts.push_back(Account(accountNumber, initialDeposit));
        cout << "Account created successfully for " << name << " with Account Number: " << accountNumber << endl;
    }

    Account* getAccount(int accountNumber) {
        for (auto &account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                return &account;
            }
        }
        return nullptr;
    }

    void viewAccounts() const {
        cout << "Customer: " << name << endl;
        for (const auto &account : accounts) {
            account.viewAccountInfo(); // Now it's fine to call on const reference
        }
    }
};

// Banking Services Class
class BankingServices {
private:
    vector<Customer> customers;

public:
    void addCustomer(string name) {
        customers.push_back(Customer(name));
        cout << "Customer " << name << " added successfully!" << endl;
    }

    Customer* getCustomer(string name) {
        for (auto &customer : customers) {
            if (customer.getName() == name) {
                return &customer;
            }
        }
        return nullptr;
    }
};

int main() {
    BankingServices bank;
    int choice;

    while (true) {
        cout << "\n1. Add Customer\n";
        cout << "2. Create Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Transfer\n";
        cout << "6. View Account Information\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string name;
        int accountNumber;
        double amount;
        Customer *customer;

        switch (choice) {
            case 1:
                cout << "Enter customer name: ";
                cin >> name;
                bank.addCustomer(name);
                break;

            case 2:
                cout << "Enter customer name: ";
                cin >> name;
                customer = bank.getCustomer(name);
                if (customer) {
                    cout << "Enter account number: ";
                    cin >> accountNumber;
                    cout << "Enter initial deposit: ";
                    cin >> amount;
                    customer->createAccount(accountNumber, amount);
                } else {
                    cout << "Customer not found!" << endl;
                }
                break;

            case 3:
                cout << "Enter customer name: ";
                cin >> name;
                customer = bank.getCustomer(name);
                if (customer) {
                    cout << "Enter account number: ";
                    cin >> accountNumber;
                    Account* account = customer->getAccount(accountNumber);
                    if (account) {
                        cout << "Enter deposit amount: ";
                        cin >> amount;
                        account->deposit(amount);
                    } else {
                        cout << "Account not found!" << endl;
                    }
                } else {
                    cout << "Customer not found!" << endl;
                }
                break;

            case 4:
                cout << "Enter customer name: ";
                cin >> name;
                customer = bank.getCustomer(name);
                if (customer) {
                    cout << "Enter account number: ";
                    cin >> accountNumber;
                    Account* account = customer->getAccount(accountNumber);
                    if (account) {
                        cout << "Enter withdrawal amount: ";
                        cin >> amount;
                        account->withdraw(amount);
                    } else {
                        cout << "Account not found!" << endl;
                    }
                } else {
                    cout << "Customer not found!" << endl;
                }
                break;

            case 5:
                cout << "Enter customer name: ";
                cin >> name;
                customer = bank.getCustomer(name);
                if (customer) {
                    int toAccount;
                    cout << "Enter from account number: ";
                    cin >> accountNumber;
                    cout << "Enter to account number: ";
                    cin >> toAccount;
                    cout << "Enter transfer amount: ";
                    cin >> amount;
                    Account* from = customer->getAccount(accountNumber);
                    Account* to = customer->getAccount(toAccount);
                    if (from && to) {
                        from->transfer(amount, *to);
                    } else {
                        cout << "One or both accounts not found!" << endl;
                    }
                } else {
                    cout << "Customer not found!" << endl;
                }
                break;

            case 6:
                cout << "Enter customer name: ";
                cin >> name;
                customer = bank.getCustomer(name);
                if (customer) {
                    customer->viewAccounts();
                } else {
                    cout << "Customer not found!" << endl;
                }
                break;

            case 7:
                cout << "Exiting..." << endl;
                return 0;

            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}
