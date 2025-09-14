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
    
    // populate member containers once (avoid shadowing locals)
    v = args;
    q.assign(v.begin(), v.end());

    // run benchmark on construction for this project
    runTest();
}

void PmergeMe::runTest()
{
    if (v.empty())
        return;

    // Vector
    std::cout << "Before : ";
    print_vector(v);
    clock_t start_vec = clock();
    vector_merge(v);
    clock_t end_vec = clock();
    std::cout << "After  : ";
    print_vector(v);

    // Deque
    std::cout << "Before : ";
    print_deque(q);
    clock_t start_deque = clock();
    deque_merge(q);
    clock_t end_deque = clock();
    std::cout << "After  : ";
    print_deque(q);

    double vec_time = 1e6 * (end_vec - start_vec) / CLOCKS_PER_SEC;
    double deq_time = 1e6 * (end_deque - start_deque) / CLOCKS_PER_SEC;

    std::cout << "Time to process a range of " << v.size()
              << " elements with std::vector : " << vec_time << " us" << std::endl;
    std::cout << "Time to process a range of " << q.size()
              << " elements with std::deque   : " << deq_time << " us" << std::endl;
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

// helpers for insertion 

static void insert_merge(std::vector<int> &m, int n)
{
    std::vector<int>::iterator it = std::lower_bound(m.begin(), m.end(), n);
    m.insert(it, n);
}

static void insert_vector_minima(std::vector<int> &m, const std::vector<int> &p)
{
    std::vector<size_t> order = jacobsthal_order(p.size());
    for (size_t oi = 0; oi < order.size(); ++oi)
        insert_merge(m, p[order[oi]]);
}

static void insert_merge_deque(std::deque<int> &m, int n)
{
    std::deque<int>::iterator it = std::lower_bound(m.begin(), m.end(), n);
    m.insert(it, n);
}

static void insert_deque_minima(std::deque<int> &m, const std::deque<int> &p)
{
    std::vector<size_t> order = jacobsthal_order(p.size());
    for (size_t oi = 0; oi < order.size(); ++oi)
        insert_merge_deque(m, p[order[oi]]);
}

// Ford Johnson algo (merge-insert) 

void PmergeMe::vector_merge(std::vector<int> &vec)
{
    if (vec.size() <= 1)
        return;

    std::vector<int> m;
    std::vector<int> p;
    m.reserve(vec.size());
    p.reserve(vec.size() / 2 + 1);

    size_t i = 0;
    while (i + 1 < vec.size())
    {
        int a = vec[i];
        int b = vec[i + 1];
        if (a > b)
        { 
            m.push_back(a);
            p.push_back(b); 
        }
        else
        {
            m.push_back(b);
            p.push_back(a);
        }
        i += 2;
    }
    if (i < vec.size())
        m.push_back(vec[i]);

    vector_merge(m);      
    insert_vector_minima(m, p);
    vec.swap(m);
}

void PmergeMe::deque_merge(std::deque<int> &dq)
{
    if (dq.size() <= 1)
        return;

    std::deque<int> m;
    std::deque<int> p;

    size_t i = 0;
    while (i + 1 < dq.size())
    {
        int a = dq[i];
        int b = dq[i + 1];
        if (a > b) { 
            m.push_back(a);
            p.push_back(b);
        }
        else {
            m.push_back(b);
            p.push_back(a);
        }
        i += 2;
    }
    if (i < dq.size())
        m.push_back(dq[i]);

    deque_merge(m);
    insert_deque_minima(m, p);
    dq.swap(m);
}

void PmergeMe::print_vector(const std::vector<int> &v) const
{
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void PmergeMe::print_deque(const std::deque<int> &l) const
{
    for (std::deque<int>::const_iterator it = l.begin(); it != l.end(); ++it)
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
