#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::~PmergeMe()
{
}

template<typename T>
void PmergeMe::print(T& container)
{
    for (typename T::iterator it = container.begin(); it != container.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::sort(char **av)
{
    std::clock_t startTime_deque = std::clock();
    int i = 1;
    while(av[i])
    {
        if(isdigit(*av[i]) == 0)
        {
            std::cerr << "Error: Invalid input" << std::endl;
            return;
        }
        deque.push_back(atoi(av[i]));
        i++;
    }
    std::cout << "Before: ";
    print(deque);
    fordJohnson(deque);
    std::clock_t endTime_deque = std::clock();

    std::clock_t startTime_vector = std::clock();
    i = 1;
    while(av[i])
    {
        vector.push_back(atoi(av[i]));
        i++;
    }
    fordJohnson(vector);
    std::cout << "After: ";
    print(deque);
    std::clock_t endTime_vector = std::clock();

    double duration_deque = 10.0 * static_cast<double>(endTime_deque - startTime_deque) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << deque.size() << " elements with std::deque: "<< duration_deque << " us\n";
    double duration_vector = 10.0 * static_cast<double>(endTime_vector - startTime_vector) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << vector.size() << " elements with std::vector: "<<duration_vector << " us\n";

}

template<typename T>
void PmergeMe::fordJohnson(T& av) {
    if (av.size() < 2) return;

    int mid = av.size() / 2;
    T left(av.begin(), av.begin() + mid);
    T right(av.begin() + mid, av.end());

    insertion(left);
    insertion(right);

    if (left.size() > right.size()) {
        std::swap(left, right);
    }

    T result;
    typename T::iterator leftIt = left.begin();
    typename T::iterator rightIt = right.begin();
    while (rightIt != right.end()) {
        if (leftIt == left.end() || *rightIt < *leftIt) {
            result.push_back(*rightIt);
            ++rightIt;
        } else {
            result.push_back(*leftIt);
            ++leftIt;
        }

        if (std::distance(leftIt, left.end()) < std::distance(rightIt, right.end())) {
            std::swap(leftIt, rightIt);
            std::swap(left, right);
        }
    }
    result.insert(result.end(), leftIt, left.end());
    av = result;
}

template<typename T>
void PmergeMe::insertion(T& av)
{
    unsigned long i = 1;
    int j = 0;
    int tmp = 0;
    while (i < av.size())
    {
        tmp = av[i];
        j = i - 1;
        while (j >= 0 && av[j] > tmp)
        {
            av[j + 1] = av[j];
            j--;
        }
        av[j + 1] = tmp;
        i++;
    }
}