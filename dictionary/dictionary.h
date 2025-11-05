#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifndef SIG_DICT_H
#define SIG_DICT_H

#ifndef arrlen
#define arrlen(src) sizeof(src) / sizeof(src[0])
#endif

struct entry_t {
  char *key;
  void *val;
};

typedef struct {
  struct entry_t *entries;
  size_t capacity, size;
} dict_t;

dict_t *dict_new() {
  dict_t *dict = malloc(sizeof(dict_t));
  dict->entries = NULL;
  dict->capacity = 0; dict->size = 0;
  if (!dict) exit(1);
  return dict;
}

void dict_push(dict_t *dest, char *key, void *val) { 
  if (dest->size >= dest->capacity) {
    dest->capacity = (!dest->capacity) ? 1 : dest->capacity*2;
    dest->entries = realloc(dest->entries, dest->capacity * sizeof(struct entry_t));
    if (!dest->entries) exit(1);
  }
  
  for (size_t i = 0; i < dest->size; i++) {
    if (!strcmp(dest->entries[i].key, key)) {
      dest->entries[i].val = val;
      return;
    }
  }

  dest->entries[dest->size].key = strdup(key);
  dest->entries[dest->size].val = val;
  dest->size++;
}

void *dict_get(dict_t *src, char *key) {
  for (size_t i = 0; i < src->size; i++) {
    if (!strcmp(src->entries[i].key, key)) return src->entries[i].val;
  }
  return NULL;
}

void dict_free(dict_t *src) {
  for (size_t i = 0; i < src->size; i++) free(src->entries[i].key);

  free(src->entries);
  free(src);
}

#endif
