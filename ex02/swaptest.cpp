/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swaptest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/28 19:30:58 by aoesterl          #+#    #+#             */
/*   Updated: 2026/08/31 18:12:58 by aoesterl         ###   ########.fr       */
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




// void ford(std::vector<int>& tab, int bloc_size)
// { 
//     int group = 2 * bloc_size;
//     int nb_pairs = tab.size()/group;
//     bool odd = tab.size()/bloc_size % 2 == 1;
//     std::vector<int> main_chain;
//     std::vector<int> pending;
//     for(int i = 0; i < nb_pairs; i++)
//     { 
//         int first = group * i;
//         int second = group * i + bloc_size;
//         for(int j = 0; j < bloc_size; j++)
//         { 
//             main_chain.push_back(tab[first + j]);
//             pending.push_back(tab[second  + j]);
//         }
//     }
//     if(odd == true)
//     {   
//         int last = (tab.size()/group) * group;
//         for(int j = 0; j < bloc_size; j++)
//             pending.push_back(tab[last + j]);
//     }
//     print_array(main_chain, "--- main --- ");
//     print_array(pending, "--- pending --- ");
// } 


void fill_bloc_size(std::vector<int>& src, std::vector<int> &dest, int bloc_size, int i)
{ 
    for(int j = 0; j < bloc_size; j++)
        dest.push_back(src[i *bloc_size + j]);    
}


std::vector<int> generate_jacob_tab(int size)
{
    std::vector<int> order;
    if(size < 1)
        return(order);
    int J_next;
    int J_prev = 1;
    int J_curr = 3;
    order.push_back(1);
    std::cout << size << std::endl;
    while(order.size() != size)
    { 
        int j = std::min(J_curr, size);
        for(int tmp = j; tmp > J_prev; tmp--)
            order.push_back(tmp);
        J_next = J_curr + 2 *J_prev;
        J_prev = J_curr;
        J_curr = J_next;
    }
    for(int i = 0; i < order.size(); i++)
        order[i] -= 1;
    return(order);
}

int binairy_search(std::vector<int>& main_chain, int low, int high, int nb)
{
    // std::cout << "low :" << low << std::endl;
    //  std::cout << "high :" << high << std::endl;
    int ret;
    if(low == high)
        return(low);
    int mid = low + (high - low)/2;
    if(nb > main_chain[mid])
        ret = binairy_search(main_chain, mid + 1, high, nb);
    else
        ret = binairy_search(main_chain, low, mid, nb);
    return(ret);
}

void jacob_insertion(std::vector<int>& main_chain, std::vector<int>& pending, int bloc_size)
{
    int high;
    int index;
    std::vector<int> order = generate_jacob_tab(pending.size());
    if(order.empty())
        return;
    for(int j = 0; j < bloc_size; j++)
            main_chain.insert(main_chain.begin() + j, pending[order[0]]);
    for(int i = 1; i < pending.size(); i++)
    { 
        high = order[i] + i; 
        index = binairy_search(main_chain, 0, high, pending[order[i]]);
        for(int j = 0; j < bloc_size; j++)
            main_chain.insert(main_chain.begin() + index + j, pending[order[i]]);
    }
}


void ford(std::vector<int>& tab, int bloc_size)
{ 
    int group = 2 * bloc_size;
    int nb_pairs = tab.size()/bloc_size;
    bool odd = tab.size()/bloc_size % 2 == 1;
    std::vector<int> main_chain;
    std::vector<int> pending;
    std::vector<int> jac;
    for(int i = 0; i  < tab.size()/bloc_size; i++)
    { 
        if(i % 2 == 0)
            fill_bloc_size(tab, pending, bloc_size, i);
        if(i % 2 == 1)
            fill_bloc_size(tab, main_chain, bloc_size, i);
    }
    jac = generate_jacob_tab(pending.size());
    print_array(main_chain, "--- main --- ");
    print_array(pending, "--- pending --- ");
    print_array(jac, "--- jac_order ---");

    jacob_insertion(main_chain, pending, bloc_size);
    print_array(main_chain, "--- main --- ");
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
    ford(tab, 1);
}