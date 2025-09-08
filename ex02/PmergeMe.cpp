

#include "PmergeMe.hpp"


PmergeMe::PmergeMe(char **av)
{
    size_t i = 1;
    std::vector<int> args;

    while (av[i])
    {
        if (is_number(av[i]))
            args.push_back(std::atoi(av[i]));
        else
            throw std::runtime_error("Invalid input");
        ++i;
    }

    std::vector<int> v = args;
    std::list<int> l(v.begin(), v.end());

    vector_merge(v.begin(), v.end());

    list_merge(l);

}



bool PmergeMe::is_number(const char *s)
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


void PmergeMe::vector_merge(std::vector<int>::iterator start, std::vector<int>::iterator end)
{
    size_t dist = std::distance(start, end);
    if (dist <= 1)
        return ;
    
    std::vector<int>::iterator mid = start;
    std::advance(mid, dist / 2);
    
    vector_merge(start, mid);
    vector_merge(mid, end);
    
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

void PmergeMe::list_merge(std::list<int> &lst)
{
    if (lst.size() <= 1)
        return ;
    
    std::list<int> left, right;

    std::list<int>::iterator mid = lst.begin();
    size_t dest = std::distance(lst.begin(), lst.end()); 
    std::advance(mid, dest / 2);

    left.splice(left.begin(), lst, lst.begin(), mid); 
    right.splice(right.begin(), lst, mid, lst.end());

    list_merge(left);
    list_merge(right);


    lst.merge(left);
    lst.merge(right);

}


PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe & b) {
    (void)b;
}

PmergeMe &PmergeMe::operator=(const PmergeMe & b) {
    (void)b; 
    return *this;
}

