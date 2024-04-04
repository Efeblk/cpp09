#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::read_db()
{
	std::ifstream dataBase("data.csv");
	if (dataBase.is_open())
	{	
		std::string line;
		std::string date;
		std::string value;
		std::getline(dataBase, line);
		if (line != "date,exchange_rate")
		{
			std::cout << "Error: Database header is invalid!" << std::endl;
			dataBase.close();
			return;
		}
		while (std::getline(dataBase, line))
		{
			std::stringstream ss(line);
			if (charCount(line, ',') != 1)
			{
				std::cout << "Error: Database line has invalid arguman count = " << line << "!" << std::endl;
				dataBase.close();
			}
			std::getline(ss, date, ',');
			std::getline(ss, value, ',');
			if (checkDate(date) == -1)
			{
				std::cout << "Error: Invalid date found in database = " << date << "!" << std::endl;
				dataBase.close();
				return;
			}
			else if (checkValue(value) == -1)
			{
				std::cout << "Error: Invalid value found in database = " << line << "!" << std::endl;
				dataBase.close();
				return;
			}
			dataMap[getIntDate(date)] = getIntValue(value);
			ss.clear();
		}
	}
	else
	{
		std::cout << "Error: Database did not found!" << std::endl;
	}
}

void BitcoinExchange::read_input(std::string file_name)
{
	std::ifstream dataBase(file_name);
	if (dataBase.is_open())
	{	
		std::string line;
		std::string date;
		std::string value;
		std::getline(dataBase, line);
		if (line != "date | value")
		{
			std::cout << "Error: Database header is invalid!" << std::endl;
			dataBase.close();
			return;
		}
		while (std::getline(dataBase, line))
		{
			std::stringstream ss(line);
			if (charCount(line, '|') != 1)
			{
				std::cout << "Error: Database line has invalid arguman count = " << line << "!" << std::endl;
				continue;
			}
			std::getline(ss, date, '|');
			std::getline(ss, value, '|');
			if (checkDate(date) == -1)
			{
				std::cout << "Error: Invalid date found in database = " << date << "!" << std::endl;
				continue;
			}
			else if (checkValue(value) == -1)
			{
				std::cout << "Error: Invalid value found in database = " << line << "!" << std::endl;
				continue;
			}
			std::cout << date << " | " << value << " | " << getValue(dataMap, getIntDate(date), getIntValue(value)) << std::endl;
			ss.clear();
		}
	}
	else
	{
		std::cout << "Error: Database did not found!" << std::endl;
	}
}

int BitcoinExchange::charCount(std::string str, char ch)
{
	int count = 0;

	for (int i = 0; str[i]; i++)
	{
		if (str[i] == ch)
			count++;
	}
	return (count);
}

int BitcoinExchange::is_num(std::string str)
{
	for (int i = 0; str[i]; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
	}
	return (1);

}

int BitcoinExchange::checkDate(std::string str)
{
	std::stringstream ss(str);
	std::string year;
	std::string month;
	std::string day;

	if (charCount(str, '-') != 2)
		return (-1);
	getline(ss, year, '-');
	getline(ss, month, '-');
	getline(ss, day, ' ');

	if (is_num(year) == -1 ||  is_num(month) == -1 || is_num(day) == -1)
		return (-1);

	int IntYear = std::stoi(year);
	int IntMonth = std::stoi(month);
	int IntDay = std::stoi(day);
	int IsLeap = 0;

	if (IntYear < 2009)
		return (-1);
	if (IntYear % 4 == 0)
		IsLeap = 1;
	if (IntMonth < 1 || IntMonth > 12)
		return (-1);
	if (IntMonth == 1 || IntMonth == 3 || IntMonth == 5 || IntMonth == 7 || IntMonth == 8 || IntMonth == 10 || IntMonth == 12)
		if (IntDay < 1 || IntDay > 31)
			return (-1);
	if (IntMonth == 4 || IntMonth == 6 || IntMonth == 9 || IntMonth == 11)
		if (IntDay < 1 || IntDay > 30)
			return (-1);
	if (IntMonth == 2)
	{
		if (IsLeap == 1)
			if (IntDay < 1 || IntDay > 29)
				return (-1);
		if (IsLeap == 0)
			if (IntDay < 1 || IntDay > 28)
				return (-1);
	}
	return (1);
}

int BitcoinExchange::checkValue(std::string str)
{
	try
	{
		int number = stoi(str);
		if (number < 0 || number > 2147483647)
		{
			return (-1);
		}
	}
	catch(const std::exception& e)
	{

		return (-1);
	}
	int flag = 0;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			i++;
		}
		if (str[i] == '.')
		{
			if (flag == 1)
				return (-1);
			flag++;
			i++;
		}
	}

	return (1);
}

int BitcoinExchange::getIntDate(std::string str)
{
	std::stringstream ss(str);
	std::string year;
	std::string month;
	std::string day;

	getline(ss, year, '-');
	getline(ss, month, '-');
	getline(ss, day, '-');

	int IntYear = std::stoi(year);
	IntYear -= 2009;
	int IntMonth = std::stoi(month);
	IntMonth -= 1;
	int rt = std::stoi(day);
	int IsLeap = IntYear % 4;

	while (IntYear > 0)
	{
		if (IntYear % 4 == 0)
			rt += 366;
		else
			rt += 365;
		IntYear--;
	}
	while (IntMonth > 0)
	{
		if (IntMonth == 1 || IntMonth == 3 || IntMonth == 5 || IntMonth == 7 || IntMonth == 8 || IntMonth == 10 || IntMonth == 12)
			rt += 31;
		if (IntMonth == 4 || IntMonth == 6 || IntMonth == 9 || IntMonth == 11)
			rt += 30;
		if (IntMonth == 2)
		{
			if (IsLeap == 0)
				rt += 29;
			if (IsLeap == 0)
				rt += 28;
		}
		IntMonth--;
	}
	return (rt);
}

double BitcoinExchange::getIntValue(std::string str)
{
	return (std::stod(str));
}


double BitcoinExchange::getValue(std::map<int, double> dataMap, int date, double value)
{
	std::map<int, double>::iterator it = dataMap.lower_bound(date);
	
	if (it->first == date)
	{
			return (it->second * value);
	}
	else
	{
		it--;
			return (it->second * value);
	}
}