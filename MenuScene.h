#ifndef MENUSCENE_H
#define MENUSCENE_H
#include "Scene.h"
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

class SceneManager;

class MenuScene : public Scene {
  private:
    SDL_Texture* background = nullptr;
    Mix_Music* music = nullptr;
    SDL_Renderer* renderer;
    SceneManager* sceneManager;

  public:
    MenuScene(SDL_Renderer* renderer, SceneManager* manager);
    ~MenuScene();
    void handleEvents(SDL_Event& event) override;
    void update() override;
    void render(SDL_Renderer* renderer) override;
};
#endif
