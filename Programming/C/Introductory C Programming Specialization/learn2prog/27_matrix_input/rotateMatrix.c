#include <stdio.h>
#include <stdlib.h>

void rotate(char matrix[10][10]);

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s filename\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL)
  {
    fprintf(stderr, "Fail to open %s.\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  char matrix[10][10];
  for (int i = 0; i < 10; i++)
  {
    char tmp[10];
    char tmpCheck;
    if (fread(tmp, sizeof(tmp), 1, fp) == 0)
    {
      fprintf(stderr, "Format Error.\n");
      exit(EXIT_FAILURE);
    }
    fread(&tmpCheck, sizeof(char), 1, fp);
    if (i < 9 && tmpCheck != '\n')
    {
      fprintf(stderr, "Format Error.\n");
      exit(EXIT_FAILURE);
    }
    for (int j = 0; j < 10; j++)
    {
      if (tmp[j] == '\n')
      {
	fprintf(stderr, "Format Error.\n");
	exit(EXIT_FAILURE);
      }
      else
      {
	matrix[i][j] = tmp[j];
      }
    }
  }
  if (fgetc(fp) != EOF)
  {
    fprintf(stderr, "Format Error.\n");
    exit(EXIT_FAILURE);
  }
  rotate(matrix);
  if (fclose(fp) != 0)
  {
    fprintf(stderr, "Fail to close %s.\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
  return EXIT_SUCCESS;
}

#define MAX 10

void rotate(char matrix[10][10]) {
  char temp[MAX][MAX];
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      temp[j][MAX - 1 - i] = matrix[i][j];
    }
  }
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      matrix[i][j] = temp[i][j];
    }
  }
}

