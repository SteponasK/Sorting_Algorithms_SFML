#include "algorithm0824.h"
#include "info0824.h"

// Global variables
 int linesCount = 50;
 int targetFrameRate = 300;
 std::vector<Bar> line;
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sorting Algorithms");
    int windowX = window.getSize().x;
    int windowY = window.getSize().y;

    // User input as string
    std::string inputString;

    sf::Texture texture;
    if (!texture.loadFromFile("Resources/Textures/background.jpg"))
    {
        return 1;
    }

    sf::Sprite  background;
    background.setTexture(texture);
    float scaleX = window.getSize().x / 1920.f;
    float scaleY = window.getSize().y / 1080.f;
    background.setScale(sf::Vector2f(scaleX, scaleY));

    sf::Font font;
    if (!font.loadFromFile("Resources/Font/coolvetica_rg_it.otf")) {
        std::cerr << "Failed to load font." << std::endl;
        return 1;
    }

    // Create buttons
    sf::RectangleShape buttons[6];
    sf::Text buttonText[6];

    //Main menu title
    buttonText[0].setFont(font);
    buttonText[0].setCharacterSize(50);
    buttonText[0].setString("Algorithm Menu");
    buttonText[0].setFillColor(sf::Color(235, 225, 181));
    buttonText[0].setOutlineColor(sf::Color(80, 53, 22));
    buttonText[0].setOutlineThickness(1); 

    float textWidth = buttonText[0].getLocalBounds().width;
    float textHeight = buttonText[0].getLocalBounds().height;
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;
    buttonText[0].setPosition((windowX - textWidth) / 2, (windowY - textHeight) / 20);

    // Sorting Algorithms
    buttonText[1].setString("Bubble Sort");
    buttonText[2].setString("Shaker Sort");
    buttonText[3].setString("Insertion Sort");
    buttonText[4].setString("Selection Sort");
    buttonText[5].setString("Double Selection Sort"); 
    for (int i = 1; i < 6; ++i)
    {
        buttonText[i].setFont(font);
        buttonText[i].setCharacterSize(38);
        buttonText[i].setFillColor(sf::Color(118, 74, 161));
        buttonText[i].setOutlineColor(sf::Color(94, 0, 135));
        buttonText[i].setOutlineThickness(1);
        buttons[i].setFillColor(sf::Color(0, 0, 74, 127));
        buttons[i].setOutlineColor(sf::Color(148,0,211));
        buttons[i].setSize(sf::Vector2f(buttonText[i].getGlobalBounds().width * 1.1, 60));
    }
    buttons[1].setPosition(sf::Vector2f(windowX / 3, 120));
    buttons[2].setPosition(sf::Vector2f(windowX / 3, 220));
    buttons[3].setPosition(sf::Vector2f(windowX / 3, 320));
    buttons[4].setPosition(sf::Vector2f(windowX / 3, 420));
    buttons[5].setPosition(sf::Vector2f(windowX / 3, 520));
    
    for (int i = 1; i < 6; ++i)
    {

        auto pos = buttons[i].getPosition();
        buttonText[i].setPosition(sf::Vector2f(buttons[i].getPosition().x + buttonText[i].getGlobalBounds().width/18, buttons[i].getPosition().y));
    }

    // frameRateText
    sf::Text frameRateText; 
    frameRateText.setFont(font);
    frameRateText.setCharacterSize(25);
    frameRateText.setFillColor(sf::Color(235, 225, 181));
    frameRateText.setString("Frame Rate: ");
    frameRateText.setOutlineColor(sf::Color::Black);
    frameRateText.setOutlineThickness(1);
    frameRateText.setPosition(windowX / 1.3, 10);

    // frameRateButton
    sf::RectangleShape frameRateButton;
    frameRateButton.setFillColor(sf::Color(0, 0, 74, 127));
    frameRateButton.setPosition(sf::Vector2f(frameRateText.getPosition().x, frameRateText.getPosition().y));
    frameRateButton.setSize(sf::Vector2f(frameRateText.getGlobalBounds().width * 1.32, frameRateText.getGlobalBounds().height * 1.5));
    frameRateButton.setOutlineColor(sf::Color::Black);
    bool frameRateButtonActive = false;

    // Lines Count Text
    sf::Text linesText;
    linesText.setFont(font);
    linesText.setCharacterSize(25);
    linesText.setFillColor(sf::Color(235, 225, 181));
    linesText.setString("Current Frame Rate: ");
    linesText.setString("Lines Count: ");
    linesText.setPosition(windowX / 1.3, 40);
    linesText.setOutlineColor(sf::Color::Black);
    linesText.setOutlineThickness(1);

    // Lines Count Button
    sf::RectangleShape linesButton;
    linesButton.setFillColor(sf::Color(0, 0, 74, 127));
    linesButton.setPosition(sf::Vector2f(linesText.getPosition().x, linesText.getPosition().y));
    linesButton.setSize(sf::Vector2f(linesText.getGlobalBounds().width * 1.31, linesText.getGlobalBounds().height * 1.5));
    linesButton.setOutlineColor(sf::Color::Black);
    bool linesButtonActive = false;

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                for (int i = 1; i < 6; ++i) {
                    if (buttons[i].getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                    {
                        line.resize(linesCount);
                        switch (i)
                        {
                            case 1:
                                runBubbleSort();
                                break;
                            case 2:
                                runShakerSort();
                                break;
                            case 3:
                                runInsertionSort();
                                break;
                            case 4:
                                runSelectionSort();
                                break;
                            case 5:
                                runDoubleSelectionSort();
                                break;
                        }
                    }
                }
                if (frameRateButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                {
                    frameRateButtonActive = true;
                }
                else if (linesButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))//cia lines button
                {
                    linesButtonActive = true;
                }
            }
            if (event.type == sf::Event::TextEntered)
            {
                
                    if (event.text.unicode >= '0' && event.text.unicode <= '9')
                    {   // Numbers between 0 and 9
                        inputString += static_cast<char>(event.text.unicode);
                    }
                    else if (event.text.unicode == 8 && !inputString.empty())
                    {
                        // Handle backspace
                        inputString.pop_back();
                    }
                    else if (event.text.unicode == 13 && !inputString.empty())
                    {
                        // Enter pressed, convert input to integer
                        std::istringstream iss(inputString);

                        if (frameRateButtonActive)
                        {
                            iss >> targetFrameRate;
                            frameRateButtonActive = false;

                            if (targetFrameRate > 999)
                                targetFrameRate = 999;
                            else if (targetFrameRate < 1)
                            {
                                targetFrameRate = 1;
                            }
                        }
                        else if (linesButtonActive)
                        {
                            iss >> linesCount;
                            linesButtonActive = false;

                            if (linesCount > 120)
                                linesCount = 120;
                            else if (linesCount < 5)
                            {
                                linesCount = 5;
                            }
                        }

                            
                        inputString.clear();
                    }
                
                
            }
        
               

        }

        window.clear();
        window.draw(background);

        for (int i = 0; i < 6; ++i)
        {
            window.draw(buttons[i]);
            window.draw(buttonText[i]);
            
        }
        frameRateText.setString("Frame Rate: " + std::to_string(targetFrameRate));
        linesText.setString("Lines Count: " + std::to_string(linesCount));

        window.draw(frameRateText);
        window.draw(linesText);

        window.display();
    }
    return 0;
}