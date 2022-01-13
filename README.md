# GGutils

### C utilities that make you say "gg"

This utilities will probably grow over time.

## **WARNING: don't use this in production. I'm not a good programmer.**

### List of utilities

- Generic Vector


## Utilities details


### Generic Vector

The header file `vec.h` provides two macros: `VEC_GEN(type, suffix)` and `VEC_GEN_IMPL(type, suffix)`.

- `VEC_GEN` generates the struct and function prototypes that work on `type`, and adds `suffix` to their names
- `VEC_GEN_IMPL` generates the respective function implementations

Example:

- `vec.c`:
        #include "vec.h"
        VEC_GEN_IMPL(int, myint)

- `main.c`:
        #include "vec.h"
        VEC_GEN(int, myint)

        int main(void) {

            struct vec_myint v = vec_new_myint();
            vec_push_myint(&v, 10);
            vec_push_myint(&v, 20);
            vec_push_myint(&v, 30);

            int out = vec_pop_myint(&v);

            return 0;
        }