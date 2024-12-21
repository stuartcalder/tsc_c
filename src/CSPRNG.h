#ifndef TSC_CSPRNG_H
#define TSC_CSPRNG_H

#include <SSC/Macro.h>
#include "Skein512.h"

#define TSC_CSPRNG_SEED_BYTES   TSC_THREEFISH512_BLOCK_BYTES
#define TSC_CSPRNG_BUFFER_BYTES (TSC_CSPRNG_SEED_BYTES * 2)

#define R_ SSC_RESTRICT
SSC_BEGIN_C_DECLS

typedef struct {
  TSC_Skein512 skein512;
  uint8_t      buffer [TSC_CSPRNG_BUFFER_BYTES];
  uint8_t      seed   [TSC_CSPRNG_SEED_BYTES];
} TSC_CSPRNG;
#define TSC_CSPRNG_NULL_LITERAL SSC_COMPOUND_LITERAL(TSC_CSPRNG, 0)

SSC_IMPORT void
TSC_CSPRNG_init(TSC_CSPRNG* ctx);

SSC_IMPORT void
TSC_CSPRNG_reseedFromBytes(TSC_CSPRNG* R_ ctx, const uint8_t* R_ bytes);

SSC_IMPORT void
TSC_CSPRNG_reseedFromOS(TSC_CSPRNG* ctx);

SSC_IMPORT void
TSC_CSPRNG_get(TSC_CSPRNG* R_ ctx, uint8_t* R_ output, size_t output_size);


SSC_END_C_DECLS
#undef R_
#endif
