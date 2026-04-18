#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function is used to figure out the ordering
// of the strings in qsort.  You do not need
// to modify it.
int stringOrder(const void *vp1, const void *vp2)
{
  const char *const *p1 = vp1;
  const char *const *p2 = vp2;
  return strcmp(*p1, *p2);
}
// This function will sort and print data (whose length is count).
void sortData(char **data, size_t count)
{
  qsort(data, count, sizeof(char *), stringOrder);
}

char **getData(size_t *count, FILE *f)
{
  char **data = NULL;
  char *line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) != -1)
  {
    data = realloc(data, (*count + 1) * sizeof(data));
    data[*count] = line;
    line = NULL;
    (*count)++;
  }
  free(line);
  return data;
}

void print_while_free(char **data, size_t count)
{
  for (int i = 0; i < count; i++)
  {
    printf("%s", data[i]);
    free(data[i]);
  }
  free(data);
}

int main(int argc, char **argv)
{

  // WRITE YOUR CODE HERE!
  if (argc == 1)
  {
    size_t count = 0;
    char **data = getData(&count, stdin);
    sortData(data, count);
    print_while_free(data, count);
  }
  else if (argc > 1)
  {
    for (int i = 1; i < argc; i++)
    {
      FILE *f = fopen(argv[i], "r");
      if (f == NULL)
      {
        fprintf(stderr, "Fail to open %s\n", argv[i]);
        exit(EXIT_FAILURE);
      }
      size_t count = 0;
      char **data = getData(&count, f);
      sortData(data, count);
      print_while_free(data, count);
      if (fclose(f) != 0)
      {
        fprintf(stderr, "Fail to close %s\n", argv[i]);
        exit(EXIT_FAILURE);
      }
    }
  }
  return EXIT_SUCCESS;
}
