#include <iostream>
#include <sstream>
#include <vector>
#include <climits>

int lourd = 0 ;

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
            lourd++;
        }
        else
        {
            tab[i].losers.push_back(tab[i+1]); 
            new_pairs.push_back(tab[i]);
            lourd++;
        }
    }
    return new_pairs;
}

void iterative_dichotomie(std::vector<t_element>& tab, t_element& elem, int low, int high)
{ 
    int range = high - low;
    int mid;
    while(range != 0)
    { 
        mid = low + range/2;
        if(elem.value > tab[mid].value)
            low = mid + 1;
        if(elem.value <= tab[mid].value) // else pour enlever la comparaison mais garder pour la lisibilite
            high = mid;
        lourd++;
        range = high - low;        
    }
    tab.insert(tab.begin() + low, elem);
}

int find_winner_pos(std::vector<t_element>& higher_elem, t_element& target)
{ 
    for(int i = 0; i < higher_elem.size(); i++)
    {
        if(higher_elem[i].index == target.index)
        { 
            std::cout << "FIND : " << higher_elem[i].value << std::endl; 
            return i;
        }
    }
    return(0);
}

std::vector<int> order_insertion(std::vector<t_element>& tab)
{
    std::vector<int> order;
    int power = 2;
    int U_prev = 1;
    int tmp;
    int size = tab.size();

    if (size < 1)
        return (order);

    order.push_back(0);
    while (order.size() != tab.size())
    {
        power *= 2;
        int U_curr = std::min(power - U_prev, size);
        for (tmp = U_curr - 1; tmp > U_prev - 1; tmp--)
            order.push_back(tmp);
        U_prev = U_curr;
    }
    return (order);
}

void jacob_insertion(std::vector<t_element>&tab, std::vector<t_element>& smaller_elem,  std::vector<t_element>& higher_elem)
{ 
    std::vector<int> order_b = order_insertion(smaller_elem);
    int b_index;
    int a_index;
    for(int i = 0; i < order_b.size(); i++)
    { 
        b_index = order_b[i];
        if(i == 0)
            higher_elem.insert(higher_elem.begin(), smaller_elem[i]);
        else if(b_index == tab.size())
        { 
            std::cout<< "impair" << std::endl;
            iterative_dichotomie(higher_elem, smaller_elem[b_index], 0, higher_elem.size());
        }

        else
        { 
            a_index = find_winner_pos(higher_elem, tab[b_index]);
            iterative_dichotomie(higher_elem, smaller_elem[b_index], 0, a_index);
        }
    }
    tab = higher_elem;
}


void prepare_insertion(std::vector<t_element>& tab, std::vector<t_element> &pend)
{ 
    std::vector<t_element> small_elem;
    std::vector<t_element> higher_elem = tab;
    int range;
    int real_index;

    for(int i = 0; i < higher_elem.size(); i++)
    {
        if(!higher_elem[i].losers.empty())
        { 
            small_elem.push_back(higher_elem[i].losers.back());
            higher_elem[i].losers.pop_back();
        }
    }
    if(!pend.empty())
    { 
        small_elem.push_back(pend.back());
        pend.pop_back(); 
    }
    jacob_insertion(tab, small_elem, higher_elem);

}


std::vector<t_element> Ford_johnson_algorithm(std::vector<t_element>& tab)
{
    std::vector<t_element> pend;
    static int lvl;
    // ZONE RECURSIVE
    if(tab.size() <= 1)
    { 
        std::cout << "--- stop upping ---" << std::endl;
        lvl--;
        return(tab);
    }
    if(tab.size() % 2 != 0)
    {
        pend.push_back(tab[tab.size() - 1]);
        tab.pop_back();
    }
    tab = new_pairs(tab);
    std::cout << " --- 😛 RECURSIVE LVL UPPER: " << lvl << " ---" << std::endl << std::endl;
    debug_ford(tab, pend);
    lvl++;
    Ford_johnson_algorithm(tab);

    // ZONE DE REDESCENTE
    prepare_insertion(tab, pend);

    std::cout << " --- 😛 RECURSIVE LVL DOWN: " << lvl << " ---" << std::endl << std::endl;
    debug_ford(tab, pend);
    lvl--;
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
    Ford_johnson_algorithm(tab_element);
    for(int i = 0; i < tab_element.size(); i++)
    { 
        std::cout << "chaine final" << std::endl;
        std::cout << tab_element[i].value << std::endl;
    }
    std::cout << "nombre d'element : " << tab_element.size() << std::endl;
    std::cout << "number of compare :" << lourd << std::endl;
}