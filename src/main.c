#include <stdio.h>

void check_flag(char flag) {
  switch (flag) {
  case 'C':
  case 'c':
    //: TODO: The logic to draw the car animiation
    //:  Currenty We can only animate car(s) only
    break;

  case 'F':
  case 'f':
    //: TODO: The logic to draw the forward animation
    break;

  case 'B':
  case 'b':
    //: TODO: The logic to draw the backward animation
    break;

  case 'P':
  case 'p':
    // TODO: Painted car animation

  case 'N':
  case 'n':
    // TODO: normal car animation
    break;

  default:
    // TODO: Display the manual and exit
    break;
  }
}

void option(int argc, char *argv[]) {
  for (int i = 1; i < argc; ++i) {
    char *arg = argv[i];
    printf("argv[%d]: %s\n", i, arg);
    if (arg[0] == '-' && arg[1] != '\n') {
      char flag = arg[1];
      check_flag(flag);
    } else {
      printf("Argument not found everything will run on default");
    }
  }
}

int main(int argc, char *argv[]) {
  printf("Hello ASCII art\n");
  printf("Art is beautiful\n");
  option(argc, argv);
  return 0;
}
