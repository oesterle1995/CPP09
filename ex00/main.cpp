/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 17:46:29 by aoesterl          #+#    #+#             */
/*   Updated: 2026/07/20 17:54:08 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if(argc <= 1 )
        return(std::cerr << "Error: could not open file" << std::endl, ERROR);
    BitcoinExchange _Bit_Ex1;
    std::ifstream file_price("data.csv");
    std::ifstream file_value(argv[1]);
    if(!file_price.is_open() || !file_value.is_open())
           return(std::cerr << "Error: could not open file" << std::endl, ERROR);
    _Bit_Ex1.download_price_map(file_price);
}