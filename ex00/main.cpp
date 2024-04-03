#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac == 2)
	{
		BitcoinExchange exchange;
		exchange.read(av[1]);
	}
	else
	{
		std::cout << "Error: Invalid arguman count!" << std::endl;
	}
	return (1);
}