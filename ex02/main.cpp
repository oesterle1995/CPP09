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

// void iterative_dichomotmie(std::vector<t_element>& tab, int nb)
// { 
//     int low = 0;
//     int high = tab.size();
//     int range = high - low;
//     int mid;
//     while(range != 0)
//     { 
//         mid = low + range/2;
//         if(nb > tab[mid])
//             low = mid + 1;
//         if(nb <= tab[mid])
//             high = mid;
//         range = high - low;        
//     }
//     tab.insert(tab.begin() + low, nb);
// }

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


void jacob_insertion(std::vector<t_element>&tab, std::vector<t_element> smaller_elem, \ 
     std::vector<t_element> higher_elem, const std::vector<int>& jacob_tab)
{ 
    int j_i;
    int range;
    int real_i;
    for(int i = 0; i < jacob_tab.size(); i++)
    {
        j_i = jacob_tab[i] - 1; // trouve l'index de jacob a inserer en premier;
        if(j_i ... )
         // condition de protection si le denrier nombre de jacob_tab > tab.size() et que se passe -t - il avec l'element seul ?
        if(i != 0) 
            range = jacob_tab[i] - jacob_tab[i - 1]; // trouve le nombre d'element a inserer a partir de l'index de jacobshtall  : 1 3 5 => entre 1-3 la range sera 2 element
        else
            range = 1;
        while(range > 0 ) // tant que ma range d'element a inserer est > 0 je continue, je dois inserer des elements
        { 
            real_i = find_winner_pos(higher_elem, tab[j_i]); // le vrai index du winner de jacob_sthall dans la liste higher
            // insertion dichotomique;
            j_i--; // je vais chercher l'index precedent
            range--;
        }
    }
}


void prepare_insertion(std::vector<t_element>& tab, std::vector<t_element> &pend, const std::vector<int>& jacob_tab)
{ 
    std::vector<t_element> small_elem;
    std::vector<t_element> higher_elem = tab;
    int range;
    int real_index;

    for(int i; i < higher_elem.size(); i++)
    {
        if(!higher_elem[i].losers.empty())
        { 
            small_elem.push_back(higher_elem[i].losers.back());
            higher_elem[i].losers.pop_back();
        }
    }
    small_elem.push_back(pend.back());
    pend.pop_back();
    jacob_insertion(tab, small_elem, higher_elem, jacob_tab);

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