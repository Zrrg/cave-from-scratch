#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <map>
#include <string>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;         // i dunno what am doing
struct SDL_Texture;
struct SDL_Rect;


class Graphics {
    public:
        Graphics();
        ~Graphics();


        //SDL_Surface* loadImage
        // loads an image into the _spriteSheets map it it doesnt' already exist
        // as a result, each image will only ever be loaded once
        // returns the image from the map regardless of whether or not it was just loaded
        SDL_Surface *loadImage(const std::string &filePath);



        // void blitSurface
        // draws a texture to a certain part of the screen  
        void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

        // void flip
        // renders everything to the screen
        
        void flip();
        
        //void clear
        // clears the screen

        void clear(); 


        // SDL_Renderer* getRenderer
        // Returns the renderer

        SDL_Renderer* getRenderer() const;

    private:
        SDL_Window* _window;
        SDL_Renderer* _renderer;

        std::map<std::string, SDL_Surface*> _spriteSheets;
};

#endif