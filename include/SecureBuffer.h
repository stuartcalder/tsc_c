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

#ifndef TSC_SECUREBUFFER_H
#define TSC_SECUREBUFFER_H

#include "Macro.h"
#include <SSC/MemMap.h>
#include <stdint.h>

#define R_ SSC_RESTRICT
SSC_BEGIN_C_DECLS

#define TSC_SECUREBUFFER_TAG_MAP UINT8_C(1)
#define TSC_SECUREBUFFER_TAG_ALT UINT8_C(2)

typedef struct {
  uint8_t* ptr;
  size_t   size;
} TSC_SecureBufferAlternate;
#define TSC_SECUREBUFFERALTERNATE_NULL_LITERAL SSC_STRUCT_LITERAL(TSC_SecureBufferAlternate, 0)

typedef union {
  SSC_MemMap                mem_map;
  TSC_SecureBufferAlternate mem_alt;
} TSC_SecureBufferUnion;

typedef struct {
  TSC_SecureBufferUnion mem_union;
  uint8_t               tag;
} TSC_SecureBuffer;
#define TSC_SECUREBUFFER_NULL_LITERAL SSC_STRUCT_LITERAL(TSC_SecureBuffer, 0)

TSC_API SSC_Error_t
TSC_SecureBuffer_init(
  TSC_SecureBuffer* ctx,
  size_t            requested_size);

TSC_API void
TSC_SecureBuffer_del(TSC_SecureBuffer* ctx);

TSC_API bool
TSC_SecureBuffer_isInitialized(TSC_SecureBuffer* ctx);

TSC_API uint8_t*
TSC_SecureBuffer_getPtr(TSC_SecureBuffer* ctx);

TSC_API size_t
TSC_SecureBuffer_getSize(const TSC_SecureBuffer* ctx);

TSC_API SSC_Error_t
TSC_SecureBuffer_resize(
  TSC_SecureBuffer* ctx,
  size_t            requested_size);

SSC_END_C_DECLS
#undef R_
#endif
