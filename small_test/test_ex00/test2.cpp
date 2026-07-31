/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 19:20:39 by aoesterl          #+#    #+#             */
/*   Updated: 2026/07/20 20:29:41 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <cctype>
#include <iostream>

void is_formatted(std::string& line, char c)
{ 
    std::string::iterator it;
    it = line.begin(); 
    while(it != line.end())
    { 
        if(std::isspace(*it))
            it = line.erase(it);
        else
            it++;
    }
}

int main()
{ 
    std::string line = "          j'aime  ,  les pommes    ";
    is_formatted(line, ',');
    std::string::size_type n;
    n = line.find(',');
    if(n == std::string::npos)
        std::cout << "gros troll" << std::endl;
    std::string s1 = line.substr(0, n);
    std::string s2 = line.substr(n + 1);
    std::cout  << s1 << std::endl;
    std::cout <<  s2 << std::endl;
    std::cout << n << std::endl;
    std::cout << line << std::endl;
}