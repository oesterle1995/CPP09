/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 12:55:43 by aoesterl          #+#    #+#             */
/*   Updated: 2026/09/03 13:36:46 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <iostream>
#include <iostream>
#include <iomanip>

double get_time()
{ 
    struct timeval time;
    gettimeofday(&time, NULL);
    
    return(time.tv_sec * 1000000.0 + time.tv_usec);
    
}


int main()
{ 
    double start = get_time();
    for(size_t i = 0; i < 100000; i++)
        i = i;
    double end = get_time();
    std::cout << std::fixed << std::setprecision(1);
    std::cout << end - start << " us" << std::endl;
}