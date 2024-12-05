#include "Stacker.h"
#include "Tile.h"
#include <vector>
extern "C" {
#include "magidoor/MagiDoor.h"
}
Stacker::Stacker() { score = 0; }

Stacker::~Stacker() {
  for (Tile *t : tiles) {
    delete t;
  }
}

int Stacker::play() {
  bool quit = false;
  int next_size = 50;
  int speed = 120000;
  int ypos = 23;
  bool direction = true;
  bool grow = false;
  int prev_xpos = 15;
  int prev_size = next_size;
  int streak = 0;

  md_clr_scr();

  Tile *t =
      new Tile(next_size, speed, ypos, prev_size, prev_xpos, direction, grow);
  t->plonked = true;
  t->xpos = 15;
  md_set_cursor(ypos, 1);
  md_printf("\x1b[K");
  md_set_cursor(ypos, t->xpos);
  if (t->colour < 8) {
    switch (t->colour) {
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
    switch (t->colour - 8) {
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
  for (int i = 0; i < t->width; i++) {
    md_printf("O");
  }
  md_printf("`white`");
  ypos--;
  tiles.push_back(t);

  while (!quit) {
    md_set_cursor(1, 1);
    md_printf("`red bright white`Score: %d   Streak: %d    Speed: %d\x1b[K",
              score, streak, speed);
    md_set_cursor(24, 1);
    md_printf("`red bright white`SPACE to Drop, Q to Quit\x1b[K`white`", score);
    Tile *t =
        new Tile(next_size, speed, ypos, prev_size, prev_xpos, direction, grow);
    while (!t->plonked && !quit) {
      quit = t->move();
    }

    if (t->plonked) {
      next_size = t->width;
      if (next_size <= 0) {
        return score;
      }
      score++;

      if (t->width >= tiles.at(tiles.size() - 1)->width) {
        md_printf("\007");
        streak++;
        if (streak % 8 == 0 && streak > 0) {
          speed += 8000;
        }
      } else {
        streak = 0;
      }
      tiles.push_back(t);

      direction = !direction;
      prev_xpos = t->xpos;
      prev_size = t->width;
      grow = false;
      if (streak >= 3) {
        grow = true;
      }

      if (ypos == 2) {
        // move all down
        md_set_cursor(ypos, 1);
        md_printf("\x1b[0J");
        for (int y = 22; y >= 1; y--) {
          Tile *ti = tiles.at(tiles.size() - y);
          md_set_cursor(y + 2, ti->xpos);
          if (ti->colour < 8) {
            switch (ti->colour) {
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
            switch (ti->colour - 8) {
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
          for (int i = 0; i < ti->width; i++) {
            md_printf("O");
          }
          md_printf("`white`");
        }
      } else {
        ypos--;
      }
      if (speed > 4000) {
        speed -= 2000;
      }
    }
  }

  return score;
}
