#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <deque> // real container , unlike queue which is an adaptor 
#include <sstream>
#include <algorithm>
#include <ctime>

class PmergeMe 
{
    public:
        PmergeMe(char **av);
        ~PmergeMe();

        void runTest();

    private:
        PmergeMe();
        PmergeMe(const PmergeMe & b);
        PmergeMe &operator=(const PmergeMe & b);

        std::vector<int> v;
        std::deque<int>  q;

        bool is_number(const char *s);

        void vector_merge(std::vector<int> &vec);
        void deque_merge(std::deque<int> &dq);

        void print_vector(const std::vector<int>& v) const;
        void print_deque(const std::deque<int> &l) const;
};