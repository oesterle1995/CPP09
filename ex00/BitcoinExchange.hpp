/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 18:14:07 by aoesterl          #+#    #+#             */
/*   Updated: 2026/07/21 20:21:14 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <utility>
#define ERROR -1

typedef std::map<std::string,float> map_str_f;
typedef std::pair<std::string, float> map_pair_type;

class BitcoinExchange
{
    private :
        map_str_f _database;
        void normalize_space(std::string& line);
        void check_data_format(std::string s1, std::string s2);
        map_pair_type is_formatted(std::string& line, char c);
        void fill_price_map(map_str_f& _database, std::string line);
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& cpy);
        BitcoinExchange& operator=(const BitcoinExchange& obj);
        ~BitcoinExchange();
        void download_price_map(std::ifstream& input_stream);
};
