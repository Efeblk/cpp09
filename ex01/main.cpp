#include "RPN.hpp"

int main(int ac, char **av) {
    (void)ac;
    RPN rpn;
    rpn.rpn(av[1]);
    return 0;
}