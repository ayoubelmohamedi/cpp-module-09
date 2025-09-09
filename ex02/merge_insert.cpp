

#include <iostream>
#include <vector>
// #include <span>
// #include <algorithm> 




// void merge_sort(const std::vector<int> & v)
// {
//     if (v.empty() || v.size() == 1)
//         return ;
    
//     int mid  =  
//     std::vector<int>::const_iterator right = v.begin() + (v.size() / 2); 
//     std::vector<int>::const_iterator right = v.begin() + (v.size() / 2); 


//     merge_sort();
//     merge_sort();
//     merge()
// }


int rec_max(const std::vector<int> & v)
{
    if (v.empty())
        return 0;
    if (v.size() == 1)
        return (v[0]);

    std::vector<int> tmp(v.begin() + 1, v.end());
    int sub_max = rec_max(tmp);
    return ( v[0] > sub_max ? v[0] : rec_max(tmp));
}


void find_max(std::vector<int> & v)
{
    size_t i = 0;
    int m = 0;
    while (i < v.size())
    {
        if (v[i++] > m)
            m = v[i - 1];
    } 
    std::cout << "max is " << m << std::endl;
}


void select_sort(std::vector<int> &v)
{
    int min_index;
    for (int i = 0; i < v.size(); i++)
    {
        min_index = i;
        for (int j = i + 1 ; j < v.size(); j++)
        {
            if (v[j] < v[min_index])
            {
                min_index = j;
            }
        }
        std::swap(v[i],v[min_index]);
    }
}


void selection_sort(std::vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        size_t max_idx = i;
        for (size_t j = i + 1; j < v.size(); ++j) {
            if (v[j] < v[max_idx])
                max_idx = j;
        }
        std::cout << v[i] << std::endl;
        std::swap(v[i], v[max_idx]);
    }
}


// void rec_sort(std::vector<int>::iterator &v)
// {
//     // if (*v.empty())
//         // return ;

    
//      return (rec_sort(v + 1))
    

// }


// void rec_sort(const std::vector<int> & v, std::vector<int> & s)
// {
//     if (v.empty())
//         return ;
//     if (v.size() == 1)
//         v.
// }

int main(int ac, char **av)
{
 
    std::vector<int> v;// = {2,34,67,13,36,100, -1};

    select_sort(v);
    // selection_sort(v);


    for (int x : v) std::cout << x << ' ';
    std::cout  << '\n';


    // find_max(v);
    // std::cout << rec_max(v) << std::endl;

    // size_t  d = std::distance(v.begin(), v.end());
    
    // // int arr[(v.size() + 1) / 2];
    // // int arr2[(v.size() + 1) / 2];

    // std::vector<int>::iterator mid;
    // // std::advance(mid, v.size() / 2);

    // // // or 
    // mid  = v.begin() + (v.size() + 1) / 2;
    
    // std::vector<int> left(v.begin(), mid);
    // std::vector<int> right(mid, v.end());


    // for (int x : left) std::cout << x << ' ';
    // std::cout  << '\n';

    // for (int x: right) std::cout << x << ' ';
    // std::cout  << '\n';

    // int size = (v.size());
    
    // int main_seq[size];
    // int small[size];


    // size_t i = 0, j = 0;

    // while (i < size)
    // {
    //     main_seq[j] = std::max(v[i], v[i+1]);
    //     small[j++] = std::min(v[i], v[i+1]);
    //     i += 2;
    // }

    // if (size % 2 == 1)
    //     main_seq[j] = v[i];

    // for (int i = 0; i < size / 2 + (size % 2 == 1); ++i)
    //     std::cout << main_seq[i] << ' ';

    // std::cout << '\n';
    // for (int i = 0; i < size / 2 ; ++i)
    //     std::cout << small[i] << ' ';
    // std::cout << '\n';

    // std::cout << "size => " << size / 2 + (size % 2 == 1) << std::endl; 



    return (0);
}
