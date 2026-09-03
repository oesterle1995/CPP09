/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 19:00:16 by aoesterl          #+#    #+#             */
/*   Updated: 2026/09/03 16:16:50 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmerge.hpp" 

size_t Pmerge::get_count()
{ 
    return(_count);
}

size_t Pmerge::get_size() 
{ 
    return(_size);
}


std::vector<Pmerge::t_element>& Pmerge::get_vector()
{ 
    return _tab;
}

std::deque<Pmerge::t_element>& Pmerge::get_deque()
{ 
    return _deque;
}