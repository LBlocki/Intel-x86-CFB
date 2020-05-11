#include <iostream>
#include <limits>
#include "cfb.h"

bool readChoice(int &menuChoice);
bool readInputText(Cfb *cfb);
bool readInitializationVector(Cfb *cfb);
bool readKey(Cfb *cfb);

int main() {

    int menuChoice;
    bool shouldExit = false;

    auto *cfb = new Cfb;

    while (!shouldExit) {

        while (!readChoice(menuChoice));

        switch (menuChoice) {
            case 1:
                while(!readInputText(cfb));
                while(!readInitializationVector(cfb));
                while(!readKey(cfb));
                cfb->performCipher();
                break;
            case 2:
                while(!readInputText(cfb));
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
    std::string inputText = "ijklmnop";

    //std::cout << "Enter text(max 100 bytes):";
    //std::getline(std:: cin, inputText);

    if (!cfb->validateAndSetInputText(inputText)) {
        std::cout << "Error while saving text. Please try again." << std::endl;
    } else {
        std::cout << "Text saved." << std::endl;
        validInput = true;
    }

    return validInput;
}

bool readInitializationVector(Cfb *cfb) {
    bool validInput = false;
    std::string initializationVector = "abcdefgh";

   // std::cout << "Enter initialization vector(4 bytes):";
    //std::getline(std:: cin, initializationVector);

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
    std::string key = "ijklmnop";

    //std::cout << "Enter key(4 bytes):";
    //std::getline(std:: cin, key);

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


