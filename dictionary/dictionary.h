#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef SIG_DICT_H
#define SIG_DICT_H

struct entry_t {
  char *key;
  void *val;
};

typedef struct {
  struct entry_t *entries;
  size_t capacity, size;
} ck_dict;

ck_dict *dict_new() {
  ck_dict *dict = malloc(sizeof(ck_dict));
  assert(dict && "ck_dict malloc failed");
  dict->entries = NULL;
  dict->capacity = 0; dict->size = 0;
  return dict;
}

void dict_push(ck_dict *dest, const char *key, const void *val) { 
  if (dest->size >= dest->capacity) {
    dest->capacity = (!dest->capacity) ? 1 : dest->capacity*2;
    dest->entries = realloc(dest->entries, dest->capacity * sizeof(struct entry_t));
    assert(dest->entries && "ck_dict realloc failed");
  }
  
  for (size_t i = 0; i < dest->size; i++) {
    if (!strcmp(dest->entries[i].key, key)) {
      dest->entries[i].val = val;
      return;
    }
  }

  dest->entries[dest->size].key = strdup(key);
  dest->entries[dest->size].val = val;
  assert(dest->entries[dest->size].key && "ck_dict strdup failed");
  dest->size++;
}

void *dict_get(const ck_dict *src, const char *key) {
  for (size_t i = 0; i < src->size; i++) {
    if (!strcmp(src->entries[i].key, key)) return src->entries[i].val;
  }
  return NULL;
}

void dict_free(ck_dict *src) {
  for (size_t i = 0; i < src->size; i++) free(src->entries[i].key);

  free(src->entries);
  free(src);
}

#endif
