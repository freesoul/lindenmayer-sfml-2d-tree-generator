#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <string>

namespace Tree {
struct TreeParams {
    sf::Vector2f canvasSize = sf::Vector2f(800, 600);

    float baseBranchLength = 50;

    float baseBranchWidth = 15;

    float baseBarkLength = 50;

    float baseBarkWidth = 15;

    float branchPushLengthReduction = 0.9;

    float branchPushWidthReduction = 0.8;

    float branchAdvanceLengthReduction = 0.95;

    float branchAdvanceWidthReduction = 0.8;

    float barkPushLengthReduction = 1;

    float barkPushWidthReduction = 1;

    float barkAdvanceLengthReduction = 0.8;

    float barkAdvanceWidthReduction = 0.70;

    sf::Vector2f angle = sf::Vector2f(10, 30);

    struct LeafFlowerProbabilities {
        float nothing = 0;
        float leaf = 0.5;
        float flower = 0.5;
    } elementProbability;

    struct LeafOrFlowerData {
        std::shared_ptr<sf::Texture> texture;
        unsigned int numPerBranch = 4;
        unsigned int minDepth = 0;
        unsigned int maxDepth = 99;
        bool isFruit = false;
        sf::Vector2f scale = { 1.0, 1.0 };
    };

    std::vector<LeafOrFlowerData> leafTexture;

    std::vector<LeafOrFlowerData> flowerTexture;

    std::shared_ptr<sf::Texture> woodTexture;

    TreeParams() = default;
};
}
