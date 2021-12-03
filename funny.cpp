//SFML C++ PACMAN pt 2
//created by Dr. Mo 11/21
//dynamicsofanasteroid.com

#include<iostream>
#include "SFML/Graphics.hpp"
using namespace std;
#include "map.h"
enum DIRECTIONS { LEFT, RIGHT, UP, DOWN }; //left is 0, right is 1, up is 2, down is 3
const int mapX = 50;
const int mapY = 50;
int distance(int x, int y, int x1, int y1);
int main() {
    //game set up (you'll need these lines in every game)
    sf::RenderWindow screen(sf::VideoMode(1000, 1000), "breakout"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    screen.setFramerateLimit(FPS); //set FPS

    //load in images
    sf::Texture brick;
    brick.loadFromFile("brick1.png");
    sf::Sprite wall;
    wall.setTexture(brick);
    int map[mapX][mapY];
    memcpy(map, map1, sizeof(map1));
    //player setup
    int xpos = 20;
    int ypos = 20;
    int vx = 0;
    int vy = 0;
    int radius = 25;
    sf::CircleShape player(radius);
    player.setFillColor(sf::Color(250, 250, 0)); //using RGB value for color here (hex also works)

    sf::CircleShape dot(5);
    dot.setFillColor(sf::Color(250, 250, 250)); //using RGB value for color here (hex also works)

    player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    bool keys[] = { false, false, false, false };


    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down

        while (screen.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                screen.close();
            //KEYBOARD INPUT 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                keys[UP] = true;
            }
            else keys[UP] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;



        }//end event loop---------------------------------------------------------------

         //move Mr. Pac
        if (keys[LEFT] == true)
            vx = -5;
        else if (keys[RIGHT] == true)
            vx = 5;
        else vx = 0;

        if (keys[UP] == true)
            vy = -5;
        else if (keys[DOWN] == true)
            vy = 5;
        else vy = 0;

        //check collision before updating position to prevent clipping
            if (vx > 0 && map[(ypos / (1000 / mapY))][((xpos + radius * 2 + 5) / (1000 / mapX))] == 1 || vx > 0 && map[((ypos + radius * 2) / (1000 / mapY))][((xpos + radius * 2 + 5) / (1000 / mapX))] == 1)
                vx = 0;
            if (vx < 0 && map[(ypos / (1000 / mapY))][((xpos-5) / (1000 / mapX))] == 1 || vx < 0 && map[((ypos + radius * 2) / (1000 / mapY))][((xpos - 5) / (1000 / mapX))] == 1)
                vx = 0;
            if (vy > 0 && map[((ypos + radius * 2 + 5) / (1000 / mapY))][(xpos / (1000 / mapX))] == 1 || vy > 0 && map[((ypos + radius * 2 + 5) / (1000 / mapY))][((xpos + radius * 2) / (1000 / mapX))] == 1)
                vy = 0;
            if (vy < 0 && map[((ypos - 5) / (1000 / mapY))][(xpos / (1000 / mapX))] == 1 || vy < 0 && map[((ypos - 5) / (1000 / mapY))][((xpos + radius * 2) / (1000 / mapX))] == 1)
                vy = 0;
            

        ypos += vy;
        xpos += vx;
        player.setPosition(xpos, ypos);


        //render section-----------------------------------------
        screen.clear(sf::Color((255, 255,255,255))); //wipes screen, without this things smear

        //draw map
        for (int rows = 0; rows < mapX; rows++)
            for (int cols = 0; cols < mapY; cols++) {
                if (map[rows][cols] == 1) {
                    wall.setPosition(cols * (1000/mapX), rows * (1000/mapY));
                    screen.draw(wall);
                }
                if (map[rows][cols] == 2) {
                    if (distance(xpos + 25, ypos + 25, cols * (1000 / mapX) + ((1000 / mapX) / 2), rows * (1000 / mapY) + ((1000 / mapY) / 2)) < 25)
                        map[rows][cols] = 0;
                    dot.setPosition(cols * (1000 / mapX) + ((1000 / mapX) / 2), rows * (1000 / mapY) + ((1000 / mapY) / 2));
                  
                        screen.draw(dot);
                }
            }
        screen.draw(player); //draw player
        screen.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

    cout << "goodbye!" << endl;
} //end of main

int distance(int x, int y, int x1, int y1) {
    return sqrt(pow((x - x1), 2) + pow((y - y1), 2));
}
