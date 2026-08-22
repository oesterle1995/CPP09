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

void tree_of_losers(const std::vector<t_element>& tab, std::string prefix = "")
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

void debug_ford(const std::vector<t_element>& tab, const std::vector<t_element>& pend)
{ 
    std::cout << "   --- TREE OF LOSERS ---- " << std::endl;
    tree_of_losers(tab);
    std::cout << std::endl << "   --- PEND --- " << std::endl;
    tree_of_losers(pend);
    std::cout << std::endl;
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


int find_winner_pos(std::vector<t_element>& new_tab, t_element& target)
{ 
    for(int i = 0; i < new_tab.size(); i++)
    { 
        if(new_tab[i].index == target.index)
        { 
            std::cout << "FIND : " << new_tab[i].value << std::endl; 
             return i;
        }
    }
    return(0);
}

void jacob_stahll_insertion(std::vector<t_element>& tab, std::vector<t_element> &pend, const std::vector<int>& jacob_tab)
{
    int jacob_range = 0;
    int jacob_index;
    int real_index;
    t_element elem_insert;
    std::vector<t_element> new_tab = tab;
    for(int i = 0; i < jacob_tab.size(); i++)
    { 
        jacob_index = jacob_tab[i] - 1; // ex : 3  devient index 2
        if(jacob_index > tab.size() - 1) // si index > index_max du tab alors jacob_index devient index_max
            jacob_index = tab.size() - 1;
        if(i != 0)
        {
            if(jacob_tab[i] > tab.size())
                jacob_range = tab.size() - jacob_tab[i - 1];
            else
                jacob_range = jacob_tab[i] - jacob_tab[i - 1];   // la range est jacob_index - (index - 1)
        }
        for(int i = 0; jacob_range - i > 0; i++)
        { 
            real_index = find_winner_pos(new_tab, tab[jacob_index - i]); // recherche dans tab[2]
            elem_insert = new_tab[real_index].losers.back(); // real_index devient la position avec les elements dans la liste;
            new_tab[real_index].losers.pop_back();
            // methode dichotomique d'insertion;
        }
    }
    tab = new_tab;
}

std::vector<int> generate_jacob_sequel(int half_list)
{
    std::vector<int> jacob_tab;
    jacob_tab.push_back(1);
    int j_prev = 1;
    int j_curr = 3;

    while(j_curr < half_list)
    {
        jacob_tab.push_back(j_curr);
        int next = j_curr + 2 * j_prev;
        j_prev = j_curr;
        j_curr = next;
    }
    jacob_tab.push_back(j_curr);
    
    for(int i = 0; i < jacob_tab.size(); i++)
        std::cout << jacob_tab[i] << std::endl;
    return(jacob_tab);
}

std::vector<t_element> Ford_johnson_algorithm(std::vector<t_element>& tab, const std::vector<int>& jacob_tab)
{
    std::vector<t_element> pend;
    static int lvl;
    // ZONE RECURSIVE
    if(tab.size() <= 1)
    { 
        std::cout << "--- stop upping ---" << std::endl;
        return(tab);
    }
    //si la liste est impair le dernier element est mis dans un pend;
    if(tab.size() % 2 != 0)
    {
        pend.push_back(tab[tab.size() - 1]);
        tab.pop_back();
    }
    //#F1
    tab = new_pairs(tab);
    std::cout << " --- 😛 RECURSIVE LVL : " << lvl << " ---" << std::endl << std::endl;
    debug_ford(tab, pend);
    lvl++;
    Ford_johnson_algorithm(tab, jacob_tab);

    // ZONE DE REDESCENTE


    return(tab);
}

int main(int argc, char **argv)
{
    std::vector <t_element> tab_element;
    std::vector <int> jacob_tab;
    std::string str_arg;
    for(int i = 1; i < argc; i++)
    { 
        str_arg += argv[i];
        str_arg += " ";
    }
    if(!is_valid_number(str_arg))
        return(std::cout << "Wrong args" << std::endl, 0);
    init_tab_element(str_arg, tab_element);
    // print_array(tab_element);
    jacob_tab = generate_jacob_sequel(tab_element.size()/ 2 );
    Ford_johnson_algorithm(tab_element, jacob_tab);
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


// #F1
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

//#F2
    // void print_array(const std::vector<t_element>& tab)
// { 
//     std::vector<t_element>::const_iterator it;
//     // std::vector<t_element>::const_iterator it_losers;
//     it = tab.begin();
//     std::cout << "---- Element tab----- " << std::endl;
//     while(it != tab.end())
//     {
//         std::cout << "index : " << (*it).index;
//         std::cout << " | value : " << (*it).value << std::endl;
//         it++;
//     }
// }