use tsc::tf512::*;

#[no_mangle]
pub extern "C" fn TSC_Threefish512Static_rekey(
    ctx_p: *mut   Threefish512Static,
    key_p: *mut   u64,
    tweak_p: *mut u64)
{
    let ctx = unsafe {&mut *ctx_p};
    let key = unsafe {std::slice::from_raw_parts_mut(key_p, NUM_KEY_WORDS_WITH_PARITY)};
    let tweak = unsafe {std::slice::from_raw_parts_mut(tweak_p, NUM_TWEAK_WORDS_WITH_PARITY)};
    ctx.rekey(key, tweak);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Static_encipher_1(
    ctx_p: *mut Threefish512Static,
    io_p:  *mut u64)
{
    let ctx = unsafe {&mut *ctx_p};
    let io  = unsafe {std::slice::from_raw_parts_mut(io_p, NUM_BLOCK_WORDS)};
    ctx.encipher_1(io);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Static_encipher_2(
    ctx_p:        *mut Threefish512Static,
    ciphertext_p: *mut u64,
    plaintext_p:  *const u64)
{
    let ctx = unsafe {&mut *ctx_p};
    let ciphertext = unsafe {std::slice::from_raw_parts_mut(ciphertext_p, NUM_BLOCK_WORDS)};
    let plaintext  = unsafe {std::slice::from_raw_parts(plaintext_p, NUM_BLOCK_WORDS)};
    ctx.encipher_2(ciphertext, plaintext);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Dynamic_rekey(
    ctx_p:   *mut   Threefish512Dynamic,
    key_p:   *const u64,
    tweak_p: *const u64)
{
    let ctx   = unsafe {&mut *ctx_p};
    let key   = unsafe {std::slice::from_raw_parts(key_p, NUM_KEY_WORDS)};
    let tweak = unsafe {std::slice::from_raw_parts(tweak_p, NUM_TWEAK_WORDS)};
    ctx.key[..NUM_KEY_WORDS].copy_from_slice(key);
    ctx.tweak[..NUM_TWEAK_WORDS].copy_from_slice(tweak);
    ctx.rekey();
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Dynamic_encipher_1(
    ctx_p: *mut Threefish512Dynamic,
    io_p:  *mut u64)
{
    let ctx = unsafe {&mut *ctx_p};
    let io  = unsafe {std::slice::from_raw_parts_mut(io_p, NUM_BLOCK_WORDS)};
    ctx.encipher_1(io);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Dynamic_encipher_2(
    ctx_p:        *mut   Threefish512Dynamic,
    ciphertext_p: *mut   u64,
    plaintext_p:  *const u64)
{
    let ctx = unsafe {&mut *ctx_p};
    let ciphertext = unsafe {std::slice::from_raw_parts_mut(ciphertext_p, NUM_BLOCK_WORDS)};
    let plaintext  = unsafe {std::slice::from_raw_parts(plaintext_p, NUM_BLOCK_WORDS)};
    ctx.encipher_2(ciphertext, plaintext);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Ctr_init(
    ctx_p:    *mut   Threefish512Ctr,
    key_p:    *mut   u64,
    tweak_p:  *mut   u64,
    ctr_iv_p: *const u64)
{
    let ctx = unsafe {&mut *ctx_p};
    let key = unsafe {
        std::slice::from_raw_parts_mut(
            key_p,
            NUM_KEY_WORDS_WITH_PARITY
        )
    };
    let tweak = unsafe {
        std::slice::from_raw_parts_mut(
            tweak_p,
            NUM_TWEAK_WORDS_WITH_PARITY
        )
    };
    let ctr_iv = unsafe {
        std::slice::from_raw_parts(
            ctr_iv_p,
            NUM_CTR_IV_WORDS
        )
    };
    ctx.init(key, tweak, ctr_iv);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish12Ctr_xor_1(
    ctx_p: *mut Threefish512Ctr,
    io_p:  *mut u8,
    io_size: usize,
    keystream_start: u64)
{
    let ctx = unsafe {&mut *ctx_p};
    let io  = unsafe {std::slice::from_raw_parts_mut(io_p, io_size)};
    ctx.xor_1(io, keystream_start);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Ctr_xor_2(
    ctx_p: *mut Threefish512Ctr,
    output_p: *mut u8,
    input_p:  *const u8,
    io_size: usize,
    keystream_start: u64)
{
    let ctx = unsafe {&mut *ctx_p};
    let output = unsafe {std::slice::from_raw_parts_mut(output_p, io_size)};
    let input  = unsafe {std::slice::from_raw_parts(input_p, io_size)};
    ctx.xor_2(output, input, keystream_start);
}
