#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "animatedSprite.h"
#include "globals.h"

class Graphics;

class Player : public AnimatedSprite {
public:
    Player();
    ~Player();
    Player(Graphics &graphics, float x, float y);
    void draw(Graphics &graphics);
    void update(float elapsedTime);
    
    // moves player left by -dx
    void moveLeft();

    // moves player right by dx
    void moveRight();
    

    // stops moving the player 
    void stopMoving();  

    virtual void animationDone(std::string currentAnimation);
    virtual void setupAnimations();

    const float getX() const;
    const float getY() const;


//private:
    float _dx, _dy;
    Direction _facing;
    bool _grounded;
};

 
#endif