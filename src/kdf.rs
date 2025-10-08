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
use tsc::kdf::*;

#[no_mangle]
pub extern "C" fn TSC_kdf(
    output: *mut u8, // NUM_OUTPUT_BYTES
    input_salt: *const u8, // NUM_SALT_BYTES
    input_password: *const u8,
    input_password_len: usize,
    thread_count: u64,
    thread_batch_size: u64,
    memory_low: u8,
    memory_high: u8,
    iterations: u8,
    use_phi: bool
) -> cty::c_int
{
    let output = unsafe {
        std::slice::from_raw_parts_mut(output, NUM_OUTPUT_BYTES)
    };
    let input_salt = unsafe {
        std::slice::from_raw_parts(input_salt, NUM_SALT_BYTES)
    };
    let input_password = unsafe {
        std::slice::from_raw_parts(input_password, input_password_len)
    };
    let thread_count = if thread_count < 1 {
        1
    } else {
        thread_count
    };
    let thread_batch_size = if thread_batch_size > thread_count {
        thread_count
    } else {
        thread_batch_size 
    };
    let memory_low = if memory_low > memory_high {
        memory_high
    } else {
        memory_low
    };

    match tsc::kdf::multi_threaded(
        output.try_into().unwrap(),
        input_salt.try_into().unwrap(),
        input_password,
        thread_count,
        thread_batch_size,
        memory_low,
        memory_high,
        iterations,
        use_phi
    )
    {
        Ok(_)  =>  0,
        Err(_) => -1,
    }
}
