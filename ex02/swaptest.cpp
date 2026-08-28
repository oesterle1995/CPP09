/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swaptest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 19:30:58 by aoesterl          #+#    #+#             */
/*   Updated: 2026/08/28 21:07:06 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <vector>
#include <climits>
#include <iomanip>
#include <algorithm>

void print_array(std::vector<int>& tab, std::string title)
{ 
    std::cout << title << std::endl;
    for(int i = 0; i < tab.size(); i++)
    { 
        std::cout << "[" << std::setw(5) << tab[i] << "]";
        std::cout << " ";
    }
    std::cout << std::endl;
}




void ford(std::vector<int>& tab, int bloc_size)
{ 
    int group = 2 * bloc_size;
    int nb_pairs = tab.size()/group;
    bool odd = tab.size()/bloc_size % 2 == 1;
    std::vector<int> main_chain;
    std::vector<int> pending;
    for(int i = 0; i < nb_pairs; i++)
    { 
        int first = group * i;
        int second = group * i + bloc_size;
        for(int j = 0; j < bloc_size; j++)
        { 
            main_chain.push_back(tab[first + j]);
            pending.push_back(tab[second  + j]);
        }
    }
    if(odd == true)
    {   
        int last = (tab.size()/group) * group;
        for(int j = 0; j < bloc_size; j++)
            pending.push_back(tab[last + j]);
    }
    print_array(main_chain, "--- main --- ");
    print_array(pending, "--- pending --- ");
} 

void ford(std::vector<int>& tab, int bloc_size)
{ 
    int group = 2 * bloc_size;
    int nb_pairs = tab.size()/group;
    bool odd = tab.size()/bloc_size % 2 == 1;
    std::vector<int> main_chain;
    std::vector<int> pending;
    for(int i = 0; i < nb_pairs; i++)
    { 
        if(i % 2 == 0)
        { 
            

            
        }
        if(i % 2 == 1)
        { 




            
        }
        int first = group * i;
        int second = group * i + bloc_size;
        for(int j = 0; j < bloc_size; j++)
        { 
            main_chain.push_back(tab[first + j]);
            pending.push_back(tab[second  + j]);
        }
    }
    if(odd == true)
    {   
        int last = (tab.size()/group) * group;
        for(int j = 0; j < bloc_size; j++)
            pending.push_back(tab[last + j]);
    }
    print_array(main_chain, "--- main --- ");
    print_array(pending, "--- pending --- ");
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
    ford(tab, 2);
}