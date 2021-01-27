#include "executor.h"

#include <sstream>

struct operation {
    operation_type_t type;
    double a, b;
};

operation parse(std::string &raw) {
    std::istringstream data(raw);
    operation res{};

    std::string part;
    data >> part;
    res.type = static_cast<operation_type_t>(std::stoi(part));
    data >> part;
    res.a = std::stod(part);
    data >> part;
    res.b = std::stod(part);

    return res;
}

std::string calc(std::string &raw) {
    auto op = parse(raw);
    switch (op.type) {
        case SUM:
            return std::to_string(op.a + op.b);
        case MUL:
            return std::to_string(op.a * op.b);
        case SQUARE_SUM:
            return std::to_string(op.a * op.a + op.b * op.b);
    }
}

