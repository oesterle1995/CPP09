/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_over.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 17:47:00 by aoesterl          #+#    #+#             */
/*   Updated: 2026/09/02 15:06:11 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <vector>
#include <climits>
#include <iomanip>
#include <algorithm>



//#1 PARSING
bool fill_number(const std::string &str, std::vector<int>& tab)
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

bool init_tab(std::vector<int>& tab, int argc, char **argv)
{ 
    std::string str;
    for(int i = 1; i < argc; i++)
    {
        str += argv[i];
        str += " ";
    }
    if(fill_number(str, tab) == false)
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
//#2 FIN DEBUG

//#3 Checker
void  checker(std::vector<int> &tab, int size)
{ 
    const std::string GREEN = "\033[32m";
    const std::string RED   = "\033[31m";
    const std::string RESET = "\033[0m";
    
    //check sort
    if(tab.size() == 1)
        std::cout << GREEN << "[OK sort]" << RESET;
    for(int i = 0; i < tab.size() - 1; i++)
    { 
        int j = i + 1;
        if(tab[i] > tab[j])
            std::cout << RED << "[FAIL sort] " << RESET;
    }
    std::cout << GREEN << "[OK]" << RESET <<  std::endl; 

    //check count
    if(tab.size() != size)
        std::cout << RED << "[FAIL] count : [" << tab.size() << "] init_count : [" << size << "]" <<  RESET << std::endl;
    else
        std::cout << GREEN << "[OK] count : [" << tab.size() << "] init_count : [" << size << "]" <<  RESET << std::endl;
}

// Utils
void swap_int(int& a, int& b)
{ 
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
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

void dichotomic_insertion(std::vector<int>& tab, std::vector<int> &main_idx, int idx, int low, int high)
{
    int e = high - low;
    if(e == 0)
    { 
        main_idx.insert(main_idx.begin() + low, idx);
        return;
    }
    int mid = low  + e/2;
    if(tab[idx] > tab[main_idx[mid]])
        dichotomic_insertion(tab, main_idx, idx, mid + 1 , high); 
    else
        dichotomic_insertion(tab, main_idx, idx, low, mid);
}


void jacob_insertion(std::vector<int>& tab, std::vector<int>& main_idx, std::vector<int>& pending_idx)
{
    std::vector<int> jacob_order = generate_jacob_tab(pending_idx.size());
    main_idx.insert(main_idx.begin(), pending_idx[0]);
    for(int i = 1; i < jacob_order.size(); i++)
    { 
        int b = jacob_order[i]; // 0 2 1 4 3 
        int high = b + i;
        int idx = pending_idx[b];
        dichotomic_insertion(tab, main_idx, idx, 0, high);
    }
}


void switch_index(std::vector<int>& tab, std::vector<int>& order, int nb_pairs)
{ 
    
    for(int i = 0; i < nb_pairs; i++)
    {
        int first = 2 * i;
        int second = 2 * i + 1;
        if(tab[first] < tab[second])
            swap_int(order[first], order[second]);
    }
}

void Ford_johnson(std::vector<int>& tab, std::vector<int>& order)
{
    int nb_pairs = tab.size()/2;
    if(tab.size() == 1)
        return;
    switch_index(tab, order, nb_pairs);

    //tableau new_order initialiser a 0 1 2... C'est les indices des gagnants(1 new_order = 2 * 1 order =>gagnants) 
    std::vector<int> new_order;
    for(int i = 0; i < nb_pairs; i++)
        new_order.push_back(i);

    //Nouveau tableau ne contenant que les gagnants. il sera envoye a ford_jhonson
    std::vector<int> new_value;
    for(int i = 0; i < nb_pairs; i++)
        new_value.push_back(tab[order[2 * i]]);

    Ford_johnson(new_value, new_order);
    

    // A partir d'ici new_order contient les index des gagnants dans un ordre trie : on se base dessus
    // pour creer main_idx et pending_idx
    
    // main_idx va contenir les index des gagnants
    std::vector<int> main_idx;
    for(int i = 0; i < new_order.size(); i++)
        main_idx.push_back(order[2 * new_order[i]]);
    
    // pending_index va contenir les index des perdants
    std::vector<int> pending_idx;
    for(int i = 0; i < new_order.size(); i++)
        pending_idx.push_back(order[2 * new_order[i] + 1]);
    
    // on rajoute a pending_index le nombre impair
    if(order.size() % 2 != 0)
        pending_idx.push_back(order[order.size() - 1]);
    
    //va inserer les pending index dans le main_index puis on dit que order_index = main comme ca en descendant
    //dans le niveau de recursion on a le bon ordre. 
    jacob_insertion(tab, main_idx, pending_idx);
    order = main_idx;
}





std::vector<int> sort_tab(std::vector<int>& tab, std::vector<int>& order)
{ 
    std::vector<int> new_tab;
    for(int i = 0; i < order.size(); i++)
        new_tab.push_back(tab[order[i]]);
    return(new_tab);
}

int main(int argc, char **argv)
{ 
    std::vector<int> tab;
    std::vector<int> order;
    int size;
    
    if(argc < 2)
        return(std::cout << "Error" << std::endl, 0);
    if(init_tab(tab, argc, argv) == false)
        return(std::cout << "Error" << std::endl, 0);
    size = tab.size();
    for(int i = 0; i < tab.size(); i++)
        order.push_back(i);
    Ford_johnson(tab, order);
    tab = sort_tab(tab, order);
    checker(tab, size);
    // print_array(tab, "--- final chain ---");
}