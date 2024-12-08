use tsc::tf512::*;

#[unsafe(no_mangle)]
pub extern "C" fn TSC_Threefish512Static_rekey(
    ctx: *mut   Threefish512Static,
    key: *mut   u64,
    tweak: *mut u64)
{
    let k = unsafe {std::slice::from_raw_parts_mut(key, NUM_KEY_WORDS_WITH_PARITY)};
    let t = unsafe {std::slice::from_raw_parts_mut(tweak, NUM_TWEAK_WORDS_WITH_PARITY)};
    unsafe {&mut *ctx}.rekey(k, t);
}

#[unsafe(no_mangle)]
pub extern "C" fn TSC_Threefish512Static_encipher_1(
    ctx_p: *mut Threefish512Static,
    io_p:  *mut u64)
{
    let ctx = unsafe {&mut *ctx_p};
    let io  = unsafe {std::slice::from_raw_parts_mut(io_p, NUM_BLOCK_WORDS)};
    ctx.encipher_1(io);
}

#[unsafe(no_mangle)]
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

#[unsafe(no_mangle)]
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

#[unsafe(no_mangle)]
pub extern "C" fn TSC_Threefish512Dynamic_encipher_1(
    ctx_p: *mut Threefish512Dynamic,
    io_p:  *mut u64)
{
    let ctx = unsafe {&mut *ctx_p};
    let io  = unsafe {std::slice::from_raw_parts_mut(io_p, NUM_BLOCK_WORDS)};
    ctx.encipher_1(io);
}

#[unsafe(no_mangle)]
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
