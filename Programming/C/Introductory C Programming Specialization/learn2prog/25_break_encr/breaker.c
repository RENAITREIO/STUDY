#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s file\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL)
  {
    fprintf(stderr, "File is not exist.\n");
    exit(EXIT_FAILURE);
  }
  int ch[26] = {0};
  char tmp;
  while(fread(&tmp, 1, 1, fp))
  {
    if (isalpha(tmp))
    {
      ch[tolower(tmp) - 'a']++;
    }
  }
  int e = 0;
  for (int i = 1; i < 26; i++)
  {
    if (ch[i] > ch[e])
    {
      e = i;
    }
  }
  int ans = e - 'e' + 'a';
  if (ans < 0)
    ans += 26;
  printf("%d\n", ans);
  fclose(fp);
  return EXIT_SUCCESS;
}
