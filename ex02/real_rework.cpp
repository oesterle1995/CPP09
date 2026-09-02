
#include <iostream>
#include <sstream>
#include <vector>
#include <climits>
#include <iomanip>

int lourd = 0 ;

typedef struct s_element
{ 
    int value;
    std::vector<s_element> losers;
}t_element;

//#1 PARSING
bool fill_number(const std::string &str, std::vector<int>& tab)
{ 
    int nb;
    int count = 0;
    std::istringstream iss(str);
    while(iss >> nb)
    { 
        if(nb < 0)      
            return false;
        tab.push_back(nb);
        count++;
    }
    if(!iss.eof() || count == 0)
        return false;
    return true;
}

bool init_tab(std::vector<int>& tab, int argc, char **argv)
{ 
    std::string str;
    for(int i = 1; i < argc; i++)
    {
        str += argv[i];
        str += " ";
    }
    if(fill_number(str, tab) == false)
        return false;
    return true;
}

void print_array(std::vector<int>& tab, std::string title)
{ 
    std::cout << title << std::endl;
    for(int i = 0; i < tab.size(); i++)
    { 
        std::cout << "[" << std::setw(5) << tab[i] << "]";
        std::cout << " ";
    }
    std::cout << std::endl;
}
//FIN DEBUG

// #3 Checker
void  checker(std::vector<int> &tab, int size)
{ 
    const std::string GREEN = "\033[32m";
    const std::string RED   = "\033[31m";
    const std::string RESET = "\033[0m";
    
    //check sort
    if(tab.size() == 1)
        std::cout << GREEN << "[OK sort]" << RESET;
    for(int i = 0; i < tab.size() - 1; i++)
    { 
        int j = i + 1;
        if(tab[i] > tab[j])
            std::cout << RED << "[FAIL sort] " << RESET;
    }
    std::cout << GREEN << "[OK]" << RESET <<  std::endl; 

    //check count
    if(tab.size() != size)
        std::cout << RED << "[FAIL] count : [" << tab.size() << "] init_count : [" << size << "]" <<  RESET << std::endl;
    else
        std::cout << GREEN << "[OK] count : [" << tab.size() << "] init_count : [" << size << "]" <<  RESET << std::endl;
}
//FIN CHECKER

void swap_int(int& a, int& b)
{ 
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}

void iterative_dichotomie(std::vector<int>& tab, int& nb, int low, int high)
{ 
    int range = high - low;
    int mid;
    while(range != 0)
    { 
        mid = low + range/2;
        if(nb > tab[mid])
            low = mid + 1;
        else
            high = mid;
        lourd++;
        range = high - low;        
    }
    tab.insert(tab.begin() + low, nb);
}

std::vector<int> generate_jacob_tab(int size)
{
    std::vector<int> order;
    int J_next;
    int J_prev = 1;
    int J_curr = 3;
    
    if(size < 1)
        return(order);
    order.push_back(1);
    while(order.size() != size)
    { 
        int j = std::min(J_curr, size);
        for(int tmp = j; tmp > J_prev; tmp--)
            order.push_back(tmp);
        J_next = J_curr + 2 *J_prev;
        J_prev = J_curr;
        J_curr = J_next;
    }
    for(int i = 0; i < order.size(); i++)
        order[i] -= 1;
    return(order);
}

void jacob_insertion(std::vector<int>& main_chain,  std::vector<int>& pending)
{ 
    std::vector<int> order_b = generate_jacob_tab(pending.size()); // 1 3 2 5 4  => 0 2 1 4 3
    int high;
    int insert_index;
    main_chain.insert(main_chain.begin(), pending[0]); 
    for(int i = 1; i < order_b.size(); i++)
    {
        high = order_b[i] + i;
        iterative_dichotomie(main_chain, pending[order_b[i]], 0, high);
    }
}

void compare_pairs(std::vector<int>& tab, std::vector<int>& order)
{
    for(int i = 0; i < tab.size(); i += 2)
    { 
        if(tab[i] < tab[i + 1])
            swap_int(order[i], order[i+1]);
        lourd++;
    }
}


std::vector<int> Ford_johnson_algorithm(std::vector<int>& tab, std::vector<int>& order)
{
    int odd;
    bool odd_here = false; 
    if(tab.size() <= 1)
        return(tab);
    if(tab.size() % 2 != 0)
    {
        odd_here = true;
        odd = tab[tab.size() - 1];
        tab.pop_back();
    }
    
    //on compaire des paires. l'indice gagnant est toujours au debut et on switch l'ordre dans order
    compare_pairs(tab, order);

    //tableau local_order ici initiliser a 0 1 2 3. En revenant de l'appel de ford_johson, l'ordre sera mis a jour.
    std::vector<int> main_order;
    for(int i = 0; i < tab.size()/2; i++)
        main_order.push_back(i);

    //tableau contenant les gagnants dans la comparaison
    std::vector<int> new_tab;
    for(int i = 0; i < tab.size()/2; i++)
        new_tab.push_back(tab[order[2 * i]]);

    Ford_johnson_algorithm(new_tab, main_order);

    std::vector<int> main_chain;
    std::vector<int> pending;

    main_chain
    //une fois que main_chain et pending on ete mis dans l'ordre, on dit que order = 



    if(odd_here == true)
        pending.push_back(odd);

    std::vector<int> sorted_pending(pending.size());
    for(int i = 0; i < main_order.size(); i++)
        sorted_pending[i] = pending[main_order[i]];

    // order doit etre regornaiser il s'aigit du pendingg order precedent 
    jacob_insertion(main_chain, sorted_pending);
    
    // ici debug
    return(main_chain);
}

int main(int argc, char **argv)
{
    std::vector <int> tab;
    std::vector <int> order;
    int size;
    if(init_tab(tab, argc, argv) == false)
        return(std::cout << "Error" << std::endl, 0);
    size = tab.size();
    for(int i = 0 ; i < tab.size(); i++)
        order.push_back(i);
    Ford_johnson_algorithm(tab, order);
    checker(tab, size);
}