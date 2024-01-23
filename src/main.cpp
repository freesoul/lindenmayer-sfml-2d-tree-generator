#include <SFML/Graphics.hpp>
#include <TreeGenerator.h>
#include <memory>

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);

    auto textureBark = std::make_shared<sf::Texture>();
    textureBark->loadFromFile("assets/barks/bark.jpg");

    auto textureBranch = textureBark;

    auto textureLeaf = std::make_shared<sf::Texture>();
    textureLeaf->loadFromFile("assets/leaves/leaf.png");

    auto textureFlower = std::make_shared<sf::Texture>();
    textureFlower->loadFromFile("assets/flowers/flower.png");

    Tree::TreeParams params;
    params.barkTexture = textureBark;
    params.branchTexture = textureBranch;
    params.leafTexture = textureLeaf;
    params.flowerTexture = textureFlower;

    auto tree = Tree::TreeGenerator();
    tree.setParams(params);
    auto rules = tree.generateRules(3);
    tree.generateTree(rules);

    auto sprite = tree.getSprite();
    sprite.setPosition(400, 600);

    sf::RenderWindow window(sf::VideoMode(800, 600), "My Game");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}