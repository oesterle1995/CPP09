/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ford_v1_struct.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 12:39:57 by aoesterl          #+#    #+#             */
/*   Updated: 2026/09/02 15:50:22 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <vector>
#include <climits>
#include <iomanip>

int lourd = 0 ;

typedef struct s_element
{ 
    int value;
    std::vector<s_element> losers;
}t_element;

//#1 PARSING
bool fill_number(const std::string &str, std::vector<t_element>& tab)
{ 
    int nb;
    int count = 0;
    t_element node;
    std::istringstream iss(str);
    while(iss >> nb)
    { 
        if(nb < 0)      
            return false;
        node.value = nb;
        tab.push_back(node);
        count++;
    }
    if(!iss.eof() || count == 0)
        return false;
    return true;
}

bool init_tab(std::vector<t_element>& tab, int argc, char **argv)
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

// #2 DEBUG
void tree_of_element(const std::vector<t_element>& tab, std::string prefix = "")
{
    std::string new_prefix;
    int end = tab.size() - 1;
    if(tab.empty())
        return;
    for(int i = 0; i < tab.size(); i++)
    {
        std::cout << prefix;
        if(i != end)
            std::cout << "├── ";
        else
            std::cout << "└── ";
        std::cout << "[Val: " << tab[i].value << "]" << std::endl;
        if(i != end)
            new_prefix = prefix + "│\t";
        else
            new_prefix = prefix + "\t";
        tree_of_element(tab[i].losers, new_prefix);
    }
}

void debug_ford(const std::vector<t_element>& tab, const std::vector<t_element>& pend, std::string& title)
{
    std::cout << title << std::endl << std::endl;
    std::cout << "   --- TREE OF LOSERS ---- " << std::endl;
    tree_of_element(tab);
    std::cout << std::endl << "   --- PEND --- " << std::endl;
    tree_of_element(pend);
    std::cout << std::endl;
}

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
//FIN DEBUG

// #3 Checker
void  checker(std::vector<t_element> &tab, int size)
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
//FIN CHECKER


void iterative_dichotomie(std::vector<t_element>& tab, t_element& elem, int low, int high)
{ 
    int range = high - low;
    int mid;
    while(range != 0)
    { 
        mid = low + range/2;
        if(elem.value > tab[mid].value)
            low = mid + 1;
        else
            high = mid;
        lourd++;
        range = high - low;        
    }
    tab.insert(tab.begin() + low, elem);
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

void jacob_insertion(std::vector<t_element>& pending,  std::vector<t_element>& main_chain)
{ 
    std::vector<int> order_b = generate_jacob_tab(pending.size()); // 1 3 2 5 4  => 0 2 1 4 3
    int high;
    int insert_index;
    main_chain.insert(main_chain.begin(), pending[0]); 
    for(int i = 1; i < order_b.size(); i++)
    {
        high = order_b[i] + i;
        iterative_dichotomie(main_chain, pending[order_b[i]], 0, high);
    }
}


void insertion(std::vector<t_element>& tab, std::vector<t_element> &odd)
{ 
    std::vector<t_element> pending;
    std::vector<t_element> main_chain;

    main_chain = tab;
    for(int i = 0; i < main_chain.size(); i++)
    {
        // if(main_chain[i].losers.empty() == false)
        // { 
            pending.push_back(main_chain[i].losers.back());
            main_chain[i].losers.pop_back();
        // }
    }
    if(odd.empty() == false)
        pending.push_back(odd.back());
    jacob_insertion(pending, main_chain);
    tab.swap(main_chain);
}


void new_tab(std::vector<t_element>& tab)
{ 
    std::vector<t_element> new_tab;
    for(int i = 0; i < tab.size(); i += 2)
    { 
        if(tab[i].value < tab[i + 1].value)
        { 
            tab[i + 1].losers.push_back(tab[i]);
            new_tab.push_back(tab[i+1]);
        }
        else
        {
            tab[i].losers.push_back(tab[i+1]);
            new_tab.push_back(tab[i]);
        }
        lourd++;
    }
    tab.swap(new_tab);
}


std::vector<t_element> Ford_johnson_algorithm(std::vector<t_element>& tab)
{
    std::vector<t_element> odd;
    if(tab.size() <= 1)
        return(tab);
    if(tab.size() % 2 != 0)
    {
        odd.push_back(tab[tab.size() - 1]);
        tab.pop_back();
    }
    new_tab(tab);
    // debug_ford(tab, odd, "--- 😛 RECURSIVE UP --- ");
    Ford_johnson_algorithm(tab);
    insertion(tab, odd);
    // debug_ford(tab, odd, " --- 😛 RECURSIVE DOWN --- ");
    return(tab);
}

int main(int argc, char **argv)
{
    std::vector <t_element> tab;
    int size;
    if(init_tab(tab, argc, argv) == false)
        return(std::cout << "Error" << std::endl, 0);
    size = tab.size();
    Ford_johnson_algorithm(tab);
    checker(tab, size);
}

