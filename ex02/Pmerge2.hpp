/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge2.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 19:00:43 by aoesterl          #+#    #+#             */
/*   Updated: 2026/09/02 20:06:44 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <deque>
#include <climits>
#include <iomanip>

class Pmerge
{
    private :
        //struct
        typedef struct s_element
        { 
            int value;
            std::vector<s_element> losers;
        }t_element;

        Container _tab;
        std::deque<t_element> _deque;
        int count;

        //vector function
            //Parsing
            template <typename Container>
            bool fill_number(const std::string &str, Container& tab);

            template <typename Container>
            bool init_tab(Container& tab, int argc, char **argv);
            //Debug
            
            template <typename Container>
            void tree_of_element(const Container& tab, std::string prefix = "");
            
            template <typename Container>
            void debug_ford(const Container& tab, const Container& pend, std::string& title);

            template <typename Container>
            void print_array(std::vector<int>& tab, std::string title);
            
            //checker
            template <typename Container>
            void  checker(Container &tab, size_t size);
            //core 
            
            template <typename Container>
            void iterative_dichotomie(Container& tab, t_element& elem, int low, int high);

            template <typename Container>
            std::vector<size_t> generate_jacob_tab(size_t size);

            template <typename Container>
            void jacob_insertion(Container& pending,  Container& main_chain);

            template <typename Container>
            void insertion(Container& tab, Container &odd);

            template <typename Container>
            void new_tab(Container& tab);

            template <typename Container>
            void ford_johnson_algorithm(Container& tab);
    public :
            int ford_johnson_vector(int argc, char **argv);
            // int ford_johnson_deque(int argc, char **argv);
};