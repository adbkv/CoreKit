#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#ifndef SIG_VECTOR_H
#define SIG_VECTOR_H

typedef struct {
  void **entries;
  size_t capacity, len;
} ck_vec;

ck_vec *vec_new() {
  ck_vec *nvec = malloc(sizeof(ck_vec));
  assert(nvec && "ck_vec malloc failed");
  nvec->entries = NULL;
  nvec->capacity = 0;
  nvec->len = 0;
  return nvec;
}

void vec_push(ck_vec *dest, void *val) {
  if (dest->len >= dest->capacity) {
    dest->capacity = (!dest->capacity) ? 4 : dest->capacity*2;
    dest->entries = realloc(dest->entries, sizeof(void *)*dest->capacity);
    if (!dest->entries) exit(1);
  }

  dest->entries[dest->len] = val;
  dest->len++;
}

void *vec_get(ck_vec *src) {
  assert(src->len && "empty ck_vec");
  return src->entries[src->len-1];
}

void vec_free(ck_vec *src) {
  free(src->entries);
  free(src);
}

#endif
