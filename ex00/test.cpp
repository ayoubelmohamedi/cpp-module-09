

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <map>



bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

std::string trim(std::string line)
{
    size_t start = 0;
    size_t end = line.size();

    while ((start < end) && (line[start] == ' ' || line[start] == '\t'))
        start++;
    while ((start < end) && ((line[end - 1] == ' ' || line[end - 1] == '\t')))
        end++;
    return (line.substr(start, end - start));
}


int main(int argc, char **argv) {

    std::string line =  "  2011-01-03 | 3 ";



    size_t pos = line.find('|');

    std::string date = trim(line.substr(0, pos));
    std::string value =  trim(line.substr(pos + 1));
    
    std::map <std::string, float> _prices;

    _prices[date] = std::stof(value);

    
    std::map <std::string, float>::const_iterator it = _prices.begin();
    while (it != _prices.end())
    {
        std::cout << "keys: " << it->first << " val: " << it->second << std::endl;
        ++it;
    }


    std::cout  << date << std::endl;
    std::cout  << value << std::endl;
  

    return (0);

}

