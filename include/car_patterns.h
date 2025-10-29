#ifndef CAR_PATTERNS_H
#define CAR_PATTERNS_H

#define TOTAL_STAGES 6 
#define STAGE_HEGIHT 20

#define LARGE_CAR 0
#define MEDIUM_CAR 1
#define SMALL_CAR 2

//: NOTE: These hold the string(chars) for each car pattern
extern char *LARGE_CAR_STRUCTURE[];
extern char *MEDIUM_CAR_STRUCTURE[];
extern char *SMALL_CAR_STRUCTURE[];

char **get_car_pattern(int stage_index);
int get_pattern_height(int stage_index);
int get_pattern_width(int stage_index);
#endif // CAR_PATTERNS_H
