#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int WINDOW_WIDTH = 1400;
const int WINDOW_HEIGHT = 600;
const int MAX_LIVES = 3;

// I used chat since balls were spawning behind the window for some reason(i used "rand() % 600+100"
float getRandomY() {
    return static_cast<float>(rand() % (WINDOW_HEIGHT - 2 * 30));
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SAVE THE CHARIZARD!!!!"); //creating window for our game(we set size of window in line 8-9)
    window.setFramerateLimit(60);

    //values may be switched (we can swap the size, position as well as charizard model for different pokemons[remember to change window name so it will not look weird])

    sf::Texture ballTexture;
    std::cout<<ballTexture.loadFromFile("../../wika4.png")<<std::endl;// we cout so we know if the file is loaded correctly(1-succes, 0-fail)

    sf::Sprite ballSprite;
    ballSprite.setTexture(ballTexture);
    ballSprite.setScale(0.15, 0.15);
    ballSprite.setPosition(0, getRandomY()); // I tought making it spawn randomly in y axis would be harder and more fun for player

    //we declare the speed and the acceleration of the ball(switch if it's to hard)
    float speed = 400.0f;
    float speedIncreaseRate = 50.0f;
    int score = 0;
    int lives = MAX_LIVES;


    sf::Texture charizard;
    std::cout<<charizard.loadFromFile("../../wika5.png")<<std::endl;

    sf::Sprite pokemon;
    pokemon.setTexture(charizard);
    pokemon.setScale(1.1,1.1);
    pokemon.setPosition(900,70);

    sf::Texture explosion;
    std::cout<<explosion.loadFromFile("../../wika8.png")<<std::endl;

    sf::Sprite boom;
    boom.setTexture(explosion);
    boom.setScale(1,1);
    boom.setPosition(900,70);

    sf::Texture heartTexture;
    std::cout << heartTexture.loadFromFile("../../wika6.png") <<std::endl;

    sf::Sprite hearts[MAX_LIVES];
    for (int i = 0; i < MAX_LIVES; ++i) {
        hearts[i].setTexture(heartTexture);
        hearts[i].setScale(0.1f, 0.1f); //
        hearts[i].setPosition(10.f + i * 60.f, 10.f);
    }

    sf::Font font; //for score results
    std::cout<<font.loadFromFile("../../wika7.ttf")<<std::endl; // we cout so we know if the file is loaded correctly(1-succes, 0-fail)

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(10.f, 60.f);

    sf::Texture backgroundTexture;
    std::cout<<backgroundTexture.loadFromFile("../../wika3.jpg")<<std::endl;

    sf::Sprite backgroundSprite;
    backgroundSprite.setScale(2,1.5);
    backgroundSprite.setTexture(backgroundTexture);



    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();
        speed += speedIncreaseRate * deltaTime;
        scoreText.setString("Score: " + std::to_string(score)); //since the score is in intiger form we use to_string to be able to output it in scoreText

        sf::Vector2f pos = ballSprite.getPosition();
        pos.x += speed * deltaTime;
        ballSprite.setPosition(pos);

        // When the ball is missed
        if (pos.x > WINDOW_WIDTH-170) {
            lives--;
            ballSprite.setPosition(0, getRandomY());
            speed = 400.0f; // Optional: Reset speed to help player catch up(comment out for lvl hard)
        }

        // event when we click the ball
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
                if (ballSprite.getGlobalBounds().contains(mousePos)) {
                    int points = static_cast<int>(speed / 10);
                    score += points;

                    ballSprite.setPosition(0, getRandomY());
                }
                else {
                    lives--;
                    ballSprite.setPosition(0, getRandomY());
                    speed = 400.0f;
                }
            }
        }

        // Game over when lives reach 0
        if (lives <= 0) {
            window.draw(boom);
            window.display();
            sf::sleep(sf::seconds(2));
            window.close();
        }

        // Rendering the "objects" that we created/added?
        window.clear();

        window.draw(backgroundSprite);
        window.draw(pokemon);
        window.draw(ballSprite);


        for (int i = 0; i < lives; ++i) {
            window.draw(hearts[i]);
        }
        window.draw(scoreText);



        window.display();
    }

    return 0;
}
