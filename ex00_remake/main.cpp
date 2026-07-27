/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 17:46:29 by aoesterl          #+#    #+#             */
/*   Updated: 2026/07/26 22:09:10 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if(argc <= 1 )
        return(std::cerr << "Error: could not open file" << std::endl, ERROR);
    BitcoinExchange Bit_price;
    std::ifstream file_price("data.csv");
    std::ifstream file_value(argv[1]);
    if(!file_price.is_open() || !file_value.is_open())
           return(std::cerr << "Error: could not open file" << std::endl, ERROR);
    if(Bit_price.download_price_map(file_price) == false)
        return(-1);
    
    map_str_d::const_iterator it = Bit_price.get_data_value("2020-11-27");
    if(it != Bit_price.end())
    { 
        std::cout << it->second<< std::endl;
        std::cout << it->first << std::endl;
    }
}