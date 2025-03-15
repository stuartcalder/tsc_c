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
use rssc::rand::*;
use tsc::tf512::*;
use tsc::ubi512::*;
use tsc::skein512::*;
use tsc::csprng::*;

#[no_mangle]
pub extern "C" fn TSC_CSPRNG_init(ctx_p: *mut Csprng)
{
    let ctx = unsafe {&mut *ctx_p};
    get_entropy(&mut ctx.seed);
}

#[no_mangle]
pub extern "C" fn TSC_CSPRNG_del(ctx_p: *mut Csprng)
{
    unsafe {std::ptr::drop_in_place(ctx_p)};
}

#[no_mangle]
pub extern "C" fn TSC_CSPRNG_reseedFromBytes(
    ctx_p: *mut Csprng,
    bytes_p: *const cty::c_void)
{
    let ctx   = unsafe {&mut *ctx_p};
    let bytes = unsafe {
        std::slice::from_raw_parts(bytes_p as *const _ as *const u8, NUM_SEED_BYTES)
    };
    ctx.reseed_from_bytes(bytes);
}

#[no_mangle]
pub extern "C" fn TSC_CSPRNG_reseedFromOS(ctx_p: *mut Csprng)
{
    let ctx = unsafe {&mut *ctx_p};
    ctx.reseed_from_os();
}

#[no_mangle]
pub extern "C" fn TSC_CSPRNG_getBytes(
    ctx_p: *mut Csprng,
    output_p: *mut cty::c_void,
    output_size: usize)
{
    let ctx = unsafe {&mut *ctx_p};
    let output = unsafe {
        std::slice::from_raw_parts_mut(output_p as *mut _ as *mut u8, output_size)
    };
    ctx.get_bytes(output);
}

#[no_mangle]
pub extern "C" fn TSC_CSPRNG_getRandomNaturalNumber(ctx_p: *mut Csprng, max: u64) -> u64
{
    let ctx = unsafe {&mut *ctx_p};
    ctx.get_random_natural_num(max)
}

#[no_mangle]
pub extern "C" fn TSC_CSPRNG_getRandomU64InRange(ctx_p: *mut Csprng, min: u64, max: u64) -> u64
{
    let ctx = unsafe {&mut *ctx_p};
    ctx.get_random_u64_in_range((min, max))
}
