

#include <iostream>
#include <sstream>
#include <stack>


bool is_ops(std::string c)
{
    if (c == "+" || c == "-" || c == "/" || c == "*") 
        return (true);
    return (false);
}


int main (int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Invalid input" << std::endl;
        return (1);
    }
    std::string line = av[1];

    std::istringstream iss(line);
    std::string c;
    std::stack<int> s;
    int a, b, res;

    while ( iss >> c)
    {
      
        if (!(c.size() == 1 && std::isdigit(c[0])) && !is_ops(c))
        {
            std::cerr << "Invalid input" << std::endl;
            return (1);
        }

        if (is_ops(c) && s.size() < 2)
        {
            std::cerr << "Error: not enough operands" << std::endl;  
            return (1);
        }
        
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
                if (b == 0) {
                    std::cerr << "Error: division by zero" << std::endl;
                    return 1;
                }
                res = a / b;
            }
            s.push(res);
        } 
    }
    if (s.size() != 1)
    {
        std::cerr << "Error: invalid expression" << std::endl;
        return 1;
    }
    else
        std::cout << s.top() << std::endl;


    return (0);
}