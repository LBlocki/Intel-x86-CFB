#ifndef INTEL_CFB_H
#define INTEL_CFB_H

#include <string>

class Cfb {

private:
    std::string inputText;
    std::string initializationVector;
    std::string key;

    static bool isInputTextValid(const std::string &newInputText);
    static bool isInitializationVectorValid(const std::string &newInitializationVector);
    static bool isKeyValid(const std::string &newKey);
    static bool validateString(const std::string &textToValidate);

public:

    Cfb();

    bool validateAndSetInputText(const std::string &newInputText);
    bool validateAndSetInitializationVector(const std::string &newInitializationVector);
    bool validateAndSetKey(const std::string &newKey);

    void performCipher();
    void performDecipher();

};
#endif //INTEL_CFB_H
