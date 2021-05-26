#ifndef _LIBBLOWFISH_BOXES_H_
#define _LIBBLOWFISH_BOXES_H_

#include <stdint.h>

#define SBOX_COUNT (4)
#define SBOX_SIZE (256)
#define PARRAY_LEN (18)

typedef uint32_t s_box_t[SBOX_COUNT][SBOX_SIZE];
typedef uint32_t p_array_t[PARRAY_LEN];

extern const s_box_t S_BOX;
extern const p_array_t P_ARRAY;

#endif
