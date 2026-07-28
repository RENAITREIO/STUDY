#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t *cts = malloc(sizeof(counts_t));
  cts->counts = NULL;
  cts->length = 0;
  cts->ukcount = 0;
  return cts;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->ukcount++;
    return;
  }
  for (int i = 0; i < c->length; i++) {
    if (strcmp(c->counts[i].name, name) == 0) {
      c->counts[i].num++;
      return;
    }
  }
  c->counts = realloc(c->counts, (c->length + 1) * sizeof(one_count_t));
  c->counts[c->length].num = 1;
  c->counts[c->length].name = malloc((strlen(name) + 1) * sizeof(char));
  strcpy(c->counts[c->length].name, name);
  c->length++;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->length; i++) {
    printf("%s: %d\n", c->counts[i].name, c->counts[i].num);
  }
  if (c->ukcount != 0)
    printf("<unknown>: %d\n", c->ukcount);
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->length; i++) {
    free(c->counts[i].name);
  }
  free(c->counts);
  free(c);
}
