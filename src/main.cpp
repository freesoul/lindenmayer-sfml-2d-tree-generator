#include <cstdlib> // For seeding rand
#include <ctime> // For seeding rand
#include <memory>

#include <SFML/Graphics.hpp>

// #include <TreeGenerator.h>
#include "core/LindenmayerBuilder.h"
#include "core/LindenmayerEncoder.h"

using Op = Tree::Operation;

int main()
{
    srand(time(0));

    // Don't buffer output, for debug
    setvbuf(stdout, NULL, _IONBF, 0);

    Tree::RuleMap rules;
    rules['s'].push_back({ { Op::Push, Op::RotateRight, 's', Op::Pop, Op::Push, Op::RotateLeft, 's', Op::Pop, 's' }, 3.0 });
    rules['s'].push_back({ { Op::Push, Op::RotateRight, Op::Advance, Op::Pop, 's' }, 1.0 });
    rules['s'].push_back({ { Op::Push, Op::RotateLeft, Op::Advance, Op::Pop, 's' }, 1.0 });

    Tree::LindenmayerBuilder builder;
    builder.setRuleMap(rules);

    auto tree = builder.build('s', 5);
    auto cleaned = builder.cleanNOOPs(tree);

    Tree::LindenmayerEncoder encoder;
    auto encoded = encoder.encode(tree);
    printf("Encoded: %s\n", encoded.c_str());

    auto encoded_cleaned = encoder.encode(cleaned);
    printf("Cleaned: %s\n", encoded_cleaned.c_str());

    // auto textureBark = std::make_shared<sf::Texture>();
    // textureBark->loadFromFile("assets/barks/bark.jpg");

    // auto textureBranch = textureBark;

    // auto textureLeaf = std::make_shared<sf::Texture>();
    // textureLeaf->loadFromFile("assets/leaves/leaf.png");

    // auto textureFlower = std::make_shared<sf::Texture>();
    // textureFlower->loadFromFile("assets/flowers/flower.png");

    // Tree::TreeParams params;
    // params.barkTexture = textureBark;
    // params.branchTexture = textureBranch;
    // params.leafTexture = textureLeaf;
    // params.flowerTexture = textureFlower;

    // auto tree = Tree::TreeGenerator();
    // tree.setParams(params);
    // auto rules = tree.generateRules(3);
    // tree.generateTree(rules);

    // auto sprite = tree.getSprite();
    // sprite.setPosition(400, 600);

    sf::RenderWindow window(sf::VideoMode(800, 600), "My Game");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        // window.draw(sprite);
        window.display();
    }
    return 0;
}