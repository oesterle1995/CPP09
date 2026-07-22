/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 16:19:19 by aoesterl          #+#    #+#             */
/*   Updated: 2026/07/22 20:21:46 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>


bool valid_date(int year, int month, int day)
{ 
   int d_month[13] = {0, 31, 28, 31, 30, 31, 30, 31 , 31 ,30, 31, 30, 31};
    if(year < 2009 || month < 1 || month > 12 ||  day < 1)
    { 
        return(false);
    }
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    { 
        d_month[2] = 29;
        std::cout << "bisextile year !" << std::endl;
    }
    if(day > d_month[month])
    { 
        return(false);
    }
    return(true);
} 


void is_formatted(std::string& line, int& nb_line, char delim)
{
    if(line.empty() || line.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
        return;
    int year;
    int month;
    int day;
    char dash1;
    char dash2;
    char sep;
    float value;
    char extra;
    std::istringstream is(line);
    is >> year >> dash1 >> month >> dash2 >> day >> sep >> value;
    
    if(is.fail() || dash1 != '-' || dash2 != '-' || sep != delim || (is >> extra))
    { 
        throw std::logic_error("Error : line " + std::to_string(nb_line) + " : Format line is : YYYY-MM-DD"\
        + delim + "value(float) | Currently this line is :" + line);
    }
    if(valid_date(year, month, day) == false)
        std::cout << "fausse date" << std::endl;
    else
        std::cout << "bonne date" << std::endl;
} 

int main()
{ 
    std::string str = "2015-02-29,1.2";
    int nb = 0;
    is_formatted(str, nb, ',');
    std::string test =  "48.5";
    double nbr = std::strtod(test.c_str(), NULL);
    std::cout << nbr << std::endl;
    
}