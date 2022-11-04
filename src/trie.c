#include "trie.h"

Trie trie;

Node *root;

void add_base_words();

void init_trie() {
  if (load_trie(&trie)) return;
  add_base_words();
}

void add_base_words() {
  trie = (Trie){
      .nodes = malloc(4096 * sizeof(Node)),
      .len = 0,
      .cap = 4096,
  };

  root = &trie.nodes[0];

  const char *file = read_file(".data/base.txt");

  for (int i = 0; file[i] != '\0'; i++) {
    int len;
    for (len = 0; file[i + len] != '\n'; len++)
      ;
    char word[len + 1];
    slice_str(word, file, i, len);
    printf("%s\n", word);
    add_word(word);
    i += len;
  }
}

void add_word(const char *word) {
}

void end_trie() {
  save_trie(&trie);
  free(trie.nodes);
}