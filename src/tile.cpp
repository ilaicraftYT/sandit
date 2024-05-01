#include "tile.h"
#include "tiletypes.h"

// ! WARNING
// ! STUPID, MESSY AND UGLY CODE THAT I SHOULD NEVER HAVE WRITTEN

void Tile::update(World *world) {
  // * Did this in a CSS of ifs because imagine all physics applied at once, way
  // * too much work to fix it
  // ? Is there even a better way?
  switch (type) {
  case TileType::AIR:
    break;
  case TileType::SAND:
    if (world->get(x, y + 1).type == TileType::AIR) { // Down
      MoveDown(world, TileType::AIR);
    } else if (world->get(x, y + 1).type == TileType::WATER) {
      MoveDown(world, TileType::WATER);
    } else if (world->get(x, y + 1).type == TileType::SMOKE) {
      MoveDown(world, TileType::SMOKE);
    } else if (world->get(x - 1, y + 1).type == TileType::AIR) {
      MoveDownLeft(world);
    } else if (world->get(x + 1, y + 1).type == TileType::AIR) {
      MoveDownRight(world);
    }
    break;
  case TileType::WATER:
    if (world->get(x, y + 1).type == TileType::AIR) {
      MoveDown(world, TileType::AIR);
    } else if (world->get(x - 1, y + 1).type == TileType::AIR) {
      MoveDownLeft(world);
    } else if (world->get(x + 1, y + 1).type == TileType::AIR) {
      MoveDownRight(world);
    }
    break;
  case TileType::WOOD:
    break; // no physics
  case TileType::FIRE:
    // TODO make have sense
    if (world->get(x, y - 1).type == TileType::WOOD) {
      Tile newTile = from(*this);
      newTile.y--;

      this->type = TileType::SMOKE;
      this->color = assignColor();

      world->set(x, y - 1, newTile);
    } else if (world->get(x - 1, y - 1).type == TileType::WOOD) {
      Tile newTile = from(*this);
      newTile.x--;
      newTile.y--;

      this->type = TileType::SMOKE;
      this->color = assignColor();

      world->set(x - 1, y - 1, newTile);
    } else if (world->get(x + 1, y - 1).type == TileType::WOOD) {
      Tile newTile = from(*this);
      newTile.x++;
      newTile.y--;

      this->type = TileType::SMOKE;
      this->color = assignColor();

      world->set(x + 1, y - 1, newTile);
    } else if (world->get(x - 1, y).type == TileType::WOOD) {
      Tile newTile = from(*this);
      newTile.x--;

      this->type = TileType::SMOKE;
      this->color = assignColor();

      world->set(x - 1, y, newTile);
    } else if (world->get(x + 1, y).type == TileType::WOOD) {
      Tile newTile = from(*this);
      newTile.x++;

      this->type = TileType::SMOKE;

      world->set(x + 1, y, newTile);
    } else if (world->get(x - 1, y + 1).type == TileType::WOOD) {
      Tile newTile = from(*this);
      newTile.x--;
      newTile.y++;

      this->type = TileType::SMOKE;
      this->color = assignColor();

      world->set(x - 1, y + 1, newTile);
    } else if (world->get(x + 1, y + 1).type == TileType::WOOD) {
      Tile newTile = from(*this);
      newTile.x++;
      newTile.y++;

      this->type = TileType::SMOKE;
      this->color = assignColor();

      world->set(x + 1, y + 1, newTile);
    } else if (GetRandomValue(0, 1) == 0) {
      Tile newTile;
      newTile.x = x;
      newTile.y = y;
      newTile.type = TileType::SMOKE;
      newTile.color = newTile.assignColor();

      world->set(x, y, newTile);
    }
    break;
  case TileType::SMOKE:
    if (world->get(x, y - 1).type == TileType::AIR) {
      Tile newTile = from(*this);
      newTile.y--;

      this->type = TileType::AIR;

      world->set(x, y - 1, newTile);
    } else if (world->get(x - 1, y - 1).type == TileType::AIR) {
      Tile newTile = from(*this);
      newTile.x--;
      newTile.y--;

      this->type = TileType::AIR;

      world->set(x - 1, y - 1, newTile);
    } else if (world->get(x + 1, y - 1).type == TileType::AIR) {
      Tile newTile = from(*this);
      newTile.x++;
      newTile.y--;

      this->type = TileType::AIR;

      world->set(x + 1, y - 1, newTile);
    } else if (world->get(x - 1, y).type == TileType::AIR) {
      Tile newTile = from(*this);
      newTile.x--;

      this->type = TileType::AIR;

      world->set(x - 1, y, newTile);
    } else if (world->get(x + 1, y).type == TileType::AIR) {
      Tile newTile = from(*this);
      newTile.x++;

      this->type = TileType::AIR;

      world->set(x + 1, y, newTile);
    }
    break;
  };
  updated = true;
}

void Tile::MoveDown(World *world, TileType type) {
  Tile newTile = from(*this);
  newTile.y++;

  this->type = type;
  this->color = assignColor();

  world->set(x, y + 1, newTile);
}

void Tile::MoveDownLeft(World *world) {
  Tile newTile = from(*this);
  newTile.x--;
  newTile.y++;

  this->type = TileType::AIR;

  world->set(x - 1, y + 1, newTile);
}

void Tile::MoveDownRight(World *world) {
  Tile newTile = from(*this);
  newTile.x++;
  newTile.y++;

  this->type = TileType::AIR;

  world->set(x + 1, y + 1, newTile);
}

void Tile::MoveLeft(World *world) {
  Tile newTile = from(*this);
  newTile.x--;

  this->type = TileType::AIR;

  world->set(x - 1, y, newTile);
}

void Tile::MoveRight(World *world) {
  Tile newTile = from(*this);
  newTile.x++;

  this->type = TileType::AIR;

  world->set(x + 1, y, newTile);
}

Color Tile::assignColor() {
  switch (type) {
  case TileType::AIR:
    return BLACK; //! Assert: should never be rendered, but just in case
    break;
  case TileType::SAND:
    return YELLOW;
    break;
  case TileType::WATER:
    return BLUE;
    break;
  case TileType::WOOD:
    return BROWN;
    break;
  case TileType::SMOKE:
    return GRAY;
    break;
  case TileType::FIRE: {
    if (GetRandomValue(0, 1) == 0) {
      return RED;
      break;
    }
    return ORANGE;
    break;
  }
  default:
    return WHITE; // ??????????????
    break;
  }
}

Tile Tile::from(Tile tile) {
  Tile nTile;
  nTile.type = tile.type;
  nTile.x = tile.x;
  nTile.y = tile.y;
  nTile.color = tile.color;
  return nTile;
}