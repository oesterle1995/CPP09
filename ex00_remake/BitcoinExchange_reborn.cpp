/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange_reborn.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 17:18:30 by aoesterl          #+#    #+#             */
/*   Updated: 2026/07/27 12:56:36 by aoesterl         ###   ########.fr       */
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
    oss << "Error : data.csv => line : " <<  nb_line;
    oss << " => " << msg_error << " => Currently : " << line << std::endl;
    throw std::logic_error(oss.str());
}

void BitcoinExchange::error_msg_datatxt(const std::string& line, int nb_line, std::string msg_error)
{
    (void) line;
    (void) nb_line;
    std::cerr << "Error:" << msg_error << std::endl;
    throw std::logic_error("Error : " + msg_error + " =>" + line);
}

bool BitcoinExchange::parsing_date(const std::string& s1, ptr_ft ft_error, int nb_line)
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
        return(ft_error(s1, nb_line, "bad input date"), false);
    if(valid_date(year, month, day) == false)
        return(ft_error(s1, nb_line, "invalid date"), false);
    return(true);
}

bool BitcoinExchange::parsing_value(const std::string& s2, ptr_ft ft_error, int nb_line, bool check_limits)
{
    double value;
    char extra;
    std::istringstream is(s2);
    is >> value;
    if(is.fail() || (is >> extra))
        return(ft_error(s2, nb_line, "bad input number"), false);
    if(check_limits == true)
    {
        if(value < 0 || value > 1000)
            return(ft_error(s2, nb_line, "number is too large"), false);
    }
    return(true);
}

bool BitcoinExchange::substr_s1_s2(const std::string line, std::string& s1, std::string&s2, char delim)
{
    size_t pos;
    pos = line.find(delim);
    if(pos == std::string::npos)
        throw std::logic_error("Error : bad input => " + line);
    s1 = line.substr(0, pos);
    s2 = line.substr(pos + 1);
    std::istringstream is_s1(s1);
    is_s1 >> s1;
    std::istringstream is_s2(s2);
    is_s2 >> s2;
    return(true);
}

bool BitcoinExchange::analyse_line(const std::string& line, map_pair_type& pair, \
    const std::string& head_s1,const std::string& head_s2, int nb)
{
    std::string s1;
    std::string s2;
    double value;
    int begin = 0;
    try 
    {
        substr_s1_s2(line, s1, s2, ',');
        if(s1 == head_s1 && s2 == head_s2)
        {
            if(begin != 0)
                throw std::logic_error("header duplication detected");
            begin = 1;
        }
        parsing_date(s1, &throw_datacsv, nb);
        parsing_value(s2, &error_msg_datatxt, nb);
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return(false);
    }
    value = std::strtod(s2.c_str(), NULL);
    pair = std::make_pair(s1, value);
    return(true);
}

bool BitcoinExchange::download_price_map(std::ifstream& input_stream)
{
    std::string line;
    map_pair_type pair;
    int nb;
    bool good = true;
    while(std::getline(input_stream, line))
    {
        nb++;
        if(line.empty() || line.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
            continue;
        if(analyse_line(line, pair, "date",  "exchange", nb) == false)
        {
            good = false;
            continue;
        }
        this->_database.insert(pair);
    }
    if(good == false)
        return(std::cerr << "DATA.CSV CORRUPTED, END OF THE PROGRAMM" << std::endl, false);
    return(true);
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

// void BitcoinExchange::display_result_btc(std::ifstream& file_value, std::string filename)
// { 
//     std::string line;
//     double res;
//     map_str_d::const_iterator it;
//     while(std::getline(file_value, line))
//     {
        
//     }
// }

// bool BitcoinExchange::download_price_map(std::ifstream& input_stream, std::string filename)
// {
//     std::string line;
//     std::string s1;
//     std::string s2;
//     int flag_error = 0;
//     int begin = 0;
//     while(std::getline(input_stream, line))
//     {
//         if(line.empty() || line.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
//             continue;
//         try 
//         {
//             substr_s1_s2(line, s1, s2, ',');
//             if(s1 == "date" && s2 == "exchange")
//             {
//                 if(begin != 0)
//                     throw (std::cerr << "double line in data.csv : date,exchange_rate");
//                 begin = 1;
//             }
//             parsing_date(s1, &throw_datacsv);
//             parsing_value(s2, &error_msg_datatxt);
//         }
//         catch(std::exception& e)
//         { 
//             flag_error = 1;
//             std::cerr << e.what() << std::endl;
//         }
        
//     }
//     if(flag_error == 1)
//         return(std::cerr << "DATA.CSV CORRUPTED, END OF THE PROGRAMM" << std::endl, false);
//     return(true);
// }




//faire une paire de cle avec une focntion pour uniformiser




// bool BitcoinExchange::download_price_map(std::ifstream& input_stream, std::string filename)
// {
//     std::string line;
//     std::string s1;
//     std::string s2;
//     int flag_error = 0;
//     int begin = 0;
//     while(std::getline(input_stream, line))
//     {
//         if(line.empty() || line.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
//             continue;
//         analyse_line
//     }
//     if(flag_error == 1)
//         return(std::cerr << "DATA.CSV CORRUPTED, END OF THE PROGRAMM" << std::endl, false);
//     return(true);
// }