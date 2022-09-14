#include "header/base-converter.h"
 
 /*
    Base number converter

    code by: Cristopher

 */



// convert other base to decimal
double Convert::toDecimal(const std::string& toConvert, const int& base)
{
    double decimal = 0;
    const int len = toConvert.length();
    const int pointIndex = findDecimalPoint(toConvert);
    int i;
    double place = 1;

    //for whole numbers
    if(pointIndex>0)
        i = pointIndex - 1;
    else
        i = len -1;
    if(pointIndex == -1 || pointIndex>0)
        for(; i>=0; i--){
            if(isDigit(toConvert[i]))
                decimal += (toConvert[i] -'0') * place;
            else if(isalpha(toConvert[i]))
                decimal += letterToDecimal(toConvert[i]) * place;
            else {
                std::cout<<"Error: invalid character\n";
                exit(1);
            }
            place *= base;
        }

    // for decimal point
    if(pointIndex>-1){
        i = pointIndex+1;
        place = 1.0/base;
        for(; i<len; i++){
            if(isDigit(toConvert[i]))
                decimal += (toConvert[i] -'0') * place;
            else if(isalpha(toConvert[i]))
                decimal += letterToDecimal(toConvert[i]) * place;
            else {
                std::cout<<"Error: invalid character\n";
                exit(1);
            }
            place *= 1.0/base;
        }
    }
    return decimal;
}

// convert decimal to other base
std::string Convert::decimalToOtherbase(const double& toConvert, const int& toBase){
    double decimal = toConvert;
    std::string result;
    bool negative = false;
    if(decimal < 0){
        negative = true;
        decimal *= -1;
    }
    int whole = decimal, digit;
    double fraction = decimal - (double)whole;
    while(whole != 0){
        digit = whole%toBase;
        whole /= toBase;
        if(digit>9)
            result.insert(0, 1, decimalToLetter(digit));
        else
            result.insert(0, 1,digit + '0');
    }
    if(fraction != 0) result += '.';
    while(fraction !=0 ){
        fraction *= toBase;
        digit = fraction;
        fraction -= digit;
        if(digit>9)
            result += decimalToLetter(digit);
        else
            result += digit + '0';
    }
    if(negative) result.insert(0, 1, '-');
    return result;
    
}

//output the index of decimal point in a std::string.
int Convert::findDecimalPoint(const std::string& str)
{
    const int len = str.length();
    int i, index, pointCount=0;
    for(i=0; i<len; i++){
        if (str[i] == '.'){
            pointCount++;
            index = i;
        }
        if(pointCount>1){
            std::cout<<"Error: To many decimal point\n";
            exit(1);
        }
    }
    if(pointCount == 0){
        return -1;
    }
    else if (pointCount == 1){
        return index;
    }
    else {
        std::cout<< "Error: To many decimal point\n";
        exit(1);
    }
}

//determine if the character is a digit
bool Convert::isDigit(const char& check)
{
    std::string digitList = "0123456789";
    //check if the character is in the digitList
    if(digitList.find(check) != std::string::npos)
        return true;
    return false;
}

// convert hex A-F to respctive decimal values
int Convert::letterToDecimal(const char& letter)
{
    return tolower(letter) - 87;
}

// convert 10-15 decimal to respective hex letter values
char Convert::decimalToLetter(const int& decimal)
{
    return decimal + 87;
}





std::string decToBin(const double& decimal)
{
    Convert c;
    return c.decimalToOtherbase(decimal, 2);
}

std::string decToOct(const double& decimal)
{
    Convert c;
    return c.decimalToOtherbase(decimal, 8);
}
std::string decToHex(const double& decimal)
{
    Convert c;
    return c.decimalToOtherbase(decimal, 16);
}

std::string decTobase(const double& decimal, const int& toBase)
{
    Convert c;
    return c.decimalToOtherbase(decimal, toBase);
}

double toDecimal(const std::string& toConvert, const int& base)
{
    Convert c;
    return c.toDecimal(toConvert, base);
}