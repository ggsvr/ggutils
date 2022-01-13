#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

void *realloc(void *ptr, size_t size);
void free(void *ptr);

#define VEC_GEN(type, suffix)  \
\
struct vec_##suffix { \
    type *data; \
    size_t len; \
    size_t capacity; \
}; \
\
struct vec_##suffix vec_new_##suffix(); \
void vec_free_##suffix(struct vec_##suffix *v); \
void vec_push_##suffix(struct vec_##suffix *v, type elem); \
type vec_pop_##suffix(struct vec_##suffix *v); \
void vec_swap_##suffix(struct vec_##suffix *v, size_t x, size_t y); \
void vec_insert_##suffix(struct vec_##suffix *v, size_t index, type elem); \
\
static inline size_t vec_len_##suffix(struct vec_##suffix *v) { \
    return v->len; \
} \
static inline bool vec_is_empty_##suffix(struct vec_##suffix *v) { \
    return v->len == 0; \
} \
static inline type *vec_get_##suffix(struct vec_##suffix *v, size_t index) { \
    assert(index < v->len); \
    return v->data + index; \
} \



#define VEC_GEN_IMPL(type, suffix) \
VEC_GEN(type, suffix) \
\
static void __attribute((unused)) realloc_capacity_##suffix(struct vec_##suffix *v, size_t new_capacity) { \
    /* if new capacity is less or equal than old capacity, do nothing */ \
    if (new_capacity <= v->capacity) return; \
    /* reallocate capacity, multiplying by element size */ \
    v->data = realloc(v->data, sizeof(type) * new_capacity); \
    v->capacity = new_capacity; \
} \
\
static void inc_len_##suffix(struct vec_##suffix *v) { \
    size_t cap = v->capacity; \
    if (v->len == cap) { \
        cap = cap ? cap * 2 : 4; \
        realloc_capacity_##suffix(v, cap); \
    } \
    v->len += 1; \
} \
\
struct vec_##suffix vec_new_##suffix() { \
    struct vec_##suffix v = { \
        .data = NULL, \
        .len = 0, \
        .capacity = 0 \
    }; \
    return v; \
} \
\
void vec_free_##suffix(struct vec_##suffix *v) { \
    free(v->data); \
    memset(v, 0, sizeof(*v)); \
} \
\
void vec_push_##suffix(struct vec_##suffix *v, type elem) { \
    inc_len_##suffix(v); \
    v->data[v->len-1] = elem; \
} \
\
type vec_pop_##suffix(struct vec_##suffix *v) { \
    assert(v->len != 0); \
    v->len -= 1; \
    return v->data[v->len]; \
} \
\
void vec_swap_##suffix(struct vec_##suffix *v, size_t x, size_t y) { \
    type *px = vec_get_##suffix(v, x); \
    type *py = vec_get_##suffix(v, y); \
    type tmp = *px; \
    *px = *py; \
    *py = tmp; \
} \
\
void vec_insert_##suffix(struct vec_##suffix *v, size_t index, type elem) { \
    if (index >= v->len) { \
        vec_push_##suffix(v, elem); \
        return; \
    } \
    \
    inc_len_##suffix(v); \
    for (size_t i = index; i < v->len; ++i) { \
        *vec_get_##suffix(v, i+1) = *vec_get_##suffix(v, i); \
    } \
    *vec_get_##suffix(v, index) = elem; \
}
