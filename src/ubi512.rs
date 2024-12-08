use tsc::tf512::*;
use tsc::ubi512::*;

#[unsafe(no_mangle)]
pub extern "C" fn TSC_UBI512_chainConfig(
    ctx_p: *mut Ubi512,
    num_output_bits: u64)
{
    let ctx = unsafe {&mut *ctx_p};
    ctx.chain_config(num_output_bits);
}

#[unsafe(no_mangle)]
pub extern "C" fn TSC_UBI512_chainMessage(
    ctx_p: *mut Ubi512,
    input_p: *const u8,
    input_size: u64)
{
    let ctx = unsafe {&mut *ctx_p};
    let input = unsafe {
        std::slice::from_raw_parts(input_p, input_size as usize)
    };
    ctx.chain_message(input);
}

#[unsafe(no_mangle)]
pub extern "C" fn TSC_UBI512_chainOutput(
    ctx_p: *mut Ubi512,
    output_p: *mut u8,
    output_size: u64)
{
    let ctx = unsafe {&mut *ctx_p};
    let output = unsafe {
        std::slice::from_raw_parts_mut(output_p, output_size as usize)
    };
    ctx.chain_output(output);
}

#[unsafe(no_mangle)]
pub extern "C" fn TSC_UBI512_chainOutputNative(
    ctx_p: *mut Ubi512,
    output_p: *mut u8)
{
    let ctx = unsafe {&mut *ctx_p};
    let output = unsafe {
        std::slice::from_raw_parts_mut(output_p, NUM_BLOCK_BYTES)
    };
    ctx.chain_output_native(output);
}

#[unsafe(no_mangle)]
pub extern "C" fn TSC_UBI512_chainKey(
    ctx_p: *mut Ubi512,
    input_key_p: *const u8)
{
    let ctx = unsafe {&mut *ctx_p};
    let input_key = unsafe {
        std::slice::from_raw_parts(input_key_p, NUM_BLOCK_BYTES)
    };
    ctx.chain_key_u8(input_key);
}
