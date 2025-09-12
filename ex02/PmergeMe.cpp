#include "PmergeMe.hpp"

static std::vector<size_t> jacobsthal_order(size_t m)
{
    std::vector<size_t> order;
    if (m == 0)
        return order;
    std::vector<bool> used(m, false);

    size_t j_prev = 0;
    size_t j_curr = 1;

    while (order.size() < m)
    {
        size_t upper = std::min(j_curr, m);
        for (size_t t = upper; t > 0; --t)
        {
            size_t idx = t - 1;
            if (!used[idx])
            {
                order.push_back(idx);
                used[idx] = true;
                if (order.size() == m)
                    break;
            }
        }
        size_t j_next = j_curr + 2 * j_prev;
        j_prev = j_curr;
        j_curr = j_next;
    }
    return order;
}

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
    if (args.empty())
        return;
    j_order = jacobsthal_order(args.size());

    v = args;
    l.assign(v.begin(), v.end());
    std::list<int> l(v.begin(), v.end());
}

void PmergeMe::runTest()
{

    if (v.empty())

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

void insert_merge(std::vector<int> &m, int n)
{
    std::vector<int>::iterator it = std::lower_bound(m.begin(), m.end(), n);
    m.insert(it, n);
}

void insert_minima(std::vector<int> &m, std::vector<int> &p)
{
    std::vector<size_t> order = jacobsthal_order(p.size());
    for (size_t idx : order)
        insert_merge(m, p[idx]);
}


void vector_merge(std::vector <int> &v)
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
    
    vector_merge(m);

    insert_minima(m, p);
    v = m;
}



void PmergeMe::list_merge(std::list<int> &lst)
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
}

void PmergeMe::print_vector(const std::vector<int> &v) const
{
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void PmergeMe::print_list(const std::list<int> &l) const
{
    for (std::list<int>::const_iterator it = l.begin(); it != l.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &b)
{
    (void)b;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &b)
{
    (void)b;
    return *this;
}
