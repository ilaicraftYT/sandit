#include "raylib.h"
#include "tile.cpp"
#include "tile.h"
#include "tiletypes.h"
#include "world.cpp"
#include <map>
#include <string>

int main() {
  int width = 600;
  int height = 800;
  int resizeFactor = 2;
  int brushSize = 2;
  std::map<std::string, TileType> availableBrushTypes{
      {"Sand", TileType::SAND},
      {"Water", TileType::WATER},
      {"Wood", TileType::WOOD},
      {"Fire", TileType::FIRE},
      {"Smoke", TileType::SMOKE}};
  TileType brushType = TileType::SAND;
  std::string brushName = "Sand";

  InitWindow(width, height, "SandIt");
  SetTargetFPS(60);
  HideCursor();

  World world;
  world.resizeFactor = resizeFactor;
  world.initWorld(width, height, resizeFactor);

  while (!WindowShouldClose()) {
    world.update();
    int mouseX = GetMouseX() / resizeFactor;
    int mouseY = GetMouseY() / resizeFactor;

    if (IsKeyPressed(KEY_SPACE)) {
      for (const auto &pair : availableBrushTypes) {
        if (pair.second == brushType) {
          auto it = std::next(availableBrushTypes.find(pair.first));
          if (it == availableBrushTypes.end()) {
            it = availableBrushTypes.begin();
          }
          brushName = it->first;
          brushType = it->second;
          break;
        }
      }
    }

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      world.paint(mouseX, mouseY, brushType, brushSize);
    }

    if (GetMouseWheelMove() != 0) {
      brushSize += GetMouseWheelMove();
    }

    if (brushSize < 1) {
      brushSize = 1;
    }

    BeginDrawing();

    ClearBackground(BLACK);
    world.draw();
    DrawText(brushName.c_str(), 4, 4, 24, WHITE);
    DrawText("<space> to switch", 4, 32, 16, WHITE);
    DrawRectangleLines(mouseX * resizeFactor, mouseY * resizeFactor,
                       brushSize * resizeFactor, brushSize * resizeFactor,
                       WHITE);

    EndDrawing();
  }
}