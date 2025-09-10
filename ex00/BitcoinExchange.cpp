#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <climits>

BitcoinExchange::BitcoinExchange() {

}



BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _prices(other._prices) {

}



BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
     if (this != &other) 
        _prices = other._prices; 
        
    return *this; 
}


BitcoinExchange::~BitcoinExchange() {

}


bool BitcoinExchange::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool BitcoinExchange::isValidDate(const std::string &date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') 
        return false;

    int y, m, d;
    std::istringstream iss(date.substr(0,4) + ' ' +  date.substr(5,2) + ' ' + date.substr(8,2));
    
    if (!(iss >> y >> m >> d))
       return false;
    
    if (y < 0 || m < 1 || m > 12 || d < 1)
        return false;
    
    int mdays[] = {31, (isLeapYear(y) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (d > mdays[m-1])
        return false;

    return true;
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



bool BitcoinExchange::stringToDouble(const std::string &s, double &out) {
    char *end = 0;
    out = std::strtod(s.c_str(), &end);
    if (*s.c_str() == '\0' || *end != '\0') return false;
    return true;
}



bool BitcoinExchange::parseLine(const std::string &line, std::string &date, double &value) {
    size_t sep = line.find('|');
    if (sep == std::string::npos)
        return false;
    date = trim(line.substr(0, sep));
    if (date.size() && date[date.size()-1] == '-')
        return false;
    std::string valueStr = trim(line.substr(sep + 1));
    if (!isValidDate(date))
        return false;
    if (!stringToDouble(valueStr, value))
        return false;
    return true;
}

double BitcoinExchange::getRateForDate(const std::string &date) const {
    std::map<std::string, double>::const_iterator it = _prices.lower_bound(date);
    if (it != _prices.end() && it->first == date)
        return it->second;
    if (it == _prices.begin()) throw std::runtime_error("No earlier date in database");
    if (it == _prices.end() || it->first > date)
        --it;
    return it->second;
}

void BitcoinExchange::loadPriceDatabase(const std::string &csvPath) {
    std::ifstream f(csvPath.c_str());
    if (!f) throw std::runtime_error("Error: could not open file.");
    std::string line;
    double rate;

    if (!std::getline(f, line))
        throw std::runtime_error("Error: empty database file.");

    while (std::getline(f, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string date, rateStr;
        if (std::getline(iss, date, ',') && std::getline(iss, rateStr)) {
            date = trim(date);
            rateStr = trim(rateStr);
            
            if (!isValidDate(date)) continue;
            if (!stringToDouble(rateStr, rate)) continue;

            _prices[date] = rate;
        }
    }
    if (_prices.empty()) throw std::runtime_error("Error: no valid data in database.");
}

void BitcoinExchange::evaluateInputFile(const std::string &inputPath) const {
    std::ifstream f(inputPath.c_str());
    if (!f) throw std::runtime_error("Error: could not open file.");
    std::string line;
    if (std::getline(f, line)) {}
    while (std::getline(f, line)) {
        if (line.empty()) continue;
        std::string date; double value;
        if (!parseLine(line, date, value)) {
            if (line.find('|') == std::string::npos) {
                std::cerr << "Error: bad input => " << line << std::endl;
            } else {
                std::cerr << "Error: bad input => " << line << std::endl;
            }
            continue;
        }

        if (value < 0) {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }

        if (value > 1000) {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        try {
            double rate = getRateForDate(date);
            double result = rate * value;
            std::cout.setf(std::ios::fixed);
            std::cout.precision(2);
            std::cout << date << " => " << value << " = " << result << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
