#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "Scene.h"
#include "GameState.h"

class SceneManager {
  private:
    Scene* currentScene = nullptr;
    GameState currentState;
  public:
    SceneManager();
    ~SceneManager();
    
    void changeScene(Scene* newScene, GameState state);
    void handleEvents(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);
    GameState getState();
};

#endif
