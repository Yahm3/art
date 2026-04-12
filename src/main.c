#include "../include/car_patterns.h"
#include "../include/help.h"
#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define DELAY 50000

typedef struct {
  const char **pattern;
  int height;
  int width;
  int x;
  int y;
  int dx;
  int dy;
} Car;

int z_direction = 1;
int paint_mode = 0;
void check_flag(char flag) {
  switch (flag) {
  case 'C':
  case 'c':
    // :NOTE: Enable car animation (reserved for future use)
    break;

  case 'F':
  case 'f':
    z_direction = 1;
    break;

  case 'B':
  case 'b':
    z_direction = -1;
    break;

  case 'P':
  case 'p':
    /* TODO: Painted car animation

     case 'N':
     case 'n':
       // Use painted/color mode (not fully implemented)
       paint_mode = 1;
       break;
    */

  case 'N':
  case 'n':
    // Normal (non-colored) mode
    paint_mode = 0;
    break;

  default:
    help_menu();
    exit(1);
    break;
  }
}

const char **select_car_pattern(int car_type, int *out_len) {
  const char **pattern = NULL;

  switch (car_type) {
  case LARGE_CAR:
    pattern = (const char **)LARGE_CAR_STRUCTURE;
    break;
  case MEDIUM_CAR:
    pattern = (const char **)MEDIUM_CAR_STRUCTURE;
    break;
  case SMALL_CAR:
    pattern = (const char **)SMALL_CAR_STRUCTURE;
    break;
  default:
    pattern = (const char **)
        MEDIUM_CAR_STRUCTURE; //: NOTE: Set the default car MEDIUM_CAR
    break;
  }

  *out_len = 0;
  while (pattern[*out_len] != NULL) {
    (*out_len)++;
  }
  return pattern;
}

void option(int argc, char *argv[]) {
  if (argc >= 4) {
    help_menu();
    exit(1);
  } else {
    for (int i = 1; i < argc; ++i) {
      char *arg = argv[i];
      if (arg[0] == '-' && arg[1] != '\n') {
        if (arg[1] == '-' && arg[2] == 'h') {
          help_menu();
          exit(1); //: NOTE: Show menu and exit
        } else {
          char flag = arg[1];
          check_flag(flag);
        }
      } else {
        printf("Argument not found everything will run on default");
      }
    }
  }
}

int main(int argc, char *argv[]) {
  option(argc, argv);
  initscr();
  cbreak();
  noecho(); //: NOTE: Hide the cursor
  int max_x, max_y;
  getmaxyx(stdscr, max_y, max_x);

  // int y = max_y / 2;
  // int x = 0;
  // char *message = "Message";
  // int msg_len = strlen(message);

  curs_set(2);
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);

  int car_order[3] = {SMALL_CAR, MEDIUM_CAR, LARGE_CAR};
  const int stages = 3;
  int stage_idx = (z_direction == 1) ? 0 : (stages - 1);
  time_t stage_start = time(NULL);
  const int stage_seconds = 3;

  while (1) {
    int ch = getch();
    if (ch != ERR) {
      /*:NOTE: any key pressed exits the animation loop */
      break;
    }

    getmaxyx(stdscr, max_y, max_x);

    int pattern_len = 0;
    const char **pattern =
        select_car_pattern(car_order[stage_idx], &pattern_len);

    clear();
    int start_row = (max_y - pattern_len) / 2;
    if (start_row < 0)
      start_row = 0;
    for (int i = 0; i < pattern_len; ++i) {
      const char *line = pattern[i];
      int s_len = strlen(line);
      int start_col = (max_x - s_len) / 2;
      if (start_col < 0) {
        start_col = 0;
      }
      mvprintw(start_row + i, start_col, "%s", line);
      refresh();
    }

    mvprintw(max_y - 1, 0, "Press any key to quit (z-direction=%d)",
             z_direction);
    refresh();

    time_t difT = time(NULL) - stage_start;
    if (difT >= stage_seconds) {
      stage_start = time(NULL);
      if (z_direction == 1) {
        stage_idx = (stage_idx + 1) % stages;
      } else {
        stage_idx = (stage_idx - 1 + stages) % stages;
      }
    }

    // usleep(DELAY);
  }
  endwin();
  return 0;
}
