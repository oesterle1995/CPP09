/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 18:34:47 by aoesterl          #+#    #+#             */
/*   Updated: 2026/08/18 18:51:29 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <vector>
#include <climits>

typedef struct s_pair
{
    int a;
    int b;
}t_pair;


bool is_valid_number(const std::string& str_arg)
{
    long nb;
    int count = 0;
    std::istringstream is(str_arg);
    while(is >> nb)
    { 
        if(nb < 0 || nb > INT_MAX)
            return false;
        count++;
    }
    if(!is.eof() || !count)
    { 
        std::cout << "error detected" << std::endl;
        return false;
    }
    return(true);
}


void new_pair(t_pair& pair, int val1, int val2)
{  
    if(val1 > val2)
    { 
        pair.a = val1;
        pair.b = val2;   
    }
    else
    { 
        pair.a = val2;
        pair.b = val1;
    }
}

std::vector<t_pair> create_pair_tab(std::vector<int>& v_tab)
{
    std::vector<t_pair> v_pair;
    std::vector<int>::iterator it;
    t_pair pair;
    int size = v_tab.size();
    int i = 1;
    std::cout << "--- size v_tab --- " << std::endl;
    std::cout << size << std::endl;
    it = v_tab.begin();
    if(size % 2 == 0)
    { 
        for(int i = 0; i < size; i +=2)
        { 
            new_pair(pair, *(it), *(it + 1));
            it += 2;
            v_pair.push_back(pair);
        }
    }
    else
    { 
        for(int i = 1; i < size; i +=2)
        { 
            new_pair(pair, *(it), *(it + 1));
            it += 2;
            v_pair.push_back(pair);
        }
    }
    return(v_pair);
}

std::vector<int> Ford_johnson_algorithm(std::vector<int> v_tab)
{ 
    std::vector<t_pair> v_pair;
    v_pair = create_pair_tab(v_tab);
    std::vector<t_pair>::iterator it = v_pair.begin();
    std::cout << "--- a : BIGGEST v_pair ---  " << std::endl;
    while(it != v_pair.end())
    { 
        std::cout << (*it).a << " | ";
        it++;
    }
     it = v_pair.begin();
    std::cout << std::endl << "--- b : SMALLEST v_pair ---  " << std::endl;
    while(it != v_pair.end())
    { 
        std::cout << (*it).b << " | ";
        it++;
    }
    std::cout << std::endl;
    return(v_tab);
}

void print_array(const std::vector<int>& tab)
{ 
    std::vector<int>::const_iterator it;
    it = tab.begin();
    while(it != tab.end())
    { 
        std::cout << "---- printf ----- " << std::endl;
        std::cout << *it << std::endl;
        it++;
    }
}

int main(int argc, char **argv)
{
    std::vector<int> v_tab;
    std::string str_arg;
    int nb;
    for(int i = 1; i < argc; i++)
    { 
        str_arg += argv[i];
        str_arg += " ";
    }
    if(!is_valid_number(str_arg))
        return(std::cout << "Wrong args" << std::endl, 0);
    std::istringstream is(str_arg);
    while(is >> nb)
        v_tab.push_back(nb);
    print_array(v_tab);
    Ford_johnson_algorithm(v_tab);
}






















// int main(int argc, char **argv)
// { 
//     std::string str_arg;
//     int a;
//     int b;
//     bool ret;
//     for(int i = 1; i < argc; i++)
//     { 
//         str_arg += argv[i];
//         str_arg += " ";
//     }
//     ret = is_valid_number(str_arg);
//     if(ret == true)
//         std::cout << "ok" << std::endl;
//     if(ret == false)
//         std::cout << "false" << std::endl;
// }
