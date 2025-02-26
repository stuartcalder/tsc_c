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

#ifndef TSC_UBI512_H
#define TSC_UBI512_H

#include <stddef.h>
#include "Threefish512.h"

#define TSC_UBI512_TWEAK_FIRST_BIT  UINT8_C(0x40)
#define TSC_UBI512_TWEAK_FIRST_MASK UINT8_C(0xBF)
#define TSC_UBI512_TWEAK_LAST_BIT   UINT8_C(0x80)
#define TSC_UBI512_TYPEMASK_KEY     UINT8_C(0)  /* Key. */
#define TSC_UBI512_TYPEMASK_CFG     UINT8_C(4)  /* Configuration. */
#define TSC_UBI512_TYPEMASK_PRS     UINT8_C(8)  /* Personalization. */
#define TSC_UBI512_TYPEMASK_PK      UINT8_C(12) /* Public-Key. */
#define TSC_UBI512_TYPEMASK_KDF     UINT8_C(16) /* Key-Derivation-Function. */
#define TSC_UBI512_TYPEMASK_NON     UINT8_C(20) /* Nonce. */
#define TSC_UBI512_TYPEMASK_MSG     UINT8_C(48) /* Message. */
#define TSC_UBI512_TYPEMASK_OUT     UINT8_C(63) /* Output. */

#define R_ SSC_RESTRICT
SSC_BEGIN_C_DECLS

#if defined(TSC_USE_PPQ)
#include <PPQ/Ubi512.h>
typedef PPQ_UBI512 TSC_UBI512;
#define TSC_UBI512_NULL_LITERAL PPQ_UBI512_NULL_LITERAL

#else /* (Don't use PPQ) */
typedef struct {
  TSC_Threefish512Dynamic threefish512;
  uint8_t	                msg [TSC_THREEFISH512_BLOCK_BYTES];
} TSC_UBI512;
#define TSC_UBI512_NULL_LITERAL SSC_COMPOUND_LITERAL(TSC_UBI512, 0)
#endif

SSC_IMPORT void
TSC_UBI512_chainConfig(
 TSC_UBI512* const R_ ctx,
 const uint64_t       num_output_bits);

SSC_IMPORT void
TSC_UBI512_chainMessage(
 TSC_UBI512* const R_ ctx,
 const uint8_t* R_    input,       /* Where to read input from. */
 uint64_t             input_size); /* How many bytes to read. */

SSC_IMPORT void
TSC_UBI512_chainOutput(
 TSC_UBI512* const R_ ctx,
 uint8_t* R_          output,       /* Where to write the output. */
 uint64_t             output_size); /* How many bytes to output. */
SSC_IMPORT void
TSC_UBI512_chainOutputNative(
 TSC_UBI512* const R_ ctx,
 uint8_t* R_          output); /* Where to write 64 bytes of hash output. */

SSC_IMPORT void
TSC_UBI512_chainKey(
 TSC_UBI512* const R_ ctx,
 const uint8_t* R_    input_key);

SSC_END_C_DECLS
#undef R_

#endif // ~ TSC_UBI512_MODE_H
