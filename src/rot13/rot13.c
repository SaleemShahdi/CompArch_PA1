#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv) {
  //printf("Uryyb");
  for(int i=0; argv[1][i] != '\0'; i++) {
    char c = argv[1][i];
    if (isalpha(c) != 0) {
      if ((c >= 'a') && (c <= 'm')) {
        c = c + 13;
      } else if ((c >= 'A') && (c <= 'M')) {
        c = c + 13;
      } else if ((c >= 'n') && (c <= 'z')) {
        c = c - 13;
      } else if ((c >= 'N') && (c <= 'Z')) {
        c = c - 13;
      }
      printf("%c", c);
    } else {
      printf("%c", c);
    }
  }
  printf("\n");
  return EXIT_SUCCESS;
}
