#include "Terrain.h"
#include<SDL2/SDL_image.h>
#include<iostream>

Terrain::Terrain(SDL_Renderer* renderer){
  for(int i=1; i<=6; i++){
    std::string path = "assets/terrain/t" + std::to_string(i) + ".png";
    SDL_Surface* surface = IMG_Load(path.c_str());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    terrainTextures.push_back(tex);
  }
  
  SDL_Surface* padSurface = IMG_Load("assets/sprites/landing_pad.png");
  if(!padSurface){
    std::cout<<"Pad load error: "<<IMG_GetError() << std::endl;
  } 
  padTexture = SDL_CreateTextureFromSurface(renderer, padSurface);
  SDL_FreeSurface(padSurface);
  
  int x = 0;
  for(int i=0; i<6; i++){
    TerrainSegment seg;
    seg.texture = terrainTextures[rand() % terrainTextures.size()];
    seg.x = x;
    seg.width = 512;
    segments.push_back(seg);
    x += seg.width;
  }
}

void Terrain::update(int cameraX){
  TerrainSegment last = segments.back();
  if(last.x + last.width < cameraX + 1200){
    TerrainSegment seg;
    seg.texture = terrainTextures[rand()%terrainTextures.size()];
    seg.width = 512;
    seg.x = last.x + last.width;
    segments.push_back(seg);
  }
}

Terrain::~Terrain(){
  if(texture){
    SDL_DestroyTexture(texture);
    }
    
  if(padTexture){
    SDL_DestroyTexture(padTexture);
  }
}

void Terrain::render(SDL_Renderer* renderer, float cameraX){
  for(auto &seg : segments){
    SDL_Rect dst;
    dst.x = seg.x - cameraX; 
    dst.y = 500;
    dst.w = seg.width;
    dst.h = 238;
    SDL_RenderCopy(renderer, seg.texture, NULL, &dst);
  }
  
  SDL_Rect padRect;
  padRect.x = padStart - cameraX;
  padRect.y = groundY;
  padRect.w = (padEnd - padStart + 200);
  padRect.h = 120;
  SDL_RenderCopy(renderer, padTexture, NULL, &padRect);
}

