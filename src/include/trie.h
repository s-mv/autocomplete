#ifndef smv_autocomplete_trie_h
#define smv_autocomplete_trie_h

#include "common.h"

typedef struct Node {
  char character;
  Node *children[26];
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