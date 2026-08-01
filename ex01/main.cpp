#include "RPN.hpp"

int main(int argc, char **argv)
{
    if(argc != 2)
        return(0);
    std::istringstream is(argv[1]);
    // std::string str;
    // is >> str;
    // std::cout << str << std::endl;
    RPN stack;
    stack.RPN_result(is);
}