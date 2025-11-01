#include "../include/help.h"
#include <stdio.h>

void help_menu() {
  printf("\nAn ASCII animation art in the terminal\n\n");
  printf("Usage: art [OPTIONS]\n\n");
  printf("OPTION:\n\n");
  printf("-c, --car\n\tCar\n");
  printf("-f, --forward\n\tThe animation of the art will from a close "
         "view\n\tperspective view and will end in a far-away view\n");
  printf("-b, --backward\n\tThe animation will start from a far-away "
         "view\n\tand end in a close viewpoint of the art animation\n");
  printf("-p --paint\n\tThis will display a colored animation\n");
  printf("-n --normal\n\tThis will display a non-colored animation\n");
  printf("\nEXAMPLE: art -c -f -p  -- This will draw a colored car animation "
         "moving forward \n");
}
