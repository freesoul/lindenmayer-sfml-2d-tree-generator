
#include "../include/core/LindenmayerBuilder.h"
#include <debug.h>
#include <stack>

namespace Tree {
LindenmayerBuilder::LindenmayerBuilder() { }

void LindenmayerBuilder::setRuleMap(RuleMap& rules) { m_rules = rules; }

std::vector<OperationOrRule> LindenmayerBuilder::build(const char& axiom, unsigned int numIterations)
{
    std::vector<OperationOrRule> operations = pickRandomRule(m_rules.at(axiom));

    for (int i = 0; i < numIterations; ++i) {
        operations = expand(operations);

#if DEBUG_LINDERNMAYER
        for (auto op : operations) {
            printf("%d ", op);
        }
        printf("\n");
#endif
    }
    return operations;
}

std::vector<OperationOrRule> LindenmayerBuilder::expand(const std::vector<OperationOrRule>& system)
{
    std::vector<OperationOrRule> newSystem;
    for (const auto& op : system) {
        if (op.isOperation()) {
            newSystem.push_back(op);
        } else {
            char rule = std::get<char>(op.operationOrRule);
            if (m_rules.find(rule) != m_rules.end()) {
                auto replacementOperation = pickRandomRule(m_rules.at(rule));
                newSystem.insert(newSystem.end(), replacementOperation.begin(), replacementOperation.end());
            }
        }
    }
    return newSystem;
}

std::vector<OperationOrRule> LindenmayerBuilder::pickRandomRule(const std::vector<RuleDefinition>& outcomes)
{
    double totalProbability = 0;
    for (const auto& outcome : outcomes) {
        totalProbability += outcome.weight;
    }

    double randomValue = (std::rand() / static_cast<double>(RAND_MAX)) * totalProbability;
    double cumulativeProbability = 0;
    for (const auto& outcome : outcomes) {
        cumulativeProbability += outcome.weight;
        if (randomValue <= cumulativeProbability) {
            return outcome.operationsOrRules;
        }
    }

    // Fallback in case of rounding errors
    return outcomes.back().operationsOrRules;
}

std::vector<Operation> LindenmayerBuilder::cleanNOOPs(const std::vector<OperationOrRule>& operations_or_rules)
{
    std::vector<Operation> operations;
    for (auto op : operations_or_rules) {
        if (op.isOperation()) {
            operations.push_back(std::get<Operation>(op.operationOrRule));
        }
    }
    return operations;
}

}