#ifndef TSC_CATENA512_H
#define TSC_CATENA512_H

#include <SSC/Error.h>
#include <SSC/Macro.h>
#include <SSC/Operation.h>

#include "Skein512.h"

#define TSC_CATENA512_SALT_BITS          256
#define TSC_CATENA512_SALT_BYTES         32
#define TSC_CATENA512_MAX_PASSWORD_BYTES 125
#define TSC_CATENA512_TWEAK_BYTES        (TSC_THREEFISH512_BLOCK_BYTES + 1 + 1 + 2 + 2)
#define TSC_CATENA512_RNG_BYTES          TSC_THREEFISH512_BLOCK_BYTES
#define TSC_CATENA512_DOMAIN_PWSCRAMBLER UINT8_C(0)
#define TSC_CATENA512_DOMAIN_KDF         UINT8_C(1)
#define TSC_CATENA512_DOMAIN_POW         UINT8_C(2)
#define TSC_CATENA512_MHF_TEMP_BYTES     TSC_GRAPHHASH_TEMP_BYTES

#define R_    SSC_RESTRICT
SSC_BEGIN_C_DECLS

enum {
  TSC_CATENA512_SUCCESS = 0,
  TSC_CATENA512_ALLOC_FAILURE = -1
};

typedef struct {
  uint8_t word_buf [TSC_THREEFISH512_BLOCK_BYTES * 2];
  uint8_t rng      [TSC_CATENA512_RNG_BYTES];
} TSC_Catena512Gamma;

typedef union {
  TSC_Catena512Gamma gamma;
  uint8_t            tw_pw_salt [TSC_CATENA512_TWEAK_BYTES + TSC_CATENA512_MAX_PASSWORD_BYTES + TSC_CATENA512_SALT_BYTES];
  uint8_t            flap       [TSC_THREEFISH512_BLOCK_BYTES * 3];
  uint8_t            phi        [TSC_THREEFISH512_BLOCK_BYTES * 2];
  uint8_t            catena     [TSC_THREEFISH512_BLOCK_BYTES + 1];
  uint8_t            mhf        [TSC_CATENA512_MHF_TEMP_BYTES];
} TSC_Catena512Temp;

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/* TSC_Catena512 {}
 *     Memory-Hard password hashing. */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
typedef struct {
  TSC_Skein512      skein512;
  uint8_t*          graph_memory;
  uint8_t           x    [TSC_THREEFISH512_BLOCK_BYTES];
  TSC_Catena512Temp temp;
  uint8_t           salt [TSC_CATENA512_SALT_BYTES];
  uint8_t           g_high;
} TSC_Catena512;
#define TSC_CATENA512_NULL_LITERAL SSC_COMPOUND_LITERAL(TSC_Catena512, 0)

/*===============================================================================================================*/

/**
 * Allocate memory for Catena512. User is responsible for initializing
 * the fields of @ctx (except for @ctx->g_high and @ctx->graph_memory).
 */
SSC_IMPORT void
TSC_Catena512_init(TSC_Catena512* ctx, uint8_t g_high);

SSC_IMPORT void
TSC_Catena512_del(TSC_Catena512* ctx);

SSC_IMPORT SSC_Error_t
TSC_Catena512_get(
 TSC_Catena512* R_ ctx,
 uint8_t*       R_ output,
 const uint8_t* R_ password,
 size_t            password_size,
 uint8_t           g_low,
 uint8_t           lambda,
 bool              use_phi);

SSC_END_C_DECLS
#undef R_
#endif // ~ TSC_CATENA512_H
