
#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "nothing to sort" << std::endl;
        return (1);
    }
   
    try {
        PmergeMe p(av);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return (1);
    } 

    return (0);
}