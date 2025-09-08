

#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>


class PmergeMe 
{
    public:
        PmergeMe(char **av);
        ~PmergeMe();

    private:
        PmergeMe();
        PmergeMe(const PmergeMe & b);
        PmergeMe &operator=(const PmergeMe & b);
        bool is_number(const char *s);
        void vector_merge(std::vector<int>::iterator start, std::vector<int>::iterator end);
        void list_merge(std::list<int> &lst);
        void print_vector(const std::vector<int>& v) const;
        void print_list(const std::list<int>& v) const;

};