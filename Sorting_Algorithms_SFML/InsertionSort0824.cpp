#include "algorithm0824.h"
#include "info0824.h"
int runInsertionSort() {

	sf::RenderWindow window(sf::VideoMode(960, 540), "Insertion Sort");
	window.setFramerateLimit(targetFrameRate);

	bool sorted = false;
	bool iteration_sorted = false;
	int lines = linesCount;
	int iteration = 0; // Moving Bar Index
	int limit = lines - 1; // Moving Bar last Index
	int virtual_iteration = 1;
	int beggining = 0; // Moving Bar Starting Index

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
		sortedText[i].setFillColor(sf::Color(118, 74, 255)); // B = 255 galas good visai 161
		sortedText[i].setOutlineColor(sf::Color(94, 0, 135));
		sortedText[i].setOutlineThickness(2);
		sortedButton[i].setPosition(sf::Vector2f(sortedText[i].getPosition().x - 5, sortedText[i].getPosition().y - 5));
		sortedButton[i].setSize(sf::Vector2f(sortedText[i].getGlobalBounds().width * 1.05, 50));
		sortedButton[i].setFillColor(sf::Color(88, 69, 97, 127));
	}
	constexpr int infoTextCount = 6;
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
	infoText[1].setString("Insertion sort resembles arranging cards in");
	infoText[2].setString("your hand. It divides an array into sorted and");
	infoText[3].setString("unsorted sections. Values from the unsorted section");
	infoText[4].setString("are placed correctly in the sorted section.");

	infoBackground.setFillColor(sf::Color(88, 69, 97, 127));
	infoBackground.setSize(sf::Vector2f(infoText[3].getGlobalBounds().width * 1.05, 240));
	infoBackground.setPosition(sf::Vector2f(window.getSize().x - infoBackground.getGlobalBounds().width,
		infoBackground.getGlobalBounds().height * 0.01));
	infoBackground.setOutlineColor(sf::Color(94, 0, 135));
	infoBackground.setOutlineThickness(3);

	infoText[0].setPosition(infoBackground.getPosition().x + infoBackground.getGlobalBounds().width * 0.35,
		infoBackground.getPosition().y + 5);
	for (int i = 1; i < infoTextCount; i++)
	{
		infoText[i].setPosition(infoBackground.getPosition().x * 1.02, infoText[0].getPosition().y + 45 * i);
	}
	sf::RectangleShape infoButton;
	infoButton.setSize(sf::Vector2f(window.getSize().y / 16, window.getSize().y / 16));
	infoButton.setFillColor(sf::Color(90, 66, 110));                  // -3, Because OutlineThickness = 3
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
	infoSprite.setScale(0.07, 0.07);
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
							runInsertionSort();
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
	    window.clear();	
	    window.draw(background);
	        for (int i = 0; i < lines; i++)
	        {
				if (iteration >= 0 && i > beggining)
					rectangle.setFillColor(sf::Color(76, 50, 95)); // Unsorted - Color
				else if (!sorted)
					rectangle.setFillColor(sf::Color(77, 96, 41)); // Sorted - Color
				if ((virtual_iteration == i) && (iteration == beggining) && (!sorted))
				{
					rectangle.setFillColor(sf::Color(131, 130, 119));  // Moving bar - Color	
				}
				if (sorted)
				{
					// Bug fix: when Sorted, sometimes, colour changes to one that  == iteration bar colour
					rectangle.setFillColor(sf::Color(77, 96, 41)); 
				}
	            rectangle.setPosition(sf::Vector2f(line[i].pos, window.getSize().y));
	            rectangle.setRotation(180);
	            rectangle.setSize(sf::Vector2f((window.getSize().x / lines) / 1.1f, line[i].height));
	            window.draw(rectangle);
	        }
	        if (!sorted) {
	        if (line[virtual_iteration].height < line[virtual_iteration - 1].height)
	        {
	            int temp = line[virtual_iteration].height;
	            line[virtual_iteration].height = line[virtual_iteration - 1].height;
	            line[virtual_iteration - 1].height = temp;
				while (true) // Bug Fix: needed
				{
					break;
				}
	        }
	            --virtual_iteration;
				if (virtual_iteration < 1)
					virtual_iteration = 2;
	            if (line[virtual_iteration].height > line[virtual_iteration - 1].height)
	                iteration_sorted = true;
	            if (virtual_iteration < 0 || iteration_sorted || iteration == 0)
	            {
	                ++beggining;
	                virtual_iteration = beggining;
	                ++iteration;
	                iteration_sorted = false;
	            }
	            if (iteration > limit)
	            {
	                sorted = true;
	            }
	        }
			if (sorted)
			{
				for (int i = 0; i < 3; i++)
				{
					window.draw(sortedButton[i]);
					window.draw(sortedText[i]);
				}
				if (infoAppear == true)
				{
					window.draw(infoBackground);
					for (int i = 0; i < 5; i++)
					{
						window.draw(infoText[i]);
					}
				}
				window.draw(infoButton);
				window.draw(infoSprite);
			}
		window.display();
	}
	return 0;
}