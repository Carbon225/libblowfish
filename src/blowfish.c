#include <blowfish.h>
#include <blowfish/boxes.h>

#include <stdint.h>
#include <string.h>

static uint32_t f(uint32_t x, const s_box_t s)
{
    uint32_t d =  x & 0x000000ff;
    uint32_t c = (x & 0x0000ff00) >> 8;
    uint32_t b = (x & 0x00ff0000) >> 16;
    uint32_t a = (x & 0xff000000) >> 24;

    uint32_t s_a = s[0][a];
    uint32_t s_b = s[1][b];
    uint32_t s_c = s[2][c];
    uint32_t s_d = s[3][d];

    return ((s_a + s_b) ^ s_c) + s_d;
}

static void feistel(uint32_t *x_l, uint32_t *x_r, const p_array_t p, const s_box_t s)
{
    for (int i = 0; i < PARRAY_LEN - 2; ++i)
    {
        *x_l ^= p[i];
        *x_r ^= f(*x_l, s);

        uint32_t tmp = *x_l;
        *x_l = *x_r;
        *x_r = tmp;
    }

    uint32_t tmp = *x_l;
    *x_l = *x_r;
    *x_r = tmp;

    *x_r ^= p[PARRAY_LEN - 2];
    *x_l ^= p[PARRAY_LEN - 1];
}

static void feistel_rev(uint32_t *x_l, uint32_t *x_r, const p_array_t p, const s_box_t s)
{
    for (int i = PARRAY_LEN - 1; i >= 2; --i)
    {
        *x_l ^= p[i];
        *x_r ^= f(*x_l, s);

        uint32_t tmp = *x_l;
        *x_l = *x_r;
        *x_r = tmp;
    }

    uint32_t tmp = *x_l;
    *x_l = *x_r;
    *x_r = tmp;

    *x_r ^= p[1];
    *x_l ^= p[0];
}

void generate_keys(const uint32_t key[], int key_len, p_array_t p, s_box_t s)
{
    memcpy(p, P_ARRAY, sizeof P_ARRAY);
    memcpy(s, S_BOX, sizeof S_BOX);

    for (int i = 0; i < PARRAY_LEN; ++i)
        p[i] ^= key[i % key_len];

    uint32_t x_l = 0;
    uint32_t x_r = 0;

    for (int i = 0; i < PARRAY_LEN - 1; i += 2)
    {
        feistel(&x_l, &x_r, p, s);
        p[i] = x_l;
        p[i + 1] = x_r;
    }

    for (int i = 0; i < SBOX_COUNT; ++i)
    {
        for (int j = 0; j < SBOX_SIZE - 1; j += 2)
        {
            feistel(&x_l, &x_r, p, s);
            s[i][j] = x_l;
            s[i][j + 1] = x_r;
        }
    }
}

void encrypt64(void *block, const p_array_t p, const s_box_t s)
{
    uint32_t *x_r = (uint32_t*) block;
    uint32_t *x_l = x_r + 1;

    feistel(x_l, x_r, p, s);
}

void decrypt64(void *block, const p_array_t p, const s_box_t s)
{
    uint32_t *x_r = (uint32_t*) block;
    uint32_t *x_l = x_r + 1;

    feistel_rev(x_l, x_r, p, s);
}
