#include <cstdlib> // For seeding rand
#include <ctime> // For seeding rand
#include <memory>

#include <SFML/Graphics.hpp>

#include "core/LindenmayerBuilder.h"
#include "core/LindenmayerEncoder.h"
#include "core/TreeGenerator.h"

using Op = Tree::Operation;

int main()
{
    srand(time(0));

    // Don't buffer output, for debug
    setvbuf(stdout, NULL, _IONBF, 0);

    Tree::RuleMap rules;
    rules['s'].push_back(
        { { Op::Advance, Op::Push, Op::RotateRight, 's', Op::Pop, Op::Push, Op::RotateLeft, 's', Op::Pop, 's' }, 3.0 });
    rules['s'].push_back({ { Op::Advance,Op::Push, Op::RotateRight, Op::Advance, Op::Pop, 's' }, 1.0 });
    rules['s'].push_back({ { Op::Advance,Op::Push, Op::RotateLeft, Op::Advance, Op::Pop, 's' }, 1.0 });

    Tree::LindenmayerBuilder builder;
    builder.setRuleMap(rules);

    auto tree = builder.build('s', 8);
    auto cleaned = builder.cleanNOOPs(tree);

    Tree::TreeParams params;
    params.woodTexture = std::make_shared<sf::Texture>();
    params.woodTexture->loadFromFile("assets/barks/bark.jpg");

    Tree::TreeParams::LeafOrFlowerData leafData;
    leafData.texture = std::make_shared<sf::Texture>();
    leafData.texture->loadFromFile("assets/leaves/leaf.png");
    params.leafTexture.push_back(leafData);

    Tree::TreeParams::LeafOrFlowerData flowerData;
    flowerData.texture = std::make_shared<sf::Texture>();
    flowerData.texture->loadFromFile("assets/flowers/flower.png");
    params.flowerTexture.push_back(flowerData);

    Tree::TreeGenerator generator;
    generator.setParams(params);
    generator.generateTree(cleaned);
    auto sprite = generator.getSprite();

    sprite.setPosition(params.canvasSize.x / 2, params.canvasSize.y);

    sf::RenderWindow window(sf::VideoMode(800, 600), "My Game");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}