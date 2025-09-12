#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <list>
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


        std::vector<size_t> j_order;
        std::vector<int> v;
        std::list<int> l;

        bool is_number(const char *s);
        // merge-insert
        void vector_merge(std::vector<int>::iterator start, std::vector<int>::iterator end);
        void list_merge(std::list<int> &lst);
        // Insertion sort helpers
        void vector_insertion(std::vector<int>::iterator start, std::vector<int>::iterator end);
        void list_insertion(std::list<int> &lst);
        void print_vector(const std::vector<int>& v) const;
        void print_list(const std::list<int>& v) const;
};