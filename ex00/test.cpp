#include <iostream>
#include <fstream>


class iloveu
{ 
    public :
    int x;
    iloveu(int a) : x(a)
    { 
        return;
    }
    operator bool()
    { 
        if(x > 0)
            return(true);
        if(x <= 0)
            return(false);
        return(false);
    }
};

int main()
{
    iloveu michel(-10);
    if(michel)
        std::cout << "I love u" << std::endl;
    if(!michel)
        std::cout << "I like u" << std::endl;
        std::stringstream
}