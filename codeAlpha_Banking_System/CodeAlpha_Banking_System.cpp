#include <iostream>
#include <string>
using namespace std;

// Customer Class
class Customer {
public:
    string name;
    int accountNumber;
};

// Transaction Class
class Transaction {
public:
    string type;
    float amount;
    float balance;
};

// Account Class
class Account {
private:
    Customer customer;
    float balance;
    Transaction history[150];
    int transactionCount;

public:

    // Constructor
    Account() {
        balance = 0;
        transactionCount = 0;
        customer.accountNumber = 0;
    }

    // Create Account
    void createAccount(int accountNumber) {
        cout << "Enter Customer Name: ";
        cin.ignore();
        getline(cin, customer.name);

        customer.accountNumber = accountNumber;

        cout << "Enter Initial Balance: ";
        cin >> balance;

        if (balance < 0) {
            cout << "Invalid Initial Balance. Balance Set to 0." << endl;
            balance = 0;
        }

        transactionCount = 0;

        cout << "Account Created Successfully!" << endl;
    }

    // Get Account Number
    int getAccountNumber() {
        return customer.accountNumber;
    }

    // Get Balance
    float getBalance() {
        return balance;
    }

    // Deposit Money
    void deposit(float amount) {
        if (amount <= 0) {
            cout << "Invalid Amount!" << endl;
            return;
        }

        balance += amount;

        if (transactionCount < 150) {
            history[transactionCount].type = "Deposit";
            history[transactionCount].amount = amount;
            history[transactionCount].balance = balance;
            transactionCount++;
        }

        cout << "Deposit Successful!" << endl;
    }

    // Withdraw Money
    bool withdraw(float amount) {
        if (amount <= 0) {
            cout << "Invalid Amount!" << endl;
            return false;
        }

        if (amount > balance) {
            cout << "Insufficient Balance!" << endl;
            return false;
        }

        balance -= amount;

        if (transactionCount < 150) {
            history[transactionCount].type = "Withdrawal";
            history[transactionCount].amount = amount;
            history[transactionCount].balance = balance;
            transactionCount++;
        }

        cout << "Withdrawal Successful!" << endl;

        return true;
    }

    // Transfer Money From Account
    bool transferOut(float amount, int receiverAccount) {
        if (amount <= 0) {
            cout << "Invalid Amount!" << endl;
            return false;
        }

        if (amount > balance) {
            cout << "Insufficient Balance!" << endl;
            return false;
        }

        balance -= amount;

        if (transactionCount < 150) {
            history[transactionCount].type =
                "Transfer to Account " + to_string(receiverAccount);

            history[transactionCount].amount = amount;
            history[transactionCount].balance = balance;
            transactionCount++;
        }

        return true;
    }

    // Receive Money
    void transferIn(float amount, int senderAccount) {
        balance += amount;

        if (transactionCount < 150) {
            history[transactionCount].type =
                "Received from Account " + to_string(senderAccount);

            history[transactionCount].amount = amount;
            history[transactionCount].balance = balance;
            transactionCount++;
        }
    }

    // Display Account Information
    void displayAccount() {
        cout << "===== ACCOUNT INFORMATION =====" << endl;
        cout << "Name: " << customer.name << endl;
        cout << "Account Number: "
             << customer.accountNumber << endl;
        cout << "Balance: "
             << balance << endl;
    }


    // Display Transaction History
    void displayHistory() {
        cout << "===== TRANSACTION HISTORY =====" << endl;

        if (transactionCount == 0) {
            cout << "No Transactions Found." << endl;
            return;
        }

        for (int i = 0; i < transactionCount; i++) {
            cout << i + 1 << ". "
                 << history[i].type
                 << " | Amount: "
                 << history[i].amount
                 << " | Balance: "
                 << history[i].balance
                 << endl;
        }
    }
};

int main() {
    Account accounts[100];
    int accountCount = 0;

    int choice;
    int accountNumber;
    int receiverAccount;
    float amount;
    bool found;

    do {
        cout << "===== BANKING SYSTEM =====" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Fund Transfer" << endl;
        cout << "5. Balance Enquiry" << endl;
        cout << "6. Transaction History" << endl;
        cout << "7. Exit" << endl;

        cout << "Enter Choice: ";
        cin >> choice;


        switch (choice)
        {

        // Create Account
        case 1: {
            if (accountCount >= 100) {
                cout << "Maximum Accounts Limit Reached!" << endl;
                break;
            }

            int newAccountNumber;

            cout << "Enter Account Number: ";
            cin >> newAccountNumber;

            found = false;

            for (int i = 0; i < accountCount; i++) {
                if (accounts[i].getAccountNumber() == newAccountNumber) {
                    found = true;
                    break;
                }
            }

            if (found) {
                cout << "Account Number Already Exists!" << endl;
            }
            else {
                accounts[accountCount].createAccount(newAccountNumber);
                accountCount++;
            }

            break;
        }

        // Deposit
        case 2: {
            cout << "Enter Account Number: ";
            cin >> accountNumber;

            found = false;

            for (int i = 0; i < accountCount; i++) {
                if (accounts[i].getAccountNumber() == accountNumber) {
                    cout << "Enter Deposit Amount: ";
                    cin >> amount;

                    accounts[i].deposit(amount);

                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Account Not Found!" << endl;
            }

            break;
        }

        // Withdraw
        case 3: {
            cout << "Enter Account Number: ";
            cin >> accountNumber;

            found = false;

            for (int i = 0; i < accountCount; i++) {
                if (accounts[i].getAccountNumber() == accountNumber) {
                    cout << "Enter Withdrawal Amount: ";
                    cin >> amount;

                    accounts[i].withdraw(amount);

                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Account Not Found!" << endl;
            }

            break;
        }

        // Fund Transfer
        case 4: {
            cout << "Enter Sender Account Number: ";
            cin >> accountNumber;

            cout << "Enter Receiver Account Number: ";
            cin >> receiverAccount;

            cout << "Enter Transfer Amount: ";
            cin >> amount;

            int senderIndex = -1;
            int receiverIndex = -1;

            for (int i = 0; i < accountCount; i++) {
                if (accounts[i].getAccountNumber() == accountNumber) {
                    senderIndex = i;
                }

                if (accounts[i].getAccountNumber() == receiverAccount) {
                    receiverIndex = i;
                }
            }

            if (senderIndex == -1 || receiverIndex == -1) {
                cout << "Invalid Account Number!" << endl;
            }

            else if (senderIndex == receiverIndex) {
                cout << "Cannot Transfer Money to the Same Account!" << endl;
            }

            else if (accounts[senderIndex].transferOut(amount, receiverAccount)) {
                accounts[receiverIndex].transferIn(amount, accountNumber);

                cout << "Transfer Successful!" << endl;
            }

            break;
        }

        // Balance Enquiry
        case 5: {
            cout << "Enter Account Number: ";
            cin >> accountNumber;

            found = false;

            for (int i = 0; i < accountCount; i++) {
                if (accounts[i].getAccountNumber() == accountNumber) {
                    accounts[i].displayAccount();

                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Account Not Found!" << endl;
            }

            break;
        }

        // Transaction History
        case 6: {
            cout << "Enter Account Number: ";
            cin >> accountNumber;

            found = false;

            for (int i = 0; i < accountCount; i++) {
                if (accounts[i].getAccountNumber() == accountNumber) {
                    accounts[i].displayHistory();

                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Account Not Found!" << endl;
            }

            break;
        }

        // Exit
        case 7: {
            cout << "Thank You for Using the Banking System!" << endl;
            break;
        }

        default: {
            cout << "Invalid Choice!" << endl;
        }

        }

    } while (choice != 7);

    return 0;
}
