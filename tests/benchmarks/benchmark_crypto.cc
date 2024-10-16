/*!
 * \file benchmark_crypto.cc
 * \brief Benchmarks for cryptographic functions
 * \author Carles Fernandez-Prades, 2024. cfernandez(at)cttc.es
 *
 *
 * -----------------------------------------------------------------------------
 *
 * GNSS-SDR is a Global Navigation Satellite System software-defined receiver.
 * This file is part of GNSS-SDR.
 *
 * Copyright (C) 2024  (see AUTHORS file for a list of contributors)
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * -----------------------------------------------------------------------------
 */

#include "gnss_crypto.h"
#include <benchmark/benchmark.h>
#include <memory>

void bm_SHA_256(benchmark::State& state)
{
    auto d_crypto = std::make_unique<Gnss_Crypto>();

    std::vector<uint8_t> message{
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x0A};

    while (state.KeepRunning())
        {
            std::vector<uint8_t> output = d_crypto->compute_SHA_256(message);
        }
}


void bm_SHA3_256(benchmark::State& state)
{
    auto d_crypto = std::make_unique<Gnss_Crypto>();

    std::vector<uint8_t> message{
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x0A};

    while (state.KeepRunning())
        {
            std::vector<uint8_t> output = d_crypto->compute_SHA3_256(message);
        }
}


void bm_HMAC_SHA_256(benchmark::State& state)
{
    auto d_crypto = std::make_unique<Gnss_Crypto>();

    std::vector<uint8_t> key = {
        0x24, 0x24, 0x3B, 0x76, 0xF9, 0x14, 0xB1, 0xA7,
        0x7D, 0x48, 0xE7, 0xF1, 0x48, 0x0C, 0xC2, 0x98,
        0xEB, 0x62, 0x3E, 0x95, 0x6B, 0x2B, 0xCE, 0xA3,
        0xB4, 0xD4, 0xDB, 0x31, 0xEE, 0x96, 0xAB, 0xFA};

    std::vector<uint8_t> message{
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x0A};

    while (state.KeepRunning())
        {
            std::vector<uint8_t> output = d_crypto->compute_HMAC_SHA_256(key, message);
        }
}


void bm_CMAC_AES(benchmark::State& state)
{
    auto d_crypto = std::make_unique<Gnss_Crypto>();

    std::vector<uint8_t> key = {
        0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6,
        0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};

    std::vector<uint8_t> message{
        0x6B, 0xC1, 0xBE, 0xE2, 0x2E, 0x40, 0x9F, 0x96,
        0xE9, 0x3D, 0x7E, 0x11, 0x73, 0x93, 0x17, 0x2A};

    while (state.KeepRunning())
        {
            std::vector<uint8_t> output = d_crypto->compute_CMAC_AES(key, message);
        }
}


void bm_verify_ecdsa_p256(benchmark::State& state)
{
    auto d_crypto = std::make_unique<Gnss_Crypto>();

    // RG example  - import crt certificate
    std::vector<uint8_t> message = {
        0x82, 0x10, 0x49, 0x22, 0x04, 0xE0, 0x60, 0x61, 0x0B, 0xDF,
        0x26, 0xD7, 0x7B, 0x5B, 0xF8, 0xC9, 0xCB, 0xFC, 0xF7, 0x04,
        0x22, 0x08, 0x14, 0x75, 0xFD, 0x44, 0x5D, 0xF0, 0xFF};

    // ECDSA P-256 signature, raw format
    std::vector<uint8_t> signature = {
        0xF8, 0xCD, 0x88, 0x29, 0x9F, 0xA4, 0x60, 0x58, 0x00, 0x20,
        0x7B, 0xFE, 0xBE, 0xAC, 0x55, 0x02, 0x40, 0x53, 0xF3, 0x0F,
        0x7C, 0x69, 0xB3, 0x5C, 0x15, 0xE6, 0x08, 0x00, 0xAC, 0x3B,
        0x6F, 0xE3, 0xED, 0x06, 0x39, 0x95, 0x2F, 0x7B, 0x02, 0x8D,
        0x86, 0x86, 0x74, 0x45, 0x96, 0x1F, 0xFE, 0x94, 0xFB, 0x22,
        0x6B, 0xFF, 0x70, 0x06, 0xE0, 0xC4, 0x51, 0xEE, 0x3F, 0x87,
        0x28, 0xC1, 0x77, 0xFB};

    // compressed ECDSA P-256 format
    std::vector<uint8_t> publicKey = {
        0x03, 0x03, 0xB2, 0xCE, 0x64, 0xBC, 0x20, 0x7B, 0xDD, 0x8B,
        0xC4, 0xDF, 0x85, 0x91, 0x87, 0xFC, 0xB6, 0x86, 0x32, 0x0D,
        0x63, 0xFF, 0xA0, 0x91, 0x41, 0x0F, 0xC1, 0x58, 0xFB, 0xB7,
        0x79, 0x80, 0xEA};

    d_crypto->set_public_key(publicKey);

    while (state.KeepRunning())
        {
            bool output = d_crypto->verify_signature_ecdsa_p256(message, signature);
            if (output)
                {
                    // Avoid unused-but-set-variable warning
                }
        }
}


void bm_verify_ecdsa_p521(benchmark::State& state)
{
    std::unique_ptr<Gnss_Crypto> d_crypto = std::make_unique<Gnss_Crypto>();

    // Message to be verified
    std::vector<uint8_t> message = {
        0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x0A};  // "Hello world\n"

    // Public key in compressed X format
    std::vector<uint8_t> publicKey = {
        0x03, 0x00, 0x28, 0x35, 0xBB, 0xE9, 0x24, 0x59, 0x4E, 0xF0,
        0xE3, 0xA2, 0xDB, 0xC0, 0x49, 0x30, 0x60, 0x7C, 0x61, 0x90,
        0xE4, 0x03, 0xE0, 0xC7, 0xB8, 0xC2, 0x62, 0x37, 0xF7, 0x58,
        0x56, 0xBE, 0x63, 0x5C, 0x97, 0xF7, 0x53, 0x64, 0x7E, 0xE1,
        0x0C, 0x07, 0xD3, 0x97, 0x8D, 0x58, 0x46, 0xFD, 0x6E, 0x06,
        0x44, 0x01, 0xA7, 0xAA, 0xC4, 0x95, 0x13, 0x5D, 0xC9, 0x77,
        0x26, 0xE9, 0xF8, 0x72, 0x0C, 0xD3, 0x88};

    // ECDSA P-521 signature, raw format
    std::vector<uint8_t> signature = {
        0x01, 0x5C, 0x23, 0xC0, 0xBE, 0xAD, 0x1E, 0x44, 0x60, 0xD4,
        0xE0, 0x81, 0x38, 0xF2, 0xBA, 0xF5, 0xB5, 0x37, 0x5A, 0x34,
        0xB5, 0xCA, 0x6B, 0xC8, 0x0F, 0xCD, 0x75, 0x1D, 0x5E, 0xC0,
        0x8A, 0xD3, 0xD7, 0x79, 0xA7, 0xC1, 0xB8, 0xA2, 0xC6, 0xEA,
        0x5A, 0x7D, 0x60, 0x66, 0x50, 0x97, 0x37, 0x6C, 0xF9, 0x0A,
        0xF6, 0x3D, 0x77, 0x9A, 0xE2, 0x19, 0xF7, 0xF9, 0xDD, 0x52,
        0xC4, 0x0F, 0x98, 0xAA, 0xA2, 0xA4, 0x01, 0xC9, 0x41, 0x0B,
        0xD0, 0x25, 0xDD, 0xC9, 0x7C, 0x3F, 0x70, 0x32, 0x23, 0xCF,
        0xFE, 0x37, 0x67, 0x3A, 0xBC, 0x0B, 0x76, 0x16, 0x82, 0x83,
        0x27, 0x3D, 0x1D, 0x19, 0x15, 0x78, 0x08, 0x2B, 0xD4, 0xA7,
        0xC2, 0x0F, 0x11, 0xF4, 0xDD, 0xE5, 0x5A, 0x5D, 0x04, 0x8D,
        0x6D, 0x5E, 0xC4, 0x1F, 0x54, 0x44, 0xA9, 0x13, 0x34, 0x71,
        0x0F, 0xF7, 0x57, 0x9A, 0x9F, 0x2E, 0xF4, 0x97, 0x7D, 0xAE,
        0x28, 0xEF};

    d_crypto->set_public_key(publicKey);

    while (state.KeepRunning())
        {
            bool output = d_crypto->verify_signature_ecdsa_p521(message, signature);
            if (output)
                {
                    // Avoid unused-but-set-variable warning
                }
        }
}


BENCHMARK(bm_SHA_256);
BENCHMARK(bm_SHA3_256);
BENCHMARK(bm_HMAC_SHA_256);
BENCHMARK(bm_CMAC_AES);
BENCHMARK(bm_verify_ecdsa_p256);
BENCHMARK(bm_verify_ecdsa_p521);

BENCHMARK_MAIN();
