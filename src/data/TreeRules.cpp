#include "../include/data/TreeRules.h"

namespace Tree {

std::unordered_map<Operation, Rule> OperationCodes = {
    { Operation::Push, '[' },
    { Operation::Pop, ']' },
    { Operation::MoveRight, '>' },
    { Operation::MoveLeft, '<' },
    { Operation::RotateLeft, '+' },
    { Operation::RotateRight, '-' },
    { Operation::AdvanceBranch, 'a' },
    { Operation::AdvanceBark, 'b' },
};

std::unordered_map<Rule, Operation> OperationCodesReversed = {
    { '[', Operation::Push },
    { ']', Operation::Pop },
    { '>', Operation::MoveRight },
    { '<', Operation::MoveLeft },
    { '+', Operation::RotateLeft },
    { '-', Operation::RotateRight },
    { 'a', Operation::AdvanceBranch },
    { 'b', Operation::AdvanceBark },
};
}