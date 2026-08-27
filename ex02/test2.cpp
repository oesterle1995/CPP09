

#include <iostream>
#include <sstream>
#include <vector>
#include <climits>
#include <algorithm>

// std::vector<int> order_insertion(std::vector<int> tab)
// {
//     std::vector<int> order;
//     int power = 2;
//     int U_prev = 1;
//     int tmp;
//     int size = tab.size();

//     if (size < 1)
//         return (order);

//     order.push_back(0);
//     while (order.size() != tab.size())
//     {
//         power *= 2;
//         int U_curr = std::min(power - U_prev, size);
//         for (tmp = U_curr - 1; tmp > U_prev - 1; tmp--)
//             order.push_back(tmp);
//         U_prev = U_curr;
//     }
//     return (order);
// }

std::vector<int> generate_jacob_order(const std::vector<int>& tab) // OK
{
    std::vector<int> order;
    int J_prev = 1;
    int J_curr = 3;
    int J_next;
    int size = tab.size();
    order.push_back(1);
    while(order.size() != tab.size())
    {
        int tmp = std::min(J_curr, size);
        for(int i = tmp; i > J_prev; i--)
            order.push_back(i);
        J_next = J_curr + 2 * J_prev;
        J_prev = J_curr;
        J_curr = J_next;
    }
        std::cout << "lourd * 2 " << std::endl;
    for(int i = 0; i < order.size(); i++)
        order[i] -= 1;
    return(order);
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
    std::vector<int> order = generate_jacob_order(tab);
    for (int i = 0; i < order.size(); i++)
        std::cout << order[i] << std::endl;
}

// }

// int main()
// {
//     // Tableau de 10 éléments
//     std::vector<int> tab(10, 0);

//     std::cout << "Lancement pour un tableau de taille 10..." << std::endl;
//     std::vector<int> order = order_insertion(tab);

//     std::cout << "Terminé ! Taille de order : " << order.size() << std::endl;
//     return 0;
// }