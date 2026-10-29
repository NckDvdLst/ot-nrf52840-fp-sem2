#include "randombytes.h"

#include "mbedtls/ctr_drbg.h"
#include "mbedtls/entropy.h"

#include <stdint.h>
#include <string.h>

static mbedtls_ctr_drbg_context mlkem_drbg;
static mbedtls_entropy_context mlkem_entropy;
static int mlkem_drbg_inited = 0;

static void mlkem_randombytes_init(void) {
    if (mlkem_drbg_inited)
        return;

    mbedtls_entropy_init(&mlkem_entropy);
    mbedtls_ctr_drbg_init(&mlkem_drbg);

    const char *pers = "mlkem-drbg";
    int ret = mbedtls_ctr_drbg_seed(&mlkem_drbg, mbedtls_entropy_func,
        &mlkem_entropy, (const unsigned char *) pers, strlen(pers));

    if (ret == 0)
        mlkem_drbg_inited = 1;
}

int randombytes(uint8_t *out, size_t outlen) {
    mlkem_randombytes_init();
    return mbedtls_ctr_drbg_random(&mlkem_drbg, out, outlen);
}