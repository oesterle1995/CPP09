/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 14:43:31 by aoesterl          #+#    #+#             */
/*   Updated: 2026/08/24 17:10:37 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <vector>
#include <climits>








void dichotomic_insertion(std::vector<int>& tab, int nb, int low, int high)
{ 
    int mid;
    int range = high - low;
    if(range == 0)
    { 
        tab.insert(tab.begin() + low, nb);
        return;
    }
    mid = low + (range/2);
    if(nb > tab[mid])
        dichotomic_insertion(tab, nb, mid + 1, high);
    if(nb <= tab[mid])
        dichotomic_insertion(tab, nb, low, mid);
}

void iterative_dichomotmie(std::vector<int>& tab, int nb)
{ 
    int low = 0;
    int high = tab.size();
    int range = high - low;
    int mid;
    while(range != 0)
    { 
        mid = low + range/2;
        if(nb > tab[mid])
            low = mid + 1;
        if(nb <= tab[mid])
            high = mid;
        range = high - low;        
    }
    tab.insert(tab.begin() + low, nb);
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
    // dichotomic_insertion(tab, 8, 0, tab.size());    
    iterative_dichomotmie(tab, 15);                  
    for(std::vector<int>::iterator it = tab.begin(); it != tab.end(); it++)
    { 
        std::cout << *it << std::endl;
    }
    
}