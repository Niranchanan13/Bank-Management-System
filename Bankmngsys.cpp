#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>   
#include <ctime>    
using namespace std;

class Bank {
private:
    long int accno, mobno;
    char name[30], accounttype[10];
    int balance;

public:
    Bank() { balance = 0; accno = 0; }

    void openAccount(set<long int>& existingAccNos) {
        cout << "\n\t********** OPEN NEW ACCOUNT ************\n";
        cout << "Enter the Name(as per the proof): ";
        cin >> name;
        cout << "Enter the type of account: ";
        cin >> accounttype;
        cout << "Enter the Mobile No: ";
        cin >> mobno;
        cout << "Enter the initial deposit amount: ";
        cin >> balance;

        
        do {
            accno = 100000 + rand() % 900000;
        } while (existingAccNos.count(accno) > 0);

        existingAccNos.insert(accno);
        cout << "\n\tAccount Opened Successfully!";
        cout << "\n\tCustomer Account Number is: " << accno << endl;
    }

    void print() {
        cout << "\n\t********** ACCOUNT DETAILS ************\n";
        cout << "\tNAME: " << name;
        cout << "\n\tACCOUNT NO: " << accno;
        cout << "\n\tACCOUNT TYPE: " << accounttype;
        cout << "\n\tMOBILE NO: " << mobno;
        cout << "\n\tACCOUNT BALANCE: " << balance << endl;
    }

    void depositWithdraw() {
        char option;
        cout << "\n\t********** TRANSACTION ************";
        cout << "\n\tD - Deposit";
        cout << "\n\tW - Withdraw";
        cout << "\n\tEnter your choice: ";
        cin >> option;

        if (option == 'D' || option == 'd') {
            int amount;
            cout << "\n\tEnter the deposit amount: ";
            cin >> amount;
            balance += amount;
            cout << "\n\tAmount Deposited Successfully!";
            cout << "\n\tBALANCE = " << balance;
        } 
        else if (option == 'W' || option == 'w') {
            int amount;
            cout << "\n\tEnter the withdrawal amount: ";
            cin >> amount;
            if (amount > balance) {
                cout << "\n\tInsufficient Balance!";
            } else {
                balance -= amount;
                cout << "\n\tAmount Withdrawn Successfully!";
                cout << "\n\tBALANCE = " << balance;
            }
        } 
        else {
            cout << "\n\tInvalid choice!";
        }
    }

    long int getAccNo() { return accno; }
    int getBalance() { return balance; }
    void addBalance(int amount) { balance += amount; }
    bool deductBalance(int amount) {
        if (amount > balance) return false;
        balance -= amount;
        return true;
    }
    void printSummary() { 
        cout << "\n\tAccNo: " << accno << " | Name: " << name << " | Balance: " << balance;
    }
};

int main() {
    srand(time(0));  

    vector<Bank> accounts;
    set<long int> existingAccNos;
    int choice;

    while (true) {
        cout << "\n\n\t********** BANK MENU ************";
        cout << "\n\t1. Open Account";
        cout << "\n\t2. Print Account Details";
        cout << "\n\t3. Deposit/Withdraw";
        cout << "\n\t4. Transfer Money";
        cout << "\n\t5. Show All Accounts";
        cout << "\n\t6. Exit";
        cout << "\n\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Bank b;
                b.openAccount(existingAccNos);
                accounts.push_back(b);
                break;
            }

            case 2: {
                long int accno;
                cout << "\n\tEnter Account Number to view details: ";
                cin >> accno;
                bool found = false;
                for (size_t i = 0; i < accounts.size(); i++) {
                    if (accounts[i].getAccNo() == accno) {
                        accounts[i].print();
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "\n\tAccount not found!";
                break;
            }

            case 3: {
                long int accno;
                cout << "\n\tEnter Account Number to Deposit/Withdraw the money: ";
                cin >> accno;
                bool found = false;
                for (size_t i = 0; i < accounts.size(); i++) {
                    if (accounts[i].getAccNo() == accno) {
                        accounts[i].depositWithdraw();
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "\n\tAccount not found!";
                break;
            }

            case 4: {
                long int fromAcc, toAcc;
                int amount;
                cout << "\n\tEnter sender Account Number: ";
                cin >> fromAcc;
                cout << "\n\tEnter the Recipient Account Number: ";
                cin >> toAcc;   
                cout << "\n\tEnter the amount to transfer: ";
                cin >> amount;

                Bank* sender = NULL;
                for (size_t i = 0; i < accounts.size(); i++) {
                    if (accounts[i].getAccNo() == fromAcc) {
                        sender = &accounts[i];
                        break;
                    }
                }

                if (sender != NULL) {
                    if (sender->deductBalance(amount)) {
                        cout << "\n\tTransferred " << amount << " to account number: " << toAcc;
                        cout << "\n\tNew Balance: " << sender->getBalance();
                    } else {
                        cout << "\n\tInsufficient Balance!";
                    }
                } else {
                    cout << "\n\tSender account not found.Open the account in the branch!";
                }
                break;
            }

            case 5: {
                cout << "\n\t********** ALL ACCOUNTS ************";
                for (size_t i = 0; i < accounts.size(); i++) {
                    accounts[i].printSummary();
                }
                break;
            }

            case 6:
                cout << "\n\tThank you for using  Bank System!";
                return 0;

            default:
                cout << "\n\tInvalid Choice! Please try again.";
        }
    }
}

