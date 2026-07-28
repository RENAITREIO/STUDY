#include "cachelab.h"
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void get_arg(int argc, char **argv, int *s, int *E, int *b, char **t)
{
    int opt;
    while ((opt = getopt(argc, argv, "s:E:b:t:")) != -1) {
        switch (opt) {
        case 's':
            *s = atoi(optarg);
            break;
        case 'E':
            *E = atoi(optarg);
            break;
        case 'b':
            *b = atoi(optarg);
            break;
        case 't':
            *t = optarg;
            break;
        default:
            fprintf(stderr,"Usage: %s -s <s> -E <E> -b <b> -t <tracefile>\n",argv[0]);
            exit(1);
        }
    }

    if (*s == 0 || *E == 0 || *b == 0 || *t == NULL) {
        fprintf(stderr, "Missing required command line argument\n");
        exit(1);
    }
}

typedef struct cache_line
{
    int valid;
    unsigned long tag, id;
    int block;
} line_t;

typedef struct cache
{
    int S, E, B;
    line_t *martrix;
} cache_t;

void cache_init(int s, int E, int b, cache_t *cache)
{
    cache->S = 1 << s;
    cache->E = E;
    cache->B = 1 << b;
    int len = cache->S * cache->E;
    cache->martrix = malloc(len * sizeof(line_t));
    for (int i = 0; i < len; i++)
    {
        cache->martrix[i].valid = 0;
        cache->martrix[i].id = 0;
    }
}

int is_hit(line_t *line, int N, unsigned long tag)
{
    for (int i = 0; i < N; i++)
        if (line[i].valid && line[i].tag == tag)
            return i;
    return -1;
}

int get_earliest(line_t *line, int N)
{
    int idx = 0;
    unsigned long id = -1;
    for (int i = 0; i < N; i++)
        if (line[i].id < id)
        {
            id = line[i].id;
            idx = i;
        }
    return idx;
}

int main(int argc, char **argv)
{
    int s = 0, E = 0, b = 0, hit_count = 0, miss_count = 0, eviction_count = 0;
    char *t = NULL;
    get_arg(argc, argv, &s, &E, &b, &t);

    cache_t cache;
    cache_init(s, E, b, &cache);

    char buf[100];
    FILE *trace = fopen(t, "r");
    if (trace == NULL)
    {
        fprintf(stderr, "Missing trace file\n");
        exit(1);
    }

    unsigned long id = 1;
    while (fgets(buf, sizeof(buf), trace))
    {
        if (buf[0] == 'I')
            continue;
        char op;
        unsigned long addr;
        int size; // do nothing
        sscanf(buf, " %c %lx,%d", &op, &addr, &size);
        
        unsigned long tag = addr >> (b + s);
        int N = cache.E;
        line_t *lineptr = &cache.martrix[N * ((addr >> b) % (1 << s))];
        int idx = is_hit(lineptr, N, tag);
        if (idx >= 0)
        {
            lineptr[idx].id = id;
            hit_count++;
        }
        else
        {
            miss_count++;
            int earliest_idx = get_earliest(lineptr, N);
            if (lineptr[earliest_idx].valid == 1)
                eviction_count++;
            lineptr[earliest_idx].valid = 1;
            lineptr[earliest_idx].tag = tag;
            lineptr[earliest_idx].id = id;
        }
        if (op == 'M')
            hit_count++;
        id++;
    }
    fclose(trace);
    free(cache.martrix);
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
