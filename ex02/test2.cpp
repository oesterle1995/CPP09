

#include <iostream>
#include <sstream>
#include <vector>
#include <climits>

std::vector<int> order_insertion(std::vector<int> tab)
{
    std::vector<int> order;
    int power = 2;
    int U_prev = 1;
    int tmp;
    int size = tab.size();

    if (size < 1)
        return (order);

    order.push_back(0);
    while (order.size() != tab.size())
    {
        power *= 2;
        int U_curr = std::min(power - U_prev, size);
        for (tmp = U_curr - 1; tmp > U_prev - 1; tmp--)
            order.push_back(tmp);
        U_prev = U_curr;
    }
    return (order);
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
    std::vector<int> order = order_insertion(tab);
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