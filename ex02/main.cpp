
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
      
    rec_sort(m);

    for (int & i : p)
        insert_merge(m, i);
    v = m;
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

    std::vector<int> v = {12, 5, 8, 3, 10};
    rec_sort(v);

    std::cout << "v: ";
    for (size_t k = 0; k < v.size(); ++k)
        std::cout << v[k] << (k + 1 < v.size() ? " " : "");
    std::cout << std::endl;

    // std::vector<int> v2 = {5, 6, 8, 12, 100};
    // insert_merge(v2, 9);
    
    // std::cout << "v2: ";
    // for (size_t k = 0; k < v2.size(); ++k)
    //     std::cout << v2[k] << (k + 1 < v2.size() ? " " : "");
    // std::cout << std::endl; 

    return (0);
}