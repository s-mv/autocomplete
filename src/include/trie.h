#ifndef smv_autocomplete_trie_h
#define smv_autocomplete_trie_h

#include "common.h"

#define CHAR_LEN 64

typedef struct Node {
  char character;
  // this is an array of relative pointers essentially
  usize children[CHAR_LEN];  // these will never be 0
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