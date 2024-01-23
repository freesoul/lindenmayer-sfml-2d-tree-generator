#include <SFML/System/Vector2.hpp>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>

namespace Tree
{
    struct TreeParams
    {
        sf::Vector2f canvasSize = sf::Vector2f(800, 600);

        sf::Vector2f origin = sf::Vector2f(400, 600);

        float baseBranchLength = 100;

        float baseBranchWidth = 10;

        float baseBranchAngle = 20;

        float baseScaleDown = 0.8;

        std::shared_ptr<sf::Texture> barkTexture;

        std::shared_ptr<sf::Texture> leafTexture;

        std::shared_ptr<sf::Texture> branchTexture;

        std::shared_ptr<sf::Texture> flowerTexture;

        TreeParams() = default;
    };
}
