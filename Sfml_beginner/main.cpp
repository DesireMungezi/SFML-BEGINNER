#include<SFML/Graphics.hpp>
#include<cstdlib>
#include<ctime>
#include<string>
#include<sstream>
int main()
{
    //create a render window
    sf::RenderWindow window(sf::VideoMode(900, 600), "My Sfml window");

    //create a texture that holds a graphical memory in the GPU
    //Create all textures needed
    sf::Texture textureBackground;
    sf::Texture textureTree;
    sf::Texture textureBee;
    sf::Texture textureCloud;

    //load an all images onto their textures
    textureBackground.loadFromFile("graphics/Background1.png");
    textureTree.loadFromFile("graphics/tree_small.png");
    textureBee.loadFromFile("graphics/bee_small.png");
    textureCloud.loadFromFile("graphics/cloud_small.png");

    /*
    we can use a texture type to display an image
    because it eats up a lot of space in the GPU
    so we create a sprite that eats less memory
    */

    //Background
    sf::Sprite spriteBackground;
    //set a texture image to a sprite
    spriteBackground.setTexture(textureBackground);
    //now set a position where to  display the sprite
    spriteBackground.setPosition(0.0f, 0.0f);


    //Tree
    sf::Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(400.0f, 0.0f);


    //Bee
    sf::Sprite spriteBee;
    //set texture for all three bee sprites
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0.0f, 500.0f);
    //is the bee moving
    bool beeActive = false;
    //Speed for the bee
    float beeSpeed = 0.0f;

    //Cloud
    //Three cloud sprites with the same texture but different properties
    sf::Sprite spriteCloud1;
    sf::Sprite spriteCloud2;
    sf::Sprite spriteCloud3;

    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);

    spriteCloud1.setPosition(0.0f, 0.0f);
    spriteCloud2.setPosition(0.0f, 100.0f);
    spriteCloud3.setPosition(0.0f, 200.0f);
    //Is the cloud moving?
    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;
    //speed for the cloud
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;


    //create a score and start text
    int score = 0;
    //Text
    sf::Text massageText;
    sf::Text scoreText;
    //Font
    sf::Font font;
    font.loadFromFile("fonts/KOMIKAP.ttf");
    //set font
    massageText.setFont(font);
    scoreText.setFont(font);
    //giving value
    massageText.setString("Press 'Enter' to start");
    scoreText.setString("Score = ");
    //font size
    massageText.setCharacterSize(50);
    scoreText.setCharacterSize(40);
    //changing the center
    sf::FloatRect textRect = massageText.getLocalBounds();
    massageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    //set position
    massageText.setPosition(900/2, 600/2);
    scoreText.setPosition(20, 20);



    //add a time bar
    sf::RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 50;
    //set size of the time bar
    timeBar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
    //set color
    timeBar.setFillColor(sf::Color::Red);
    //set position
    timeBar.setPosition(900/2 - timeBarStartWidth / 2, 300);

    //time for the bar
    sf::Time totalBarTime;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = (timeBarStartWidth / timeRemaining);


    //Creating time for framerate
    sf::Clock clock;
    //create a new variable for pausing the game
    bool pause = true;



    //create sfml game loop and check if window is closed
    while(window.isOpen())
    {
        //Check for player's input and press Escape to close the window
        sf::Event event;
        while(window.pollEvent(event))
        {
           if(event.type == sf::Event::Closed)
           {
               window.close();
           }
           else if(event.key.code == sf::Keyboard::Escape)
           {
               window.close();
           }
        }

        //check if the play has entered the Enter key to unpause the game
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            pause = false;
            //reset score and time for the bar
            score = 0;
            timeRemaining = 6.0f;
        }
        //check if the player has entered Enter key
        if(!pause)
        {
            //increment score each frame
            score++;

            //Measure time
            sf::Time deltaTime = clock.restart();

            //shrinking the time bar
            timeRemaining -= deltaTime.asSeconds();
            //resize the time bar
            timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
            //check if time has run out
            if(timeRemaining <= 0.0f)
            {
                //pause the game
                pause = true;
                //display game over
                massageText.setString("Game over !");
                sf::FloatRect textRect = massageText.getLocalBounds();
                massageText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
                massageText.setPosition(900/2, 600/2);
            }

            //Manage the bee
            //if the bee is not moving then update its posision
            if(!beeActive)
            {
                //create a random speed for the bee to look natural
                srand((int)time(0) * 10);
                //So plus hundred ensures that the random speed is not below 200
                beeSpeed = (rand() % 200) + 200;

                //create a random number for the bee to spawn on different heights
                srand(static_cast<unsigned int>(time(0)) * 10);
                float height = (rand() % 200) + 200;
                //Setting the random height and outside the screen
                spriteBee.setPosition(950, height);
                //then make the bee to be active for the next Frame
                beeActive = true;
            }//is the bee active in this frame? if yes move it
            else
            {
                //Moving the bee
                spriteBee.setPosition(spriteBee.getPosition().x -
                (beeSpeed * deltaTime.asSeconds()), spriteBee.getPosition().y);
                //check if the bee is moved out of screen and set active to false
                if(spriteBee.getPosition().x < -100)
                {
                    //if it outside the screen set it's active to false
                    beeActive = false;
                    //for the other frame to randomize its speed and height spawn
                }
            }
            //Manage the cloud1
            if(!cloud1Active)
            {
                //Create random speed
                srand((int)time(0) * 10);
                cloud1Speed = (rand() % 250);

                //Create random height
                srand((int)time(0) * 10);
                float height = (rand() % 150);
                spriteCloud1.setPosition(-200, height);
                //Now change cloudActive to true
                cloud1Active = true;
            }
            //Moving the clouds and spawn
            else
            {
                //Move the clouds using delta and cloud speed
                spriteCloud1.setPosition(spriteCloud1.getPosition().x +
                (cloud1Speed * deltaTime.asSeconds()), spriteCloud1.getPosition().y);
                //check if its outside of view
                if(spriteCloud1.getPosition().x > 950)
                {
                    //Turn active cloud off
                    cloud1Active = false;
                }
            }
            //Manage the cloud2
            if(!cloud2Active)
            {
                //Create random speed
                srand((int)time(0) * 20);
                cloud2Speed = (rand() % 200);

                //Create random height
                srand((int)time(0) * 20);
                float height = (rand() % 350) - 150;
                spriteCloud2.setPosition(-200, height);
                //Now change cloudActive to true
                cloud2Active = true;
            }
            //Moving the clouds and spawn
            else
            {
                //Move the clouds using delta and cloud speed
                spriteCloud2.setPosition(spriteCloud2.getPosition().x +
                (cloud2Speed * deltaTime.asSeconds()), spriteCloud2.getPosition().y);
                //check if its outside of view
                if(spriteCloud2.getPosition().x > 950)
                {
                    //Turn active cloud off
                    cloud2Active = false;
                }
            }
            //Manage the cloud3
            if(!cloud3Active)
            {
                //Create random speed
                srand((int)time(0) * 30);
                cloud3Speed = (rand() % 200);

                //Create random height
                srand((int)time(0) * 30);
                float height = (rand() % 450) - 150;
                spriteCloud3.setPosition(-200, height);
                //Now change cloudActive to true
                cloud3Active = true;
            }
            //Moving the clouds and spawn
            else
            {
                //Move the clouds using delta and cloud speed
                spriteCloud3.setPosition(spriteCloud3.getPosition().x +
                (cloud3Speed * deltaTime.asSeconds()), spriteCloud3.getPosition().y);
                //check if its outside of view
                if(spriteCloud3.getPosition().x > 950)
                {
                    //Turn active cloud off
                    cloud3Active = false;
                }
            }
        }
        //update the score
        std::stringstream ss;
        ss<<"Score = "<<score;
        scoreText.setString(ss.str());

        /*
        *****************************************************
        UPDATE OF GAME
        *****************************************************
        */

        //Clear the last frame
        window.clear();

        /*
        ************************************************
        DRAW NEW FRAME OR CHANGE THE SCENE
        ************************************************
        */

        window.draw(spriteBackground);
        //Draw clouds
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        //Draw tree
        window.draw(spriteTree);
        //Draw Bee
        window.draw(spriteBee);
        //Draw score
        window.draw(scoreText);
        //draw time bar
        window.draw(timeBar);
        if(pause)
        {
            //draw the message
            window.draw(massageText);
        }

        //Display the changes or scene
        window.display();
    }
    return 0;
}
