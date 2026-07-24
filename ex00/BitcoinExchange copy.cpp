/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange copy.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 17:18:30 by aoesterl          #+#    #+#             */
/*   Updated: 2026/07/24 22:21:58 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

typedef struct s_info_msg
{ 

}t_info_msg;

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

void throw_datacsv(std::string& filename, const std::string& line, int nb_line, std::string msg_error)
{ 
    std::ostringstream oss;
    oss << "Error : " << std::endl;
    oss << "File : " << filename <<  "line :" << nb_line << std::endl;
    oss << "Problem : " << msg_error << std::endl;
    oss << "Currently this line is : " << line << std::endl;
    throw std::logic_error(oss.str());
}
void error_txt(std::string& filename, const std::string& line, int nb_line, std::string msg_error)
{
    (void) filename;
    (void) line;
    (void) nb_line;
    std::cerr << "Error : " << msg_error << std::endl;
}

bool BitcoinExchange::is_formatted(const std::string& line, ptr_ft_err_msg ft_error, \
    std::string& filename, int nb_line, char delim, bool check_limits = false)
{
    int year;
    int month;
    int day;
    char dash1;
    char dash2;
    char sep;
    double value;
    char extra;
    
    int fail_ft = 0;
    std::string msg_error;
    std::istringstream is(line);
    is >> year >> dash1 >> month >> dash2 >> day >> sep >> value;
    
    if(line == "date,exchange_rate" || line == "date | value")
        return(false);
    if(line.empty() || line.find_first_not_of(" \t\n\v\f\r") == std::string::npos)
        return(false);
    if(check_limits == true)
    { 
        if(value < 0 || value > 1000)
            return(ft_error(filename, line, nb_line, "number is too large"), false);
    }
    if(is.fail() || dash1 != '-' || dash2 != '-' || sep != delim || (is >> extra))
    {
        return(ft_error(filename, line, nb_line, "Bad input"),false);
        // // msg_error = " : Format line is : YYYY-MM-DD,value(float)";
        // throw_datacsv(filename, line, nb_line, delim,  msg_error);
    }
    if(valid_date(year, month, day) == false)
    {
        // msg_error = " unvalid date;
        return(ft_error(filename, line, nb_line, "Bad input"), false);
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
    std::istringstream is(s1);
    is >> s1;
    nb = std::strtod(s2.c_str(), NULL);
    this->_database.insert(std::make_pair(s1, nb));
}

bool BitcoinExchange::download_price_map(std::ifstream& input_stream, std::string filename)
{ 
   std::string line;
   bool ret;
   int flag_error = 0;
   int nb_line = 0;
   while(std::getline(input_stream, line))
    {
        nb_line++;
        try
        { 
            ret = is_formatted(line, &throw_datacsv, filename, nb_line, ',');
            if(ret == true)
                fill_data(line);  
        }
        catch(std::exception& e)
        { 
            flag_error = 1;
            std::cerr << e.what() << std::endl;
        }
    }
    if(flag_error == 1)
    { 
        std::cerr << "DATA.CSV CORRUPTED, END OF THE PROGRAMM" << std::endl;
        return(false);
    }
    return(true);
}

    
void BitcoinExchange::display_result_btc(std::ifstream& file_value, std::string filename)
{ 
    std::string line;
    std::string s1;
    std::string s2;
    double nb_btc;
    double res;
    map_str_d::const_iterator it;
    size_t pos;
    while(std::getline(file_value, line))
    {
        if(is_formatted(line, &error_txt, filename, 0, '|') == false)
            continue;
        pos = line.find('|');
        s1 = line.substr(0, pos);
        s2 = line.substr(pos + 1);
        std::istringstream is (line);
        is >> s1;
        nb_btc = std::strtod(s2.c_str(), NULL);
        it = get_data_value(s1);
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