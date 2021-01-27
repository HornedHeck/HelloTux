#ifndef HELLOTUX_EXECUTOR_H
#define HELLOTUX_EXECUTOR_H

#include <string>

enum operation_type_t{
    SUM = 1,
    MUL = 2,
    SQUARE_SUM = 3
};

std::string calc(std::string &raw);

#endif //HELLOTUX_EXECUTOR_H
