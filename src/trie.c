#include "trie.h"

Trie trie;

Node *root;
void dump_dot(FILE *sink, Node *root);

void add_base_words();
int push_node(Node node);
int get_i(char c);  // vague naming I know, forgive me
void print_trie(Node *root, char str[], int level, int limit);
int traverse_prefix(const char *prefix, Node *parent);

void init_trie() {
  // NOTE: later delete the ; and uncomment the next two commented lines
  if (load_trie(&trie)) {
    root = &trie.nodes[0];
  } else
    add_base_words();

  printf("tree packing: %i / %i\n", trie.len, trie.cap);

  char word[1024];
}

void add_base_words() {
  trie = (Trie){
      .nodes = calloc(2048, sizeof(Node)),
      .cap = 2048,
  };

  root = &trie.nodes[0];
  trie.len = 1;

  const char *file = read_file(".data/base.txt");

  for (usize i = 0; file[i] != '\0'; i++) {
    usize len;
    for (len = 0; get_i(file[i + len]) != -1; len++)
      ;
    char word[len + 1];
    slice_str(word, file, i, len);
    add_word(word);
    i += len;
  }
}

void add_word(const char *word) {
  Node *parent = root;

  usize len = strlen(word);

  for (usize i = 0; i < len; i++) {
    char c = word[i];

    // if the index is 0 (which is the index of the ROOT) that means the child
    // is uninitialised, so we check if the index is 0 for now
    // NOTE: this might have to change in the future, may not cover some things
    if (parent->children[get_i(c)] == 0)
      parent->children[get_i(c)] = push_node((Node){
          .character = c,
          .is_end = i == len - 1,
          .children = {0},
      });  // NOTE: push_node simply gives back the index not a pointer

    parent = &trie.nodes[parent->children[get_i(c)]];
  }
}

void print_trie(Node *root, char *str, int level, int limit) {
  static int inner_lim = 0;

  if (inner_lim >= limit) {
    return;
  }

  if (root->is_end) {
    str[level] = '\0';
    printf("  %s\n", str);
    inner_lim++;
  }

  // NOTE: untested on actual data sooo yeah
  for (usize i = 0; i < CHAR_LEN; i++) {
    if (root->children[i] != 0) {
      str[level] = i + 'a';
      print_trie(&trie.nodes[root->children[i]], str, level + 1, limit);
    }
  }
}

int traverse_prefix(const char *prefix, Node *parent) {
  if (prefix[0] == '\0') return parent - root;
  return traverse_prefix(&prefix[1],
                         &trie.nodes[parent->children[get_i(prefix[0])]]);
}

void get_completion(const char *word) {
  // first get the root node
  // if the world is "hello" the root node is the one at 'o'
  int id = traverse_prefix(word, root);
  if (!id) return;

  char str[1024];
  print_trie(&trie.nodes[id], str, 0, 3);
}

int push_node(Node node) {
  if (trie.len >= trie.cap) {
    GROW_ARRAY(trie.nodes, trie.cap * 2, Node);
    trie.cap *= 2;
  }
  trie.nodes[trie.len] = node;
  return trie.len++;  // return the index of the last element
}

// END TREE
void end_trie() {
  // PS: save trees
  save_trie(&trie);
  free(trie.nodes);
}

// gives back an index i for any node
// TODO think of a suitable name for this function
int get_i(char c) {
  if ('a' <= c && c <= 'z') return c - 'a';
  if ('A' <= c && c <= 'Z') return 26 + c - 'a';
  if (c == '\'') return 26 + 26;

  return -1;
}
