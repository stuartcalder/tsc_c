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
    let num_allocated_bytes = {1usize << {g_high + 6}};
    let v = vec![0u8; num_allocated_bytes];
    ctx.graph_memory = v.into_boxed_slice();
    ctx.g_high = g_high;
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
    let result = ctx.get(output, password, g_low, lambda, use_phi);
    match result {
        Ok(_)     => 0    as c_int,
        Err(code) => code as c_int,
    }
}
