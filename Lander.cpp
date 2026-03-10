#include "Lander.h"
#include<SDL2/SDL_image.h>
#include<cmath>

const float GRAVITY = 0.03f;
const float THRUST_POWER = 0.25f;

Lander::Lander(SDL_Renderer* renderer){
  SDL_Surface* s1 = IMG_Load("assets/sprites/Rocket/1.png");
  SDL_Surface* s2 = IMG_Load("assets/sprites/Rocket/2.png");
  SDL_Surface* s3 = IMG_Load("assets/sprites/Rocket/3.png");
  
  sprite1 = SDL_CreateTextureFromSurface(renderer, s1);
  sprite2 = SDL_CreateTextureFromSurface(renderer, s2);
  sprite3 = SDL_CreateTextureFromSurface(renderer, s3);
  
  SDL_FreeSurface(s1);
  SDL_FreeSurface(s2);
  SDL_FreeSurface(s3);
  
}

Lander::~Lander(){
  if(sprite1){
    SDL_DestroyTexture(sprite1);
  }
  if(sprite2){
    SDL_DestroyTexture(sprite2);
  }
  if(sprite3){
    SDL_DestroyTexture(sprite3);
  }
}

void Lander::thrust() {
  if(fuel <= 0) return;
  thrusting = true;
  float rad = angle * M_PI / 180.0f;
  velocityX += sin(rad) * THRUST_POWER;
  velocityY -= cos(rad) * THRUST_POWER;
  fuel -= 0.1f;
}

void Lander::rotateLeft(){
  angle -= 3;
}

void Lander::rotateRight(){
  angle +=3;
}

void Lander::update(Terrain& terrain){
  velocityY += GRAVITY;
  x += velocityX;
  y += velocityY;
  
  float terrainHeight = 550;
  float padTop = 520 - landerHeight;
  bool onPad = (x > 1200 && x < 1200 + 120);
  if(onPad){
    if(y > padTop){
      y = padTop;
      velocityY = 0;
      velocityX *= 0.8f;
    }
  }
  else{ 
    if(y > 550){
      y = 550;
      velocityY = 0;
      velocityX *= 0.8f;
    }
  }
  velocityX *= 0.999f;
  uint32_t currentTime = SDL_GetTicks();
  if(thrusting && currentTime - lastFrameTime > 150){
    animationFrame++;
    if(animationFrame > 2){
      animationFrame = 0;
    }
  if(!thrusting){
    animationFrame = 0;
  }
    lastFrameTime = currentTime;
  }
}

void Lander::render(SDL_Renderer* renderer, float cameraX){
  SDL_Rect dest;
  dest.x = x - cameraX;
  dest.y = y;
  dest.w = 64;
  dest.h = 64;
  if(dest.x < 0) dest.x = 0;
  if(dest.x > 1088 - dest.w) dest.x = 1088 - dest.w;

  SDL_Texture* currentSprite;
  if(!thrusting){
    currentSprite = sprite1;
  }
  else{
    if(animationFrame == 0){
      currentSprite = sprite1;
    }
    else if(animationFrame == 1){
      currentSprite = sprite2;
    }
    else{
      currentSprite = sprite3;
    }
  }

  SDL_RenderCopyEx(
  renderer, 
  currentSprite,
  NULL,
  &dest,
  angle, 
  NULL,
  SDL_FLIP_NONE);
}
