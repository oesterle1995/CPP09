/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retry.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurito <arthurito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 17:18:30 by aoesterl          #+#    #+#             */
/*   Updated: 2026/07/31 16:20:33 by arthurito        ###   ########.fr       */
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
        return(false);
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        d_month[2] = 29;
    if(day > d_month[month])
        return(false);
    return(true);
}

void BitcoinExchange::throw_datacsv(const std::string& line, int nb_line, std::string msg_error)
{ 
    std::ostringstream oss;
    oss << "Error: data.csv => line : " <<  nb_line;
    oss << " => " << msg_error << " => Currently : " << line << std::endl;
    throw std::logic_error(oss.str());
}

void BitcoinExchange::throw_input_file(const std::string& line, int nb_line, std::string msg_error)
{
    (void) nb_line;
    if(nb_line == 1)
        throw std::logic_error("Error: " + msg_error + " => " + line);
    if(nb_line == 0)
        throw std::logic_error("Error: " + msg_error);
}

int BitcoinExchange::parsing_date(const std::string& s1, ptr_ft ft_error, int nb_line)
{
    int year;
    int month;
    int day;
    char dash1;
    char dash2;
    char extra;
    std::istringstream is(s1);
    is >> year >> dash1 >> month >> dash2 >> day;
    if(is.fail() || dash1 != '-' || dash2 != '-' || is >> extra)
        ft_error(s1, nb_line, "bad input date");
    if(valid_date(year, month, day) == false)
        ft_error(s1, nb_line, "invalid date");
    return(TRUE);
}

int BitcoinExchange::parsing_value(const std::string& s2, ptr_ft ft_error, int nb_line)
{
    double value;
    char extra;
    std::istringstream is(s2);
    is >> value;
    if(is.fail() || (is >> extra))
        ft_error(s2, nb_line, "bad input number");
    return(TRUE);
}

int BitcoinExchange::substr_s1_s2(const std::string line, ptr_ft ft_error, std::string& s1, std::string&s2, \
    char delim, int nb_line)
{
    size_t pos;
    pos = line.find(delim);
    if(pos == std::string::npos)
       ft_error(line, nb_line, "bad input");
    s1 = line.substr(0, pos);
    s2 = line.substr(pos + 1);
    std::istringstream is_s1(s1);
    is_s1 >> s1;
    std::istringstream is_s2(s2);
    is_s2 >> s2;
    return(TRUE);
}

int BitcoinExchange::analyse_line_data(const std::string& line, map_pair_type& pair, int nb_line)
{
    std::string s1;
    std::string s2;
    double value;
    try 
    {
        substr_s1_s2(line, &throw_datacsv, s1, s2, ',', nb_line);
        if(s1 == "date" && s2 == "exchange_rate")
            return(PASS);
        parsing_date(s1, &throw_datacsv, nb_line);
        parsing_value(s2, &throw_datacsv,  nb_line);
        value = std::strtod(s2.c_str(), NULL);
        if(value < 0)
            throw_datacsv(s2, nb_line, "not a positive number");
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return(FALSE);
    }
    pair = std::make_pair(s1, value);
    return(TRUE);
}

int BitcoinExchange::analyse_input_line(const std::string& line, map_pair_type& pair)
{
    std::string s1;
    std::string s2;
    double value;
    try 
    {
        substr_s1_s2(line, &throw_input_file, s1, s2, '|', 1);
        if(s1 == "date" && s2 == "value")
            return(PASS);
        parsing_date(s1, &throw_input_file, 0);
        parsing_value(s2, &throw_input_file,  0);
        value = std::strtod(s2.c_str(), NULL);
        if(value > 1000)
            throw_input_file(s2, 0, "number is too large");
        if(value < 0)
            throw_input_file(s2, 0, "not a positive number");
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return(FALSE);
    }
    pair = std::make_pair(s1, value);
    return(TRUE);
}

int BitcoinExchange::download_price_map(std::ifstream& ifs_data)
{
    std::string line;
    map_pair_type pair;
    int nb_line = 0;
    int ret; 
    int good = TRUE;
    while(std::getline(ifs_data, line))
    {
        nb_line++;
        if(line.empty() || line.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
            continue;
        ret = analyse_line_data(line, pair, nb_line);
        if(ret == FALSE || ret == PASS)
        {
            if(ret == FALSE)
                good = FALSE;
            continue;
        }
        this->_database.insert(pair);
    }
    if(good == FALSE)
        return(std::cerr << "DATA.CSV CORRUPTED, END OF THE PROGRAMM" << std::endl, false);
    return(TRUE);
}

void  BitcoinExchange::display_result_btc(std::ifstream& ifs_txt)
{
    std::string line;
    map_pair_type pair;
    map_str_d::const_iterator it;
    int ret;
    double res; 
    while(std::getline(ifs_txt, line))
    {
        if(line.empty() || line.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
            continue;
        ret = analyse_input_line(line, pair);
        if(ret == FALSE || ret == PASS)
            continue;
        it = get_data_value(pair.first);
        res = pair.second * it->second;
        std::cout << pair.first << " => " << pair.second << " = " << res << std::endl;
    }
}

map_str_d::const_iterator BitcoinExchange::get_data_value(const std::string& key) const
{ 
    map_str_d::const_iterator it;
    it = this->_database.find(key);
    if(it == _database.end())
    {
        it = _database.lower_bound(key);
        if(it == _database.begin())
            return(it);
        else
        {
            it--;
            return(it);
        }
    }
    return(it);
}

map_str_d::const_iterator BitcoinExchange::end() const
{ 
    return(this->_database.end());
}

