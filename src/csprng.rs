use ssc::rand::*;
use tsc::tf512::*;
use tsc::ubi512::*;
use tsc::skein512::*;
use tsc::csprng::*;

#[no_mangle]
pub extern "C" fn TSC_CSPRNG_init(ctx_p: *mut Csprng)
{
    let ctx = unsafe {&mut *ctx_p};
    ctx.buffer.fill(0u8);
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
    bytes_p: *const u8)
{
    let ctx   = unsafe {&mut *ctx_p};
    let bytes = unsafe {
        std::slice::from_raw_parts(bytes_p, NUM_SEED_BYTES)
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
pub extern "C" fn TSC_CSPRNG_get(
    ctx_p: *mut Csprng,
    output_p: *mut u8,
    output_size: usize)
{
    let ctx = unsafe {&mut *ctx_p};
    let output = unsafe {
        std::slice::from_raw_parts_mut(output_p, output_size)
    };
    ctx.get_bytes(output);
}
