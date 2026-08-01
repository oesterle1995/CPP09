#include <stack>
#include <iostream>

int main()
{
    std::stack<int> lourd;
    lourd.push(0);
    lourd.push(6);
    lourd.push(7);
    lourd.push(8);
    lourd.push(9);
    std::cout << lourd.size() << std::endl;
    std::cout << lourd.top() << std::endl;
    lourd.pop();
    std::cout << lourd.top() << std::endl;

}