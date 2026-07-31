/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 14:56:59 by aoesterl          #+#    #+#             */
/*   Updated: 2026/07/22 21:07:24 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <sstream>

typedef std::map<std::string, float> map_str_d;

std::string format_error_msg(int line_num, const std::string& filename, double invalid_val)
{ 
    std::ostringstream os; 
    os << line_num << filename << invalid_val;
    std::string msg = os.str();
    return(msg);
}

int main()
{ 
    int line_num = 12;
    std::string filename = "input.txt";
    double invalid_val = -5.5;
    std::cout << format_error_msg(line_num, filename, invalid_val) << std::endl;
}




// int main()
// { 
//     std::string s1 = "2001-12-25";
//     std::string s2 = "2001-12-25";
//     float nb = 1.2556;
//     float nb2 = 4165;
//     std::map<std::string, float> map1;
//     std::map<std::string, float>::value_type pair(s1, nb);
//     std::pair<std::string, float> pair2;
//     pair2.first = s2;
//     pair2.second = nb2;
//     std::pair<map_str_d::iterator, bool> result;
//     map1.insert(pair);
//     result = map1.insert(pair2);
//     if(result.second == false)
//         std::cout << "doublon detected" << std::endl;
//     map_str_d::iterator it;
//     it = map1.find("200112-25");
//     if(it == map1.end())
//         std::cout << "not found" << std::endl;
//     std::cout << it->second << std::endl;
    
// }