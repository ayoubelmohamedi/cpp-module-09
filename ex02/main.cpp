
#include <string>
#include <set>
#include <iostream>

bool is_number(const char *s)
{
    if (!s)
        return (false);
    while (*s)
    {
        if (!std::isdigit(*s))
            return (false);
        ++s;
    }
    return (true);
}

void merge_set(std::set<int>::iterator start, std::set<int>::iterator end)
{
    size_t dist = std::distance(start, end);
    if (dist <= 1)
        return ;
    
    std::set<int>::iterator mid = start;
    std::advance(mid, dist / 2);
    
    std::cout << " dist / 2 "<< dist / 2 << std::endl;

    merge_set(start, mid);
    merge_set(mid, end);




    std::set<int>::iterator left = start, right = mid;
    std::cout << "mid " << *mid << " left is " << *left << " right is " << *right << std::endl;


}

int main(int ac, char **av)
{
    // if (ac < 2)
    // {
    //     std::cerr << "nothing to sort" << std::endl;
    //     return (1);
    // }
    // std::set<int> nbrs;
    // for (int i = 1; i < ac; ++i)
    // {
    //     if (is_number(av[i]))
    //         nbrs.insert(std::atoi(av[i]));
    //     else
    //     {
    //        std::cerr << "Invalid input" << std::endl;
    //        return (1);
    //     }
    // } 

    // merge_set(nbrs.begin(),nbrs.end());

    std::vector<int> v;

    std::vector<int> v2;

    v.push_back(5);
    v.push_back(std::move(12));
    v.push_back(1);

    std::cout << "before " << v[1] << std::endl;
    std::cout << v[1] << std::endl;

    v2 = v;

    v2.insert(1, 0, v.size());




    return (0);
}