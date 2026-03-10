#include "SceneManager.h"
#include<iostream>

SceneManager::SceneManager(){
  currentScene = nullptr;
}

SceneManager::~SceneManager(){
  if(currentScene){
    delete currentScene;
  }
}

void SceneManager::changeScene(Scene* newScene, GameState state) {
  if(currentScene){
    delete currentScene;
  }
  currentScene = newScene;
  currentState = state;
  
  currentScene->sceneManager = this;
}

void SceneManager::handleEvents(SDL_Event& event){
  if(currentScene){
    currentScene->handleEvents(event);
  }
}

void SceneManager::update(){
  if(currentScene){
    currentScene->update();
  }
}

void SceneManager::render(SDL_Renderer* renderer){
  if(currentScene){
    currentScene->render(renderer);
  }
}

GameState SceneManager::getState(){
  return currentState;
}
