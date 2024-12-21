#ifndef TSC_SKEIN512_H
#define TSC_SKEIN512_H

#include <SSC/Macro.h>
#include "Ubi512.h"

#define R_ SSC_RESTRICT
SSC_BEGIN_C_DECLS

typedef TSC_UBI512 TSC_Skein512;

SSC_IMPORT void
TSC_Skein512_hash(
  TSC_Skein512*  R_ ctx,
  uint8_t*       R_ output,
  size_t            output_size,
  const uint8_t* R_ input,
  size_t            input_size);

SSC_IMPORT void
TSC_Skein512_hashNative(
  TSC_Skein512*  R_ ctx,
  uint8_t*       R_ output,
  const uint8_t* R_ input,
  size_t            input_size);

SSC_IMPORT void
TSC_Skein512_mac(
  TSC_Skein512*   R_ ctx,
  uint8_t*        R_ output,
  size_t             output_size,
  const uint8_t*  R_ input,
  size_t             input_size,
  const uint64_t* R_ key)

SSC_END_C_DECLS
#undef R_

#endif
