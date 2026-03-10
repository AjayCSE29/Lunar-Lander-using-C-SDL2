#include "LoadingScene.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "GameState.h"
#include<iostream>

LoadingScene::LoadingScene(SDL_Renderer* renderer){
  this->renderer = renderer;
  startTime = SDL_GetTicks();
  SDL_Surface* surface = IMG_Load("assets/sprites/re_loading.png");
  if(!surface){
    std::cout<<"Loading Scene error \n ";
    return;
  }
  background = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  
  music = Mix_LoadMUS("assets/music/loading.wav");
  if(music){
    Mix_PlayMusic(music, -1);
  }
  startTime = SDL_GetTicks();
}

LoadingScene::~LoadingScene(){
  if(background){
    SDL_DestroyTexture(background);
  }
  if(music){
    Mix_FreeMusic(music);
  }
}

void LoadingScene::handleEvents(SDL_Event& event){

}

void LoadingScene::update(){
  uint32_t currentTime = SDL_GetTicks();
  if(currentTime - startTime > 5000){
    sceneManager->changeScene(new GameScene(renderer), GAME);
  }
}

void LoadingScene::render(SDL_Renderer* renderer){
  SDL_RenderCopy(renderer, background, NULL, NULL);
  uint32_t time = SDL_GetTicks();
  if((time / 500) % 2) {
    SDL_Rect rect = {380, 500, 40, 40};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
  }
}
