#pragma once

#include "../data/TreeRules.h"
#include <stack>
#include <vector>

namespace Tree {
class LindenmayerEncoder {

public:
    LindenmayerEncoder();

    std::string encode(const std::vector<OperationOrRule>& system);

    std::vector<OperationOrRule> decode(const std::string& system);

        std::string encode(const std::vector<Operation>& system);

    std::vector<Operation> decodeOps(const std::string& system);

private:
};
}