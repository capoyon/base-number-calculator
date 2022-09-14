#include "header/parser.h"
 /*
    Paser
    Based on Shunting Yard Algorithm

    code by: Cristopher
    P.S.it does not intended for effeciency nor it is very optimized;
 */


// check if the equation is balance (i.e. it has correct braces, bracket, or parenthesis)
bool Parse::isBalance(std::string equation)
{
    const int length = equation.length();
    int i;
    std::stack<char> symbol;
    for(i=0; i<length; i++)
    {
        if (isOpenParen(equation[i]))
            // put to std::stack
            symbol.push(equation[i]);
        else if (isCloseParen(equation[i]))
        {
            //comapare if not match return false
            if(symbol.empty())
                return false;
            if(!isOpenCloseMatch(symbol.top(), equation[i]))
                    return false;
                symbol.pop();
        }
    }
    if(symbol.size() == 0)
        return true;
    else
        return false;
}

// convert infix notation to postfix, using shunting yard algorithm
std::queue<std::string> Parse::infixToPostfix(const std::string equation)
{
    std::queue <std::string> parsed;
    std::stack<char> symbol;
    std::string buffer, tmp;
    const int length = equation.length();
    int i, priorityNum;
    for (i=0; i<length; i++){

        if (isDigit(equation[i]))
            buffer.push_back(equation[i]);
    
        else if (isSymbol(equation[i])){
            if (!buffer.empty()){
                parsed.push(buffer);
                buffer.clear();
            }

            priorityNum = priorityNumber(equation[i]);
            if(priorityNum == 0){
                symbol.push(equation[i]);
            }
            else if(priorityNum == 3){
                while (!symbol.empty()){
                    if(isOpenCloseMatch(symbol.top(), equation[i])){
                        symbol.pop();
                        break;
                    }
                    tmp.clear();
                    tmp = symbol.top();
                    symbol.pop();
                    parsed.push(tmp);    
                }
            }
            else{
                while (!symbol.empty()){
                    if(priorityNumber(symbol.top())<priorityNum)
                        break;
                    tmp.clear();
                    tmp = symbol.top();
                    symbol.pop();
                    parsed.push(tmp);    
                }
                symbol.push(equation[i]);
            }  
        }
    }
    //pop and push the remaining in symbol std::stack
    if (!buffer.empty()){
            parsed.push(buffer);
            buffer.clear();
        }
    while(!symbol.empty()){
        tmp.clear();
        tmp = symbol.top();
        symbol.pop();
        parsed.push(tmp);
    }
    return parsed;
}

double Parse::evalPostfix(std::queue<std::string> eq, const int base)
{
    std::stack<double> num;
    double left, right;
    std::string c;
    while(!eq.empty()){
        c = eq.front();
        eq.pop();   
        if(isValidDigit(c)){
            num.push(toDecimal(c,base));
        }
        else{
            right = num.top();
            num.pop();
            left = num.top();
            num.pop();
            if (c[0] == '+') num.push(left+right);
            else if (c[0] == '-') num.push(left-right);
            else if (c[0] == '*') num.push(left*right);
            else if (c[0] == '/') num.push(left/right);
            //else if (op == '%') num.push(left%right);
        }
             
    }
    return num.top();
    /*else{
        std::cout<<"Error unbalance\n";
        exit(1);
    }*/
}

bool Parse::isSymbol(const char& check)
{
    std::string symbolList = "()[]{}+-*/%";
    //check if the character is in the symbolList
    if(symbolList.find(check) != std::string::npos)
        return true;
    return false;
}

// check a character if it is digit
bool Parse::isDigit(const char& check)
{
    std::string digitList = ".0123456789AaBbCcDdEeFf";
    //check if the character is in the symbolList
    if(digitList.find(check) != std::string::npos)
        return true;
    return false;
}


// check std::string is valid digit
bool Parse::isValidDigit(const std::string& str)
{
    int dotCount = 0;
    for (char const &c: str){
        if(!isDigit(c)) return false;
        if(c =='.') dotCount++;
    }
    if (dotCount < 2) return true;
    else return false;
}


const int Parse::priorityNumber(const char& symbol)
{
    /*
        3 immediate ), ], }
        2 high      /, *, %
        1 low       +, -
        0 wild      (, [, {
    */
    
    if (symbol == ')' || symbol == ']' || symbol == '}')
        return 3;
    if (symbol == '/' || symbol == '*' || symbol == '%')
        return 2;
    if (symbol == '-' || symbol == '+')
        return 1;
    if (symbol == '(' || symbol == '[' || symbol == '{')
        return 0;
    else{
        std::cout<< "invalid operation"<< std::endl;
        exit(1);
    }
}

//check if the braces, bracket or parenthesis matches
bool Parse::isOpenCloseMatch(const char& open, const char& close)
{
    if(open == '(' && close == ')')
        return true;
    if(open == '[' && close == ']')
        return true;
    if(open == '{' && close == '}')
        return true;
    return false;
}

// check if it is open parenthesis i.e "([{" 
bool Parse::isOpenParen(const char& symbol)
{
    if(symbol == '(' || symbol == '[' || symbol == '{')
        return true;
    return false;
}

// check if it is open parenthesis i.e ")]}" 
bool Parse::isCloseParen(const char& symbol)
{
    if(symbol == ')' || symbol == ']' || symbol == '}')
        return true;
    return false;
}

bool isBalance(std::string equation)
{
    Parse parse;
    return parse.isBalance(equation);
}
double evaluatePostfix(std::queue<std::string> eq, const int base)
{
    Parse parse;
    return parse.evalPostfix(eq, base);
}

std::queue<std::string> parseInfixToPostfix(const std::string equation)
{
    Parse parse;
    return parse.infixToPostfix(equation);
}