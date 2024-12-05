#pragma once

#include <vector>

class Tile;

class Stacker {
public:
  Stacker();
  ~Stacker();
  int play();

private:
  int score;
  std::vector<Tile *> tiles;
};
