#include "common.h"

// for read_file
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "trie.h"

void *grow_array(void *arr, int size) {
  void *newArr = realloc(arr, size);
  if (newArr == NULL) {
    free(newArr);
    printf("allocation error (exiting)\n");
    exit(0);
  }
  return newArr;
}

void save_trie(Trie *trie) {
  FILE *file = fopen(".data/progress", "w+");
  fwrite(trie, sizeof(Trie), 1, file);
  fwrite(&trie->nodes, sizeof(Node), trie->len, file);
  fclose(file);
}

bool load_trie(Trie *trie) {
  FILE *file = fopen(".data/progress", "r+");
  if (!file) return false;

  fread(trie, sizeof(Trie), 1, file);

  trie->nodes = malloc(trie->cap * sizeof(Node));
  fread(trie->nodes, sizeof(Node), trie->len, file);

  fclose(file);
  return true;
}

char *read_file(char *file_name) {
  char *command;

  int f = open(file_name, O_RDONLY);
  if (f == -1) return NULL;

  struct stat sb;
  if (fstat(f, &sb) == -1) return NULL;

  command = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, f, 0);
  if (command == MAP_FAILED) return NULL;

  return command;
}

void slice_str(char *dest, const char *text, int start, const int len) {
  strncpy(dest, &text[start], len);
  dest[len] = '\0';
}