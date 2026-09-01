/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 18:21:04 by aoesterl          #+#    #+#             */
/*   Updated: 2026/09/01 02:48:14 by aoesterl         ###   ########.fr       */
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

int binairy_search_bloc(std::vector<int>& main_chain, int low, int high, int bloc_size, int nb)
{
    int ret;
    if(low == high)
        return(low); 
    int mid = low + (high - low)/2;
    int mid_bloc = mid * bloc_size;
    if(nb > main_chain[mid_bloc])
        ret = binairy_search_bloc(main_chain, mid + 1, high, bloc_size, nb);
    else
        ret = binairy_search_bloc(main_chain, low, mid, bloc_size,  nb);
    return(ret);
}

void jacob_insertion(std::vector<int>& main_chain, std::vector<int>& pending, int bloc_size)
{
    std::vector<int> order = generate_jacob_tab(pending.size()/bloc_size);
    if(order.empty())
        return;
    for(int j = 0; j < bloc_size; j++)
            main_chain.insert(main_chain.begin() + j, pending[order[0] + j]);
    for(int i = 1; i < order.size(); i++)
    { 
        int high = order[i] + i;
        int pending_target = order[i] * bloc_size;
        int bloc_index = binairy_search_bloc(main_chain, 0, high, bloc_size, pending[pending_target]) * bloc_size;
        for(int j = 0; j < bloc_size; j++)
            main_chain.insert(main_chain.begin() + bloc_index + j, pending[pending_target + j]);
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
    // print_array(tab, "--- after --- ");

    Ford_johnson(tab, 2 * bloc_size);

    std::vector<int> main_chain;
    std::vector<int> pending;
    int nb_pairs = tab.size()/bloc_size;
    for(int i = 0; i  < nb_pairs; i++)
    {
        if(i == nb_pairs - 1  && nb_pairs % 2 == 1)
            fill_bloc_size(tab, pending, bloc_size, i);
        else if(i % 2 == 0)
            fill_bloc_size(tab, main_chain, bloc_size, i);
        else if(i % 2 == 1)
            fill_bloc_size(tab, pending, bloc_size, i);
        
    }
    // std::cout << " DEBUT PENDING ET MAIN" << std::endl;
    // print_array(main_chain, "--- main --- ");
    // print_array(pending, "--- pending --- ");
    
    jacob_insertion(main_chain, pending, bloc_size);
    for(int j = nb_pairs * bloc_size; j < tab.size(); j++)
                main_chain.push_back(tab[j]);
    // std::cout << " FIN MAIN" << std::endl;
    // print_array(main_chain, "--- main --- ");
    // std::cout << std::endl;
    tab = main_chain;
} 

void  checker_tab(std::vector<int> &tab)
{ 
    const std::string GREEN = "\033[32m";
    const std::string RED   = "\033[31m";
    const std::string RESET = "\033[0m";
    if(tab.size() == 1)
        std::cout << GREEN << "[OK sort]" << RESET;
    for(int i = 0; i < tab.size() - 1; i++)
    { 
        int j = i + 1;
        if(tab[i] > tab[j])
            std::cout << RED << "[FAIL sort] " << RESET;
    }
    std::cout << GREEN << "[OK]" << RESET <<  std::endl; 
}

void checker_count(std::vector<int>& tab, int size)
{
    const std::string GREEN = "\033[32m";
    const std::string RED   = "\033[31m";
    const std::string RESET = "\033[0m";
    
    if(tab.size() != size)
    {
        std::cout << RED << "[FAIL] count : [" << tab.size() \
        << "] init_count : [" << size << "]" <<  RESET << std::endl;
    }
    else
    {
        std::cout << GREEN << "[OK] count : [" << tab.size() \
        << "] init_count : [" << size << "]" <<  RESET << std::endl;
    }
}

int main(int argc, char **argv)
{ 
    std::vector<int> tab;
    int size; 
    if(argc < 2)
        return(std::cout << "Error" << std::endl, 0);
    if(recup_argc(tab, argc, argv) == false)
        return(std::cout << "Error" << std::endl, 0);
    size = tab.size();    
    if(tab.size() == 1)
    {
        checker_tab(tab);
        checker_count(tab,size);
        return(0);
    }
    Ford_johnson(tab);
    checker_tab(tab);
    checker_count(tab, size);
}


// int main(int argc, char **argv) {
//     // Optimisation des entrées/sorties pour supporter 1 000 000 d'éléments sans ralentissement
//     std::ios_base::sync_with_stdio(false);
//     std::cin.tie(NULL);

//     std::vector<int> numbers;

//     if (argc > 1) {
//         // MODE 1 : Lecture classique via argv
//         for (int i = 1; i < argc; ++i) {
//             try {
//                 size_t pos;
//                 int val = std::stoi(argv[i], &pos);
//                 if (argv[i][pos] != '\0' || val < 0) {
//                     std::cout << "Error" << std::endl;
//                     return 1;
//                 }
//                 numbers.push_back(val);
//             } catch (...) {
//                 std::cout << "Error" << std::endl;
//                 return 1;
//             }
//         }
//     } else {
//         // MODE 2 : Lecture via std::cin (pour les très grands ensembles)
//         std::string input;
//         while (std::cin >> input) {
//             try {
//                 size_t pos;
//                 int val = std::stoi(input, &pos);
//                 if (input[pos] != '\0' || val < 0) {
//                     std::cout << "Error" << std::endl;
//                     return 1;
//                 }
//                 numbers.push_back(val);
//             } catch (...) {
//                 std::cout << "Error" << std::endl;
//                 return 1;
//             }
//         }
//     }

//     // Gestion du cas vide
//     if (numbers.empty()) {
//         std::cout << "Error" << std::endl;
//         return 1;
//     }

//     int initial_size = numbers.size();

//     // Cas d'un seul élément
//     if (numbers.size() == 1) {
//         checker_tab(numbers);
//         checker_count(numbers, initial_size);
//         return 0;
//     }

//     // Exécution du tri Ford-Johnson
//     Ford_johnson(numbers);

//     // Vérification du tri et de la taille pour tes scripts Shell
//     checker_tab(numbers);
//     checker_count(numbers, initial_size);

//     return 0;
// }