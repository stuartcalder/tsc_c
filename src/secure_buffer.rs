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

use rssc::c::*;
use tsc::secure_buffer::*;

#[no_mangle]
pub extern "C" fn TSC_SecureBuffer_init(
    ctx_p: *mut SecureBuffer,
    requested_size: usize) -> Error
{
    let ctx = unsafe {&mut *ctx_p};
    match SecureBuffer::new_in_place(ctx, requested_size) {
        Ok(_)  => 0,
        Err(_) => -1,
    }
}

#[no_mangle]
pub extern "C" fn TSC_SecureBuffer_del(ctx_p: *mut SecureBuffer)
{
    unsafe {std::ptr::drop_in_place(ctx_p)};
}

#[no_mangle]
pub extern "C" fn TSC_SecureBuffer_isInitialized(ctx_p: *const SecureBuffer) -> bool
{
    let ctx = unsafe {& *ctx_p};
    ctx.is_initialized()
}

#[no_mangle]
pub extern "C" fn TSC_SecureBuffer_getPtr(ctx_p: *mut SecureBuffer) -> *mut u8
{
    let ctx = unsafe {&mut *ctx_p};
    match ctx.get_raw_ptr() {
        Ok(p)  => p,
        Err(_) => std::ptr::null_mut(),
    }
}

#[no_mangle]
pub extern "C" fn TSC_SecureBuffer_getSize(ctx_p: *const SecureBuffer) -> usize
{
    let ctx = unsafe {& *ctx_p};
    match ctx.get_size() {
        Ok(size) => size,
        Err(_)   => 0usize
    }
}

#[no_mangle]
pub extern "C" fn TSC_SecureBuffer_resize(
    ctx_p: *mut SecureBuffer,
    requested_size: usize) -> Error
{
    let ctx = unsafe {& *ctx_p};
    match ctx.resize(requested_size) {
        Ok(_)  =>  0,
        Err(_) => -1
    }
}
