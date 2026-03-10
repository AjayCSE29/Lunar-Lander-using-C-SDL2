#include "MenuScene.h"
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include "SceneManager.h"
#include "LoadingScene.h"
#include<iostream>

MenuScene::MenuScene(SDL_Renderer* renderer, SceneManager* manager){
  this->renderer = renderer;
  this->sceneManager = manager;
  SDL_Surface* surface = IMG_Load("assets/sprites/re_menu.png");
  if(!surface){
    std::cout<<"Image load error: "<<SDL_GetError()<<std::endl;
  }
  
  background = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  music = Mix_LoadMUS("assets/music/meet-the-princess.wav");
  if(music){
    Mix_PlayMusic(music, -1);
  }
}

MenuScene::~MenuScene(){
  if(background){
    SDL_DestroyTexture(background);
  }
  if(music){
    Mix_FreeMusic(music);
  }
}

void MenuScene::handleEvents(SDL_Event& event){
  if(event.type == SDL_KEYDOWN && event.key.repeat == 0){
    if(event.key.keysym.sym == SDLK_RETURN){
      sceneManager->changeScene(new LoadingScene(renderer), LOADING);
    }
    if(event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == 27){
      std::cout<<"Exit selected \n";
      SDL_Event quit;
      quit.type = SDL_QUIT;
      SDL_PushEvent(&quit);
    }
  }
}

void MenuScene::update(){
}

void MenuScene::render(SDL_Renderer* renderer){
  SDL_RenderCopy(renderer, background, nullptr, nullptr);
}
