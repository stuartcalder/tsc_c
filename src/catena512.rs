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

#![allow(unused_imports)]
use tsc::tf512::*;
use tsc::ubi512::*;
use tsc::ubi512::NUM_HASH_BYTES;
use tsc::skein512::*;
use tsc::catena512::*;

use cty::c_int;

#[no_mangle]
pub extern "C" fn TSC_Catena512_init(
    ctx_p: *mut Catena,
    g_high: u8)
{
    let ctx = unsafe {&mut *ctx_p};
    ctx.new_in_place(g_high);
}

#[no_mangle]
pub extern "C" fn TSC_Catena512_del(ctx_p: *mut Catena)
{
    unsafe {std::ptr::drop_in_place(ctx_p)};
}

#[no_mangle]
pub extern "C" fn TSC_Catena512_get(
    ctx_p: *mut Catena,
    output_p: *mut u8,
    password_p: *const u8,
    password_size: usize,
    g_low: u8,
    lambda: u8,
    use_phi: bool) -> c_int
{
    let ctx = unsafe {&mut *ctx_p};
    let output = unsafe {
        std::slice::from_raw_parts_mut(output_p, NUM_HASH_BYTES)
    };
    let password = unsafe {
        std::slice::from_raw_parts(password_p, password_size)
    };
    match ctx.get(output, password, g_low, lambda, use_phi) {
        Ok(_)     => 0    as c_int,
        Err(code) => code as c_int,
    }
}
