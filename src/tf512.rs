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

use tsc::tf512::*;

#[no_mangle]
pub extern "C" fn TSC_Threefish512Static_init(
    ctx_p: *mut   Threefish512Static,
    key_p: *mut   u64,
    tweak_p: *mut u64)
{
    let ctx = unsafe {&mut *ctx_p};
    let key = unsafe {std::slice::from_raw_parts_mut(key_p, NUM_KEY_WORDS_WITH_PARITY)};
    let tweak = unsafe {std::slice::from_raw_parts_mut(tweak_p, NUM_TWEAK_WORDS_WITH_PARITY)};
    ctx.init(key, tweak);
}

macro_rules! encipher_1 {
    ($ctx_p:expr, $io_p:expr) => {{

        let ctx = unsafe {&mut *$ctx_p};
        let io  = unsafe {std::slice::from_raw_parts_mut($io_p, NUM_BLOCK_WORDS)};
        ctx.encipher_1(io);
    }}
}
macro_rules! decipher_1 {
    ($ctx_p:expr, $io_p:expr) => {{
        let ctx = unsafe {&mut *$ctx_p};
        let io  = unsafe {std::slice::from_raw_parts_mut($io_p, NUM_BLOCK_WORDS)};
        ctx.decipher_1(io);
    }}
}
macro_rules! encipher_2 {
    ($ctx_p:expr, $ciphertext_p:expr, $plaintext_p:expr) => {{
        let ctx = unsafe {&mut *$ctx_p};
        let ciphertext = unsafe {std::slice::from_raw_parts_mut($ciphertext_p, NUM_BLOCK_WORDS)};
        let plaintext  = unsafe {std::slice::from_raw_parts($plaintext_p, NUM_BLOCK_WORDS)};
        ctx.encipher_2(ciphertext, plaintext);
    }}
}
macro_rules! decipher_2 {
    ($ctx_p:expr, $plaintext_p:expr, $ciphertext_p:expr) => {{
        let ctx = unsafe {&mut *$ctx_p};
        let plaintext  = unsafe {std::slice::from_raw_parts_mut($plaintext_p, NUM_BLOCK_WORDS)};
        let ciphertext = unsafe {std::slice::from_raw_parts($ciphertext_p, NUM_BLOCK_WORDS)};
        ctx.decipher_2(plaintext, ciphertext);
    }}
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Static_encipher_1(
    ctx_p: *mut Threefish512Static,
    io_p:  *mut u64)
{
    encipher_1!(ctx_p, io_p);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Static_decipher_1(
    ctx_p: *mut Threefish512Static,
    io_p: *mut u64)
{
    decipher_1!(ctx_p, io_p);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Static_encipher_2(
    ctx_p:        *mut Threefish512Static,
    ciphertext_p: *mut u64,
    plaintext_p:  *const u64)
{
    encipher_2!(ctx_p, ciphertext_p, plaintext_p);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Static_decipher_2(
    ctx_p:        *mut Threefish512Static,
    plaintext_p:  *mut u64,
    ciphertext_p: *const u64)
{
    decipher_2!(ctx_p, plaintext_p, ciphertext_p);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Dynamic_init(
    ctx_p:   *mut   Threefish512Dynamic,
    key_p:   *const u64,
    tweak_p: *const u64)
{
    let ctx   = unsafe {&mut *ctx_p};
    let key   = unsafe {std::slice::from_raw_parts(key_p, NUM_KEY_WORDS)};
    let tweak = unsafe {std::slice::from_raw_parts(tweak_p, NUM_TWEAK_WORDS)};
    ctx.init(key, tweak);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Dynamic_computeParity(
    ctx_p: *mut Threefish512Dynamic)
{
    let ctx = unsafe {&mut *ctx_p};
    ctx.compute_parity();
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Dynamic_setKey(
    ctx_p: *mut Threefish512Dynamic,
    key_p: *const u64)
{
    let ctx = unsafe {&mut *ctx_p};
    let key = unsafe {std::slice::from_raw_parts(key_p, NUM_KEY_WORDS)};
    ctx.set_key(key);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Dynamic_setTweak(
    ctx_p: *mut Threefish512Dynamic,
    tweak_p: *const u64)
{
    let ctx   = unsafe {&mut *ctx_p};
    let tweak = unsafe {std::slice::from_raw_parts(tweak_p, NUM_TWEAK_WORDS)};
    ctx.set_tweak(tweak);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Dynamic_encipher_1(
    ctx_p: *mut Threefish512Dynamic,
    io_p:  *mut u64)
{
    encipher_1!(ctx_p, io_p);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Dynamic_decipher_1(
    ctx_p: *mut Threefish512Dynamic,
    io_p:  *mut u64)
{
    decipher_1!(ctx_p, io_p);
}


#[no_mangle]
pub extern "C" fn TSC_Threefish512Dynamic_encipher_2(
    ctx_p:        *mut   Threefish512Dynamic,
    ciphertext_p: *mut   u64,
    plaintext_p:  *const u64)
{
    encipher_2!(ctx_p, ciphertext_p, plaintext_p);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Dynamic_decipher_2(
    ctx_p:        *mut   Threefish512Dynamic,
    plaintext_p:  *mut   u64,
    ciphertext_p: *const u64)
{
    decipher_2!(ctx_p, plaintext_p, ciphertext_p);
}

macro_rules! ctr_init {
    ($ctx_p:expr, $key_p:expr, $tweak_p:expr, $ctr_iv_p:expr) => {{
        let ctx = unsafe {&mut *$ctx_p};
        let key = unsafe {
            std::slice::from_raw_parts_mut(
                $key_p,
                NUM_KEY_WORDS_WITH_PARITY
            )
        };
        let tweak = unsafe {
            std::slice::from_raw_parts_mut(
                $tweak_p,
                NUM_TWEAK_WORDS_WITH_PARITY
            )
        };
        let ctr_iv = unsafe {
            std::slice::from_raw_parts(
                $ctr_iv_p,
                NUM_CTR_IV_WORDS
            )
        };
        ctx.init(key, tweak, ctr_iv);
    }}
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Ctr_init(
    ctx_p:    *mut   Threefish512Ctr,
    key_p:    *mut   u64,
    tweak_p:  *mut   u64,
    ctr_iv_p: *const u64)
{
    ctr_init!(ctx_p, key_p, tweak_p, ctr_iv_p);
}
#[no_mangle]
pub extern "C" fn TSC_Threefish512CtrStatic_init(
    ctx_p: *mut Threefish512CtrStatic,
    key_p: *mut u64,
    tweak_p: *mut u64,
    ctr_iv_p: *const u64)
{
    TSC_Threefish512Ctr_init(ctx_p, key_p, tweak_p, ctr_iv_p);
}

macro_rules! xor_1 {
    ($ctx_p:expr, $io_p:expr, $io_size:expr, $keystream_start:expr) => {{
        let ctx = unsafe {&mut *$ctx_p};
        let io  = unsafe {std::slice::from_raw_parts_mut($io_p, $io_size)};
        ctx.xor_1(io, $keystream_start);
    }}
}
macro_rules! xor_2 {
    ($ctx_p:expr, $output_p:expr, $input_p:expr, $io_size:expr, $keystream_start:expr) => {{
        let ctx    = unsafe {&mut *$ctx_p};
        let output = unsafe {std::slice::from_raw_parts_mut($output_p, $io_size)};
        let input  = unsafe {std::slice::from_raw_parts($input_p, $io_size)};
        ctx.xor_2(output, input, $keystream_start);
    }}
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Ctr_xor_1(
    ctx_p: *mut Threefish512Ctr,
    io_p:  *mut u8,
    io_size: usize,
    keystream_start: u64)
{
    xor_1!(ctx_p, io_p, io_size, keystream_start);
}
#[no_mangle]
pub extern "C" fn TSC_Threefish512CtrStatic_xor_1(
    ctx_p: *mut Threefish512Ctr,
    io_p:  *mut u8,
    io_size: usize,
    keystream_start: u64)
{
    TSC_Threefish512Ctr_xor_1(ctx_p, io_p, io_size, keystream_start);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Ctr_xor_2(
    ctx_p: *mut Threefish512Ctr,
    output_p: *mut u8,
    input_p:  *const u8,
    io_size: usize,
    keystream_start: u64)
{
    xor_2!(ctx_p, output_p, input_p, io_size, keystream_start);
}
#[no_mangle]
pub extern "C" fn TSC_Threefish512CtrStatic_xor_2(
    ctx_p: *mut Threefish512Ctr,
    output_p: *mut u8,
    input_p:  *const u8,
    io_size: usize,
    keystream_start: u64)
{
    TSC_Threefish512Ctr_xor_2(ctx_p, output_p, input_p, io_size, keystream_start);
}

// <----------------- CTR Dyamic ----------------->

#[no_mangle]
pub extern "C" fn TSC_Threefish512CtrDynamic_init(
    ctx_p: *mut Threefish512CtrDynamic,
    key_p: *mut u64,
    tweak_p: *mut u64,
    ctr_iv_p: *const u64)
{
    ctr_init!(ctx_p, key_p, tweak_p, ctr_iv_p);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512CtrDynamic_xor_1(
    ctx_p: *mut Threefish512CtrDynamic,
    io_p:  *mut u8,
    io_size: usize,
    keystream_start: u64)
{
    xor_1!(ctx_p, io_p, io_size, keystream_start);
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512CtrDynamic_xor_2(
    ctx_p: *mut Threefish512CtrDynamic,
    output_p: *mut u8,
    input_p:  *const u8,
    io_size: usize,
    keystream_start: u64)
{
    xor_2!(ctx_p, output_p, input_p, io_size, keystream_start);
}

// <----------------- OCB-T ---------------------->
// At present OCB-T does not need to be initialized, since everything inside Threefish512Ocbt is by
// default zeroed, which can be handled from the C side with a NULL_LITERAL macro.

#[no_mangle]
pub extern "C" fn TSC_Threefish512Ocbt_seal(
    ctx_p:     *mut Threefish512Ocbt,
    ct_out_p:  *mut u8,
    tag_out_p: *mut u8,
    key_in_p:  *const u64,
    nonce_in:  u64,
    ad_in_p:   *const u8,
    ad_size:   usize,
    pt_in_p:   *const u8,
    pt_size:   usize,
) -> i32 {
    let ctx     = unsafe {&mut *ctx_p};
    let ct_out  = unsafe {std::slice::from_raw_parts_mut(ct_out_p, pt_size)};
    let tag_out_slice = unsafe {std::slice::from_raw_parts_mut(tag_out_p, OCBT_TAG_BYTES)};
    let tag_out = <&mut [u8; OCBT_TAG_BYTES]>::try_from(tag_out_slice).unwrap();
    let key_in_slice = unsafe {std::slice::from_raw_parts(key_in_p, NUM_KEY_WORDS)};
    let key_in = <&[u64; NUM_KEY_WORDS]>::try_from(key_in_slice).unwrap();
    let ad_in = unsafe {std::slice::from_raw_parts(ad_in_p, ad_size)};
    let pt_in = unsafe {std::slice::from_raw_parts(pt_in_p, pt_size)};

    let res = ctx.seal(
        ct_out,
        tag_out,
        key_in,
        nonce_in,
        ad_in,
        pt_in
    );
    match res {
        Ok(_) => {0i32},
        Err(OcbtError::TagMismatch)   => {1i32},
        Err(OcbtError::InvalidLength) => {2i32},
    }
}

#[no_mangle]
pub extern "C" fn TSC_Threefish512Ocbt_open(
    ctx_p:    *mut Threefish512Ocbt,
    pt_out_p: *mut u8,
    key_in_p: *const u64,
    nonce_in: u64,
    ad_in_p:  *const u8,
    ad_size:  usize,
    ct_in_p:  *const u8,
    ct_size:  usize,
    tag_in_p: *const u8,
) -> i32 {
    let ctx = unsafe {&mut *ctx_p};
    let pt_out = unsafe {std::slice::from_raw_parts_mut(pt_out_p, ct_size)};
    let key_in_slice = unsafe {std::slice::from_raw_parts(key_in_p, NUM_KEY_WORDS)};
    let key_in = <&[u64; NUM_KEY_WORDS]>::try_from(key_in_slice).unwrap();
    let ad_in = unsafe {std::slice::from_raw_parts(ad_in_p, ad_size)};
    let ct_in = unsafe {std::slice::from_raw_parts(ct_in_p, ct_size)};
    let tag_in_slice = unsafe {std::slice::from_raw_parts(tag_in_p, OCBT_TAG_BYTES)};
    let tag_in = <&[u8; OCBT_TAG_BYTES]>::try_from(tag_in_slice).unwrap();

    let res = ctx.open(
        pt_out,
        key_in,
        nonce_in,
        ad_in,
        ct_in,
        tag_in
    );
    match res {
        Ok(_) => {0i32},
        Err(OcbtError::TagMismatch)   => {1i32},
        Err(OcbtError::InvalidLength) => {2i32},
    }
}
