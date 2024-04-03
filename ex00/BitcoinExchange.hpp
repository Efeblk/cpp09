#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

class BitcoinExchange {
private:
    std::map<int, double> dataMap;
public:
    BitcoinExchange();
    ~BitcoinExchange();
    void read(std::string file_name);
    static int getIntDate(std::string str);
    static double getIntValue(std::string str);
    static int checkDate(std::string str);
    static int checkValue(std::string str);
    static int charCount(std::string str, char c);
    static int is_num(std::string str);
    static double getValue(std::map<int, double> dataMap, int date, double value);
};  

#endif