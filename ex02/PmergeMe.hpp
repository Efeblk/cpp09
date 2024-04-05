#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <ctime>
#include <iomanip>

class PmergeMe
{
private:
    std::vector<int> vector;
    std::deque<int> deque;
public:
    PmergeMe();
    ~PmergeMe();
    void sort(char **av);
    template<typename T>
    void fordJohnson(T& av);
    template<typename T>
    void insertion(T& av);
    template<typename T>
    void print(T& container);
};

#endif