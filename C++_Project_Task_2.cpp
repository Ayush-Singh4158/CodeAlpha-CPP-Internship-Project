#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sys/stat.h> 
#include <cerrno>       
#include <cstring>      
#ifdef _WIN32
    #include <direct.h> 
#endif

using namespace std;

string hashPassword(const string& password) {
    string hash;
    for (char c : password) {
        hash += to_string((int)c + 7);
    }
    return hash;
}

bool userExists(const string& username) {
    ifstream infile("users/" + username + ".txt");
    return infile.good();
}

void ensureUserFolderExists() {
    struct stat info;
    if (stat("users", &info) != 0) {
#ifdef _WIN32
        if (_mkdir("users") != 0)
            cerr << "Failed to create users folder: " << strerror(errno) << endl;
#else
        if (mkdir("users", 0777) != 0)
            cerr << "Failed to create users folder: " << strerror(errno) << endl;
#endif
    }
}

void registerUser() {
    string username, password;

    cout << "\nEnter a username: ";
    cin >> username;

    if (userExists(username)) {
        cout << " Username already exists. Try a different one.\n";
        return;
    }

    cout << "Enter a password: ";
    cin >> password;

    ensureUserFolderExists();

    ofstream userFile("users/" + username + ".txt");
    if (userFile) {
        userFile << hashPassword(password);
        userFile.close();
        cout << " Registration successful for '" << username << "'!\n";
    } else {
        cout << " Error creating user file. Try again.\n";
    }
}

void loginUser() {
    string username, password;

    cout << "\nEnter your username: ";
    cin >> username;

    if (!userExists(username)) {
        cout << " No account found for this username.\n";
        return;
    }

    cout << "Enter your password: ";
    cin >> password;

    ifstream userFile("users/" + username + ".txt");
    string storedHash;
    getline(userFile, storedHash);
    userFile.close();

    if (storedHash == hashPassword(password)) {
        cout << " Login successful! Welcome, " << username << ".\n";
    } else {
        cout << " Incorrect password.\n";
    }
}

int main() {
    int choice;

    cout << "=== Welcome to the Login System ===\n";
    cout << "1. Register\n2. Login\nChoose an option: ";
    cin >> choice;

    switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        default:
            cout << " Invalid option selected.\n";
    }

    return 0;
}
