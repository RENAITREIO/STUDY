#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

char * strcopy(char *src, size_t length);

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE *input = fopen(filename, "r");
  if (input == NULL) {
    fprintf(stderr, "Fail to open %s\n", filename);
    exit(EXIT_FAILURE);
  }
  counts_t *ans = createCounts();
  char *line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, input) != -1) {
    char *key = strcopy(line, strlen(line) - 1);
    addCount(ans, lookupValue(kvPairs, key));
    free(key);
    free(line);
    line = NULL;
  }
  free(line);
  fclose(input);
  return ans;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc <= 2) {
    fprintf(stderr, "Usage: %s file1 file2 ...\n", argv[0]);
    exit(EXIT_FAILURE);
  }
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t *kv = readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t *c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char *outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE *f = fopen(outName, "w");

    //print the counts from c into the FILE f
    for (int i = 0; i < c->length; i++) {
      fprintf(f, "%s: %d\n", c->counts[i].name, c->counts[i].num);
    }
    if (c->ukcount != 0)
      fprintf(f, "<unknown> : %d\n", c->ukcount);
    //close f
    fclose(f);
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
    }
 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
