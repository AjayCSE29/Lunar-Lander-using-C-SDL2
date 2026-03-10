#include "GameScene.h"
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<iostream>

const int SCREEN_WIDTH = 1088;

GameScene::GameScene(SDL_Renderer* renderer){
  music = Mix_LoadMUS("assets/music/ingamebg.wav");
  if(music){
    Mix_PlayMusic(music, -1);
  }
  
  planetTexture = IMG_LoadTexture(renderer, "assets/sprites/planet.png");
  int texW, texH;
  SDL_QueryTexture(planetTexture, NULL, NULL, &texW, &texH);
  planetFrameWidth = texH;
  planetFrameHeight = texH;
  planetTotalFrames = texW / texH;
  
  for(int i = 0; i < 150; i++){
    Star s;
    s.x = rand() % 1000;
    s.y = rand() % 1000;
    s.size = 1 + rand() % 3;
    s.brightness = 150 + rand() % 105;
    s.twinkleSpeed = rand() % 3 + 1;
    stars.push_back(s);
  }
  
  this->renderer = renderer;
  lander = new Lander(renderer);
  terrain = new Terrain(renderer);
}

GameScene::~GameScene(){
  delete lander;
  delete terrain;
}

void GameScene::update(){
  planetTimer++;
  gameTimer++;
  if(planetTimer > 30){
    planetFrame++;
    planetTimer = 0;
    
    if(planetFrame >= planetTotalFrames){
      planetFrame = 0;
    }
  }

  if(win){
    return;
  }
  
  if(lander){
    lander->update(*terrain);
    float screenX = lander->x - cameraX;
    if(screenX > RIGHT_MARGIN){
      float target = lander->x - RIGHT_MARGIN;
      cameraX += (target - cameraX) * 0.1f;
    }
    
    if(screenX < LEFT_MARGIN){
      float target = lander->x - LEFT_MARGIN;
      cameraX += (target - cameraX) * 0.1f;
    }
  }
  
  //cameraX = lander->x - SCREEN_WIDTH / 2;
  
  for(auto &star : stars){
    if(rand()%50 < star.twinkleSpeed){
      star.brightness += rand() % 21 - 10;
      if(star.brightness < 120){
        star.brightness = 120;
      }
      if(star.brightness > 255){
        star.brightness = 255;
      }
    }
  }
  
  if(!shootingStar.active && rand() % 800 == 0){
    shootingStar.x = rand() % 1080;
    shootingStar.y = rand() % 200;
    shootingStar.vx = -6;
    shootingStar.vy = 2;
    shootingStar.active = true;
  }
  
  if(shootingStar.active){
    shootingStar.x += shootingStar.vx;
    shootingStar.y += shootingStar.vy;
    if(shootingStar.x < 0 || shootingStar.y > 720){
      shootingStar.active = false;
    }
  }

  //float worldPadX = landingPadX;
  float landerLeft = lander->x;
  float landerRight = lander->x + 40;
  float landerBottom = lander->y + 60;//lander->landerHeight;
  //std::cout<<lander->x << " " <<lander->y << std::endl;
  if(landerBottom >= landingPadY &&
     landerRight >= landingPadX &&
     landerLeft <= landingPadX + landingPadWidth){
    landingTimer++;
    if(landingTimer > 60){
      win = true;
      std::cout<<"WIN TRIGGERED"<<std::endl;
    }
  }
  else{
    landingTimer = 0;
  }
}

void GameScene::handleEvents(SDL_Event& event){
  if(event.type == SDL_KEYDOWN){
    switch(event.key.keysym.sym){
      case SDLK_UP:
        lander->thrust();
        break;
        
      case SDLK_LEFT:
        lander->rotateLeft();
        break;
        
      case SDLK_RIGHT:
        lander->rotateRight();
        break;
      
      case SDLK_f:
        if(gameTimer > 900){
          win = true;
        }
        break;
    }
  }
  
  if(event.type == SDL_KEYUP){
    if(event.key.keysym.sym == SDLK_UP){
      lander->thrusting = false;
    }
  }
}

void GameScene::render(SDL_Renderer* renderer){
  SDL_Rect bgRect = {0, 0, 1088, 640};
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  for(auto &star : stars){
    SDL_SetRenderDrawColor(
      renderer,
      star.brightness,
      star.brightness,
      star.brightness,
      255
    );
    
    SDL_Rect r;
    r.x = star.x;
    r.y = star.y;
    r.w = star.size;
    r.h = star.size;
    SDL_RenderFillRect(renderer, &r);
  }
  
  if(shootingStar.active){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(
      renderer,
      shootingStar.x,
      shootingStar.y,
      shootingStar.x + 15,
      shootingStar.y - 5
    );
  }
  
  cameraX = lander->x - 400;
  terrain->update(cameraX);
  terrain->render(renderer, cameraX);
  if(lander){
    lander->render(renderer, cameraX);
  }
  
  SDL_Rect src;
  src.x = planetFrame * planetFrameWidth;
  src.y = 0;
  src.w = planetFrameWidth;
  src.h = planetFrameHeight;
  
  SDL_Rect dst;
  dst.x = SCREEN_WIDTH - 350;
  dst.y = 80;
  dst.w = 180;
  dst.h = 180;
  SDL_RenderCopy(renderer, planetTexture, &src, &dst);
  
  if(win){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
    SDL_Rect overlay = {0, 0, SCREEN_WIDTH, 720};
    SDL_RenderFillRect(renderer, &overlay);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect winBox = {SCREEN_WIDTH / 2 - 150, 250, 300, 100};
    SDL_RenderFillRect(renderer, &winBox);
    
    TTF_Font* font = TTF_OpenFont("arial.ttf", 64);
    SDL_Color textColor = {0, 0, 0};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "YOU WON!", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect;
    textRect.x = SCREEN_WIDTH / 2 - 140;
    textRect.y = 270;
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
  }
}
