/* *
 * tsc_c - Provide a C API for the TSC library.
 * Copyright (C) 2025 Stuart Calder
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
TSC_CSPRNG_del(TSC_CSPRNG* ctx);

/* Read in 64 bytes from @bytes, and hash them into @seed for future
 * invocations of the CSPRNG.
 */
SSC_IMPORT void
TSC_CSPRNG_reseedFromBytes(TSC_CSPRNG* R_ ctx, const void* R_ bytes);

/* Read in 64 pseudorandom bytes from the Operating System, and hash them
 * into @seed for future invocations of the CSPRNG.
 */
SSC_IMPORT void
TSC_CSPRNG_reseedFromOS(TSC_CSPRNG* ctx);

/* Repeatedly hash @seed to obtain @output_size pseudorandom bytes and write
 * all those pseudorandom bytes to @output.
 */
SSC_IMPORT void
TSC_CSPRNG_getBytes(TSC_CSPRNG* R_ ctx, void* R_ output, size_t output_size);


SSC_END_C_DECLS
#undef R_
#endif
