#ifndef LOADINGSCENE_H
#define LOADINGSCENE_H
#include "Scene.h"
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>

class LoadingScene:public Scene{
  private:
    SDL_Texture* background = nullptr;
    Mix_Music* music = nullptr;
    uint32_t startTime = 0;
    SDL_Renderer* renderer;
    
  public:
    LoadingScene(SDL_Renderer *renderer);
    ~LoadingScene();
    void handleEvents(SDL_Event& event) override;
    void update() override;
    void render(SDL_Renderer *renderer) override;
};

#endif
