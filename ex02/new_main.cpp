#include <iostream>
#include <sstream>
#include <vector>
#include <climits>

typedef struct s_element
{ 
    int value;
    int index;
    std::vector<t_element> losers;
}t_element;

bool is_valid_number(const std::string& str_arg)
{
    long nb;
    int count = 0;
    std::istringstream is(str_arg);
    while(is >> nb)
    { 
        if(nb < 0 || nb > INT_MAX)
            return false;
        count++;
    }
    if(!is.eof() || !count)
    { 
        std::cout << "error detected" << std::endl;
        return false;
    }
    return(true);
}

void print_array(const std::vector<t_element>& tab)
{ 
    std::vector<t_element>::const_iterator it;
    // std::vector<t_element>::const_iterator it_losers;
    it = tab.begin();
    std::cout << "---- Element tab----- " << std::endl;
    while(it != tab.end())
    {
        std::cout << "index : " << (*it).index << std::endl;
        std::cout << "value : " << (*it).value << std::endl;

        it++;
    }
}

void init_tab_element(const std::string& str_arg, std::vector<t_element>& tab_element)
{
    int i = 0;
    int nb;
    std::istringstream is(str_arg);
    t_element node;
    while(is >> nb)
    {
        node.value = nb;
        node.index = i;
        i++;
    }
}


std::vector<t_element> Ford_johnson_algorithm(std::vector<t_element>& winners)
{ 
    



}

int main(int argc, char **argv)
{
    std::vector <t_element> tab_element;
    std::string str_arg;
    for(int i = 1; i < argc; i++)
    { 
        str_arg += argv[i];
        str_arg += " ";
    }
    if(!is_valid_number(str_arg))
        return(std::cout << "Wrong args" << std::endl, 0);
    init_tab_element(str_arg, tab_element);
    print_array(tab_element);
    Ford_johnson_algorithm(tab_element);
}


// std::vector<int> Ford_johnson_algorithm(std::vector<int> v_tab)
// { 
//     std::vector<t_pair> v_pair;
//     v_pair = create_pair_tab(v_tab);
//     std::vector<t_pair>::iterator it = v_pair.begin();
//     std::cout << "--- a : BIGGEST v_pair ---  " << std::endl;
//     while(it != v_pair.end())
//     { 
//         std::cout << (*it).a << " | ";
//         it++;
//     }
//      it = v_pair.begin();
//     std::cout << std::endl << "--- b : SMALLEST v_pair ---  " << std::endl;
//     while(it != v_pair.end())
//     { 
//         std::cout << (*it).b << " | ";
//         it++;
//     }
//     std::cout << std::endl;
//     return(v_tab);
// }