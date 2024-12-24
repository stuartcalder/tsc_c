use tsc::tf512::*;
use tsc::ubi512::*;
use tsc::skein512::*;

#[no_mangle]
pub extern "C" fn TSC_Skein512_hash(
    ctx_p: *mut Skein512,
    output_p: *mut u8,
    output_size: usize,
    input_p:  *const u8,
    input_size:  usize)
{
    let ctx = unsafe {&mut *ctx_p};
    let output = unsafe {
        std::slice::from_raw_parts_mut(output_p, output_size)
    };
    let input = unsafe {
        std::slice::from_raw_parts(input_p, input_size)
    };
    ctx.hash(output, input);
}

#[no_mangle]
pub extern "C" fn TSC_Skein512_hashNative(
    ctx_p: *mut Skein512,
    output_p: *mut u8,
    input_p:  *const u8,
    input_size: usize)
{
    let ctx = unsafe {&mut *ctx_p};
    let output = unsafe {
        std::slice::from_raw_parts_mut(output_p, NUM_HASH_BYTES)
    };
    let input = unsafe {
        std::slice::from_raw_parts(input_p, input_size)
    };
    ctx.hash_native(output, input);
}

#[no_mangle]
pub extern "C" fn TSC_Skein512_mac(
    ctx_p: *mut Skein512,
    output_p: *mut u8,
    output_size: usize,
    input_p: *const u8,
    input_size: usize,
    key_p: *const u64)
{
    let ctx = unsafe {&mut *ctx_p};
    let output = unsafe {
        std::slice::from_raw_parts_mut(output_p, output_size)
    };
    let input = unsafe {
        std::slice::from_raw_parts(input_p, input_size)
    };
    let key = unsafe {
        std::slice::from_raw_parts(key_p, NUM_KEY_WORDS)
    };
    ctx.mac(output, input, key);
}
