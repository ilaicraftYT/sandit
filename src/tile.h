#pragma once
#include "raylib.h"
#include "tiletypes.h"
#include "world.h"

class World;

class Tile {
public:
  TileType type = TileType::AIR;
  bool updated = false;
  Color color = YELLOW;
  int x;
  int y;

  Color assignColor();
  Tile from(Tile);
  void update(World *);

  void MoveDown(World *, TileType);
  void MoveRight(World *);
  void MoveLeft(World *);
  void MoveDownRight(World *);
  void MoveDownLeft(World *);
  void MoveUp(World *);
  void MoveUpLeft(World *);
};