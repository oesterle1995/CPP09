/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 16:06:45 by aoesterl          #+#    #+#             */
/*   Updated: 2026/08/26 19:41:03 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <vector>
#include <climits>
#include <iomanip>

//#1 PARSING
bool is_valid_number(const std::string &str, std::vector<int>& tab)
{ 
    int nb;
    int count = 0;
    std::istringstream iss(str);
    while(iss >> nb)
    { 
        if(nb < 0 || nb > INT_MAX)        
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
 



std::vector<int> generate_jacob_order(std::vector<int> tab)
{ 
    std::vector<int> order;
    int J_prev = 1;
    int J_curr = 3;
    int J_next;
    order.push_back(1); 
    while(order.size() != tab.size())
    {   
        J_next = 2 


    }
}

void Ford_johnson(std::vector<int>& tab, std::vector<int>& idx)
{
    print_array(idx, "--- basic index tab ---");
    print_array(tab, "--- value tab ---");
    if(tab.size() == 1)
    { 
        return;
    }
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
        main_idx.push_back(idx[new_idx[i] * 2]);
    for(int i = 0; i < new_idx.size(); i ++)
        small_idx.push_back(idx[new_idx[i] + 1]);
    if(idx.size() % 2 != 0)
        small_idx.push_back(idx[idx.size() - 1]);
    std::vector<int> jacob_order = generate_jacob_order(small_idx);
    
    
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
}