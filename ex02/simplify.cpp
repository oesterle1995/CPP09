/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 16:06:45 by aoesterl          #+#    #+#             */
/*   Updated: 2026/08/27 18:21:24 by aoesterl         ###   ########.fr       */
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
//#2 FIN DEBUG

// Utils
void swap_int(int& a, int& b)
{ 
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}
 



std::vector<int> generate_jacob_order(const std::vector<int>& tab) // OK
{
    std::vector<int> order;
    if (tab.empty()) 
        return order;
    int J_prev = 1;
    int J_curr = 3;
    int J_next;

    order.push_back(1);
    while(order.size() != tab.size())
    {
        int tmp = std::min(J_curr, static_cast<int>(tab.size()));
        for(int i = tmp; i > J_prev; i--)
            order.push_back(i);
        J_next = J_curr + 2 * J_prev;
        J_prev = J_curr;
        J_curr = J_next;
    }
    for(int i = 0; i < order.size(); i++)
        order[i] -= 1;
    print_array(order, "--- tableau jacob ---- ");
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
    std::vector<int> jacob_order = generate_jacob_order(small_idx);
    main_idx.insert(main_idx.begin(), small_idx[0]);
    for(int i = 1; i < jacob_order.size(); i++)
    { 
        int b = jacob_order[i]; // 0 2 1 4 3 
        int high = b + i;
        int j = small_idx[b];
        dichotomic_insertion(tab, main_idx, j, 0, high);
    }
}

void Ford_johnson(std::vector<int>& tab, std::vector<int>& idx)
{
    
    print_array(tab, "--- value tab ---");
    if(tab.size() == 1)
        return;
    int nb_pairs = tab.size()/2;
    for(int i = 0; i < nb_pairs; i++)
    {
        int first = 2 * i;
        int second = 2 * i + 1;
        if(tab[first] < tab[second])
            swap_int(idx[first], idx[second]);
    }
    print_array(idx, "--- pairs index ---");
    std::vector<int> new_idx;
    std::vector<int> new_value;
    for(int i = 0; i < nb_pairs; i++)
        new_idx.push_back(i);
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

void  checker_tab(std::vector<int> &tab)
{ 
    if(tab.size() == 1)
        std::cout << "[OK]" << std::endl;
    for(int i = 0; i < tab.size() - 1; i++)
    { 
        int j = i + 1;
        if(tab[i] > tab[j])
            std::cout << "[FAIL]" << std::endl;
    }
    std::cout << "[OK]" << std::endl;

    
}

int main(int argc, char **argv)
{ 
    std::vector<int> tab;
    std::vector<int> idx;

    if(argc < 2)
        return(0);
    recup_argc(tab, argc, argv);
    for(int i = 0; i < tab.size(); i++)
        idx.push_back(i);
    Ford_johnson(tab, idx);
    tab = sort_tab(tab, idx);
    checker_tab(tab);
    // print_array(tab, "--- final chain ---");
}