#ifndef _LIBBLOWFISH_BLOWFISH_H_
#define _LIBBLOWFISH_BLOWFISH_H_

#include <stdint.h>
#include <blowfish/boxes.h>

void generate_keys(const uint32_t key[], int key_len, p_array_t p, s_box_t s);

void encrypt64(void *block, const p_array_t p, const s_box_t s);

void decrypt64(void *block, const p_array_t p, const s_box_t s);

#endif
