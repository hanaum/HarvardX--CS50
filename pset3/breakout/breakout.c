//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//Hana Um

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 8

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    double x_velocity = drand48() + 1.0;
    double y_velocity = 3.0;
    
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        
        move(ball, x_velocity, y_velocity);
        pause(8);
           
        if (getX(ball) + getWidth(ball) >= getWidth(window))
            x_velocity = -x_velocity;
        else if (getY(ball) + getWidth(ball) >= getHeight(window)){
            y_velocity = -y_velocity;
            lives--;
            removeGWindow(window, ball);
            setLocation(ball, 194, 300);
            add(window, ball);
            waitForClick();
        }
        else if (getX(ball) <= 0)cd .
            x_velocity = -x_velocity;
        else if (getY(ball) <= 0)
            y_velocity = -y_velocity;
        
        GObject object = detectCollision(window, ball);
       
        if (object != NULL){
            if (object == paddle)
                y_velocity = -y_velocity;
            else if (strcmp(getType(object), "GRect") == 0) {
                y_velocity = -y_velocity;
                points++;
                removeGWindow(window, object);
                updateScoreboard(window, label, points);
            }
        }
            
        GEvent event = getNextEvent(MOUSE_EVENT);
        if (event != NULL) {
            if (getEventType(event) == MOUSE_MOVED){
               double x = getX(event) - getWidth(paddle) / 2;
               setLocation(paddle, x, 450);
            }    
        }                      
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
    GRect bricks;
    double x = 0;
    double y = 0;
    
    for (int i = 0; i < ROWS; i++) {
        x = 2;
        y += 20;
        for (int j = 0; j < COLS; j++) {
            if (i == 0) { 
                bricks = newGRect(0, 0, 35, 10);
                setColor(bricks, "BLACK");
                setFilled(bricks, true);
                setLocation(bricks, x, y);
                add(window, bricks);
                x += 40;
            }
            else if (i == 1) {
                bricks = newGRect(0, 0, 35, 10);
                setColor(bricks, "BLUE");
                setFilled(bricks, true);
                setLocation(bricks, x, y);
                add(window, bricks);
                x += 40; 
            }
            else if (i == 2) {
                bricks = newGRect(0, 0, 35, 10);
                setColor(bricks, "ORANGE");
                setFilled(bricks, true);
                setLocation(bricks, x, y);
                add(window, bricks);
                x += 40;
            }
            else if (i == 3) {
                bricks = newGRect(0, 0, 35, 10);
                setColor(bricks, "GREEN");
                setFilled(bricks, true);
                setLocation(bricks, x, y);
                add(window, bricks);
                x += 40; 
            }
            else if (i == 4) {
                bricks = newGRect(0, 0, 35, 10);
                setColor(bricks, "RED");
                setFilled(bricks, true);
                setLocation(bricks, x, y);
                add(window, bricks);
                x += 40;
            }
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    GOval circle;
    double x = 194;
    double y = 300;
    
    circle = newGOval(12, 12, 12, 12);
    setColor(circle, "BLACK");
    setFilled(circle, true);
    setLocation(circle, x, y);
    add(window, circle);
    return circle;
    
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    GRect paddle = newGRect(0, 0, 100, 10);
    setColor(paddle, "RED");
    setFilled(paddle, true);
    double x = 150;
    double y = 450;
    add(window, paddle);
    setLocation(paddle, x, y);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    GLabel score = newGLabel("");
    setFont(score, "SansSerif-18");
    int x = (getWidth(window) - getWidth(score)) / 2;
    int y = (getHeight(window) + getFontAscent(score)) / 2;
    setLocation(score, x, y);
    add(window, score);
    return score;   
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
