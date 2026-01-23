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

#ifndef TSC_KDF_H
#define TSC_KDF_H

#include "Catena512.h"
#define TSC_KDF_OUTPUT_BYTES TSC_THREEFISH512_BLOCK_BYTES /* (64) */
#define TSC_KDF_SALT_BYTES   TSC_CATENA512_SALT_BYTES     /* (32) */

#define R_ SSC_RESTRICT
SSC_BEGIN_C_DECLS

TSC_API SSC_Error_t
TSC_kdf(
  uint8_t* R_       output, /* 64 byte buffer. */
  const uint8_t* R_ input_salt, /* 32 byte pseudorandom input salt. */
  const uint8_t* R_ input_password,
  size_t            input_password_len,
  uint64_t          thread_count,
  uint64_t          thread_batch_size,
  uint8_t           memory_low,
  uint8_t           memory_high,
  uint8_t           iterations,
  bool              use_phi);

SSC_END_C_DECLS
#undef R_

#endif // ~ TSC_KDF_H
