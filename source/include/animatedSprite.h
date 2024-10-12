#ifndef ANIMATED_SPITE_H
#define ANIMATED_SPRITE_H

#include <map>
#include <string>
#include <vector>
#include "globals.h"
#include "sprite.h"

class Graphics;

/*  animatedSprite class
 *  holds logic for animated sprites
 */

class AnimatedSprite : public Sprite {
public:
    AnimatedSprite();
    ~AnimatedSprite();
    AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
                    float posX, float posY, float timeToUpdate);

    // void playAnimation
    // plays the animation provided if its not already playing

    void playAnimation(std::string animation, bool once = false);

    // void update
    // updates the animated sprite (timer)
    void update(int elapsedTime);

    // void draw
    // draws the sprite to the screen
    //
    void draw(Graphics &graphics, int x, int y);

 
protected:
    double _timeToUpdate;
    bool _currentAnimationOnce;
    std::string _currentAnimation;
    // void addAnimation
    // Adds an animation to the map of animations for the sprite
    void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

    // void resetAnimations
    //  Resets all animations associated with this sprite

    void resetAnimations();

    void stopAnimation();

    void setVisible(bool visible);

    virtual void animationDone(std::string currentAnimation) = 0;

    // void setupAnimation
    // a required function that sets up all animations for a sprite
    //
    virtual void setupAnimations() = 0;

private:



    std::map<std::string, std::vector<SDL_Rect>> _animations;
    std::map<std::string, Vector2> _offsets;

    int _frameIndex;
    double _timeElapsed;
    bool _visible;

};

#endif