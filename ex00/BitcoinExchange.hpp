
#pragma once

#include <string>
#include <map>
#include <stdexcept>

class BitcoinExchange {
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

    void loadPriceDatabase(const std::string &csvPath);

    void evaluateInputFile(const std::string &inputPath) const;

private:
    std::map<std::string, double> _prices;

    static bool isValidDate(const std::string &date);
    static bool isLeapYear(int year);
    static std::string trim(const std::string &s);
    static bool parseLine(const std::string &line, std::string &date, double &value);
    static bool stringToDouble(const std::string &s, double &out);

    double getRateForDate(const std::string &date) const;
};

 
