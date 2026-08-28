/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 18:21:04 by aoesterl          #+#    #+#             */
/*   Updated: 2026/08/28 20:41:31 by aoesterl         ###   ########.fr       */
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

// void Ford_johnson(std::vector<int>& tab, int bloc_size = 1)
// {
//     int group = 2 * bloc_size; // nouveau groupe de pair (si on a des paires de 2, le nouveau groupe sera 4)
//     // int nb_pairs = tab.size()/bloc_size; // nombre de pairs
//     bool odd = tab.size()/bloc_size % 2 == 1; // renvoie true si nb_pairs = impair, false si pair

//     if(tab.size()/bloc_size == 1)
//         return;
//     // if(odd == true)
//     //     std::cout << "true" << std::endl;
//     // else
//     //     std::cout << "false" << std::endl;
//     for(int i = 0; i < tab.size()/ group; i++)
//     { 
//         int first = group * i + (bloc_size - 1); // 1er sous groupe
//         int second = group * i + (group - 1);
//         // std::cout << "first = " << first << std::endl;
//         // std::cout << "second = " <<  second << std::endl; // 2eme sous groupe
//         if(tab[first] > tab[second])
//             switch_group(tab, group * i, bloc_size);
//     }
//     print_array(tab, "--- after --- ");

//     Ford_johnson(tab, 2 * bloc_size);

//     int nb_pairs = tab.size()/group;
//     std::vector<int> main_chain;
//     std::vector<int> pending;
//     for(int i = 0; i < nb_pairs; i++)
//     { 
        

        
//     }
    
    
// }

void Ford_johnson(std::vector<int>& tab, int bloc_size = 1)
{
    int group = 2 * bloc_size; // nouveau groupe de pair (si on a des paires de 2, le nouveau groupe sera 4)
    bool odd = tab.size()/bloc_size % 2 == 1; // renvoie true si nb_pairs = impair, false si pair

    if(tab.size()/bloc_size == 1)
        return;
    // if(odd == true)
    //     std::cout << "true" << std::endl;
    // else
    //     std::cout << "false" << std::endl;
    for(int i = 0; i < tab.size()/ group; i++)
    { 
        int first = group * i; // 1er sous groupe
        int second = group * i + bloc_size; 
        // std::cout << "first = " << first << std::endl;
        // std::cout << "second = " <<  second << std::endl; // 2eme sous groupe
        if(tab[first] < tab[second])
            switch_block_size(tab, group * i, bloc_size);
    }
    print_array(tab, "--- after --- ");

    Ford_johnson(tab, 2 * bloc_size);

    std::vector<int> main_chain;
    std::vector<int> pending;
    for(int i; i < tab.size()/group; i++)
    { 
        int first = group * i;
        int second = group * i + bloc_size;
        for(int i = 0; i < bloc_size; i++)
        { 
            main_chain.push_back(tab[first]);
            pending.push_back(tab[second]);
        }
    }
    
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