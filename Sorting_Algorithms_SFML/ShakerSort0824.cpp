#include "algorithm0824.h"
#include "info0824.h"

int runShakerSort() {

    sf::RenderWindow window(sf::VideoMode(960, 540), "Shaker Sort");
    window.setFramerateLimit(targetFrameRate);

    bool sorted = false;
    bool backwards = false;
    int lines = linesCount;
    int iteration = 0; // Moving Bar Index
    int limit = lines - 2; // Moving Bar last Index
    int minimum = 0;

    sf::RectangleShape rectangle(sf::Vector2f(1.f, 1.f));
    rectangle.setOutlineThickness(1);
    rectangle.setOutlineColor(sf::Color(143, 114, 74));

    sf::Texture texture;
    if (!texture.loadFromFile("Resources/Textures/background.jpg"))
    {
        return 1;
    }
    float scaleX = window.getSize().x / 1920.f;
    float scaleY = window.getSize().y / 1080.f;

    sf::Sprite  background;
    background.setTexture(texture);
    background.setScale(sf::Vector2f(scaleX, scaleY));

    int Bar_width = window.getSize().x / lines;
    for (int i = 0; i < lines; ++i)
    {
        line[i].height = (std::rand() % (window.getSize().y - 30) + 10);
        line[i].pos = Bar_width * i + Bar_width;
    }
    sf::Font font;
    if (!font.loadFromFile("Resources/Font/coolvetica_rg_it.otf")) {
        std::cerr << "Failed to load font." << std::endl;
        return 1;
    }
    // Navigation Buttons
    constexpr int sortedButtonCount = 3;
    sf::RectangleShape sortedButton[sortedButtonCount];
    sf::Text sortedText[sortedButtonCount];
    sortedText[0].setString("Open The Menu");
    sortedText[1].setString("Restart The Algorithm");
    sortedText[2].setString("Exit The Application");
    sortedText[0].setPosition(sf::Vector2f(window.getSize().x * 0.05, window.getSize().y / 8.0));
    sortedText[1].setPosition(sf::Vector2f(window.getSize().x * 0.05, window.getSize().y / 8.0 * 2.0));
    sortedText[2].setPosition(sf::Vector2f(window.getSize().x * 0.05, window.getSize().y / 8.0 * 3.0));
    for (int i = 0; i < sortedButtonCount; ++i)
    {
        sortedText[i].setFont(font);
        sortedText[i].setCharacterSize(24);
        sortedText[i].setFillColor(sf::Color(118, 74, 255));
        sortedText[i].setOutlineColor(sf::Color(94, 0, 135));
        sortedText[i].setOutlineThickness(2);
        sortedButton[i].setPosition(sf::Vector2f(sortedText[i].getPosition().x - 5, sortedText[i].getPosition().y - 5));
        sortedButton[i].setSize(sf::Vector2f(sortedText[i].getGlobalBounds().width * 1.05, 50));
        sortedButton[i].setFillColor(sf::Color(88, 69, 97, 127));
    }
    constexpr int infoTextCount = 6; // 5 Actually, Because of Index Stuff.
    sf::RectangleShape infoBackground;
    sf::Text infoText[infoTextCount];
    bool infoAppear = false;
    for (int i = 0; i < infoTextCount; ++i)
    {
        infoText[i].setFillColor(sf::Color(118, 74, 255));
        infoText[i].setOutlineColor(sf::Color::Black);
        infoText[i].setOutlineThickness(1.3);
        infoText[i].setFont(font);
        infoText[i].setCharacterSize(28);
    }
    infoText[0].setString("About:");
    infoText[1].setString("Cocktail sort, an optimised version of bubble");
    infoText[2].setString("sort, optimizes sorting by swapping adjacent");
    infoText[3].setString("elements. It alternates directions after each");
    infoText[4].setString("pass, enhancing efficiency for certain scenarios.");

    infoBackground.setFillColor(sf::Color(88, 69, 97, 127));
    infoBackground.setSize(sf::Vector2f(infoText[3].getGlobalBounds().width * 1.14, 240));
    infoBackground.setPosition(sf::Vector2f(window.getSize().x - infoBackground.getGlobalBounds().width,
        infoBackground.getGlobalBounds().height * 0.01));
    infoBackground.setOutlineColor(sf::Color(94, 0, 135));
    infoBackground.setOutlineThickness(3);

    infoText[0].setPosition(infoBackground.getPosition().x + infoBackground.getGlobalBounds().width * 0.35,
        infoBackground.getPosition().y + 5);
    infoText[0].setPosition(infoBackground.getPosition().x + infoBackground.getGlobalBounds().width * 0.35,
        infoBackground.getPosition().y + 5);
    for (int i = 1; i < 5; i++)
    {

        infoText[i].setPosition(infoBackground.getPosition().x * 1.02, infoText[0].getPosition().y + 45 * i);
    }




    sf::RectangleShape infoButton;
    infoButton.setSize(sf::Vector2f(window.getSize().y / 16, window.getSize().y / 16));
    infoButton.setFillColor(sf::Color(90, 66, 110));                                          // -3, Because OutlineThickness = 3
    infoButton.setPosition(sf::Vector2f(window.getSize().x - infoButton.getGlobalBounds().width - 3, 3));
    infoButton.setOutlineColor(sf::Color::Black);
    infoButton.setOutlineThickness(3);

    sf::Texture infoTexture;
    if (!infoTexture.loadFromFile("Resources/Textures/infoButton.png"))
    {
        std::cerr << "error loading info button texture";
        std::exit(1);
    }
    sf::Sprite infoSprite;
    infoSprite.setTexture(infoTexture);
    infoSprite.setScale(0.068, 0.068);
    infoSprite.setPosition(infoButton.getPosition().x, infoButton.getPosition().y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && sorted)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                for (int i = 0; i < 3; ++i)
                {
                    if (sortedButton[i].getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                    {
                        switch (i)
                        {
                        case 0:
                            window.close();
                            break;
                        case 1:
                            window.close();
                            runShakerSort();
                            break;
                        case 2:
                            std::exit(0);
                            break;
                        }
                    }
                }
                if (infoButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) && infoAppear == false)
                {
                    infoAppear = true;
                }
                else if (infoButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)) && infoAppear == true)
                {
                    infoAppear = false;
                }
            }
        }
        if (!sorted) {
            if (iteration < 0)
                iteration = 0;
            if ((!backwards) && line[iteration].height > line[iteration + 1].height)
            {
                int temp = line[iteration].height;
                line[iteration].height = line[iteration + 1].height;
                line[iteration + 1].height = temp;
            }
            else if (backwards && line[iteration].height > line[iteration + 1].height)
            {
                int temp = line[iteration].height;
                line[iteration].height = line[iteration + 1].height;
                line[iteration + 1].height = temp;
            }
        }
        window.clear();
        window.draw(background);
        for (int i = 0; i < lines; i++)
        {
            if (iteration >= 0 && (i > limit + 1 || i < minimum))
                rectangle.setFillColor(sf::Color(77, 96, 41)); // Sorted - Color
            else if (!sorted)
                rectangle.setFillColor(sf::Color(76, 50, 95)); // Unsorted - Color
            if ((iteration+1 == i) && !sorted && !backwards) {
                rectangle.setFillColor(sf::Color(131, 130, 119));  // Moving bar - Color
            }
            else if ((iteration == i) && !sorted && backwards) {
                rectangle.setFillColor(sf::Color(131, 130, 119));  // Moving bar - Color
            }
            rectangle.setPosition(sf::Vector2f(line[i].pos, window.getSize().y));
            rectangle.setSize(sf::Vector2f((window.getSize().x / lines) / 1.1f, line[i].height)); 
            rectangle.setRotation(180);

            window.draw(rectangle);
        }
        if (sorted)
        {
            for (int i = 0; i < 3; ++i)
            {
                window.draw(sortedButton[i]);
                window.draw(sortedText[i]);
            }
            if (infoAppear == true)
            {
                window.draw(infoBackground);
                for (int i = 0; i < 5; ++i)
                {
                    window.draw(infoText[i]);
                }

            }
            window.draw(infoButton);
            window.draw(infoSprite);
        }

        window.display();

        if (minimum == lines / 2)
            sorted = true;
        if (!backwards)
            ++iteration;
        if (iteration > limit)
        {
            backwards = true;
            --iteration;
            --limit;
            if (limit == 0)
                sorted = true;
        }
        if (backwards)
        {
            --iteration;
            if (iteration < minimum)
            {
                backwards = false;
                ++minimum;
            }
        } 
    }
    return 0;
}