/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurito <arthurito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 17:46:29 by aoesterl          #+#    #+#             */
/*   Updated: 2026/07/31 16:21:09 by arthurito        ###   ########.fr       */
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
    if(Bit_price.download_price_map(file_price) == FALSE)
        return(ERROR);
    Bit_price.display_result_btc(file_value);
}