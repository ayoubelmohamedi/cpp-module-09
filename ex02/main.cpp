
#include "PmergeMe.hpp"




void insert_merge(std::vector <int> &m, int n)
{
    std::vector<int>::iterator it = std::lower_bound(m.begin(), m.end(), n);
    m.insert(it, n); 
}

void rec_sort(std::vector <int> &v)
{
    if (v.empty() || v.size() == 1)
        return ; 

    std::vector <int> m , p;

    size_t i = 0;
    while (i + 1 < v.size())
    { 
        if (v[i] > v[i + 1])
        {
            m.push_back(v[i]);
            p.push_back(v[i + 1]);
        }
        else
        {
            m.push_back(v[i + 1]);
            p.push_back(v[i]);
        }
        i += 2;
    }
    if (i  <  v.size())
        m.push_back(v[i]);
    
    std::cout << "m: ";
    for (size_t k = 0; k < m.size(); ++k)
        std::cout << v[k] << (k + 1 < v.size() ? " " : "");
    std::cout << std::endl;


    
    rec_sort(m);

    for (int & i : p)
        insert_merge(m, i);
    v = m;
}



void print_list(const std::list<int> &l);

void list_merge(std::list<int> &lst)
{
    if (lst.size() <= 1)
        return;

    std::list<int> left, right;
    std::list<int>::iterator mid = lst.begin();

    size_t dest = std::distance(lst.begin(), lst.end());
    std::advance(mid, dest / 2);
    left.splice(left.begin(), lst, lst.begin(), mid);

    right.splice(right.begin(), lst, mid, lst.end());
    list_merge(left);
    list_merge(right);
    left.merge(right);
    lst.swap(left);
    std::cout << "left now : " << std::endl;
    print_list(lst);
}


void list_insert_merge(std::list<int> &lst)
{
    if (lst.size() <= 1)
        return;

    std::list <int> maxima;
    std::vector<int> minima;

    minima.reserve(lst.size(), );
    
}



void print_list(const std::list<int> &l)
{
    for (std::list<int>::const_iterator it = l.begin(); it != l.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}


int main(int ac, char **av)
{
    // if (ac < 2)
    // {
    //     std::cerr << "nothing to sort" << std::endl;
    //     return (1);
    // }
   
    // try {
    //     PmergeMe p(av);
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    //     return (1);
    // } 

    // std::vector<int> v = {12, 5, 8, 3, 10};
    std::list<int> l;
    std::list<int> r = { 3, 10, 12};
    


    std::list<int> v = {12, 5, 8, 3, 10};


    l.splice(l.begin(), v, v.begin(), v.end());
    // l.sort();

    // print_list(l);
    // r.sort();
    // print_list(r);
    l.merge(r);

    print_list(l);

    v.swap(l);

    print_list(v);

    // std::list<int> left, right;
    // std::list<int>::iterator mid = l.begin();

    // // size_t dest = std::distance(l.begin(), l.end());
    // // std::advance(mid, dest / 2);
    // // left.splice(left.begin(), l, l.begin(), mid);

    // // print_list(left);

    // // print_list(l);
    // // right.splice(right.begin(), l, mid, l.end());

    
    // // print_list(right);
    // // rec_sort(v);


    // list_merge(l);
    // print_list(l);


    return (0);
}