#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"
#include <string>
#include "tile.h"
#include <vector>

class Graphics;
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;

class Level {
public:
    Level();
    Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
    ~Level();
    void update(int elapsedTime);
    void draw(Graphics &graphics);
    Vector2 getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight);

private:
    std::string _mapName;
    std::string _tilesetName;
    Vector2 _spawnPoint;

    Vector2 _size;
    Vector2 _tileSize;

    SDL_Texture* _backgroundTexture;

    std::vector<Tile> _tileList;
    std::vector<Tileset> _tilesets;


    // void loadMap
    // loads a map
    void loadMap(std::string mapName, Graphics &graphics);

};


// tileset structure
struct Tileset {
    SDL_Texture* Texture;
    int FirstGid;

    Tileset() {
        this->FirstGid = -1;
    }
    Tileset(SDL_Texture* texture, int firstGid) {
        this->Texture = texture;
        this->FirstGid = firstGid;
    }
};




#endif