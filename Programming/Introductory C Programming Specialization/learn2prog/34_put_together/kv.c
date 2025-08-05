#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

char * strcopy(char *src, size_t length) {
  char *s = malloc((length + 1) * sizeof(*s));
  for (int i = 0; i < length; i++) {
    s[i] = src[i];
  }
  s[length] = '\0';
  return s;
}

void kvcpy(char *line, kvarray_t *arr) {
  char *ptr = strchr(line, '=');
  if (ptr == NULL) {
    fprintf(stderr, "Line has no =\n");
    exit(EXIT_FAILURE);
  }
  arr->length++;
  arr->arr = realloc(arr->arr, (arr->length) * sizeof(kvpair_t));
  size_t lengthk = ptr - line;
  arr->arr[arr->length - 1].key = strcopy(line, lengthk);
  size_t lengthv =  strlen(line) - lengthk - 1 - 1;
  arr->arr[arr->length - 1].value = strcopy(ptr + 1, lengthv);
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE *f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Fail to open %s\n", fname);
    exit(EXIT_FAILURE);
  }

  kvarray_t *kvarr = malloc(sizeof(*kvarr));
  kvarr->length = 0;
  kvarr->arr = NULL;
  char *line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) != -1) {
    kvcpy(line, kvarr);
    free(line);
    line = NULL;
  }
  free(line);
  fclose(f);
  return kvarr;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {
    free(pairs->arr[i].key);
    free(pairs->arr[i].value);
  }
  free(pairs->arr);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->arr[i].key, pairs->arr[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {
    if (strcmp(pairs->arr[i].key, key) == 0) {
      return pairs->arr[i].value;
    }
  }
  return NULL;
}
