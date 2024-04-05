#include "RPN.hpp"

RPN::RPN() : operators("+-*/"){
}

RPN::~RPN() {
}

bool RPN::rpn(std::string input) {
    int top;
    int bottom;
    int result;
    unsigned long i;
    for (i = 0; i < (input.size()); i++) 
    {
        if (isdigit(input[i]) && input[i + 1] == ' ') 
        {
            operands.push(input[i] - '0');
        }
        else if (operators.find(input[i]) != std::string::npos) 
        {
            if(operands.size() < 2)
            {
                std::cout << "Error: not enough operands" << std::endl;
                return false;
            }
            top = operands.top();
            operands.pop();
            bottom = operands.top();
            operands.pop();
            switch (input[i]) 
            {
                case '+':
                    result = bottom + top;
                    break;
                case '-':
                    result = bottom - top;
                    break;
                case '*':
                    result = bottom * top;
                    break;
                case '/':
                    result = bottom / top;
                    break;
            }
            operands.push(result);
        }
        else if (input[i] == ' ')
        {
            continue;
        }
        else
        {
            std::cout << "Error: invalid character" << std::endl;
            return false;
        }
    }
    if (i == (input.size()) && operands.size() == 2)
    {
        std::cout << "Error: too few operator" << std::endl;
        return false;
    }
    std::cout << result << std::endl;
    return true;
}