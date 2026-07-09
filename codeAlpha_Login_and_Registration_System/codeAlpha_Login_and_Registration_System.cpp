#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Registration Function
void registerUser() {
    string username, password;
    string storedUser, storedPass;

    cout << "REGISTRATION " << endl;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    // Validate input
    if (username.empty() || password.empty()) {
        cout << "Error: Username and password cannot be empty!" << endl;
        return;
    }

    // Check for duplicate username
    ifstream checkFile("usersFile.txt");

    while (checkFile >> storedUser >> storedPass) {
        if (storedUser == username) {
            cout << "Error: Username already exists!" << endl;
            checkFile.close();
            return;
        }
    }
    checkFile.close();

    // Store user credentials
    ofstream outFile("usersFile.txt", ios::app);
    outFile << username << " " << password << endl;
    outFile.close();

    cout << "Registration successful!" << endl;
}

//Login Function
void loginUser() {
    string username, password;
    string storedUsername, storedPassword;
    bool found = false;

    cout << "LOGIN" << endl;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    ifstream inFile("usersFile.txt");

    if (!inFile) {
        cout << "Error: No registered users found!" << endl;
        return;
    }

    while (inFile >> storedUsername >> storedPassword) {
        if (storedUsername == username && storedPassword == password) {
            found = true;
            break;
        }
    }

    inFile.close();

    if (found)
        cout << "Login successful! Welcome, " << username << "!" << endl;
    else
        cout << "Invalid username or password!" << endl;
}

//Main Menu
int main() {
    int choice;

    do {
        cout << "MAIN MENU" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerUser();
            break;

        case 2:
            loginUser();
            break;

        case 3:
            cout << "Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 3);

    return 0;
}
