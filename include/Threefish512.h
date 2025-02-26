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

#ifndef TSC_THREEFISH512_H
#define TSC_THREEFISH512_H

#include <SSC/Macro.h>

#define R_ SSC_RESTRICT
SSC_BEGIN_C_DECLS

#define TSC_THREEFISH512_BLOCK_BITS              512 /* 512 bits per Threefish block. */
#define TSC_THREEFISH512_BLOCK_BYTES             64  /* 64  bytes per Threefish block. */
#define TSC_THREEFISH512_BLOCK_WORDS             8   /* 8 64-bit words per Threefish block. */
#define TSC_THREEFISH512_KEY_BITS                TSC_THREEFISH512_BLOCK_BITS  /* Same key bits as block bits. */
#define TSC_THREEFISH512_KEY_BYTES               TSC_THREEFISH512_BLOCK_BYTES /* Same key bytes as block bytes. */
#define TSC_THREEFISH512_KEY_WORDS               TSC_THREEFISH512_BLOCK_WORDS /* Same key words as block words. */
#define TSC_THREEFISH512_TWEAK_BITS              128 /* 128 bits per Threefish tweak. */
#define TSC_THREEFISH512_TWEAK_BYTES             16  /* 16 bytes per Threefish tweak. */
#define TSC_THREEFISH512_TWEAK_WORDS             2   /* 2 64-bit words per Threefish tweak. */
#define TSC_THREEFISH512_NUMBER_ROUNDS           72  /* 72 iterations of the round function per Threefish encrypt/decrypt. */
#define TSC_THREEFISH512_NUMBER_SUBKEYS          19  /* 19 subkeys constitute the Threefish keyschedule. */
#define TSC_THREEFISH512_KEY_WORDS_WITH_PARITY   9
#define TSC_THREEFISH512_TWEAK_WORDS_WITH_PARITY 3
#define TSC_THREEFISH512_KEYSCHEDULE_WORDS       (TSC_THREEFISH512_KEY_WORDS * TSC_THREEFISH512_NUMBER_SUBKEYS)
#define TSC_THREEFISH512CTR_IV_BYTES             32  /* Counter Mode initialization vector bytes, copied into the second half of the block. */
#define TSC_THREEFISH512CTR_IV_WORDS             4

/**
 * CONSTANT_240 gets XOR'd with the 8 bytes of the provided key. The key is described by the specification in the little
 * endian format. When this file gets pre-processed on a Big Endian sytem, swap the byte order of the CONST_240 constant
 * so the appropriate bits get XOR'd during the bitwise XOR operation.
 */
#if   SSC_ENDIAN == SSC_ENDIAN_LITTLE
 #define TSC_THREEFISH512_CONSTANT_240 UINT64_C(0x1bd11bdaa9fc1a22)
#elif SSC_ENDIAN == SSC_ENDIAN_BIG
 #define TSC_THREEFISH512_CONSTANT_240 UINT64_C(0x221afca9da1bd11b)
#else
 #error "Invalid endianness!"
#endif

typedef struct {
  uint64_t state        [TSC_THREEFISH512_BLOCK_WORDS];
  uint64_t key_schedule [TSC_THREEFISH512_KEYSCHEDULE_WORDS];
} TSC_Threefish512Static;
#define TSC_THREEFISH512STATIC_NULL_LITERAL \
 SSC_COMPOUND_LITERAL(TSC_Threefish512Static, 0)

typedef struct {
  uint64_t state [TSC_THREEFISH512_BLOCK_WORDS];
  uint64_t key   [TSC_THREEFISH512_KEY_WORDS_WITH_PARITY];
  uint64_t tweak [TSC_THREEFISH512_TWEAK_WORDS_WITH_PARITY];
} TSC_Threefish512Dynamic;
#define TSC_THREEFISH512DYNAMIC_NULL_LITERAL \
 SSC_COMPOUND_LITERAL(TSC_Threefish512Dynamic, 0)

typedef struct {
  TSC_Threefish512Static threefish512;
  uint64_t               keystream [TSC_THREEFISH512_BLOCK_WORDS];
  uint64_t               buffer    [TSC_THREEFISH512_BLOCK_WORDS];
} TSC_Threefish512Ctr;
#define TSC_THREEFISH512CTR_NULL_LITERAL \
 SSC_COMPOUND_LITERAL(TSC_Threefish512Ctr,\
  TSC_THREEFISH512STATIC_NULL_LITERAL,\
  {0},\
  {0})

// Static Procedures.
SSC_IMPORT void
TSC_Threefish512Static_rekey(
  TSC_Threefish512Static* R_ ctx,
  uint64_t*               R_ key,
  uint64_t*               R_ tweak);

SSC_IMPORT void
TSC_Threefish512Static_encipher_1(
  TSC_Threefish512Static* R_ ctx,
  uint64_t*               R_ io);

SSC_IMPORT void
TSC_Threefish512Static_encipher_2(
  TSC_Threefish512Static* R_ ctx,
  uint64_t*               R_ ciphertext,
  const uint64_t*         R_ plaintext);

// Dynamic Procedures.
SSC_IMPORT void
TSC_Threefish512Dynamic_rekey(
  TSC_Threefish512Dynamic* R_ ctx,
  uint64_t*                R_ key,
  uint64_t*                R_ tweak);

SSC_IMPORT void
TSC_Threefish512Dynamic_encipher_1(
  TSC_Threefish512Dynamic* R_ ctx,
  uint64_t*                R_ io);

SSC_IMPORT void
TSC_Threefish512Dynamic_encipher_2(
  TSC_Threefish512Dynamic* R_ ctx,
  uint64_t*                R_ ciphertext,
  const uint64_t*          R_ plaintext);

// Ctr Mode Procedures.
SSC_IMPORT void
TSC_Threefish512Ctr_init(
  TSC_Threefish512Ctr* R_ ctx,
  uint64_t*            R_ key,
  uint64_t*            R_ tweak,
  const uint64_t*      R_ ctr_iv);

SSC_IMPORT void
TSC_Threefish512Ctr_xor_1(
  TSC_Threefish512Ctr* R_ ctx,
  uint8_t*             R_ io,
  size_t                  io_size,
  uint64_t                keystream_start);

SSC_IMPORT void
TSC_Threefish512Ctr_xor_2(
  TSC_Threefish512Ctr* R_ ctx,
  uint8_t*             R_ output,
  const uint8_t*       R_ input,
  size_t                  io_size,
  uint64_t                keystream_start);

SSC_END_C_DECLS
#undef R_

#endif
