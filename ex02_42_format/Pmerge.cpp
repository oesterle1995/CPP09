/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 19:00:16 by aoesterl          #+#    #+#             */
/*   Updated: 2026/09/03 17:26:50 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmerge.hpp" 

Pmerge::Pmerge(): _count(0), _size(0)
{
    
}

Pmerge::Pmerge(const Pmerge& cpy)
{ 
    *this = cpy;
}

Pmerge& Pmerge::operator=(const Pmerge& obj)
{ 
    if(this != &obj)
    { 
        _count = obj._count;
        _size = obj._size;
        _tab = obj._tab;
        _deque = obj._deque;
    }
    return(*this);
}

Pmerge::~Pmerge()
{
    return;
}

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