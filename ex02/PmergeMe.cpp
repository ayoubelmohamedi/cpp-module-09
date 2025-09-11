#include "PmergeMe.hpp"


PmergeMe::PmergeMe(char **av)
{
    size_t i = 1;
    std::vector<int> args;

    while (av[i])
    {
        if (is_number(av[i]))
        {
            int val;
            std::istringstream(av[i]) >> val;
            if (val < 0)
                throw std::runtime_error("Invalid input: negative number");
            args.push_back(val);
        }
        else
            throw std::runtime_error("Invalid input");
        ++i;
    }

    std::vector<int> v = args;
    std::list<int> l(v.begin(), v.end());

    std::cout << "Before : ";
    print_vector(v);
    clock_t start_vec = clock();
    vector_merge(v.begin(), v.end());
    clock_t end_vec = clock();
    std::cout << "After : ";
    print_vector(v);

    std::cout << "Before : ";
    print_list(l);

    clock_t start_list = clock();
    list_merge(l);
    clock_t end_list = clock(); 
    std::cout << "After :";
    print_list(l);

    double vec_time = 1e6 * (end_vec - start_vec) / CLOCKS_PER_SEC;
    double list_time = 1e6 * (end_list - start_list) / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << v.size()
              << " elements with std::vector : " << vec_time << " us" << std::endl;
    std::cout << "Time to process a range of " << l.size()
              << " elements with std::list : " << list_time << " us" << std::endl;


}


bool PmergeMe::is_number(const char *s)
{
    if (!s || !*s)
        return (false);
    while (*s)
    {
        if (!std::isdigit(static_cast<unsigned char>(*s)))
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
    merged.reserve(dist);
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
    std::copy(merged.begin(), merged.end(), start); 
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
    left.merge(right);
    lst.swap(left); 
}

void PmergeMe::print_vector(const std::vector<int>& v) const {
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void PmergeMe::print_list(const std::list<int>& l) const{
    for (std::list<int>::const_iterator it = l.begin(); it != l.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe & b) {
    (void)b;
}

PmergeMe &PmergeMe::operator=(const PmergeMe & b) {
    (void)b; 
    return *this;
}

