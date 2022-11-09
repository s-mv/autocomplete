#ifndef smv_autocomplete_common_h
#define smv_autocomplete_common_h

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef size_t usize;

typedef struct Node Node;
typedef struct Trie Trie;

void *grow_array(void *arr, int size);

#define GROW_ARRAY(__smvArr__, __smvSize__, __smvType__)    \
  {                                                         \
    __smvArr__ = (__smvType__ *)grow_array(                 \
        (__smvArr__), (__smvSize__) * sizeof(__smvType__)); \
  }

bool load_trie(Trie *trie);
void save_trie(Trie *trie);
char *read_file(char *file_name);
void slice_str(char *dest, const char *text, int start, const int len);

#endif