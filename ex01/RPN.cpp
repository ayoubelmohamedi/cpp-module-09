
#include "RPN.hpp"



RPN::RPN(const std::string & exp)
{
    std::istringstream iss(exp);
    std::string c;
    std::stack<int> s;
    int a, b, res;

    while ( iss >> c)
    {
      
        if (!(c.size() == 1 && std::isdigit(c[0])) && !is_ops(c))
            throw std::runtime_error("Invalid input");

        if (is_ops(c) && s.size() < 2)
            throw std::runtime_error("Error: not enough operands");
        
        if (!is_ops(c))
            s.push(std::stoi(c));
        else
        { 
            b = s.top(); s.pop();
            a = s.top(); s.pop();
            if (c == "+")       res = a + b;
            else if (c == "-") res = a - b;
            else if (c == "*") res = a * b;
            else if (c == "/") {
                if (b == 0)
                    throw std::runtime_error("Error: division by zero");
                res = a / b;
            }
            s.push(res);
        } 
    }
    if (s.size() != 1)
        throw std::runtime_error("Error: invalid expression");
    else
        std::cout << s.top() << std::endl;
}

RPN::RPN(const RPN &other) {
    (void)other;
}

RPN &RPN::operator=(const RPN &other) {
    (void)other; 
    return *this;
}

bool RPN::is_ops(const std::string &c)
{
    if (c == "+" || c == "-" || c == "/" || c == "*") 
        return (true);
    return (false);
}

RPN::~RPN() {}
