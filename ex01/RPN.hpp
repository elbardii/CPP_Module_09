#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>

class RPN {
private:
    std::stack<int> _stack;

    bool isOperator(char c) const;
    bool executeOperation(char op);

public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

    bool calculate(const std::string& expression);
};

#endif
