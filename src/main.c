#include "../include/car_patterns.h"
#include "../include/help.h"
#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
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

// Global animation settings settable via flags
int z_direction = 1; /* 1 = forward (small->large), -1 = backward (large->small) */
int paint_mode = 0;  /* 0 = normal, 1 = painted/color (not yet implemented) */

void check_flag(char flag) {
  switch (flag) {
  case 'C':
  case 'c':
    // Enable car animation (reserved for future use)
    break;

  case 'F':
  case 'f':
    help_menu();
    break;

  case 'B':
  case 'b':
    // Backward Z-Depth: large -> small
    z_direction = -1;
    break;

  case 'P':
  case 'p':
    // TODO: Painted car animation

//  case 'N':
//  case 'n':
//    // Use painted/color mode (not fully implemented)
//    paint_mode = 1;
//    break;
//
  case 'N':
  case 'n':
    // Normal (non-colored) mode
    paint_mode = 0;
    break;
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
    return;
  }

  for (int i = 1; i < argc; ++i) {
    char *arg = argv[i];
    printf("argv[%d]: %s\n", i, arg);
    if (arg[0] == '-' && arg[1] != '\n') {
      if (arg[1] == '-' && arg[2] == 'h') {
        help_menu();
      }
      char flag = arg[1];
      check_flag(flag);
    } else {
      printf("Argument not found everything will run on default");
    }
  }
}

int main(int argc, char *argv[]) {
  option(argc, argv);
  initscr();
  cbreak();
  noecho(); //: Hide the cursor
  //: NOTE: Declare the value
  int max_x, max_y;
  getmaxyx(stdscr, max_y, max_x);

  int y = max_y / 2;
  int x = 0;
  char *message = "Message";
  int msg_len = strlen(message);

  curs_set(0);
  /* Configure non-blocking input so animation can run while waiting for a key */
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);

  /* Z-depth order: small -> medium -> large (index order). We'll cycle through
     these to create the illusion of cars moving closer/farther. Direction is
     controlled by the `z_direction` flag set from CLI options. */
  int car_order[3] = {SMALL_CAR, MEDIUM_CAR, LARGE_CAR};
  const int stages = 3;
  int stage_idx = (z_direction == 1) ? 0 : (stages - 1);
  time_t stage_start = time(NULL);
  const int stage_seconds = 4; /* display each car for 4 seconds */

  while (1) {
    int ch = getch();
    if (ch != ERR) {
      /* any key pressed exits the animation loop */
      break;
    }

    /* keep terminal size up-to-date */
    getmaxyx(stdscr, max_y, max_x);

    /* obtain pattern and its length */
    int pattern_len = 0;
    const char **pattern = select_car_pattern(car_order[stage_idx], &pattern_len);

    /* draw centered */
    clear();
    int start_row = (max_y - pattern_len) / 2;
    if (start_row < 0) start_row = 0;
    for (int i = 0; i < pattern_len; ++i) {
      const char *line = pattern[i];
      int s_len = strlen(line);
      int start_col = (max_x - s_len) / 2;
      if (start_col < 0) start_col = 0;
      mvprintw(start_row + i, start_col, "%s", line);
    }
    /* optional small status message at bottom-left */
    mvprintw(max_y - 1, 0, "Press any key to quit (z-direction=%d)", z_direction);
    refresh();

    /* advance stage after interval */
    if (difftime(time(NULL), stage_start) >= stage_seconds) {
      stage_start = time(NULL);
      if (z_direction == 1)
        stage_idx = (stage_idx + 1) % stages;
      else
        stage_idx = (stage_idx - 1 + stages) % stages;
    }

    usleep(DELAY);
  }
  endwin();
  return 0;
}
