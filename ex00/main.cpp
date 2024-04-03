#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./btc <file_name>" << std::endl;
        return 1;
    }
    std::map<int, double> map;
    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "Error: file not found" << std::endl;
        return 1;
    }
    std::string line;
    std::string date;
    std::string value;
    int i = 0;
    while(std::getline(file, line))
    {
        std::stringstream ss(line);
        std::getline(ss, date, '|');
        std::getline(ss, value, ',');
        try
        {
            int a = BitcoinExchange::getIntDate(date);
            std::cout << a << std::endl;
            map[i] = std::stod(value);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        i++;
    }
    file.close();
    for (std::map<int, double>::iterator it = map.begin(); it != map.end(); it++)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }
    return 0;
}
