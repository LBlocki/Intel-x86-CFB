#include <iostream>
#include <limits>
#include "cfb.h"
#include <fstream>

bool readChoice(int &menuChoice);
bool readInputText(Cfb *cfb);
bool readInitializationVector(Cfb *cfb);
bool readKey(Cfb *cfb);
bool readTextInputChoice(int &menuChoice, bool cipher);
bool readTextInputUsingFile(Cfb *cfb, bool cipher);

int main() {

    int menuChoice;
    bool shouldExit = false;

    auto *cfb = new Cfb;

    while (!shouldExit) {

        while (!readChoice(menuChoice));

        switch (menuChoice) {
            case 1:
                while(!readTextInputChoice(menuChoice, true));
                switch (menuChoice) {
                    case 1:
                        while(!readInputText(cfb));
                        break;
                    case 2:
                        if(!readTextInputUsingFile(cfb, true)) {
                            std:: cout << "Failed to get plain text from textToCipher.txt. Exiting..." << std:: endl;
                            exit(1);
                        }
                        break;
                    default:
                        std:: cout << "Unexpected choice detected. Program will exit";
                        exit(1);
                }
                while(!readInitializationVector(cfb));
                while(!readKey(cfb));
                cfb->performCipher();
                break;
            case 2:
                while(!readTextInputChoice(menuChoice, false));
                switch (menuChoice) {
                    case 1:
                        while(!readInputText(cfb));
                        break;
                    case 2:
                        if(!readTextInputUsingFile(cfb, false)) {
                            std:: cout << "Failed to get plain text from textToDecipher.txt. Exiting..." << std:: endl;
                            exit(1);
                        }
                        break;
                    default:
                        std:: cout << "Unexpected choice detected. Program will exit";
                        exit(1);
                }
                while(!readInitializationVector(cfb));
                while(!readKey(cfb));
                cfb->performDecipher();
                break;
            case 3:
                shouldExit = true;
                break;
            default:
                std:: cout << "Unexpected choice detected. Program will exit";
                shouldExit = true;
        }
    }

    std:: cout << "Goodbye" << std:: endl;

    return 0;
}

bool readInputText(Cfb *cfb) {
    bool validInput = false;
    std::string inputText;

    std::cout << "Enter text(max 100 bytes):";
    std::getline(std:: cin, inputText);

    if (!cfb->validateAndSetInputText(inputText)) {
        std::cout << "Error while saving text. Please try again." << std::endl;
    } else {
        std::cout << "Text saved." << std::endl;
        validInput = true;
    }

    return validInput;
}

bool readTextInputUsingFile(Cfb *cfb, bool cipher) {

    std::string inputText;

    if(cipher) {
        std::ifstream  myFile;
        myFile.open ("textToCipher.txt");
        if (myFile.is_open()) {
            getline (myFile,inputText);
            myFile.close();
            return cfb->validateAndSetInputText(inputText);
        }
    } else {
        std::ifstream  myFile;
        myFile.open ("textToDecipher.txt");
        if (myFile.is_open()) {
            getline (myFile,inputText);
            myFile.close();
            return cfb->validateAndSetInputText(inputText);
        }
        myFile.close();
    }

    return false;
}

bool readInitializationVector(Cfb *cfb) {
    bool validInput = false;
    std::string initializationVector;

    std::cout << "Enter initialization vector(4 bytes):";
    std::getline(std:: cin, initializationVector);

    if (!cfb->validateAndSetInitializationVector(initializationVector)) {
        std::cout << "Error while saving initialization vector. Please try again." << std::endl;
    } else {
        std::cout << "Initialization vector saved." << std::endl;
        validInput = true;
    }

    return validInput;
}

bool readKey(Cfb *cfb) {
    bool validInput = false;
    std::string key;

    std::cout << "Enter key(4 bytes):";
    std::getline(std:: cin, key);

    if (!cfb->validateAndSetKey(key)) {
        std::cout << "Error while saving key. Press try again." << std::endl;
    } else {
        std::cout << "Key saved." << std::endl;
        validInput = true;
    }

    return validInput;
}

bool readChoice(int &menuChoice) {

    bool validInput = false;

    std::cout << "Choose: Cipher(1), Decipher(2), Exit(3):";
    std::cin >> menuChoice;

    if (std::cin.fail() || !(menuChoice == 1 || menuChoice == 2 || menuChoice == 3)) {
        std::cout << "Wrong option." << std::endl;
    } else {
        validInput = true;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return validInput;
}

bool readTextInputChoice(int &menuChoice, bool cipher) {

    bool validInput = false;

    if(cipher) {
        std::cout << "Choose: Enter text by hand(1), get text from file(textToCipher.txt)(2):";
    } else {
        std::cout << "Choose: Enter text by hand(1), get text from file(textToDecipher.txt)(2):";
    }

    std::cin >> menuChoice;

    if (std::cin.fail() || !(menuChoice == 1 || menuChoice == 2)) {
        std::cout << "Wrong option." << std::endl;
    } else {
        validInput = true;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return validInput;
}


