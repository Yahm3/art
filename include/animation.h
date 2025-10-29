#ifndef ANIMATION_H
#define ANIMATION_H

#define TOTAL_STAGES 6

typedef enum {
  FORWARD, // Receding (Large -> Small)
  BACKWARD
} Direction;

void start_animation(Direction direction, int start_y, int start_x);

void draw_car_stage(int stage, int y, int x);

void my_mvaddstr(int y, int x, char *str);

void clear_car_area(int y, int x);

#endif // ANIMATION_H
