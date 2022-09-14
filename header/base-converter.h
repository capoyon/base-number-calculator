#ifndef BASE_CONVERTER_H
#define BASE_CONVERTER_H

#include <iostream>
#include <string>

class Convert{
    public:
        std::string decimalToOtherbase(const double& decimal, const int& toBase);
        double toDecimal(const std::string& toConvert, const int& base);

    private:
        bool isDigit(const char& check);
        int letterToDecimal(const char& letter);
        int findDecimalPoint(const std::string& str);
        char decimalToLetter(const int& decimal); 
};

std::string decToBin(const double& decimal);
std::string decToOct(const double& decimal);
std::string decToHex(const double& decimal);
std::string decTobase(const double& decimal, const int& toBase);
double toDecimal(const std::string& toConvert, const int& base);
#endif