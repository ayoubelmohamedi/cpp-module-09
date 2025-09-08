


#pragma once


#include <iostream>
#include <sstream>
#include <string>
#include <stack>

class RPN
{
    public:
        RPN(const std::string &exp);
        ~RPN();
    
    private:
        bool is_ops(const std::string & c) const;
        RPN();
        RPN(const RPN & a);
        RPN &operator=(const RPN & a);
    
};