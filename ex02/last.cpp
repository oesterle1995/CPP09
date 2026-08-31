/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 18:21:04 by aoesterl          #+#    #+#             */
/*   Updated: 2026/08/31 20:21:02 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <sstream>
#include <vector>
#include <climits>
#include <iomanip>
#include <algorithm>

//#1 PARSING
bool is_valid_number(const std::string &str, std::vector<int>& tab)
{ 
    int nb;
    int count = 0;
    std::istringstream iss(str);
    while(iss >> nb)
    { 
        if(nb < 0)      
            return false;
        tab.push_back(nb);
        count++;
    }
    if(!iss.eof() || count == 0)
        return false;
    return true;
}

bool recup_argc(std::vector<int>& tab, int argc, char **argv)
{ 
    std::string str;
    for(int i = 1; i < argc; i++)
    {
        str += argv[i];
        str += " ";
    }
    if(is_valid_number(str, tab) == false)
        return false;
    return true;
}
//#1 FIN PARSING

//#2 DEBUG
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

void swap_int(int& a, int& b)
{ 
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}

void switch_block_size(std::vector<int>& tab, int group, int bloc_size)
{ 
    for(int i = 0; i < bloc_size; i++)
    { 
        int first = group + i; 
        int second = group + bloc_size + i;
        swap_int(tab[first], tab[second]);
    }    
}

void fill_bloc_size(std::vector<int>& src, std::vector<int> &dest, int bloc_size, int i)
{ 
    for(int j = 0; j < bloc_size; j++)
        dest.push_back(src[i *bloc_size + j]);    
}


std::vector<int> generate_jacob_tab(int size)
{
    std::vector<int> order;
    int J_next;
    int J_prev = 1;
    int J_curr = 3;
    
    if(size < 1)
        return(order);
    order.push_back(1);
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


// void jacob_insertion(std::vector<int>& main_chain, std::vector<int>& pending, int bloc_size)
// {
//     int high;
//     int index;
//     std::vector<int> order = generate_jacob_tab(pending.size());
//     if(order.empty())
//         return;
//     for(int j = 0; j < bloc_size; j++)
//             main_chain.insert(main_chain.begin() + j, pending[order[0] * bloc_size + j]);
//     for(int i = 1; i < pending.size(); i++)
//     { 
//         high = order[i] + i; 
//         index = binairy_search(main_chain, 0, high, pending[order[i]]);
//         for(int j = 0; j < bloc_size; j++)
//             main_chain.insert(main_chain.begin() + index + j, pending[order[i] * bloc_size + j]);
//     }
// }

void jacob_insertion(std::vector<int>& main_chain, std::vector<int>& pending, int bloc_size)
{
    std::vector<int> order = generate_jacob_tab(pending.size());
    if(order.empty())
        return;
    for(int j = 0; j < bloc_size; j++)
            main_chain.insert(main_chain.begin() + j, pending[order[0] + j]);
    for(int i = 1; i < pending.size(); i++)
    { 
        int bloc_index = order[i] * bloc_size; 
        int high = bloc_index + i * bloc_
        int index = binairy_search(main_chain, 0, high, pending[order[i]]);
        for(int j = 0; j < bloc_size; j++)
            main_chain.insert(main_chain.begin() + index + j, pending[order[i] * bloc_size + j]);
    }
}


void Ford_johnson(std::vector<int>& tab, int bloc_size = 1)
{
    int group = 2 * bloc_size; // nouveau groupe de pair (si on a des paires de 2, le nouveau groupe sera 4)

    if(tab.size()/bloc_size == 1)
        return;
    for(int i = 0; i < tab.size()/ group; i++)
    { 
        int first = group * i; // 1er sous groupe
        int second = group * i + bloc_size; 
        if(tab[first] < tab[second])
            switch_block_size(tab, group * i, bloc_size);
    }
    print_array(tab, "--- after --- ");

    Ford_johnson(tab, 2 * bloc_size);

    std::vector<int> main_chain;
    std::vector<int> pending;

    for(int i = 0; i  < tab.size()/bloc_size; i++)
    { 
        if(i % 2 == 0)
            fill_bloc_size(tab, main_chain, bloc_size, i);
        if(i % 2 == 1)
            fill_bloc_size(tab, pending, bloc_size, i);
    }
    std::cout << " DEBUT PENDING ET MAIN" << std::endl;
    print_array(main_chain, "--- main --- ");
    print_array(pending, "--- pending --- ");
    
    jacob_insertion(main_chain, pending, bloc_size);
    for(int i = main_chain.size(); i < tab.size(); i++)
        main_chain.push_back(tab[i]);
    std::cout << " FIN MAIN" << std::endl;
    print_array(main_chain, "--- main --- ");
    std::cout << std::endl;
    tab = main_chain;
} 


int main(int argc, char **argv)
{ 
    std::vector<int> tab;

    if(argc < 2)
        return(0);
    recup_argc(tab, argc, argv);
    print_array(tab, " --- before --- ");
    Ford_johnson(tab);
    // checker_tab(tab);
    // print_array(tab, "--- final chain ---");
}

// void  checker_tab(std::vector<int> &tab)
// { 
//     if(tab.size() == 1)
//         std::cout << "[OK]" << std::endl;
//     for(int i = 0; i < tab.size() - 1; i++)
//     { 
//         int j = i + 1;
//         if(tab[i] > tab[j])
//             std::cout << "[FAIL]" << std::endl;
//     }
//     std::cout << "[OK]" << std::endl;

    
// }

// if(static_cast<int>(tab.size())/bloc_size == 1)
    //     exit(0);