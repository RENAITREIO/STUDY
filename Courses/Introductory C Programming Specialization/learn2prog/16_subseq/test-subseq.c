#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int *array, size_t n);

int main(void)
{
  int array0[] = {-1, 0, 1};
  if (maxSeq(array0, 3) != 3)
  {
    printf("Failure on array0\n");
    exit(EXIT_FAILURE);
  }
  int array1[] = {-1, -1, -1};
  if (maxSeq(array1, 3) != 1)
  {
    printf("Failure on array1\n");
    exit(EXIT_FAILURE);
  }
  int array2[0];
  if (maxSeq(array2, 0) != 0)
  {
    printf("Failure on array2\n");
    exit(EXIT_FAILURE);
  }
  int array3[] = {3,2,1};
  if (maxSeq(array3, 3) != 1)
  {
    printf("Failure on array3\n");
    exit(EXIT_FAILURE);
  }
  int array4[] = {-4,-3,-2,-1};
  if (maxSeq(array4, 4) != 4)
  {
    printf("Failure on array4\n");
    exit(EXIT_FAILURE);
  }
  int array5[] = {1,2,3,1,2,3,4};
  if (maxSeq(array5, 7) != 4)
  {
    printf("Failure on array5\n");
    exit(EXIT_FAILURE);
  }
  printf("Congratulation!\n");
  return EXIT_SUCCESS;
}
