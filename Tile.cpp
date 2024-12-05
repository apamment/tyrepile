#include "Tile.h"
extern "C" {
#include "magidoor/MagiDoor.h"
}
#include <cstdlib>

Tile::Tile(int width, int speed, int ypos, int below_width, int below_x_pos,
           bool direction, bool grow) {
  this->width = width;
  this->speed = speed;
  this->ypos = ypos;
  this->below_width = below_width;
  plonked = false;
  this->direction = direction;
  this->colour = rand() % 15 + 1;
  below_xpos = below_x_pos;
  if (direction == true) {
    xpos = 1;
  } else {
    xpos = 80 - width;
  }
  this->grow = grow;
}

bool Tile::move() {
  md_set_cursor(ypos, 1);
  md_printf("\x1b[K");
  md_set_cursor(ypos, xpos);
  if (colour < 8) {
    switch (colour) {
    case 1:
      md_printf("`white`");
      break;
    case 2:
      md_printf("`red`");
      break;
    case 3:
      md_printf("`green`");
      break;
    case 4:
      md_printf("`yellow`");
      break;
    case 5:
      md_printf("`blue`");
      break;
    case 6:
      md_printf("`magenta`");
      break;
    case 7:
      md_printf("`cyan`");
      break;
    }
  } else {
    switch (colour - 8) {
    case 0:
      md_printf("`bright black`");
      break;
    case 1:
      md_printf("`bright white`");
      break;
    case 2:
      md_printf("`bright red`");
      break;
    case 3:
      md_printf("`bright green`");
      break;
    case 4:
      md_printf("`bright yellow`");
      break;
    case 5:
      md_printf("`bright blue`");
      break;
    case 6:
      md_printf("`bright magenta`");
      break;
    case 7:
      md_printf("`bright cyan`");
      break;
    }
  }

  for (int i = 0; i < width; i++) {
    md_printf("O");
  }
  md_printf("`white`");
  char c = md_getche(0, speed);
  if (c == ' ') {
    // plonk
    if (below_xpos == xpos) {
      if (grow == true && xpos > 1) {
        xpos--;
        width += 2;
      }

    } else {
      if (xpos < below_xpos) {
        width -= (below_xpos - xpos);
        xpos = below_xpos;
      } else {
        width -= (xpos - below_xpos);
      }
    }
    md_set_cursor(ypos, 1);
    md_printf("\x1b[K");
    if (colour < 8) {
      switch (colour) {
      case 1:
        md_printf("`white`");
        break;
      case 2:
        md_printf("`red`");
        break;
      case 3:
        md_printf("`green`");
        break;
      case 4:
        md_printf("`yellow`");
        break;
      case 5:
        md_printf("`blue`");
        break;
      case 6:
        md_printf("`magenta`");
        break;
      case 7:
        md_printf("`cyan`");
        break;
      }
    } else {
      switch (colour - 8) {
      case 0:
        md_printf("`bright black`");
        break;
      case 1:
        md_printf("`bright white`");
        break;
      case 2:
        md_printf("`bright red`");
        break;
      case 3:
        md_printf("`bright green`");
        break;
      case 4:
        md_printf("`bright yellow`");
        break;
      case 5:
        md_printf("`bright blue`");
        break;
      case 6:
        md_printf("`bright magenta`");
        break;
      case 7:
        md_printf("`bright cyan`");
        break;
      }
    }
    md_set_cursor(ypos, xpos);
    for (int i = 0; i < width; i++) {
      md_printf("O");
    }
    md_printf("`white`");
    plonked = true;
  } else if (c == 'q' || c == 'Q') {
    return true;
  } else {
    if ((!direction && xpos <= 1) || (direction && xpos + width >= 80)) {
      direction = !direction;
    }
    if (direction) {
      xpos++;
    } else {
      xpos--;
    }
  }

  return false;
}
