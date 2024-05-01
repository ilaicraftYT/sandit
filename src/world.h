#pragma once
#include "tile.h"
#include <unordered_map>

class Tile;

class World {
public:
  std::unordered_map<int, Tile> sandbox;

  int width, height, resizeFactor, brushSize = 0;

  void initWorld(int, int, int);

  void paint(int, int, TileType, int);

  void set(int, int, Tile);

  // No hagan IndexOutOfBounds, gracias
  Tile get(int x, int y);

  void update();

  void draw();
};