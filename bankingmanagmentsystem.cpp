#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Account {
    string accountNumber;
    string name;
    string password;
    double balance;
    Account* next;
};

class BankManagementSystem {
private:
    Account* head;
    string dataFile;

public:
    BankManagementSystem() : head(NULL), dataFile("accounts.txt") {}

    void addAccount() {
        Account* newAccount = new Account;
        cout << "Enter Account Number: ";
        cin >> newAccount->accountNumber;
        if (isAccountNumberUnique(newAccount->accountNumber)) {
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, newAccount->name);
            cout << "Enter Password: ";
            cin >> newAccount->password;
            cout << "Enter Initial Balance: ";
            cin >> newAccount->balance;
            newAccount->next = NULL;
            if (head == NULL) {
                head = newAccount;
            } else {
                Account* current = head;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newAccount;
            }
            cout << "\nAccount Added Successfully!" << endl;
            saveAccountsToFile();
        } else {
            cout << "\t\tAccount Number is not unique. Please enter a unique account number." << endl;
            delete newAccount;
        }
    }

    bool isAccountNumberUnique(const string& accountNumber) {
        Account* current = head;
        while (current != NULL) {
            if (current->accountNumber == accountNumber) {
                return false;
            }
            current = current->next;
        }
        return true;
    }

    Account* findAccount(const string& accountNumber, const string& password) {
        Account* current = head;
        while (current != NULL) {
            if (current->accountNumber == accountNumber && current->password == password) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }
 void deleteAccount() {
        string accountNumber;
        cout << "Enter Account Number to Delete: ";
        cin >> accountNumber;

        Account* current = head;
        Account* prev = NULL;

        while (current != NULL) {
            if (current->accountNumber == accountNumber) {
                if (prev == NULL) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                cout << "Account Deleted Successfully!" << endl;
                saveAccountsToFile();
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "Account Not Found!" << endl;
    }
    void searchAccount() {
        string accountNumber;
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        string password;
        cout << "Enter the Password: ";
        cin >> password;

        Account* account = findAccount(accountNumber, password);
        if (account != NULL) {
            cout << "\tAccount Number: " << account->accountNumber << endl;
            cout << "Name: " << account->name << endl;
            cout << "Balance: " << account->balance << endl;
        } else {
            cout << "\nAccount Not Found or Invalid Password" << endl;
        }
    }

    void depositFunds() {
        string accountNumber;
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        string password;
        cout << "Enter Password: ";
        cin >> password;

        Account* account = findAccount(accountNumber, password);
        if (account != NULL) {
            double amount;
            cout << "Enter Deposit Amount: ";
            cin >> amount;

            account->balance += amount;
            cout << "\tDeposit Successful" << endl;
            saveAccountsToFile();
        } else {
            cout << "\tAccount Not Found or Invalid Password" << endl;
        }
    }

    void withdrawFunds() {
        string accountNumber;
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        string password;
        cout << "Enter Password: ";
        cin >> password;

        Account* account = findAccount(accountNumber, password);
        if (account != NULL) {
            double amount;
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;

            if (account->balance >= amount) {
                account->balance -= amount;
                cout << "\tWithdrawal Successful" << endl;
                saveAccountsToFile();
            } else {
                cout << "\tInsufficient Funds" << endl;
            }
        } else {
            cout << "\tAccount Not Found or Invalid Password" << endl;
        }
    }

    void displayAccounts() {
        cout << "\t====== All Accounts =======" << endl;
        Account* current = head;
        while (current != NULL) {
            cout << "\tAccount Number: " << current->accountNumber << endl;
            cout << "Name: " << current->name << endl;
            cout << "Balance: " << current->balance << endl;
            current = current->next;
        }
        cout << endl;
    }

    void saveAccountsToFile() {
        ofstream outputFile(dataFile.c_str());

        if (outputFile.is_open()) {
            Account* current = head;
            while (current != NULL) {
                outputFile << current->accountNumber << "," << current->name << "," << current->password << "," << current->balance << endl;
                current = current->next;
            }
            outputFile.close();
            cout << "\tAccounts saved to file: " << dataFile << endl;
        } else {
            cout << "\nError: Unable to open file for writing." << endl;
        }
    }

    void loadAccountsFromFile() {
        ifstream inputFile(dataFile.c_str());

        if (inputFile.is_open()) {
            string line;
            while (getline(inputFile, line)) {
                stringstream ss(line);
                string accountNumber, name, password;
                double balance;

                getline(ss, accountNumber, ',');
                getline(ss, name, ',');
                getline(ss, password, ',');
                ss >> balance;

                Account* newAccount = new Account;
                newAccount->accountNumber = accountNumber;
                newAccount->name = name;
                newAccount->password = password;
                newAccount->balance = balance;
                newAccount->next = NULL;

                if (head == NULL) {
                    head = newAccount;
                } else {
                    Account* current = head;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = newAccount;
                }
            }
            inputFile.close();
            cout << "\tAccounts loaded from file: " << dataFile << endl;
        } else {
            cout << "\tError: Unable to open file for reading." << endl;
        }
    }

    // New ATM Function
    void atm() {
        string accountNumber, password;
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Password: ";
        cin >> password;

        Account* account = findAccount(accountNumber, password);
        if (account != NULL) {
            int choice;
            while (true) {
                cout << "\n\t==== ATM Menu ====" << endl;
                cout << "1. Check Balance" << endl;
                cout << "2. Deposit Funds" << endl;
                cout << "3. Withdraw Funds" << endl;
                cout << "4. Exit ATM" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                if (choice == 1) {
                    cout << "\tYour Balance: " << account->balance << endl;
                } else if (choice == 2) {
                    double amount;
                    cout << "Enter Deposit Amount: ";
                    cin >> amount;
                    account->balance += amount;
                    cout << "\tDeposit Successful!" << endl;
                } else if (choice == 3) {
                    double amount;
                    cout << "Enter Withdrawal Amount: ";
                    cin >> amount;
                    if (account->balance >= amount) {
                        account->balance -= amount;
                        cout << "\tWithdrawal Successful!" << endl;
                    } else {
                        cout << "\tInsufficient Funds!" << endl;
                    }
                } else if (choice == 4) {
                    cout << "Exiting ATM. Thank you!" << endl;
                    break;
                } else {
                    cout << "Invalid Choice!" << endl;
                }
            }
            saveAccountsToFile();
        } else {
            cout << "\tAccount Not Found or Invalid Password" << endl;
        }
    }
    
     void loan() {
        string accountNumber, password;
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Password: ";
        cin >> password;

        Account* account = findAccount(accountNumber, password);
        if (account != NULL) {
            int loanType;
            double loanAmount;
            cout << "\n\t==== Loan Options ====" << endl;
            cout << "1. Student Loan (Max $10,000)" << endl;
            cout << "2. House Loan (Max $100,000)" << endl;
            cout << "3. Car Loan (Max $50,000)" << endl;
            cout << "Enter Loan Type: ";
            cin >> loanType;

            if (loanType == 1) {
                cout << "Enter Loan Amount (Max $10,000): ";
                cin >> loanAmount;
                if (loanAmount > 10000) {
                    cout << "Loan amount exceeds the maximum limit for Student Loan!" << endl;
                    return;
                }
            } else if (loanType == 2) {
                cout << "Enter Loan Amount (Max $100,000): ";
                cin >> loanAmount;
                if (loanAmount > 100000) {
                    cout << "Loan amount exceeds the maximum limit for House Loan!" << endl;
                    return;
                }
            } else if (loanType == 3) {
                cout << "Enter Loan Amount (Max $50,000): ";
                cin >> loanAmount;
                if (loanAmount > 50000) {
                    cout << "Loan amount exceeds the maximum limit for Car Loan!" << endl;
                    return;
                }
            } else {
                cout << "Invalid Loan Type!" << endl;
                return;
            }

            // Loan Approved
            account->balance += loanAmount;
            cout << "\nLoan Approved! $" << loanAmount << " has been credited to your account." << endl;
            saveAccountsToFile();
        } else {
            cout << "\tAccount Not Found or Invalid Password" << endl;
        }
    }
void billPayment() {
        string accountNumber, password;
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Password: ";
        cin >> password;

        Account* account = findAccount(accountNumber, password);
        if (account != NULL) {
            int billType;
            double amount;
            cout << "\n\t==== Bill Payment Options ====" << endl;
            cout << "1. Utility Bill" << endl;
            cout << "2. Internet Bill" << endl;
            cout << "3. Loan Payment" << endl;
            cout << "Enter Bill Type: ";
            cin >> billType;

            cout << "Enter Payment Amount: ";
            cin >> amount;

            if (account->balance >= amount) {
                account->balance -= amount;
                cout << "\nPayment Successful! $" << amount << " has been deducted from your account." << endl;
                saveAccountsToFile();
            } else {
                cout << "\nInsufficient Balance for this payment!" << endl;
            }
        } else {
            cout << "\tAccount Not Found or Invalid Password" << endl;
        }
    }
 void adminMenu() {
        int choice;
        while (true) {
            cout << "\n\t==== Admin Menu ====" << endl;
            cout << "1. Delete Account" << endl;
            cout << "2. Show All Account Balances" << endl;
            cout << "3. Exit to Main Menu" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                deleteAccount();
                break;
            case 2:
                displayAccounts();
                break;
            case 3:
                return;
            default:
                cout << "Invalid Choice!" << endl;
            }
        }
    }

    void menu() {
        loadAccountsFromFile();
        int choice;
        while (true) {
            cout << "\n\t==== Bank Management System ====" << endl;
            cout << "1. Add Account" << endl;
            cout << "2. Search Account" << endl;
            cout << "3. Deposit Funds" << endl;
            cout << "4. Withdraw Funds" << endl;
            cout << "5. Display All Accounts" << endl;
            cout << "6. ATM" << endl;
            cout << "7. LOAN" << endl;
			cout << "8. BILL PAYMENT" << endl;
            cout << "9. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                addAccount();
                break;
            case 2:
                searchAccount();
                break;
            case 3:
                depositFunds();
                break;
            case 4:
                withdrawFunds();
                break;
            case 5:
                displayAccounts();
                break;
            case 6:
                atm();
                break;
            case 7:
            	loan();
            	break;
            case 8:
                billPayment();
                break;
            case 9:
            	return;
            default:
                cout << "Invalid Choice!" << endl;
            }
        }
    }
    void initialMenu() {
        loadAccountsFromFile();
        while (true) {
            int choice;
            cout << "\n\t==== Welcome to the Bank Management System ====" << endl;
            cout << "1. Admin" << endl;
            cout << "2. User" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                adminMenu();
                break;
            case 2:
                menu();
                break;
            case 3:
                cout << "Exiting. Thank you!" << endl;
                return;
            default:
                cout << "Invalid Choice!" << endl;
            }
        }
    }
};

int main() {
    BankManagementSystem bankingSystem;
    bankingSystem.initialMenu();
    return 0;
}
