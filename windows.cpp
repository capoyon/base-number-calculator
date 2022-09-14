#include "header/base-converter.h"
#include "header/parser.h"
#include <iostream>
#include <queue>
#include <windows.h>


int main()
{
    int base;
    std::string equation;
    std::queue<std::string> reversePolish;

    for(;;){
        std::cout<<"Base: ";
        std::cin>>base;
        std::cout<<"Equation: ";
        std::cin>>equation;
        if(isBalance(equation)){
            reversePolish = parseInfixToPostfix(equation);
            double answer = evaluatePostfix(reversePolish, base);
            std::cout<<"Answer: \nDecimal: "<< answer
                <<"   Base["<<base<<"]: "<<decTobase(answer, base)<<std::endl;
        }
        else
            std::cout<<"Invalid Equation\n";
        std::cout<<"\n\n";
        fflush(stdin);
    }
}


