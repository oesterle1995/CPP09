/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 18:34:47 by aoesterl          #+#    #+#             */
/*   Updated: 2026/08/14 20:21:13 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>
#include <vector>

typedef struct s_pair
{
    int a;
    int b;
}t_pair;


int main(int argc, char **argv)
{
    std::vector<t_pair> v_pair;
    std::string str_arg;
    int a;
    int b;
    for(int i = 0; i < argc; i++)
    { 
        str_arg += argv[i];
        str_arg += " ";
    }
    std::istringstream is(str_arg);
    while(1)
    { 
        

    }

    
}