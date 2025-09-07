


#pragma once


#include <iostream>
#include <sstream>
#include <stack>

class RPN
{
    public:
        RPN(const std::string &exp);
        RPN(const RPN & a);
        RPN &operator=(const RPN & a);
        ~RPN();
    
    private:
        bool is_ops(const std::string & c);
    

};