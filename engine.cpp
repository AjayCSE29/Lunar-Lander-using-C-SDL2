#include<iostream>
#define SDL_MAIN_HANDLED
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<cstdint>
#include "SceneManager.h"
#include "MenuScene.h"
#include<ctime>

const int WIDTH = 1088;
const int HEIGHT = 640;

class Engine {
  public:
    bool init();
    void run();
    void cleanup();
    
  private:
    void handleEvents();
    void update();
    void render();
    SceneManager sceneManager;
    
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;
    uint32_t* pixels = nullptr;
    
    bool running = false;
    uint32_t time = 0;
    
};

bool Engine::init() {
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cout<<"SDL Init Error: "<< SDL_GetError() << std::endl;
    return 1;
  }
  
  IMG_Init(IMG_INIT_PNG);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  TTF_Init();
  
  window = SDL_CreateWindow(
    "Lunar lander 0.1.1",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WIDTH, HEIGHT,
    SDL_WINDOW_SHOWN
  );
  if(!window) {
    std::cout<<"Window Error: " << SDL_GetError() << std::endl;
    return false;
  }
  
  renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_ACCELERATED
  );
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  if(!renderer){
    std::cout<<"Renderer error: " << SDL_GetError() << std::endl;
    return 1;
  }
  
  texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_STREAMING,
    WIDTH, HEIGHT
  );
  if(!texture){
    std::cout<<"Texture error: "<<SDL_GetError()<<std::endl;
    return false;
  }
  
  pixels = new uint32_t[WIDTH * HEIGHT];
  running = true;
  sceneManager.changeScene(new MenuScene(renderer, &sceneManager), MENU);
  return true;
}

void Engine::handleEvents(){
  SDL_Event event; 
  while(SDL_PollEvent(&event)) {
    if(event.type == SDL_QUIT) {
      running = false;
    }
  }
}

void Engine::update(){
  time++;
}

void Engine::render(){
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  sceneManager.render(renderer);
  SDL_RenderPresent(renderer);
}

void Engine::run(){
  SDL_Event event;
  while(running){
  
    uint32_t frameStart = SDL_GetTicks();
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT){
        running = false;
      }
      sceneManager.handleEvents(event);
    }
    sceneManager.update();
    sceneManager.render(renderer);
    SDL_RenderPresent(renderer);
    uint32_t frameTime = SDL_GetTicks() - frameStart;
    
    if(frameTime < 16){
      SDL_Delay(16 - frameTime);
    }
  }
}

void Engine::cleanup(){
  delete[] pixels;
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

//To Compile: g++ *.cpp -o game $(sdl2-config --cflags --libs) \-lSDL2_image -lSDL2_mixer -lSDL2_ttf

int main(int argc, char* argv[]){
  srand(time(NULL));
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
  Engine obj;
  if(!obj.init()){
    return 1;
  }
  obj.run();
  obj.cleanup();
  return 0;
}
