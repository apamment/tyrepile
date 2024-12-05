#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "Stacker.h"

extern "C" {
#include "magidoor/MagiDoor.h"
}

struct score {
  char name[128];
  uint32_t score;
  time_t date;
};

std::vector<struct score> scores;

bool compareScore(struct score s1, struct score s2) {
  return (s1.score > s2.score);
}

void display_high_scores() {
  const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  md_clr_scr();
  md_sendfile("tyrepile.ans", 0);
  for (int i = 0; i < 10 && i < scores.size(); i++) {
    struct tm scoretime;
#ifdef _MSC_VER
    localtime_s(&scoretime, &scores.at(i).date);
#else
    localtime_r(&scores.at(i).date, &scoretime);
#endif

    md_set_cursor(9 + i, 7);
    md_printf("`bright white`%-32.32s `bright green`%5d      `bright blue`%2d "
              "%s %04d %02d:%02d`white`\r\n",
              scores.at(i).name, scores.at(i).score, scoretime.tm_mday,
              months[scoretime.tm_mon], scoretime.tm_year + 1900,
              scoretime.tm_hour, scoretime.tm_min);
  }
}

bool save_high_scores() {
  FILE *fptr = fopen("scores.hi", "wb");

  if (fptr) {
    for (int i = 0; i < 10 && i < scores.size(); i++) {
      fwrite(&scores.at(i), sizeof(struct score), 1, fptr);
    }
    fclose(fptr);
    return true;
  }
  return false;
}

bool load_high_scores() {
  FILE *fptr = fopen("scores.hi", "rb");

  if (fptr) {
    for (int i = 0; i < 10 && !feof(fptr); i++) {
      struct score s;
      if (fread(&s, sizeof(struct score), 1, fptr) == 1) {
        scores.push_back(s);
      }
    }
    fclose(fptr);
    return true;
  }
  return false;
}

int main(int argc, char **argv) {
  int socket = -1;
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " DROPFILE [SOCKET]" << std::endl;
    return -1;
  }
  if (argc == 3) {
    socket = strtol(argv[2], NULL, 10);
  }

  md_init(argv[1], socket);

  char c;

  srand(time(NULL));

  load_high_scores();
  std::sort(scores.begin(), scores.end(), compareScore);
  display_high_scores();

  while ((c = tolower(md_getc())) != 'q') {
    int score = Stacker().play();
    struct score news;
    news.score = score;
    snprintf(news.name, 128, "%s %s", mdcontrol.user_firstname,
             mdcontrol.user_lastname);
    news.date = time(NULL);
    scores.push_back(news);
    std::sort(scores.begin(), scores.end(), compareScore);
    save_high_scores();
    display_high_scores();
  }

  md_exit(0);

  return 0;
}
