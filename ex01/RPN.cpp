
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
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
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

RPN::RPN(const RPN &other) {}

RPN &RPN::operator=(const RPN &other) {
    
    return *this;
}

bool RPN::is_ops(std::string &c)
{
    if (c == "+" || c == "-" || c == "/" || c == "*") 
        return (true);
    return (false);
}

RPN::~RPN() {}
