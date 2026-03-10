#ifndef TERRAIN_H
#define TERRAIN_H
#include<SDL2/SDL.h>
#include<vector>

class Terrain{
  private:
    std::vector<SDL_Point> points;
    SDL_Texture* texture = nullptr;
    SDL_Texture* padTexture = nullptr;
    struct TerrainSegment{
      SDL_Texture* texture;
      int x;
      int width;
    };
    std::vector<TerrainSegment> segments;
    std::vector<SDL_Texture*> terrainTextures;
  public:
    int groundY = 555;
    int padStart = 30 * 512;
    int padEnd = padStart + 200;
    int overlap = 4;
    int padHeight = 450;
    Terrain(SDL_Renderer* renderer);
    void update(int cameraX);
    ~Terrain();
    void render(SDL_Renderer* renderer, float cameraX);
};
#endif
