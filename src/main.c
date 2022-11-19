#include "common.h"
#include "trie.h"

// so much TODO
int main() {
  init_trie();

  printf(
      "autocomplete by smv\n"
      "TODO lots\n"
      "press ctrl-C to quit\n");

  // for (;;) {
  printf("enter incomplete word: ");
  char word[1024];
  scanf("%s", word);
  printf("possible completions:\n");
  get_completion(word);
  // }

  end_trie();
  return 0;
}