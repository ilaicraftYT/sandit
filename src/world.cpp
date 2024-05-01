#include "world.h"
#include "raylib.h"
#include "tiletypes.h"

void World::initWorld(int w, int h, int resizeFactor) {
  resizeFactor = resizeFactor;
  width = w / resizeFactor;
  height = h / resizeFactor;

  for (int i = 0, y = 0, x; y < h; y++) {
    for (x = 0; x < w; x++, i++) {
      Tile tile;

      tile.x = x;
      tile.y = y;
      tile.type = TileType::AIR;
      tile.color = tile.assignColor();
      sandbox[i] = tile;
    };
  };
}

Tile World::get(int x, int y) { return sandbox[y * width + x]; }

void World::paint(int x, int y, TileType type, int brushSize) {
  for (int i = 0; i < brushSize; ++i) {
    for (int j = 0; j < brushSize; ++j) {
      Tile tile;

      tile.x = x + i;
      tile.y = y + j;
      tile.type = type;
      tile.color = tile.assignColor();
      set(x + i, y + j, tile);
    }
  }
}

void World::set(int x, int y, Tile tile) {
  bool canGoUnder =
      get(x, y).type == TileType::AIR ||
      (get(x, y).type == TileType::WATER &&
       (tile.type == TileType::SAND || tile.type == TileType::WATER));

  if ((x <= 0 || x > width || y <= 0 || y > height) && !canGoUnder)
    return;
  // printf("type: %d\n", tile.type);
  sandbox[y * width + x] = tile;
}

void World::update() {
  int i = width * height - 1;
  while (true) {
    if (sandbox[i].type != TileType::AIR)
      sandbox[i].update(this);

    if (i == 0)
      break;
    i--;
  }
}

void World::draw() {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      if (sandbox[i + j * width].type != TileType::AIR) {
        /* printf("dibujando x: %d, y: %d tipo: %d dX: %d dY: %d RGB: %d%d%d
           \n", i, j, sandbox[i + j * width].type, i * resizeFactor, j *
           resizeFactor, sandbox[i + j * width].color.r, sandbox[i + j *
           width].color.g, sandbox[i + j * width].color.b); */
        DrawRectangle(i * resizeFactor, j * resizeFactor, resizeFactor,
                      resizeFactor, sandbox[i + j * width].color);
      }
    }
  }
}