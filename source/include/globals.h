#ifndef GLOBALS_H
#define GLOBALS_H
#include <string>





namespace globals {
    const int SCREEN_WIDTH {640};
    const int SCREEN_HEIGHT {480};

    const int SPRITE_SCALE {2};
    inline std::string WORKING_FOLDER;
    inline std::string EXECUTABLE_PATH;
    inline std::string SLASH;

}



enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN
};




struct Vector2 {
    int x,y;
    Vector2() :
        x(0), y(0) 
    {}
    Vector2(int x, int y) :
        x(x), y(y)
    {}
    Vector2 zero() {
        return Vector2(0, 0);
    }
};



#endif