#include "RPN.hpp"
#include <sstream>
#include <cctype>
#include <climits>

RPN::RPN() : _stack() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        this->_stack = other._stack;
    }
    return *this;
}

RPN::~RPN() {}

bool RPN::isOperator(char c) const {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::executeOperation(char op) {
    if (_stack.size() < 2) {
        return false;
    }

    int b = _stack.top();
    _stack.pop();
    int a = _stack.top();
    _stack.pop();

    long long res = 0;
    if (op == '+') {
        res = static_cast<long long>(a) + b;
    } else if (op == '-') {
        res = static_cast<long long>(a) - b;
    } else if (op == '*') {
        res = static_cast<long long>(a) * b;
    } else if (op == '/') {
        if (b == 0) {
            return false;
        }
        res = static_cast<long long>(a) / b;
    } else {
        return false;
    }

    if (res > INT_MAX || res < INT_MIN) {
        return false;
    }

    _stack.push(static_cast<int>(res));
    return true;
}

bool RPN::calculate(const std::string& expression) {
    while (!_stack.empty()) {
        _stack.pop();
    }

    std::stringstream ss(expression);
    std::string token;

    while (ss >> token) {
        if (token.length() == 1 && std::isdigit(token[0])) {
            _stack.push(token[0] - '0');
        } else if (token.length() == 1 && isOperator(token[0])) {
            if (!executeOperation(token[0])) {
                return false;
            }
        } else {
            return false;
        }
    }

    if (_stack.size() != 1) {
        return false;
    }

    std::cout << _stack.top() << std::endl;
    return true;
}
