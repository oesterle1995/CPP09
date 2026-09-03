/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 19:00:43 by aoesterl          #+#    #+#             */
/*   Updated: 2026/09/03 16:39:57 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <deque>
#include <climits>
#include <iomanip>
#include <sys/time.h>

class Pmerge
{
    public :
        typedef struct s_element
        { 
            int value;
            std::vector<s_element> losers;
        }t_element;
    private :

        std::vector<t_element> _tab;
        std::deque<t_element> _deque;
        size_t _count;
        size_t _size;

        template <typename Container>
        void tree_of_element(const Container& tab, std::string prefix = "");
        
        template <typename Container>
        void debug_ford(const Container& tab, const Container& pend, std::string& title);
        
        template <typename Container>
        bool fill_number(const std::string &str, Container& tab);
        
        // template <typename Container>
        // void iterative_dichotomie(Container& tab, t_element& elem, int low, int high);

        template <typename Container>
        int binairy_search(Container& tab, t_element& elem, int low, int high);

        template <typename Container>
        void generate_jacob_tab(Container &order, size_t size);

        template <typename Container>
        void jacob_insertion(Container& pending,  Container& main_chain);

        template <typename Container>
        void insertion(Container& tab, Container &odd);

        template <typename Container>
        void new_tab(Container& tab);

    public :
        template <typename Container>
        void get_array(Container& tab, std::string title);
        
        template <typename Container>
        bool init_tab(Container& tab, int argc, char **argv);

        template <typename Container>
        void  checker(Container &tab, size_t size); 
        
        template <typename Container>
        void ford_johnson_algorithm(Container& tab);
        std::vector<t_element>& get_vector();
        std::deque<t_element>& get_deque();
        size_t get_count();
        size_t get_size();
};

template <typename Container>
void Pmerge::tree_of_element(const Container& tab, std::string prefix)
{
    std::string new_prefix;
    size_t end = tab.size() - 1;
    if(tab.empty())
        return;
    for(size_t i = 0; i < tab.size(); i++)
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

template <typename Container>
void Pmerge::debug_ford(const Container& tab, const Container& pend, std::string& title)
{
    std::cout << title << std::endl << std::endl;
    std::cout << "   --- TREE OF LOSERS ---- " << std::endl;
    tree_of_element(tab);
    std::cout << std::endl << "   --- PEND --- " << std::endl;
    tree_of_element(pend);
    std::cout << std::endl;
}

template <typename Container>
void Pmerge::get_array(Container& tab, std::string title)
{ 
    std::cout << title;
    for(size_t i = 0; i < tab.size(); i++)
    { 
        std::cout << std::setw(4) << tab[i].value;
        std::cout << " ";
    }
    std::cout << std::endl;
} 



template <typename Container>
void  Pmerge::checker(Container &tab, size_t size)
{ 
    const std::string GREEN = "\033[32m";
    const std::string RED   = "\033[31m";
    const std::string RESET = "\033[0m";
    
    //check sort
    if(tab.size() == 1)
        std::cout << GREEN << "[OK sort]" << RESET;
    for(size_t i = 0; i < tab.size() - 1; i++)
    { 
        size_t j = i + 1;
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

template <typename Container>
bool Pmerge::fill_number(const std::string &str, Container& tab)
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

template <typename Container>
bool Pmerge::init_tab(Container& tab, int argc, char **argv)
{
    _size = 0;
    _count = 0;
    std::string str;
    for(int i = 1; i < argc; i++)
    {
        str += argv[i];
        str += " ";
    }
    if(fill_number(str, tab) == false)
        return false;
    _size = tab.size();
    return true;
}

// template <typename Container>
// void Pmerge::iterative_dichotomie(Container& tab, t_element& elem, int low, int high)
// { 
//     int range = high - low;
//     int mid;
//     while(range != 0)
//     { 
//         mid = low + range/2;
//         if(elem.value > tab[mid].value)
//             low = mid + 1;
//         else
//             high = mid;
//         _count++;
//         range = high - low;        
//     }
// }

template <typename Container>
int Pmerge::binairy_search(Container& tab, t_element& elem, int low, int high)
{
    int ret;
    int e = high - low;
    if(e == 0)
    { 
        ret = low;
        return(ret);
    }
    int mid = low  + e/2;
    if(elem.value > tab[mid].value)
        ret = binairy_search(tab, elem, mid + 1 , high); 
    else
        ret = binairy_search(tab, elem, low, mid);
    return(ret);
}

template <typename Container>
void Pmerge::generate_jacob_tab( Container &order, size_t size)
{
    size_t J_next;
    size_t J_prev = 1;
    size_t J_curr = 3;
    
    t_element elem;
    if(size < 1)
        return;
    elem.value = 1;
    order.push_back(elem);
    while(order.size() != size)
    { 
        size_t j = std::min(J_curr, size);
        for(size_t tmp = j; tmp > J_prev; tmp--)
        { 
            elem.value = static_cast<int>(tmp);
            order.push_back(elem);
        }
        J_next = J_curr + 2 *J_prev;
        J_prev = J_curr;
        J_curr = J_next;
    }
    for(size_t i = 0; i < order.size(); i++)
        order[i].value -= 1;
}

template <typename Container>
void Pmerge::jacob_insertion(Container& pending,  Container& main_chain)
{ 
    Container order;
    generate_jacob_tab(order, pending.size()); // 1 3 2 5 4  => 0 2 1 4 3
    size_t high;
    size_t insert_i;
    main_chain.insert(main_chain.begin(), pending[0]); 
    for(size_t i = 1; i < order.size(); i++)
    {
        high = order[i].value + i;
        insert_i = binairy_search(main_chain, pending[order[i].value], 0, high);
        main_chain.insert(main_chain.begin() + insert_i, pending[order[i].value]);
    }
}

template <typename Container>
void Pmerge::insertion(Container& tab, Container &odd)
{ 
    Container pending;
    Container main_chain;

    main_chain = tab;
    for(size_t i = 0; i < main_chain.size(); i++)
    {
            pending.push_back(main_chain[i].losers.back());
            main_chain[i].losers.pop_back();
    }
    if(odd.empty() == false)
        pending.push_back(odd.back());
    jacob_insertion(pending, main_chain);
    tab.swap(main_chain);
}

template <typename Container>
void Pmerge::new_tab(Container& tab)
{ 
    Container new_tab;
    for(size_t i = 0; i < tab.size(); i += 2)
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
        _count++;
    }
    tab.swap(new_tab);
}

template <typename Container>
void Pmerge::ford_johnson_algorithm(Container& tab)
{
    Container odd;
    if(tab.size() <= 1)
        return;
    if(tab.size() % 2 != 0)
    {
        odd.push_back(tab[tab.size() - 1]);
        tab.pop_back();
    }
    new_tab(tab);
    // debug_ford(tab, "--- 😛 RECURSIVE UP --- ");
    ford_johnson_algorithm(tab);
    insertion(tab, odd);
    // debug_ford(tab, " --- 😛 RECURSIVE DOWN --- ");
}