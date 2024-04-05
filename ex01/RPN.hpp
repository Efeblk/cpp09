#ifndef RPN_HPP 
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN {
private:
    std::stack<int> operands;
    std::string input_operators;
    const std::string operators;

public:
    RPN();
    ~RPN();
    bool rpn(std::string input);
};

#endif