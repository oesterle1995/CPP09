#include "RPN.hpp"

bool RPN::RPN_calculate(const std::string& str)
{
    if(_stack.size() < 2)
        return(std::cerr << "Error" << std::endl, false);
    double val2 = _stack.top();
    _stack.pop();
    double val1 = _stack.top();
    _stack.pop();
    if(str == "+")
        _stack.push(val1 + val2);
    else if(str == "-")
        _stack.push(val1 - val2);
    else if(str == "/")
    {
        if(val2 == 0)
            return(std::cerr << "Error : division by 0" << std::endl, false);
        _stack.push(val1 / val2);
    }
    else if(str == "*")
        _stack.push(val1 * val2);
    return(true); 
}

bool RPN::RPN_result(std::istringstream& is)
{
    std::string token;
    double value;
    char extra;
    while(is >> token)
    {
        if(token == "+" || token == "-" ||token == "*" ||token == "/")
        {
                if(RPN_calculate(token) == false)
                    return(false);
        }
        else
        {
            std::istringstream is_token(token);
            if(is_token >> value && !(is_token >> extra))
                _stack.push(value);
            else
                return(std::cerr << "Error" << std::endl, false);
        }
    }
    if(_stack.size() != 1)
        return(std::cerr << "Error" << std::endl, false);
    else
        std::cout << _stack.top() << std::endl;
    return(true);
}