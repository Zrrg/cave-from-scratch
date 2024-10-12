#include "Level.h"
#include "graphics.h"
#include "globals.h"

#include "tinyxml2.h"

#include <SDL2/SDL.h>

#include <sstream>
#include <algorithm>
#include <cmath>
#include <iostream>

 
using namespace tinyxml2;

Level::Level() {}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) :
            _mapName(mapName),
            _spawnPoint(spawnPoint),
            _size(Vector2(0,0))

{
    this->loadMap(mapName, graphics);
}

Level::~Level() {

}

void Level::loadMap(std::string mapName, Graphics &graphics) {
	//Parse the .tmx file
	XMLDocument doc;

	 
	
    std::string mapPath = globals::WORKING_FOLDER + globals::SLASH + "maps" + globals::SLASH + mapName + ".tmx";  
    std::cout << "mapPath!!! : " << mapPath << std::endl;
	doc.LoadFile(mapPath.c_str());
	XMLElement* mapNode = doc.FirstChildElement("map");


    // get the width and the height of the whole map and store it in _size
    int width, height; 
    mapNode->QueryIntAttribute("width", &width);
    mapNode->QueryIntAttribute("height", &height);
    this->_size = Vector2(width, height); 

    // get the width and the height of the tiles and store it in _tileSize

    int tileWidth, tileHeight;
    mapNode->QueryIntAttribute("tilewidth",&tileWidth);
    mapNode->QueryIntAttribute("tileheight",&tileHeight);
    this->_tileSize = Vector2(tileWidth, tileHeight);

    // load the tilesets
    XMLElement* pTileset = mapNode->FirstChildElement("tileset");
    if (pTileset != NULL) {
        while (pTileset) {
            int firstgid;
            const char* source = pTileset->FirstChildElement("image")->Attribute("source"); 
            char* path;
            std::stringstream ss;
            ss << source;
            pTileset->QueryIntAttribute("firstgid", &firstgid);  
            SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
            this->_tilesets.push_back(Tileset(tex, firstgid));

            pTileset = pTileset->NextSiblingElement("tileset");
        }
    }

    // loading the layers

    XMLElement* pLayer = mapNode->FirstChildElement("layer");
    if ( pLayer != NULL) {
        while (pLayer) {
            // loading the date element
            XMLElement * pData = pLayer->FirstChildElement("data");
            if (pData != NULL) {
                while (pData) {
                    //loading the tile element
                    XMLElement* pTile = pData->FirstChildElement("tile");
                    if (pTile != NULL) {
                        int tileCounter = 0;
                        while (pTile) {
                            // build each individual tile here
                            // if gid is 0, no tile should be drawn. Continue loop
                            if (pTile->IntAttribute("gid") == 0) {
                                tileCounter++;
                                if (pTile->NextSiblingElement("tile")) {
                                     pTile = pTile->NextSiblingElement("tile");
                                     continue;  
                                }
                                else {
                                    break;  
                                }
                            }

                            //get the tileset for this specifit gid 
                            int gid = pTile->IntAttribute("gid");
                            Tileset tls;
                            for (int i = 0; i < this->_tilesets.size(); i++) {
                                if (this->_tilesets[i].FirstGid <= gid) {
                                    // this it the tileset we want
                                    tls = this->_tilesets.at(i);
                                    break;
                                }
                            }

                            if (tls.FirstGid == -1) {
                                // No tileset was found for this gid
                                tileCounter++;
                                if (pTile->NextSiblingElement("tile")) {
                                    pTile = pTile->NextSiblingElement("tile");
                                    continue;
                                } 
                                else {
                                    break;
                                }
                            }


                            // get the position of the tile in the level
                            int xx = 0;
                            int yy = 0;
                            xx = tileCounter % width;
                            xx *= tileWidth;
                            yy += tileHeight * (tileCounter / width);
                            Vector2 finalTilePosition = Vector2(xx,yy);

                            // calculate the position of the tile in the tileset 
                            // dude what
							Vector2 finalTilesetPosition = this->getTilesetPosition(tls, gid, tileWidth, tileHeight);

                            // build the actual tile and add it to the level's tile list
                            Tile tile(tls.Texture, Vector2(tileWidth, tileHeight), finalTilesetPosition, finalTilePosition);
                            this->_tileList.push_back(tile);
                            tileCounter++;

                            pTile = pTile->NextSiblingElement("tile");
                        }
                    }
                    pData = pData->NextSiblingElement("data");
                }
            }
            pLayer = pLayer->NextSiblingElement("layer");
        }
    }
}

Vector2 Level::getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight) {
	int tilesetWidth, tilesetHeight;
	SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
	int tsxx = gid % (tilesetWidth / tileWidth) - 1;
	tsxx *= tileWidth;
	int tsyy = 0;
	int amt = ((gid - tls.FirstGid) / (tilesetWidth / tileWidth));
	tsyy = tileHeight * amt;
	Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);
	return finalTilesetPosition;
}

void Level::update(int elapsedTime) {

}

void Level::draw(Graphics &graphics) {
 
	for (int i = 0; i < this->_tileList.size(); i++) {
		this->_tileList.at(i).draw(graphics);
    }
}