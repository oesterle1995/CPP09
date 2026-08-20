#include <iostream>
#include <sstream>
#include <vector>
#include <climits>

typedef struct s_element
{ 
    int value;
    int index;
    std::vector<s_element> losers;
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
        std::cout << "index : " << (*it).index;
        std::cout << " | value : " << (*it).value << std::endl;
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
        tab_element.push_back(node);
        i++;
    }
}

void tree_of_losers(std::vector<t_element>& tab, std::string prefix = "")
{
    std::string new_prefix;
    int end = tab.size() - 1;
    if(tab.empty())
        return;
    for(int i = 0; i < tab.size(); i++)
    {
        std::cout << prefix;
        if(i != end)
            std::cout << "├── ";
        else
            std::cout << "└── ";
        std::cout << "[Val: " << tab[i].value << " | Idx: " << tab[i].index << "]" << std::endl;
        if(i != end)
            new_prefix = prefix + "│\t";
        else
            new_prefix = prefix + "\t";
        tree_of_losers(tab[i].losers, new_prefix);
    }
}

std::vector<t_element> new_pairs(std::vector<t_element>& tab)
{ 
    std::vector<t_element> new_pairs;
    for(int i = 0; i < tab.size(); i += 2)
    { 
        if(tab[i].value < tab[i + 1].value)
        { 
            tab[i + 1].losers.push_back(tab[i]);
            new_pairs.push_back(tab[i+1]);
        }
        else
        {
            tab[i].losers.push_back(tab[i+1]); 
            new_pairs.push_back(tab[i]);
        }
    }
    return new_pairs;
}

std::vector<t_element> Ford_johnson_algorithm(std::vector<t_element>& tab)
{
    t_element pend;
    if(tab.size() <= 1)
    { 
        std::cout << "--- stop upping ---" << std::endl;
    }
    //si la liste est impair le dernier element est mis dans un pend;
    if(tab.size() % 2 != 0)
    {
        pend = tab[tab.size() - 1];
        std::cout << "pend : " << " value -> " << pend.value << " index -> " << pend.index << std::endl;
        tab.pop_back();
    }
    // on compare maintenant les pairs de deux et les gagnantes vont rester dans tab_element, les perdants iront dans les std::vector<t_element> losers;
    // std::vector<t_element> new_pairs;
    // for(int i = 0; i < tab.size(); i += 2)
    // { 
    //     if(tab[i].value < tab[i + 1].value)
    //     { 
    //         tab[i + 1].losers.push_back(tab[i]);
    //         new_pairs.push_back(tab[i+1]);
    //     }
    //     else
    //     {
    //         tab[i].losers.push_back(tab[i+1]); 
    //         new_pairs.push_back(tab[i]);
    //     }
    // }
    // tab = new_pairs;
    tab = new_pairs(tab);
    std::cout << "--- TREE OF LOSERS ---- " << std::endl;
    tree_of_losers(tab);
    return(tab);
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