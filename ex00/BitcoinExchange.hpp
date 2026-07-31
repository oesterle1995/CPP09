/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurito <arthurito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 18:14:07 by aoesterl          #+#    #+#             */
/*   Updated: 2026/07/31 16:21:46 by arthurito        ###   ########.fr       */
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
#define TRUE 1
#define FALSE 0
#define PASS 2

typedef std::map<std::string,double> map_str_d;
typedef std::pair<std::string, double> map_pair_type;

class BitcoinExchange
{
    private :
        std::map<std::string,double> _database;
        typedef  void (*ptr_ft)(const std::string& line, int nb_line, std::string msg_error);
        
        //ft_error_message
        static void throw_datacsv(const std::string& line, int nb_line, std::string msg_error);
        static void throw_input_file(const std::string& line, int nb_line, std::string msg_error);
        
        //ft classic
        bool valid_date(int year, int month, int day);
        int parsing_date(const std::string& s1, ptr_ft ft_error, int nb_line);
        int parsing_value(const std::string& s2, ptr_ft ft_error, int nb_line);
        int substr_s1_s2(const std::string line, ptr_ft ft_error, \
            std::string& s1, std::string&s2, char delim, int nb_line);
        int analyse_line_data(const std::string& line, map_pair_type& pair, int nb_line);
        int analyse_input_line(const std::string& line, map_pair_type& pair);
    public:
    
        //Canonnic form
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& cpy);
        BitcoinExchange& operator=(const BitcoinExchange& obj);
        ~BitcoinExchange();
        
        //function
        int download_price_map(std::ifstream& ifs_data);
        void display_result_btc(std::ifstream& ifs_txt);
        map_str_d::const_iterator get_data_value(const std::string& key) const;
        map_str_d::const_iterator end() const;
};      
