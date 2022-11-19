#ifndef smv_autocomplete_trie_h
#define smv_autocomplete_trie_h

#include "common.h"

#define CHAR_LEN 64

typedef usize ID;

typedef struct Node {
  char character;
  // this is an array of relative pointers essentially
  ID children[CHAR_LEN];  // these should never be 0 if initialised
  bool is_end;
} Node;

typedef struct Trie {
  Node *nodes;
  int len, cap;
} Config;

void init_trie();
void add_word(const char *word);
void get_completion(const char *word);
void end_trie();

#endif