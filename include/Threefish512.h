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

#include "Macro.h"
#include <stdint.h>

#define R_ SSC_RESTRICT
SSC_BEGIN_C_DECLS

/* Block Cipher */
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
/* CTR Mode */
#define TSC_THREEFISH512CTR_IV_BYTES             32  /* Counter Mode initialization vector bytes, copied into the second half of the block. */
#define TSC_THREEFISH512CTR_IV_WORDS             4
/* OCB-T Mode */
#define TSC_THREEFISH512OCBT_FLAG_AD             UINT64_C(1)
#define TSC_THREEFISH512OCBT_FLAG_DATA           UINT64_C(2)
#define TSC_THREEFISH512OCBT_FLAG_PARTIAL        UINT64_C(4)
#define TSC_THREEFISH512OCBT_FLAG_TAG            UINT64_C(8)

#define TSC_THREEFISH512OCBT_TAG_WORDS            8
#define TSC_THREEFISH512OCBT_TAG_BYTES            64

#define TSC_THREEFISH512OCBT_ERROR_TAG_MISMATCH   INT32_C(1)
#define TSC_THREEFISH512OCBT_ERROR_INVALID_LENGTH INT32_C(2)

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

/* TSC_Threefish512Static computes the Key Schedule for Threefish-512 once,
 * and stores all its subkeys in the @key_schedule array. This is efficient
 * when repeatedly invoking the cipher with a single key, such as during
 * CTR mode encryption.
 */
typedef struct {
  uint64_t state        [TSC_THREEFISH512_BLOCK_WORDS];
  uint64_t key_schedule [TSC_THREEFISH512_KEYSCHEDULE_WORDS];
} TSC_Threefish512Static;
#define TSC_THREEFISH512STATIC_NULL_LITERAL \
 SSC_STRUCT_LITERAL(TSC_Threefish512Static, 0)

/* TSC_Threefish512Dynamic computes the Key Schedule for Threefish-512 on the fly,
 * and stores all the words of the @key and @tweak, including their respective parity words.
 * This is efficient when repeatedly re-keying the cipher, such as during Skein hashing.
 */
typedef struct {
  uint64_t state [TSC_THREEFISH512_BLOCK_WORDS];
  uint64_t key   [TSC_THREEFISH512_KEY_WORDS_WITH_PARITY];
  uint64_t tweak [TSC_THREEFISH512_TWEAK_WORDS_WITH_PARITY];
} TSC_Threefish512Dynamic;
#define TSC_THREEFISH512DYNAMIC_NULL_LITERAL \
 SSC_STRUCT_LITERAL(TSC_Threefish512Dynamic, 0)

/* TSC_Threefish512Ctr constructs a stream cipher by utilizing Threefish512 in Counter Mode (CTR Mode). */
typedef struct {
  TSC_Threefish512Static threefish512;
  uint64_t               keystream [TSC_THREEFISH512_BLOCK_WORDS];
  uint64_t               buffer    [TSC_THREEFISH512_BLOCK_WORDS];
} TSC_Threefish512Ctr;
#define TSC_THREEFISH512CTR_NULL_LITERAL \
 SSC_STRUCT_LITERAL(\
  TSC_Threefish512Ctr,\
  TSC_THREEFISH512STATIC_NULL_LITERAL,\
  {0},\
  {0}\
 )

typedef TSC_Threefish512Ctr TSC_Threefish512CtrStatic; //TODO: The underlying type will become the typedef.
#define TSC_THREEFISH512CTRSTATIC_NULL_LITERAL TSC_THREEFISH512CTR_NULL_LITERAL

typedef struct {
  TSC_Threefish512Dynamic threefish512;
  uint64_t                keystream [TSC_THREEFISH512_BLOCK_WORDS];
  uint64_t                buffer    [TSC_THREEFISH512_BLOCK_WORDS];
} TSC_Threefish512CtrDynamic;
#define TSC_THREEFISH512CTRDYNAMIC_NULL_LITERAL \
 SSC_STRUCT_LITERAL(TSC_Threefish512CtrDynamic, TSC_THREEFISH512DYNAMIC_NULL_LITERAL, {0}, {0})

typedef struct {
  uint64_t                nonce;
  uint64_t                block_counter;
  TSC_Threefish512Dynamic tf;
  uint64_t                ad_acc   [TSC_THREEFISH512_BLOCK_WORDS];
  uint64_t                data_acc [TSC_THREEFISH512_BLOCK_WORDS];
} TSC_Threefish512Ocbt;
#define TSC_THREEFISH512OCBT_NULL_LITERAL \
 SSC_STRUCT_LITERAL(\
  TSC_Threefish512Ocbt,\
  UINT64_C(0),\
  UINT64_C(0),\
  TSC_THREEFISH512DYNAMIC_NULL_LITERAL,\
  {0},\
  {0}\
 )

/* Static Procedures. */
TSC_API void
TSC_Threefish512Static_init(
  TSC_Threefish512Static* R_ ctx,
  uint64_t*               R_ key,
  uint64_t*               R_ tweak);

TSC_API void
TSC_Threefish512Static_encipher_1(
  TSC_Threefish512Static* R_ ctx,
  uint64_t*               R_ io);

TSC_API void
TSC_Threefish512Static_decipher_1(
  TSC_Threefish512Static* R_ ctx,
  uint64_t*               R_ io);


TSC_API void
TSC_Threefish512Static_encipher_2(
  TSC_Threefish512Static* R_ ctx,
  uint64_t*               R_ ciphertext,
  const uint64_t*         R_ plaintext);

TSC_API void
TSC_Threefish512Static_decipher_2(
  TSC_Threefish512Static* R_ ctx,
  uint64_t*               R_ plaintext,
  const uint64_t*         R_ ciphertext);

/* Dynamic Procedures. */
TSC_API void
TSC_Threefish512Dynamic_init(
  TSC_Threefish512Dynamic* R_ ctx,
  uint64_t*                R_ key,
  uint64_t*                R_ tweak);

TSC_API void
TSC_Threefish512Dynamic_computeParity(
  TSC_Threefish512Dynamic* R_ ctx);

TSC_API void
TSC_Threefish512Dynamic_setKey(
  TSC_Threefish512Dynamic* R_ ctx,
  uint64_t*                R_ key);

TSC_API void
TSC_Threefish512Dynamic_setTweak(
  TSC_Threefish512Dynamic* R_ ctx,
  uint64_t*                R_ tweak);

TSC_API void
TSC_Threefish512Dynamic_encipher_1(
  TSC_Threefish512Dynamic* R_ ctx,
  uint64_t*                R_ io);

TSC_API void
TSC_Threefish512Dynamic_decipher_1(
  TSC_Threefish512Dynamic* R_ ctx,
  uint64_t*                R_ io);

TSC_API void
TSC_Threefish512Dynamic_encipher_2(
  TSC_Threefish512Dynamic* R_ ctx,
  uint64_t*                R_ ciphertext,
  const uint64_t*          R_ plaintext);

TSC_API void
TSC_Threefish512Dynamic_decipher_2(
  TSC_Threefish512Dynamic* R_ ctx,
  uint64_t*                R_ plaintext,
  const uint64_t*          R_ ciphertext);

// Static Ctr Mode Procedures.
TSC_API void //TODO: REMOVE ME.
TSC_Threefish512Ctr_init(
  TSC_Threefish512Ctr* R_ ctx,
  uint64_t*            R_ key,
  uint64_t*            R_ tweak,
  const uint64_t*      R_ ctr_iv);
TSC_API void
TSC_Threefish512CtrStatic_init(
  TSC_Threefish512CtrStatic* R_ ctx,
  uint64_t*                  R_ key,
  uint64_t*                  R_ tweak,
  const uint64_t*            R_ ctr_iv);

TSC_API void //TODO: REMOVE ME.
TSC_Threefish512Ctr_xor_1(
  TSC_Threefish512Ctr* R_ ctx,
  uint8_t*             R_ io,
  size_t                  io_size,
  uint64_t                keystream_start);
TSC_API void
TSC_Threefish512CtrStatic_xor_1(
  TSC_Threefish512CtrStatic* R_ ctx,
  uint8_t*                   R_ io,
  size_t                        io_size,
  uint64_t                      keystream_start);

TSC_API void //TODO: REMOVE ME.
TSC_Threefish512Ctr_xor_2(
  TSC_Threefish512Ctr* R_ ctx,
  uint8_t*             R_ output,
  const uint8_t*       R_ input,
  size_t                  io_size,
  uint64_t                keystream_start);
TSC_API void
TSC_Threefish512CtrStatic_xor_2(
  TSC_Threefish512CtrStatic* R_ ctx,
  uint8_t*                   R_ output,
  const uint8_t*             R_ input,
  size_t                        io_size,
  uint64_t                      keystream_start);

// Dynamic Ctr Mode Procedures.
TSC_API  void
TSC_Threefish512CtrDynamic_init(
  TSC_Threefish512CtrDynamic* R_ ctx,
  uint64_t*                   R_ key,
  uint64_t*                   R_ tweak,
  const uint64_t*             R_ ctr_iv);

TSC_API void
TSC_Threefish512CtrDynamic_xor_1(
  TSC_Threefish512CtrDynamic* R_ ctx,
  uint8_t*                    R_ io,
  size_t                         io_size,
  uint64_t                       keystream_start);

TSC_API void
TSC_Threefish512CtrDynamic_xor_2(
  TSC_Threefish512CtrDynamic* R_ ctx,
  uint8_t*                    R_ output,
  const uint8_t*              R_ input,
  size_t                         io_size,
  uint64_t                       keystream_start);

// OCB-T Mode Procedures.

/* The seal() function encrypts a payload and/or authenticates additional data.
 * Returns 0 on success, or
 * TSC_THREEFISH512OCBT_ERROR_TAG_MISMATCH or
 * TSC_THREEFISH512OCBT_ERROR_INVALID_LENGTH.
 */
TSC_API int32_t
TSC_Threefish512Ocbt_seal(
  TSC_Threefish512Ocbt* R_ ctx,
  uint8_t*              R_ ciphertext_out, /* Where we're writing the ciphertext bytes.*/
  uint8_t*              R_ tag_out, /* Where we're writing the 512-bit authentication tag. */
  const uint64_t*       R_ key_in,  /* Where we're getting the 512-bit key. */
  uint64_t                 nonce_in, /* The 62-bit nonce. */
  const uint8_t*        R_ additional_data_in, /* Additional data to authenticate. */
  size_t                   additional_data_size, /* The amount of additional data to authenticate. */
  const uint8_t*        R_ plaintext_in, /* Where we're getting the plaintext to encrypt. */
  size_t                   plaintext_size); /* How much plaintext we're going to encrypt. */

TSC_API int32_t
TSC_Threefish512Ocbt_open(
  TSC_Threefish512Ocbt* R_ ctx,
  uint8_t*              R_ plaintext_out,
  const uint64_t*       R_ key_in,
  uint64_t                 nonce_in,
  const uint8_t*        R_ additional_data_in,
  size_t                   additional_data_size,
  const uint8_t*        R_ ciphertext_in,
  size_t                   ciphertext_size,
  const uint8_t*        R_ tag_in);

SSC_END_C_DECLS
#undef R_

#endif
