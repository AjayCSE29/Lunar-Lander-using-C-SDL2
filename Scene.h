#ifndef SCENE_H
#define SCENE_H
#include<SDL2/SDL.h>

class SceneManager;

class Scene {
  public:
    SceneManager* sceneManager = nullptr;
    virtual ~Scene() {}
    virtual void handleEvents(SDL_Event& event) = 0;
    virtual void update() = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
};

#endif
