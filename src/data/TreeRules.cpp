#include "../include/data/TreeRules.h"

namespace Tree {

std::unordered_map<Operation, Rule> OperationCodes = {
    { Operation::Push, '[' },
    { Operation::Pop, ']' },
    { Operation::MoveRight, '>' },
    { Operation::MoveLeft, '<' },
    { Operation::RotateLeft, '+' },
    { Operation::RotateRight, '-' },
    { Operation::Advance, 'a' },
};

std::unordered_map<Rule, Operation> OperationCodesReversed = {
    { '[', Operation::Push },
    { ']', Operation::Pop },
    { '>', Operation::MoveRight },
    { '<', Operation::MoveLeft },
    { '+', Operation::RotateLeft },
    { '-', Operation::RotateRight },
    { 'a', Operation::Advance },
};
}