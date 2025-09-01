#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

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

    // Evaluate an input file containing lines of the form "date | value"
    void evaluateInputFile(const std::string &inputPath) const;

private:
    std::map<std::string, double> _prices; // key: date (YYYY-MM-DD), value: rate

    static bool isValidDate(const std::string &date);
    static bool isLeapYear(int year);
    static std::string trim(const std::string &s);
    static bool parseLine(const std::string &line, std::string &date, double &value);
    static bool stringToDouble(const std::string &s, double &out);

    // Find rate for date or closest earlier date
    double getRateForDate(const std::string &date) const;
};

#endif // BITCOINEXCHANGE_HPP
