/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 18:14:07 by aoesterl          #+#    #+#             */
/*   Updated: 2026/07/22 22:08:13 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <utility>
#include <cstdlib>
#include <sstream>
#define ERROR -1

typedef std::map<std::string,double> map_str_d;
typedef std::pair<std::string, double> map_pair_type;

class BitcoinExchange
{
    private :
        map_str_d _database;
        bool valid_date(int year, int month, int day);
        bool is_formatted(const std::string& line, const int& nb_line, std::string& filename, const char delim);
        void fill_data(const std::string& line);
    public:

        //Canonnic form
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& cpy);
        BitcoinExchange& operator=(const BitcoinExchange& obj);
        ~BitcoinExchange();

        //function
        void download_price_map(std::ifstream& input_stream, std::string filename);

        //Getter
        map_str_d::const_iterator get_data_value(const std::string& key) const;
        map_str_d::const_iterator end() const;
};
