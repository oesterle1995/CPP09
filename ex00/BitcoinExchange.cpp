/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 17:18:30 by aoesterl          #+#    #+#             */
/*   Updated: 2026/07/22 22:10:05 by aoesterl         ###   ########.fr       */
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

bool BitcoinExchange::valid_date(int year, int month, int day)
{ 
   int d_month[13] = {0, 31, 28, 31, 30, 31, 30, 31 , 31 ,30, 31, 30, 31};
    if(year < 2009 || month < 1 || month > 12 ||  day < 1)
    { 
        return(false);
    }
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        d_month[2] = 29;
    if(day > d_month[month])
    { 
        return(false);
    }
    return(true);
} 

bool BitcoinExchange::is_formatted(const std::string& line, const int& nb_line, std::string& filename, const char delim)
{
    int year;
    int month;
    int day;
    char dash1;
    char dash2;
    char sep;
    double value;
    char extra;
    std::istringstream is(line);
    is >> year >> dash1 >> month >> dash2 >> day >> sep >> value;
    
    if(line == "date,exchange_rate" || line == "date | value")
        return(false);
    if(line.empty() || line.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
        return(false);
    if(is.fail() || dash1 != '-' || dash2 != '-' || sep != delim || (is >> extra))
    {
        std::cerr << "Error : File : " << filename <<  " line :" << nb_line << " : Format line is : YYYY-MM-DD" \
        << delim << "value(float) | Currently this line is : " << line << std::endl;
        return(false);
    }
    if(valid_date(year, month, day) == false)
    { 
        std::cerr << "Error : File : " << filename <<  " line : " << nb_line \
        << " the date is unvalid (before 2009) or doesn't exist | Currently this line is : " << line << std::endl;
        return(false);
    }
    else
        return(true);
} 

void BitcoinExchange::fill_data(const std::string& line)
{
    std::string s1;
    std::string s2;
    double nb;
    int n;
    n = line.find(',');
    s1 = line.substr(0, n);
    s2 = line.substr(n + 1);
    nb = std::strtod(s2.c_str(), NULL);
    this->_database.insert(std::make_pair(s1, nb));
}

void BitcoinExchange::download_price_map(std::ifstream& input_stream, std::string filename)
{ 
   std::string line;
   int nb_line = 0;
   while(std::getline(input_stream, line))
    {
        nb_line++;
        if(line.empty() || line.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
            continue;
        if(is_formatted(line, nb_line, filename, ',') == false)
            continue;
        fill_data(line);
    }
}

map_str_d::const_iterator BitcoinExchange::get_data_value(const std::string& key) const
{ 
    map_str_d::const_iterator it;
    it = this->_database.find(key);
    return(it);
}

map_str_d::const_iterator BitcoinExchange::end() const
{ 
    return(this->_database.end());
}