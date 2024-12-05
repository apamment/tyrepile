#pragma once

class Tile {
public:
  Tile(int width, int speed, int ypos, int below_width, int below_x_pos,
       bool direction, bool grow);
  bool move();

  bool plonked;
  int width;
  int xpos;
  int colour;

private:
  int speed;
  int ypos;
  int below_width;
  int below_xpos;
  bool direction;
  bool grow;
};
