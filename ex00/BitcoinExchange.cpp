/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 17:34:32 by aoesterl          #+#    #+#             */
/*   Updated: 2026/07/20 21:36:32 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{ 
    return;
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& cpy) : _data_csv(cpy._data_csv)
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

bool BitcoinExchange::is_formatted(map_str_f& _database, std::string& line, char c)
{ 
    normalize_space(line);
    std::string::size_type n;
    std::string s1;
    std::string s2;
    n = line.find(",");
    if(n == std::string::npos)
        throw std::logic_error("Error : Bad format file.csv : line format : YYYY-MM-DD,value");
    s1 = line.substr(0, n);
    s2 = line.substr(n + 1);
    fill
}

void BitcoinExchange::fill_price_map(map_str_f& _database, std::string line)
{ 
    if(is_formatted(line, ',') == true)
    { 
        


    }
    else
    { 
        std::string msg;
        msg = "Error : Format line isn't good in the csv :" + line;
        throw std::logic_error(msg); 
    } 
}

void BitcoinExchange::download_price_map(std::ifstream& input_stream)
{ 
   std::string line;
   while(std::getline(input_stream, line))
   { 
        std::cout << line << std::endl;
        fill_price_map(this->_database, line);
   }
}