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
  const uint64_t* R_ key);

SSC_END_C_DECLS
#undef R_

#endif
