#include <string>
#include <iostream>
#include <cstring>
#include "cfb.h"

extern "C" void _cipher(char *text, char *vector, char *key);
extern "C" void _decipher(char *text, char *vector, char *key);

bool Cfb::isInputTextValid(const std::string &newInputText) {
   return Cfb::validateString(newInputText) && !newInputText.empty() && newInputText.length() <= 100;
}

bool Cfb::isKeyValid(const std::string &newInitializationVector) {
    return Cfb::validateString(newInitializationVector) && newInitializationVector.length() == 4;
}

bool Cfb::isInitializationVectorValid(const std::string &newKey) {
    return Cfb::validateString(newKey) && newKey.length() == 4;
}

bool Cfb::validateAndSetInputText(const std::string &newInputText) {
   if(Cfb::isInputTextValid(newInputText)) {
       this->inputText = newInputText;
       return true;
   }
   return false;
}

bool Cfb::validateAndSetInitializationVector(const std::string &newInitializationVector) {
    if(Cfb::isInitializationVectorValid(newInitializationVector)) {
        this->initializationVector = newInitializationVector;
        return true;
    }
    return false;
}

bool Cfb::validateAndSetKey(const std::string &newKey) {
    if(Cfb::isKeyValid(newKey)) {
        this->key = newKey;
        return true;
    }

    return false;
}

void Cfb::performDecipher() {
    if(Cfb::isInputTextValid(this->inputText) && Cfb::isInitializationVectorValid(this->initializationVector) &&
    Cfb::isKeyValid(this->key)) {

        char * cText = new char [this->inputText.length()+1];
        char * cVector = new char [this->initializationVector.length()+1];
        char * cKey = new char [this->key.length()+1];
        std::strcpy (cText, this->inputText.c_str());
        std::strcpy (cVector, this->initializationVector.c_str());
        std::strcpy (cKey, this->key.c_str());

        _decipher(cText, cVector, cKey);

        std:: cout <<  "result is: " << this->inputText;

    }
}

void Cfb::performCipher() {
    if(Cfb::isInputTextValid(this->inputText) && Cfb::isInitializationVectorValid(this->initializationVector) &&
    Cfb::isKeyValid(this->key)) {

        char * cText = new char [this->inputText.length()+1];
        char * cVector = new char [this->initializationVector.length()+1];
        char * cKey = new char [this->key.length()+1];
        std::strcpy (cText, this->inputText.c_str());
        std::strcpy (cVector, this->initializationVector.c_str());
        std::strcpy (cKey, this->key.c_str());

        _cipher(cText, cVector, cKey);
        std:: cout <<  "result is: " << this->inputText << std:: endl;
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