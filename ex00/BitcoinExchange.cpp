#include "BitcoinExchange.hpp"

int getIntDate(std::string str)
{
	std::stringstream ss(str);
	std::string year;
	std::string month;
	std::string day;

	getline(ss, year, '-');
	getline(ss, month, '-');
	getline(ss, day, '-');

	int IntYear = stoi(year);
	IntYear -= 2009;
	int IntMonth = stoi(month);
	IntMonth -= 1;
	int rt = stoi(day);
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