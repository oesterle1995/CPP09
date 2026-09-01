/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_over.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 17:47:00 by aoesterl          #+#    #+#             */
/*   Updated: 2026/09/01 18:08:08 by aoesterl         ###   ########.fr       */
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
        if(tab[i].value > tab[j].value)
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


void jacob_insertion(std::vector<int>& tab, std::vector<int>& main_idx, std::vector<int>& small_idx)
{
    std::vector<int> jacob_order = generate_jacob_tab(small_idx.size());
    main_idx.insert(main_idx.begin(), small_idx[0]);
    for(int i = 1; i < jacob_order.size(); i++)
    { 
        int b = jacob_order[i]; // 0 2 1 4 3 
        int high = b + i;
        int j = small_idx[b];
        dichotomic_insertion(tab, main_idx, j, 0, high);
    }
}


void switch_index(std::vector<int>& tab, std::vector<int>& idx, int nb_pairs)
{ 
    
    for(int i = 0; i < nb_pairs; i++)
    {
        int first = 2 * i;
        int second = 2 * i + 1;
        if(tab[first] < tab[second])
            swap_int(idx[first], idx[second]);
    }
}

void Ford_johnson(std::vector<int>& tab, std::vector<int>& idx)
{
    int nb_pairs = tab.size()/2;
    if(tab.size() == 1)
        return;
    switch_index(tab, idx, nb_pairs);

    std::vector<int> new_idx;
    for(int i = 0; i < nb_pairs; i++)
        new_idx.push_back(i);
    std::vector<int> new_value;
    for(int i = 0; i < nb_pairs; i++)
    { 
        int first = 2 * i;
        new_value.push_back(tab[idx[first]]);
    }
    Ford_johnson(new_value, new_idx);
    
    //on suppose  ici que new_index possede les index dans l'ordre de mes vainqueurs // idx 0 1 2 3 4  devient 2 4 1 3 0 
    std::vector<int> main_idx;
    std::vector<int> small_idx;
    for(int i = 0; i < new_idx.size(); i++)
        main_idx.push_back(idx[2 * new_idx[i]]);
    print_array(main_idx, "--- main index ---");
    for(int i = 0; i < new_idx.size(); i++)
        small_idx.push_back(idx[2 * new_idx[i] + 1]);
    print_array(small_idx, "--- small index ---");
    if(idx.size() % 2 != 0)
        small_idx.push_back(idx[idx.size() - 1]);
    jacob_insertion(tab, main_idx, small_idx);
    print_array(main_idx, "--- main index sort ---");
    idx = main_idx;
}





std::vector<int> sort_tab(std::vector<int>& tab, std::vector<int>& idx)
{ 
    std::vector<int> new_tab;
    for(int i = 0; i < idx.size(); i++)
        new_tab.push_back(tab[idx[i]]);
    return(new_tab);
}

int main(int argc, char **argv)
{ 
    std::vector<int> tab;
    std::vector<int> idx;
    int size;
    
    if(argc < 2)
        return(0);
    if(init_tab(tab, argc, argv) == false);
        std::cout << "Error" << std::endl;
    size = tab.size();
    for(int i = 0; i < tab.size(); i++)
        idx.push_back(i);
    Ford_johnson(tab, idx);
    tab = sort_tab(tab, idx);
    checker(tab, size);
    // print_array(tab, "--- final chain ---");
}