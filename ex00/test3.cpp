/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:56:59 by aoesterl          #+#    #+#             */
/*   Updated: 2026/07/21 20:04:01 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <map>
#include <string>
#include <utility>

typedef std::map<std::string, float> map_str_f;

int main()
{ 
    std::string s1 = "2001-12-25";
    std::string s2 = "2001-12-25";
    float nb = 1.2556;
    float nb2 = 4165;
    std::map<std::string, float> map1;
    std::map<std::string, float>::value_type pair(s1, nb);
    std::pair<std::string, float> pair2;
    pair2.first = s2;
    pair2.second = nb2;
    std::pair<map_str_f::iterator, bool> result;
    map1.insert(pair);
    result = map1.insert(pair2);
    if(result.second == false)
        std::cout << "doublon detected" << std::endl;
    map_str_f::iterator it;
    it = map1.find("200112-25");
    if(it == map1.end())
        std::cout << "not found" << std::endl;
    std::cout << it->second << std::endl;
    
}