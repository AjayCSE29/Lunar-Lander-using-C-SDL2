#ifndef GAMESCENE_H
#define GAMESCENE_H
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include "Scene.h"
#include "Lander.h"
#include "Terrain.h"
#include<vector>

class GameScene : public Scene {
  private:
    Mix_Music* music = nullptr;
    SDL_Renderer* renderer;
    Lander* lander;
    Terrain* terrain;
    struct Star{
      int x;
      int y;
      int size;
      int brightness;
      int twinkleSpeed;
    };
    struct ShootingStar{
      float x;
      float y;
      float vx;
      float vy;
      bool active;
    };
    std::vector<Star> stars;
    ShootingStar shootingStar;
    int landingPadX = 1200;
    int landingPadY = 520;
    int landingPadWidth = 120;
    float cameraX = 0;
    const int LEFT_MARGIN = 200;
    const int RIGHT_MARGIN = 888;
    SDL_Texture* planetTexture;
    int planetFrame = 0;
    int planetFrameWidth = 32;
    int planetFrameHeight = 32;
    int planetTotalFrames = 48;
    int planetTimer = 0;
    bool landed = false;
    int landingTimer = 0;
    bool win = false;
    int gameTimer = 0;
    
  public:
    GameScene(SDL_Renderer* renderer);
    ~GameScene();
    
    void handleEvents(SDL_Event& event) override;
    void update() override;
    void render(SDL_Renderer* renderer) override;
};

#endif
