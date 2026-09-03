/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 19:17:47 by aoesterl          #+#    #+#             */
/*   Updated: 2026/09/03 17:30:33 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmerge.hpp"

double get_time()
{ 
    struct timeval time;
    gettimeofday(&time, NULL);
    return(time.tv_sec * 1000000.0 + time.tv_usec);
}

void print_time_process(Pmerge &sort, double start, double end)
{ 
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Time to process a range of " << sort.get_size() << \
    " elements with std::vector<> : " << \
    end - start << " us" << std::endl;
    
}

int main(int argc, char ** argv)
{
    Pmerge sort;
    
    double start;
    double end;

    //vector
    start = get_time();
    if(sort.init_tab(sort.get_vector(), argc, argv) == false)
        return(std::cout << "Error" << std::endl, 0);
    sort.get_array(sort.get_vector(), "Before:");
    sort.ford_johnson_algorithm(sort.get_vector());
    sort.get_array(sort.get_vector(), "After: ");
    end = get_time();
    print_time_process(sort, start, end); 

    std::cout << std::endl;
    
    //deque
    start = get_time();
    if(sort.init_tab(sort.get_deque(), argc, argv) == false)
        return(std::cout << "Error" << std::endl, 0);
    sort.get_array(sort.get_deque(), "Before:");
    sort.ford_johnson_algorithm(sort.get_deque());
    sort.get_array(sort.get_deque(), "After: ");
    end = get_time();
    print_time_process(sort, start, end);

    // Pmerge sort2(sort);
    // std::cout << "Sort2 copy constructor" << std::endl;
    // sort2.get_array(sort.get_vector(), "After: ");
    // sort2.get_array(sort.get_deque(), "After: ");

    // std::cout << "Sort3 operator cpy" << std::endl;
    // Pmerge sort3;
    // sort3 = sort;
    // sort3.get_array(sort.get_vector(), "After: ");
    // sort3.get_array(sort.get_deque(), "After: ");
    
}



// int main(int argc, char **argv)
// { 
//         Pmerge sort;

//     //vector
//     // if(sort.init_tab(sort.get_vector(), argc, argv) == false)
//     //     return(std::cout << "Error" << std::endl, 0);
//     // sort.ford_johnson_algorithm(sort.get_vector());
//     // sort.checker(sort.get_vector(), sort.get_size());
    
//     //deque
//     // if(sort.init_tab(sort.get_deque(), argc, argv) == false)
//     //     return(std::cout << "Error" << std::endl, 0);
//     // sort.ford_johnson_algorithm(sort.get_deque());
//     // sort.checker(sort.get_deque(), sort.get_size());
    


    
// }