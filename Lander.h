#ifndef LANDER_H
#define LANDER_H
#include "Terrain.h"
#include<SDL2/SDL.h>

class Lander{
  private:
    SDL_Texture* sprite1;
    SDL_Texture* sprite2;
    SDL_Texture* sprite3;
  
  public:
    float x = 500;
    float y = 100;
    float velocityX = 0;
    float velocityY = 0;
    float angle = 0;
    float fuel = 5000;
    bool thrusting = false;
    int animationFrame = 0;
    uint32_t lastFrameTime = 0;
    int landerHeight = 64;
    
    Lander(SDL_Renderer* renderer);
    ~Lander();
    
    void update(Terrain& terrain);
    void thrust();
    void rotateLeft();
    void rotateRight();
    
    void render(SDL_Renderer* renderer, float cameraX);
};

#endif
