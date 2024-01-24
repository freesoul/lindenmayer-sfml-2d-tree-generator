#pragma once

#include "../data/TreeRules.h"
#include <stack>
#include <vector>

namespace Tree {
class LindenmayerBuilder {

public:
    LindenmayerBuilder();

    void setRuleMap(RuleMap& rules);

    std::vector<OperationOrRule> build(const char& axiom, unsigned int numIterations);

    std::vector<Operation> cleanNOOPs(const std::vector<OperationOrRule>& axiom);

private:
    std::vector<OperationOrRule> expand(const std::vector<OperationOrRule>& system);
    std::vector<OperationOrRule> pickRandomRule(const std::vector<RuleDefinition>& outcomes);

    RuleMap m_rules;
    char m_axiom;
};
}