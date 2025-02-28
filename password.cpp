#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <sstream>
#include <cctype>
#include <tuple>
#include <memory>
// #include <bcrypt.h>
// #include <Python.h>
#include <cstdlib>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

const string YELLOW_CODE = "\033[1;33m";
const string BLACK_CODE = "\033[0m";
const string RED_CODE = "\033[1;31m";
const string GREEN_CODE = "\033[1;32m";

// string encryptPassword(const std::string& password) {
//     std::stringstream command;
//     command << "python hash.py " << password;

//     FILE* pipe = _popen(command.str().c_str(), "r");
//     if (!pipe) {
//         std::cerr << "Failed to run command!" << std::endl;
//         return "";
//     }

//     char buffer[128];
//     std::string result = "";
//     while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
//         cout << buffer <<endl;
//         result += buffer; 
//     }

//     fclose(pipe);

//     return result;
// }

string encryptDecrypt(std::string password) {
    const string key = "MYSECRETKEY";
    std::string output = password;
    size_t keyLength = key.length();

    for (size_t i = 0; i < password.length(); ++i) {
        output[i] = password[i] ^ key[i % keyLength];
    }

    return output;
}

string toLowerCase(const std::string& str) {
    string lowerStr = str;
    for (char& ch : lowerStr) {
        ch = std::tolower(ch);
    }
    return lowerStr;
}

bool deletePassword(string nameOfPassword){
    ifstream file("password.txt");
    ofstream tempFile("temp.txt");
    if(!tempFile.is_open()){
        cerr << "\033[1;31mFailed to open temp file\033[0m" <<endl;
        return false;
    }    
    if(!file.is_open()){ 
        cerr << "\033[1;31mFailed to open password file\033[0m" <<endl;
        return false;
    }
    string line;
    bool found = false;

    while (getline(file, line)) {
        istringstream stream(line);
        string storedName, storedPassword;
        stream >> storedName >> storedPassword;
        if (toLowerCase(storedName) == toLowerCase(nameOfPassword)) {
            found = true;
            continue;
        }
        tempFile << line <<endl;
    }

    file.close();
    tempFile.close();

    if(found){
        remove("password.txt");
        rename("temp.txt", "password.txt");
        cout << "\033[1;32mPassword deleted successfully\033[0m" <<endl;
    }else{
        remove("temp.txt");
        cout << "\033[1;31mPassword to entry not found\033[0m" <<endl;
    }
    return found;
}

tuple<bool, string, string> checkIfPasswordIsStored(string nameOfPassword){
    ifstream file("password.txt");
    string line;
    if(file.is_open()){
        string line;
        while (getline(file, line)) {
            // cout <<line <<endl;
            istringstream stream(line);
            string storedName, storedPassword;
            stream >> storedName >> storedPassword;
            // cout << storedName <<endl;
            if (toLowerCase(storedName) == toLowerCase(nameOfPassword)) {
                return {true, storedName, encryptDecrypt(storedPassword)};
            }
        } 
        return {false, "error", "Not found"};
    }
    return {false, "error", "error opening file"};
}

bool isPasswordTheSame(string password, string confirmPassword){
    if(password == confirmPassword){
        return true;
    }
    return false;
}

void writePasswordToFile(string password, string passwordName){
    auto [found, nameOfPassword, passwordstored] = checkIfPasswordIsStored(passwordName);
    if(found){
        cout << "\033[1;31mPassword name already exists\033[0m" <<endl;
        return;
    }
    ofstream file("password.txt", ios::app);
    if(file.is_open()){
        string hashedPassword = encryptDecrypt(password);
        // cout << encryptDecrypt(hashedPassword) <<endl;
        file << passwordName << " " << hashedPassword <<endl;
        cout << "\033[1;32mpassword saved\033[0m" << endl;
        file.close();
    }else{
        cout << "\033[1;31merror writting file\033[0m" <<endl;
    }
}

void addPassword(){
    string nameOfPassword;
    string password;
    string confirmPassword;
    cout << "\033[1;33mName of password\033[0m" <<endl;
    cin >> nameOfPassword;
    if(nameOfPassword == ""){  
        cout << RED_CODE <<"Name of password cant be empty"<<BLACK_CODE <<endl;
        return;
    }
    cout << "\033[1;33mInsert the password\033[0m" <<endl;
    cin >> password;
    cout << "\033[1;33mConfirm password\033[0m" <<endl;
    cin >> confirmPassword;
    if(isPasswordTheSame(password, confirmPassword)){
        writePasswordToFile(password, nameOfPassword);
    }else{
        cout << "\033[1;31mPassword are not the same\033[0m" <<endl;
    }
  
}

void retrievePassword(){
    string nameOfPassword;
    cout << "\033[1;33mName of password you want to retrieve \033[0m" << endl;
    cin >> nameOfPassword;
    auto [found, storedname, storedPassword] = checkIfPasswordIsStored(nameOfPassword);
    if(found){
        cout << "\033[1;32mThe password for " << storedname << " is " << storedPassword << "\033[0m"<<endl;
    }else{
        cout << "\033[1;31m" << storedPassword << "\033[0m"<<endl;
    }
}

void callDeletePassword(){
    string nameOfPasswordToDelete;
    char sureDelete;
    cout << "\033[1;33mName of password you want to delete\033[0m" <<endl;
    cin >> nameOfPasswordToDelete;
    do
    {
        cout << "\033[1;33mAre you sure you want to delete password? (Y/N)\033[0m" <<endl;
        cin >> sureDelete;
        if(sureDelete == 'Y' || sureDelete == 'y'){
            bool deleted = deletePassword(nameOfPasswordToDelete);
            return;
        }else if(sureDelete == 'N' || sureDelete == 'n'){
            return;
        }else{
            cout <<RED_CODE <<"Not a valid option" <<BLACK_CODE<<endl;
        }
    } while (sureDelete != 'Y' || sureDelete != 'y' );
    
    return;
}

void modifyPassword(){
    string nameOfPasswordToModify;
    string oldPassword;
    string newPassword;
    char sureToModify;
    cout << "\033[1;33mName of password you want to modify \033[0m" <<endl;
    cin >> nameOfPasswordToModify;
    auto [found, nameofPassword, passwordStored] = checkIfPasswordIsStored(nameOfPasswordToModify);
    if(found){
        do
        {
            cout << "\033[1;33mAre you sure you want to modify the password (Y/N)\033[0m" <<endl;
            cin >> sureToModify;
            if(sureToModify == 'N' || sureToModify == 'n'){
                return;
            }
        } while (sureToModify != 'Y' || sureToModify != 'y');

        cout << "\033[1;33mInsert the old Password \033[0m" <<endl;
        cin >> oldPassword;
        if(oldPassword == passwordStored){
            cout << "\033[1;33mEnter new password \033[0m" <<endl;
            cin >> newPassword;
            bool deleted = deletePassword(nameofPassword);
            if(deleted){
                writePasswordToFile(newPassword, nameofPassword);
            }
        }else{
            cout << "\033[1;31mPassword not the same please try again \033[0m" <<endl;
        }
        return;
    }
}

bool checkIfPasswordExist(string password){
    std::ifstream file("password.txt");
    string line;
    if(file.is_open()){
        std::string line;
        while (getline(file, line)) {
            std::istringstream stream(line);
            string storedName, storedPassword;
            stream >> storedName >> storedPassword;
            if (toLowerCase(encryptDecrypt(storedPassword)) == toLowerCase(password)) {
                return true;
            }
        } 
        return false;
    }
    return false;
}

string generatePasswordForUser() {
    
    string password;
    do
    {
        int maxLength = 20;
        
        const string charLower = "abcdefghijklmnopqrstuvwxyz";
        const string charUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const string charNum = "0123456789";
        const string charSpecial = "!@#$%^&*()-_=+";
        string allChar = charLower + charUpper + charNum + charSpecial;
    
        srand(time(0));
        password += charLower[rand() % charLower.length()];
        password += charUpper[rand() % charUpper.length()];
        password += charNum[rand() % charNum.length()];
        password += charSpecial[rand() % charSpecial.length()];
        
        for(int i = 4; i < maxLength; ++i){
            password += allChar[rand() % allChar.length()];
        }
    
        std::random_device rd;
        mt19937 g(rd());
        shuffle(password.begin(), password.end(), g);
    } while (checkIfPasswordExist(password));
    
    return password;
}

void callGeneratePassword(){

    string nameOfPassword;
    char sureContinue;
    cout << "\033[1;33mName of Password \033[0m" <<endl;
    cin >> nameOfPassword;
    auto [found, nameofPassword, passwordStored] = checkIfPasswordIsStored(nameOfPassword);
    if(found){
        cout << "\033[1;31mPassword name already exist\033[0m" <<endl;
        return;
    }
    string passwordGenerated;
    do {
        // passwordGenerated = "";
        passwordGenerated = generatePasswordForUser();
        cout << "\033[1;33mThe generated password is " << passwordGenerated <<"\033[0m" <<endl;
        cout << "\033[1;33mWould you like to continue (Y/N)\033[0m" <<endl;
        cin >> sureContinue;
    } while (sureContinue == 'N' || sureContinue == 'n');
    
    writePasswordToFile(passwordGenerated, nameOfPassword);
}

void exitProgram(){
    cout << "Exiting the program" <<endl;
    exit(0);
}

void determineChoice(char choice){
    switch (choice)
    {
    case '1':
        addPassword();
        break;
    case '2':
        retrievePassword();
        break;
    case '3':
        modifyPassword();
        break;
    case '4':
        callGeneratePassword();
        break;
    case '5':
        callDeletePassword();
        break;
    case '6':
        exitProgram();
    default:
        cout << "\033[1;31mNot an option try again\033[0m" <<endl;
        break;
    }
}

int main() {
    char choice;
    cout << "\033[1;33m1. Add Password\n2. Retrieve Password\n3. Modify Password\n4. Generate Password\n5. Delete Password \n6. Exit\033[0m \n\n";
    cin >> choice;
    determineChoice(choice);

    return 0;
}