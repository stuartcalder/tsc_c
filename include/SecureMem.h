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

#ifndef TSC_SECUREMEM_H
#define TSC_SECUREMEM_H

#include "Macro.h"
#include <SSC/MemMap.h>

#define R_ SSC_RESTRICT
SSC_BEGIN_C_DECLS

#define TSC_SECUREMEM_TAG_MAP UINT8_C(1)
#define TSC_SECUREMEM_TAG_ALT UINT8_C(2)

typedef struct {
  uint8_t* ptr;
  size_t   size;
} TSC_SecureMemAlternate;
#define TSC_SECUREMEMALTERNATE_NULL_LITERAL SSC_STRUCT_LITERAL(TSC_SecureMemAlternate, 0)

typedef union {
  SSC_MemMap             mem_map;
  TSC_SecureMemAlternate mem_alt;
} TSC_SecureMemUnion;

typedef struct {
  TSC_SecureMemUnion mem_union;
  uint8_t            tag;
} TSC_SecureMem;
#define TSC_SECUREMEM_NULL_LITERAL SSC_STRUCT_LITERAL(TSC_SecureMem, 0)

TSC_API SSC_Error_t
TSC_SecureMem_init(
  TSC_SecureMem* ctx,
  size_t         requested_size);//TODO

TSC_API void
TSC_SecureMem_del(TSC_SecureMem* ctx);//TODO

TSC_API bool
TSC_SecureMem_isInitialized(TSC_SecureMem* ctx);//TODO

TSC_API uint8_t*
TSC_SecureMem_getPtr(TSC_SecureMem* ctx);//TODO

TSC_API size_t
TSC_SecureMem_getSize(const TSC_SecureMem* ctx);//TODO

TSC_API SSC_Error_t
TSC_SecureMem_resize(
  TSC_SecureMem* ctx,
  size_t         requested_size);//TODO


SSC_END_C_DECLS
#undef R_
#endif
