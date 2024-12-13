#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib> // For rand()
#include <ctime>   // For seeding rand()

using namespace sf;

// Function to initialize the bars
// Function to implement Bubble Sort with visualization
void bubbleSort(std::vector<std::pair<sf::RectangleShape, int>> &bars, sf::Font &font, sf::RenderWindow &window)
{
    bool swapped;
    // Bubble sort loop
    for (size_t i = 0; i < bars.size() - 1; ++i)
    {
        swapped = false;

        // Loop through the bars and compare adjacent elements
        for (size_t j = 0; j < bars.size() - i - 1; ++j)
        {
            // Highlight the bars being compared (optional)
            bars[j].first.setFillColor(sf::Color::Yellow); // Set color of bar being compared
            bars[j + 1].first.setFillColor(sf::Color::Yellow);

            // Visualize before swap: Draw all bars and display their values
            window.clear();
            for (const auto &bar : bars)
            {
                window.draw(bar.first);

                // Create and configure the text
                sf::Text text;
                text.setFont(font);
                text.setString(std::to_string(bar.second)); // Convert value to string
                text.setCharacterSize(20);                  // Adjust as necessary to fit within bars
                text.setFillColor(sf::Color::White);

                // Calculate the center position of the text within the bar
                sf::FloatRect textBounds = text.getLocalBounds(); // Get text dimensions
                float textX = bar.first.getPosition().x + (bar.first.getSize().x - textBounds.width) / 2 - textBounds.left;
                float textY = bar.first.getPosition().y + (bar.first.getSize().y - textBounds.height) / 2 - textBounds.top;

                text.setPosition(textX, textY); // Set text position to center it within the bar

                // Draw the text
                window.draw(text);
            }
            window.display();
            sf::sleep(sf::milliseconds(100)); // Delay for visualization

            // If the current pair is out of order, swap them
            if (bars[j].second > bars[j + 1].second)
            {
                // Swap the elements
                std::swap(bars[j], bars[j + 1]);

                // Update their position (not strictly necessary, as they will be redrawn automatically)
                bars[j].first.setPosition(j * 120, bars[j].first.getPosition().y);               // Update X position
                bars[j + 1].first.setPosition((j + 1) * 120, bars[j + 1].first.getPosition().y); // Update X position

                swapped = true; // Mark that a swap happened
            }

            // Reset the colors of the bars after comparison
            bars[j].first.setFillColor(sf::Color::Green); // Set back to default color
            bars[j + 1].first.setFillColor(sf::Color::Green);
        }

        // If no two elements were swapped, the list is sorted, and we can break early
        if (!swapped)
            break;
    }
}

void initializeBars(std::vector<std::pair<sf::RectangleShape, int>> &bars, int size, sf::Color barColor)
{
    bars.clear(); // Clear previous bars

    float maxBarWidth = 1200.0f; // Maximum width of bars
    float barHeight = 50.0f;     // Fixed height for all bars
    float spacing = 20.0f;       // Space between each bar
    float maxBarValue = 1000.0f; // Maximum value for random bar width

    for (int i = 0; i < size; ++i)
    {
        int value = rand() % (int)maxBarValue + 50;                                         // Random bar width value
        sf::RectangleShape bar(sf::Vector2f(value / maxBarValue * maxBarWidth, barHeight)); // Scaled width
        bar.setFillColor(barColor);
        bar.setOutlineColor(sf::Color::White);                      // Border color
        bar.setOutlineThickness(2.0f);                              // Border thickness
        bar.setPosition(600.0f, 50.0f + i * (barHeight + spacing)); // Position with spacing

        bars.push_back({bar, value}); // Add the bar and its value to the vector
    }
}

// Function to randomize the array of bars
void randomizeArray(std::vector<std::pair<sf::RectangleShape, int>> &bars, float maxBarWidth)
{
    float maxBarValue = 1000.0f; // Maximum value for random bar width

    for (auto &bar : bars)
    {
        // Generate a new random value for each bar
        int newValue = rand() % (int)maxBarValue + 50;                                // Random width value
        bar.second = newValue;                                                        // Update stored value
        bar.first.setSize(sf::Vector2f(newValue / maxBarValue * maxBarWidth, 45.0f)); // Update width
    }
}

int main()
{
    std::vector<std::pair<sf::RectangleShape, int>> bars;

    // Seed random number generator
    std::srand(std::time(nullptr));

    // Create the SFML window
    RenderWindow window(VideoMode(1920, 1080), "Sorting Visualizer");

    // Define the left panel
    RectangleShape leftPanel(Vector2f(500, 1200)); // Panel dimensions
    leftPanel.setFillColor(Color(0, 0, 41));       // Dark blue color
    leftPanel.setPosition(50, 50);                 // Position

    // Load the font
    Font font;
    if (!font.loadFromFile("C:\\Users\\Jk_Afridi\\Desktop\\montserrat"))
    {
        return -1; // Exit if the font is not found
    }

    // Title Text
    Text title("Sorting\nVisualizer", font, 60); // Font size
    title.setFillColor(Color::White);            // Text color
    title.setPosition(100, 100);                 // Position inside the left panel

    // Sorting Button
    RectangleShape sortingButton(Vector2f(200, 50));
    sortingButton.setFillColor(Color(70, 70, 70)); // Gray color
    sortingButton.setPosition(100, 300);           // Position on the left panel

    Text sortingText("Bubble Sort", font, 20);
    sortingText.setFillColor(Color::White);
    sortingText.setPosition(sortingButton.getPosition().x + 10, sortingButton.getPosition().y + 10);

    // Sorting Dropdown Options
    std::vector<std::string> sortingOptions = {"Bubble Sort", "Heap Sort", "Merge Sort", "Insertion Sort"};
    std::vector<RectangleShape> sortingDropdownShapes;
    std::vector<Text> sortingDropdownTexts;

    // Adjust dropdown position
    float dropdownOffsetX = 220.0f; // Shift dropdowns to the right

    for (size_t i = 0; i < sortingOptions.size(); ++i)
    {
        RectangleShape option(Vector2f(200, 50));
        option.setFillColor(Color(50, 50, 50));                  // Darker gray
        option.setPosition(100 + dropdownOffsetX, 360 + i * 60); // Shifted right
        sortingDropdownShapes.push_back(option);

        Text optionText(sortingOptions[i], font, 20);
        optionText.setFillColor(Color::White);
        optionText.setPosition(option.getPosition().x + 10, option.getPosition().y + 10);
        sortingDropdownTexts.push_back(optionText);
    }

    // Speed Button
    RectangleShape speedButton(Vector2f(200, 50));
    speedButton.setFillColor(Color(70, 70, 70)); // Gray color
    speedButton.setPosition(100, 400);           // Below sorting button

    Text speedText("Normal", font, 20);
    speedText.setFillColor(Color::White);
    speedText.setPosition(speedButton.getPosition().x + 10, speedButton.getPosition().y + 10);

    // Speed Dropdown Options
    std::vector<std::string> speedOptions = {"Very Fast", "Fast", "Normal", "Slow", "Very Slow"};
    std::vector<RectangleShape> speedDropdownShapes;
    std::vector<Text> speedDropdownTexts;

    for (size_t i = 0; i < speedOptions.size(); ++i)
    {
        RectangleShape option(Vector2f(200, 50));
        option.setFillColor(Color(50, 50, 50));                  // Darker gray
        option.setPosition(100 + dropdownOffsetX, 460 + i * 60); // Shifted right
        speedDropdownShapes.push_back(option);

        Text optionText(speedOptions[i], font, 20);
        optionText.setFillColor(Color::White);
        optionText.setPosition(option.getPosition().x + 10, option.getPosition().y + 10);
        speedDropdownTexts.push_back(optionText);
    }

    // Array Size Button
    RectangleShape sizeButton(Vector2f(200, 50));
    sizeButton.setFillColor(Color(70, 70, 70)); // Gray color
    sizeButton.setPosition(100, 500);           // Below speed button

    Text sizeText("Size: 10", font, 20);
    sizeText.setFillColor(Color::White);
    sizeText.setPosition(sizeButton.getPosition().x + 10, sizeButton.getPosition().y + 10);

    // Size Dropdown Options
    std::vector<int> sizeOptions = {10, 15, 20, 25, 30};
    std::vector<RectangleShape> sizeDropdownShapes;
    std::vector<Text> sizeDropdownTexts;

    for (size_t i = 0; i < sizeOptions.size(); ++i)
    {
        RectangleShape option(Vector2f(200, 50));
        option.setFillColor(Color(50, 50, 50));                  // Darker gray
        option.setPosition(100 + dropdownOffsetX, 560 + i * 60); // Shifted right
        sizeDropdownShapes.push_back(option);

        Text optionText("Size: " + std::to_string(sizeOptions[i]), font, 20);
        optionText.setFillColor(Color::White);
        optionText.setPosition(option.getPosition().x + 10, option.getPosition().y + 10);
        sizeDropdownTexts.push_back(optionText);
    }

    // Color Button
    RectangleShape colorButton(Vector2f(200, 50));
    colorButton.setFillColor(Color(70, 70, 70)); // Gray color
    colorButton.setPosition(100, 600);           // Below size button

    Text colorText("Color: Black", font, 20);
    colorText.setFillColor(Color::White);
    colorText.setPosition(colorButton.getPosition().x + 10, colorButton.getPosition().y + 10);

    // Color Dropdown Options
    std::vector<std::string> colorOptions = {"Black", "Blue", "Red", "Green", "Yellow"};
    std::vector<RectangleShape> colorDropdownShapes;
    std::vector<Text> colorDropdownTexts;

    for (size_t i = 0; i < colorOptions.size(); ++i)
    {
        RectangleShape option(Vector2f(200, 50));
        option.setFillColor(Color(50, 50, 50));                  // Darker gray
        option.setPosition(100 + dropdownOffsetX, 660 + i * 60); // Shifted right
        colorDropdownShapes.push_back(option);

        Text optionText(colorOptions[i], font, 20);
        optionText.setFillColor(Color::White);
        optionText.setPosition(option.getPosition().x + 10, option.getPosition().y + 10);
        colorDropdownTexts.push_back(optionText);
    }
    // Randomize Array Button (New Button)
    RectangleShape randomizeButton(Vector2f(300, 75)); // 50% larger than other buttons
    randomizeButton.setFillColor(Color::Red);          // Red color for the button
    randomizeButton.setPosition(100, 700);             // Position on the left panel

    Text randomizeText("Randomize Array", font, 20);
    randomizeText.setFillColor(Color::White);
    randomizeText.setPosition(randomizeButton.getPosition().x + 10, randomizeButton.getPosition().y + 25);

    // Dropdown Visibility Flags
    bool sortingDropdownVisible = false;
    bool speedDropdownVisible = false;
    bool sizeDropdownVisible = false;
    bool colorDropdownVisible = false;

    // Bar Color Variable
    Color barColor = Color::Black;

    // Bars for visualization

    initializeBars(bars, 10, barColor); // Initialize with default size 10

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

                // Handle button clicks
                if (sortingButton.getGlobalBounds().contains(mousePos))
                {
                    sortingDropdownVisible = !sortingDropdownVisible;
                    speedDropdownVisible = sizeDropdownVisible = colorDropdownVisible = false;
                }
                else if (speedButton.getGlobalBounds().contains(mousePos))
                {
                    speedDropdownVisible = !speedDropdownVisible;
                    sortingDropdownVisible = sizeDropdownVisible = colorDropdownVisible = false;
                }
                else if (sizeButton.getGlobalBounds().contains(mousePos))
                {
                    sizeDropdownVisible = !sizeDropdownVisible;
                    sortingDropdownVisible = speedDropdownVisible = colorDropdownVisible = false;
                }
                else if (colorButton.getGlobalBounds().contains(mousePos))
                {
                    colorDropdownVisible = !colorDropdownVisible;
                    sortingDropdownVisible = speedDropdownVisible = sizeDropdownVisible = false;
                } /*else if (resetButton.getGlobalBounds().contains(mousePos)) {
                    barColor = Color::Black;
                    colorText.setString("Color: Black");
                    sizeText.setString("Size: 10");
                    sortingText.setString("Bubble Sort");
                    initializeBars(bars, 10, barColor); // Reset to default settings
                    sortingDropdownVisible = speedDropdownVisible = sizeDropdownVisible = colorDropdownVisible = false;
                }*/
                else if (randomizeButton.getGlobalBounds().contains(mousePos))
                {
                    randomizeArray(bars, 1400.0f); // Pass the vector and max bar width
                }

                // Handle dropdown selections
                 if (sortingDropdownVisible)
                {
                    for (size_t i = 0; i < sortingDropdownShapes.size(); ++i)
                    {
                        if (sortingDropdownShapes[i].getGlobalBounds().contains(mousePos))
                        {
                            sortingText.setString(sortingOptions[i]);
                            sortingDropdownVisible = false;
                            break;
                        }
                    }
                }

                // Draw dropdowns if visible
                if (sortingDropdownVisible)
                {
                    for (size_t i = 0; i < sortingDropdownShapes.size(); ++i)
                    {
                        window.draw(sortingDropdownShapes[i]);
                        window.draw(sortingDropdownTexts[i]);
                    }
                }
                if (speedDropdownVisible)
                {
                    for (size_t i = 0; i < speedDropdownShapes.size(); ++i)
                    {
                        if (speedDropdownShapes[i].getGlobalBounds().contains(mousePos))
                        {
                            speedText.setString(speedOptions[i]);
                            speedDropdownVisible = false;
                            break;
                        }
                    }
                }
                if (sizeDropdownVisible)
                {
                    for (size_t i = 0; i < sizeDropdownShapes.size(); ++i)
                    {
                        if (sizeDropdownShapes[i].getGlobalBounds().contains(mousePos))
                        {
                            int newSize = sizeOptions[i];
                            sizeText.setString("Size: " + std::to_string(newSize));
                            initializeBars(bars, newSize, barColor);
                            sizeDropdownVisible = false;
                            break;
                        }
                    }
                }
                if (colorDropdownVisible)
                {
                    for (size_t i = 0; i < colorDropdownShapes.size(); ++i)
                    {
                        if (colorDropdownShapes[i].getGlobalBounds().contains(mousePos))
                        {
                            if (colorOptions[i] == "Black")
                                barColor = Color::Black;
                            if (colorOptions[i] == "Blue")
                                barColor = Color::Blue;
                            if (colorOptions[i] == "Red")
                                barColor = Color::Red;
                            if (colorOptions[i] == "Green")
                                barColor = Color::Green;
                            if (colorOptions[i] == "Yellow")
                                barColor = Color::Yellow;

                            colorText.setString("Color: " + colorOptions[i]);
                            for (auto &bar : bars)
                            {
                                bar.first.setFillColor(barColor); // Access the RectangleShape via bar.first
                            }

                            colorDropdownVisible = false;
                            break;
                        }
                    }
                }
            }
        }

        // Clear the window
        window.clear(Color(24, 26, 27));

        // Draw UI components
        window.draw(leftPanel);
        window.draw(title);
        window.draw(sortingButton);
        window.draw(sortingText);
        window.draw(speedButton);
        window.draw(speedText);
        window.draw(sizeButton);
        window.draw(sizeText);
        window.draw(colorButton);
        window.draw(colorText);
        // window.draw(resetButton);
        // window.draw(resetText);
        // Draw Randomize Array button
        window.draw(randomizeButton);
        window.draw(randomizeText);
        // Draw dropdowns if visible
        if (sortingDropdownVisible)
        {
            for (size_t i = 0; i < sortingDropdownShapes.size(); ++i)
            {
                window.draw(sortingDropdownShapes[i]);
                window.draw(sortingDropdownTexts[i]);
            }
        }
        if (speedDropdownVisible)
        {
            for (size_t i = 0; i < speedDropdownShapes.size(); ++i)
            {
                window.draw(speedDropdownShapes[i]);
                window.draw(speedDropdownTexts[i]);
            }
        }
        if (sizeDropdownVisible)
        {
            for (size_t i = 0; i < sizeDropdownShapes.size(); ++i)
            {
                window.draw(sizeDropdownShapes[i]);
                window.draw(sizeDropdownTexts[i]);
            }
        }
        if (colorDropdownVisible)
        {
            for (size_t i = 0; i < colorDropdownShapes.size(); ++i)
            {
                window.draw(colorDropdownShapes[i]);
                window.draw(colorDropdownTexts[i]);
            }
        }

        // Draw the bars
          for (const auto &bar : bars)
        {
            // Draw the bar
            window.draw(bar.first);

            // Create and configure the text
            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(bar.second)); // Convert value to string
            text.setCharacterSize(20);                  // Adjust as necessary to fit within bars
            text.setFillColor(sf::Color::White);

            // Calculate the center position of the text within the bar
            sf::FloatRect textBounds = text.getLocalBounds(); // Get text dimensions
            float textX = bar.first.getPosition().x + (bar.first.getSize().x - textBounds.width) / 2 - textBounds.left;
            float textY = bar.first.getPosition().y + (bar.first.getSize().y - textBounds.height) / 2 - textBounds.top;

            text.setPosition(textX, textY); // Set text position to center it within the bar

            // Draw the text
            window.draw(text);
        }

        // Display the rendered frame
        window.display();
    }

    return 0;
}
