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


    // Start olive tree rules
    Tree::RuleMap rules;

    // Tree base
    rules['s'].push_back({ { 
        // Start trunk
        Op::AdvanceBark, Op::AdvanceBark, Op::AdvanceBark,
        
        // Branch left & right
        Op::Push, Op::RotateRight,Op::RotateRight,Op::RotateRight, Op::AdvanceBranch, Op::RotateLeft, Op::AdvanceBranch,'c', Op::Pop,
        Op::Push, Op::RotateLeft,Op::RotateLeft,Op::RotateLeft, Op::AdvanceBranch,Op::RotateRight, Op::AdvanceBranch, 'c', Op::Pop,  

        // Advance trunk
        Op::AdvanceBark,
        
        // Branch left & right
        Op::Push, Op::RotateRight, Op::RotateRight, 'c', Op::Pop,
        Op::Push, Op::RotateLeft,  Op::RotateLeft, 'c', Op::Pop,  
        
        // Advance trunk
        Op::AdvanceBark,
        
        // Branch left & right
        Op::Push, Op::RotateRight,'c', Op::Pop,
        Op::Push, Op::RotateLeft, 'c', Op::Pop,  
        },
        1.0 });

    // Branch definition
    rules['c'].push_back({ { Op::AdvanceBranch, Op::Push, Op::RotateRight, 'c', Op::Pop, Op::Push, Op::RotateLeft, 'c', Op::Pop, 'c' }, 4.0 });
    rules['c'].push_back({ { Op::AdvanceBranch, Op::AdvanceBranch, Op::Push, Op::RotateRight, 'c', Op::Pop, Op::Push, Op::RotateLeft, 'c', Op::Pop, 'c' }, 1.0 });

    // Build the lindenmayer sequence
    Tree::LindenmayerBuilder builder;
    builder.setRuleMap(rules);

    auto tree = builder.build('s', 4);
    auto cleaned = builder.cleanNOOPs(tree);

    // Define rendering params for the olive tree
    Tree::TreeParams params;
    params.woodTexture = std::make_shared<sf::Texture>();
    params.woodTexture->loadFromFile("assets/barks/bark_brown.png");

    params.angle = sf::Vector2f(20, 30);
    params.barkAdvanceWidthReduction = 0.95;
    params.baseBarkWidth = 50;

    // Leaves
    {
        Tree::TreeParams::LeafOrFlowerData leafData;
        leafData.texture = std::make_shared<sf::Texture>();
        leafData.texture->loadFromFile("assets/leaves/olive_leaf_1.png");
        params.leafTexture.push_back(leafData);
    }

    {
        Tree::TreeParams::LeafOrFlowerData leafData;
        leafData.texture = std::make_shared<sf::Texture>();
        leafData.texture->loadFromFile("assets/leaves/olive_leaf_2.png");
        params.leafTexture.push_back(leafData);
    }

    {
        Tree::TreeParams::LeafOrFlowerData leafData;
        leafData.texture = std::make_shared<sf::Texture>();
        leafData.texture->loadFromFile("assets/leaves/olive_leaf_3.png");
        params.leafTexture.push_back(leafData);
    }

    // Flowers
    {
        Tree::TreeParams::LeafOrFlowerData flowerData;
        flowerData.texture = std::make_shared<sf::Texture>();
        flowerData.texture->loadFromFile("assets/flowers/olive_1.png");
        params.flowerTexture.push_back(flowerData);
    }
    {
        Tree::TreeParams::LeafOrFlowerData flowerData;
        flowerData.texture = std::make_shared<sf::Texture>();
        flowerData.texture->loadFromFile("assets/flowers/olive_2.png");
        params.flowerTexture.push_back(flowerData);
    }
    {
        Tree::TreeParams::LeafOrFlowerData flowerData;
        flowerData.texture = std::make_shared<sf::Texture>();
        flowerData.texture->loadFromFile("assets/flowers/olive_3.png");
        params.flowerTexture.push_back(flowerData);
    }

    // Generate the texture
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