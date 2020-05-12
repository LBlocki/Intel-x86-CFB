#include <string>
#include <iostream>
#include <fstream>
#include "cfb.h"

extern "C" void _cipher(char *text, char *vector, char *key, int textLength);
extern "C" void _decipher(char *text, char *vector, char *key, int textLength);

bool Cfb::isInputTextValid(const std::string &newInputText) {
    return !newInputText.empty() && newInputText.length() <= 100;
}

bool Cfb::isKeyValid(const std::string &newInitializationVector) {
    return Cfb::validateString(newInitializationVector) && newInitializationVector.length() == 4;
}

bool Cfb::isInitializationVectorValid(const std::string &newKey) {
    return Cfb::validateString(newKey) && newKey.length() == 4;
}

bool Cfb::validateAndSetInputText(const std::string &newInputText) {
    if (Cfb::isInputTextValid(newInputText)) {
        this->inputText = newInputText;
        return true;
    }
    return false;
}

bool Cfb::validateAndSetInitializationVector(const std::string &newInitializationVector) {
    if (Cfb::isInitializationVectorValid(newInitializationVector)) {
        this->initializationVector = newInitializationVector;
        return true;
    }
    return false;
}

bool Cfb::validateAndSetKey(const std::string &newKey) {
    if (Cfb::isKeyValid(newKey)) {
        this->key = newKey;
        return true;
    }

    return false;
}

void Cfb::performDecipher() {
    if (Cfb::isInputTextValid(this->inputText) && Cfb::isInitializationVectorValid(this->initializationVector) &&
        Cfb::isKeyValid(this->key)) {

        char *cText = new char[this->inputText.length() + 1];
        char *cVector = new char[this->initializationVector.length() + 1];
        char *cKey = new char[this->key.length() + 1];

        std::copy(this->inputText.begin(), this->inputText.end(), cText);
        std::copy(this->initializationVector.begin(), this->initializationVector.end(), cVector);
        std::copy(this->key.begin(), this->key.end(), cKey);

        cText[this->inputText.size()] = '\0';
        cVector[this->initializationVector.size()] = '\0';
        cKey[this->key.size()] = '\0';

        _decipher(cText, cVector, cKey, (int) this->inputText.length());

        std::ofstream myFile;
        myFile.open("deciphered.txt");
        if (myFile.is_open()) {
            myFile << cText;
            myFile.close();
            std::cout << "text written to file deciphered.txt " << std::endl;
        } else {
            std::cout << "Failed to open deciphered.txt for writing..." << std::endl;
        }

        delete[] cText;
        delete[] cVector;
        delete[] cKey;

    }
}

void Cfb::performCipher() {
    if (Cfb::isInputTextValid(this->inputText) && Cfb::isInitializationVectorValid(this->initializationVector) &&
        Cfb::isKeyValid(this->key)) {

        char *cText = new char[this->inputText.length() + 1];
        char *cVector = new char[this->initializationVector.length() + 1];
        char *cKey = new char[this->key.length() + 1];

        std::copy(this->inputText.begin(), this->inputText.end(), cText);
        std::copy(this->initializationVector.begin(), this->initializationVector.end(), cVector);
        std::copy(this->key.begin(), this->key.end(), cKey);

        cText[this->inputText.size()] = '\0';
        cVector[this->initializationVector.size()] = '\0';
        cKey[this->key.size()] = '\0';

        _cipher(cText, cVector, cKey, (int) this->inputText.length());

        std::ofstream myFile;
        myFile.open("ciphered.txt");
        if (myFile.is_open()) {
            myFile << cText;
            myFile.close();
            std::cout << "text written to file ciphered.txt " << std::endl;
        } else {
            std::cout << "Failed to open ciphered.txt for writing..." << std::endl;
        }

        delete[] cText;
        delete[] cVector;
        delete[] cKey;

    }
}

Cfb::Cfb() {
    this->inputText = "";
    this->initializationVector = "";
    this->key = "";
}

bool Cfb::validateString(const std::string &textToValidate) {
    for (const char c : textToValidate) {
        if (!isalpha(c) && !isspace(c))
            return false;
    }
    return true;
}
