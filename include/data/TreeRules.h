#pragma once

#include "../debug.h"
#include <stdexcept>
#include <unordered_map>
#include <variant>
#include <vector>

namespace Tree {
enum Operation {
    Push,
    Pop,

    MoveRight,
    MoveLeft,

    RotateLeft,
    RotateRight,

    Advance,
};

using Rule = char;

extern std::unordered_map<Operation, Rule> OperationCodes;
extern std::unordered_map<Rule, Operation> OperationCodesReversed;

struct OperationOrRule {
    std::variant<Operation, Rule> operationOrRule;

    Rule getRule() const { return std::get<Rule>(operationOrRule); };

    Operation getOperation() const { return std::get<Operation>(operationOrRule); };

    OperationOrRule(Operation operation)
        : operationOrRule(operation) {};

    OperationOrRule(Rule rule)
        : operationOrRule(rule)
    {
#if RUNTIME_CHECKS
        for (const auto& pair : OperationCodes) {
            if (pair.first == rule) {
                throw std::invalid_argument("Rule cannot be a reserved character");
            }
        }
#endif
    };

    bool isOperation() const { return std::holds_alternative<Operation>(operationOrRule); }

    bool isRule() const { return std::holds_alternative<Rule>(operationOrRule); }
};

struct RuleDefinition {

    std::vector<OperationOrRule> operationsOrRules;

    float weight;

    RuleDefinition(std::vector<OperationOrRule> operationsOrRules, float weight)
        : operationsOrRules(operationsOrRules)
        , weight(weight) {};

    RuleDefinition(std::vector<OperationOrRule> operationsOrRules)
        : operationsOrRules(operationsOrRules)
        , weight(1.f) {};
};

using RuleMap = std::unordered_map<Rule, std::vector<RuleDefinition>>;
}