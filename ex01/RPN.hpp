


#include <iostream>
#include <sstream>
#include <stack>
#include <string>

class RPN
{
    private : 
        std::stack<double> _stack;
        bool RPN_calculate(const std::string& str);
    public :

        bool RPN_result(std::istringstream& is);
};
