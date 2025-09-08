
#include <string>
#include <iostream>
#include <vector>
#include <list>

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


void sort_vector(std::vector<int>::iterator start, std::vector<int>::iterator end)
{
    size_t dist = std::distance(start, end);
    if (dist <= 1)
        return ;
    
    std::vector<int>::iterator mid = start;
    std::advance(mid, dist / 2);
    
    sort_vector(start, mid);
    sort_vector(mid, end);
    
    std::vector<int> merged;
    std::vector<int>::iterator left = start, right  = mid;

    while (left != mid && right != end)
    {
        if (*left  < *right)
            merged.push_back(*left++);
        else
            merged.push_back(*right++); 
    }
    merged.insert(merged.end(), left, mid);
    merged.insert(merged.end(), right, end);
    std::move(merged.begin(), merged.end(), start); 
}

void list_merge(std::list<int> &lst)
{

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

    std::vector<int> v = {4, 3, 2,  1,5, 12,89, -6};
    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    
    std::vector<int>::iterator start = v.begin(), end = v.end();
    sort_vector(start , end);

    for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;


    return (0);
}