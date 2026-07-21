/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 17:34:32 by aoesterl          #+#    #+#             */
/*   Updated: 2026/07/21 20:45:56 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{ 
    return;
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& cpy) : _database(cpy._database)
{ 
    return;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& obj)
{ 
    if(this != &obj)
    { 
        _database = obj._database;
    }
    return(*this);
}

BitcoinExchange::~BitcoinExchange()
{ 
    return;
}


void BitcoinExchange::normalize_space(std::string& line)
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

void BitcoinExchange::check_data_format(std::string s1, std::string s2)
{ 
    

    
}

map_pair_type BitcoinExchange::is_formatted(std::string& line, char c)
{
    map_pair_type pair;
    std::string::size_type n;
    std::string s1;
    std::string s2;
    
    normalize_space(line);
    n = line.find(c);
    if(n == std::string::npos)
        throw std::logic_error("Error : Bad format file.csv : line format : YYYY-MM-DD , value");
    s1 = line.substr(0, n);
    s2 = line.substr(n + 1);
}

void BitcoinExchange::fill_price_map(map_str_f& _database, std::string line)
{ 
    is_formatted(line, ',');
    { 
        std::string msg = "Error : Format line isn't good in the csv :" + line;
        throw std::logic_error(msg); 
    } 
}

void BitcoinExchange::download_price_map(std::ifstream& input_stream)
{ 
   std::string line;
   while(std::getline(input_stream, line))
    {
        if(line.empty() || line.find_first_not_of(" \t\n\v\f\r\n") == std::string::npos)
            continue;
        std::cout << line << std::endl;
        fill_price_map(this->_database, line);
    }
}