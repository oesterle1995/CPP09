

#include <iostream>
#include <sstream>
#include <vector>
#include <climits>

std::vector<int> order_insertion(std::vector<int> losers)
{ 
    std::vector<int> order;
    if(losers.size() < 1)
        return(order);
    int location_max = 2;
    int compare = 1;
    int i = 1;
    int size = losers.size();
    while(order.size() != losers.size())
    { 
        order.push_back(i);
        location_max *= 2;
        i = location_max - i;
        
    }


}

int main()
{ 
    std::vector<int> tab;
    tab.push_back(2);
    tab.push_back(4);
    tab.push_back(6);
    tab.push_back(8);
    tab.push_back(10);
    tab.push_back(12);
    tab.push_back(14);
    tab.push_back(16);
    tab.push_back(18);
    tab.push_back(20);
    tab.push_back(22);
    tab.push_back(24);
    std::vector<int> order = order_insertion();

}