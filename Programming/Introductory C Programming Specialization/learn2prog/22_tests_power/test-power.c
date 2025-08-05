#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y);

int main(void) {
  if (power(0,0) != 1) {
    printf("Fail on 1\n");
    exit(EXIT_FAILURE);
  }
  if (power(2,2) != 4) {
    printf("Fail on 2\n");
    exit(EXIT_FAILURE);
  }
  if (power(4,0) != 1) {
    printf("Fail on 3\n");
    exit(EXIT_FAILURE);
  }
  if (power(10,2) != 100) {
    printf("Fail on 4\n");
    exit(EXIT_FAILURE);
  }
  if (power(1,200) != 1) {
    printf("Fail on 5\n");
    exit(EXIT_FAILURE);
  }
  if (power(0,5) != 0) {
    printf("Fail on 6\n");
    exit(EXIT_FAILURE);
  }
  if (power(-2,3) != -8) {
    printf("Fail on 6\n");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
