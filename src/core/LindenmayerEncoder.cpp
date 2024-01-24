#include "../include/core/LindenmayerEncoder.h"

namespace Tree {

LindenmayerEncoder::LindenmayerEncoder() { }

std::string LindenmayerEncoder::encode(const std::vector<OperationOrRule>& system)
{
    std::string encoded;
    for (const auto& op : system) {
        if (op.isRule()) {
            encoded.push_back(op.getRule());
        } else {
            encoded.push_back(OperationCodes.at(op.getOperation()));
        }
    }
    return encoded;
}

std::vector<OperationOrRule> LindenmayerEncoder::decode(const std::string& system)
{
    std::vector<OperationOrRule> decoded;
    for (const auto& op : system) {
        if (OperationCodesReversed.find(op) != OperationCodesReversed.end()) {
            decoded.push_back(OperationCodesReversed.at(op));
        } else {
            decoded.push_back(op);
        }
    }
    return decoded;
}

std::string LindenmayerEncoder::encode(const std::vector<Operation>& system)
{
    std::string encoded;
    for (const auto& op : system) {
        encoded.push_back(OperationCodes.at(op));
    }
    return encoded;
}

std::vector<Operation> LindenmayerEncoder::decodeOps(const std::string& system)
{
    std::vector<Operation> decoded;
    for (const auto& op : system) {
        decoded.push_back(OperationCodesReversed.at(op));
    }
    return decoded;
}

}
