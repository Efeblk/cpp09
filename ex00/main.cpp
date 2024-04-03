#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	std::string CSV;
	std::map<std::string, double> dataMap;
	
	int flag = 0;

	if (ac == 2)
	{
		std::ifstream dataBase(av[1]);
		if (dataBase.is_open())
		{	
			std::string line;
			std::string date;
			std::string value;
			while (std::getline(dataBase, line))
			{
				std::stringstream ss(line);
				if (BitcoinExchange::charCount(line, '|') != 1)
				{
					std::cout << "Error: Database line has invalid arguman count = " << line << "!" << std::endl;
					dataBase.close();
					return (1);
				}
				std::getline(ss, date, '|');
				std::getline(ss, value, '|');
				if (date == "date" || value == "exchange_rate")
				{
					flag++;
					if (flag > 1)
					{
						std::cout << "Error: Database has more than one format line count = " << line << "!" << std::endl;
						dataBase.close();
						return (1);
					}
					continue;
				}
				else if (BitcoinExchange::checkDate(date) == -1)
				{
					std::cout << "Error: Invalid date found in database = " << date << "!" << std::endl;
					dataBase.close();
					return (1);
				}
				else if (BitcoinExchange::checkValue(value) == -1)
				{
					std::cout << "Error: Invalid value found in database = " << line << "!" << std::endl;
					dataBase.close();
					return (1);
				}
				dataMap[date] = BitcoinExchange::getIntValue(value);
				ss.clear();
			}
		}
		else
		{
			std::cout << "Error: Database did not found!" << std::endl;
		}
	}
	else
	{
		std::cout << "Error: Invalid arguman count!" << std::endl;
	}
	return (1);
}