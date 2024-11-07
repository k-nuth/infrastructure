// Copyright (c) 2016-2024 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <test_helpers.hpp>

#include <cstdint>
#include <kth/infrastructure.hpp>

using namespace kth;
using namespace kth::infrastructure::wallet;

// Start Test Suite: qrcode tests

#ifdef WITH_QRENCODE

TEST_CASE("qrcode  invoke  qrencode data  success", "[qrcode tests]") {
    static uint8_t const expected_data[]
    {
        0x03, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0xc1, 0xc1, 0xc1, 0xc1,
        0xc1, 0xc1, 0xc1, 0xc0, 0x84, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03, 0x02,
        0x03, 0x03, 0x03, 0x02, 0x03, 0xc0, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1,
        0xc1, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1, 0xc0, 0x85, 0x02, 0x03,
        0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x03, 0x03, 0x02, 0x03, 0xc0, 0xc1,
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1, 0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0,
        0xc1, 0xc0, 0x84, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02,
        0x02, 0x02, 0x03, 0xc0, 0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0, 0xc1, 0xc1,
        0xc0, 0xc1, 0xc1, 0xc1, 0xc0, 0xc1, 0xc0, 0x85, 0x03, 0x03, 0x02, 0x03,
        0x03, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03, 0xc0, 0xc1, 0xc0, 0xc1,
        0xc1, 0xc1, 0xc0, 0xc1, 0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0, 0xc1, 0xc0,
        0x84, 0x03, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03,
        0x03, 0xc0, 0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0, 0xc1, 0xc1, 0xc0, 0xc0,
        0xc0, 0xc0, 0xc0, 0xc1, 0xc0, 0x85, 0x03, 0x02, 0x03, 0x03, 0x03, 0x02,
        0x03, 0x02, 0x02, 0x03, 0x02, 0x02, 0xc0, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0,
        0xc0, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc0, 0x91, 0x90,
        0x91, 0x90, 0x91, 0x90, 0x91, 0x90, 0x91, 0x90, 0x91, 0x90, 0x91, 0xc0,
        0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
        0xc0, 0xc0, 0xc0, 0x84, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02,
        0x02, 0x03, 0x02, 0x02, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
        0x85, 0x85, 0x85, 0x85, 0x85, 0x84, 0x91, 0x85, 0x85, 0x03, 0x02, 0x03,
        0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03, 0x85, 0x84, 0x85,
        0x84, 0x85, 0x84, 0x85, 0x84, 0x02, 0x02, 0x03, 0x02, 0x03, 0x03, 0x90,
        0x03, 0x03, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03,
        0x03, 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02,
        0x03, 0x02, 0x03, 0x03, 0x91, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02,
        0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03,
        0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x90, 0x02, 0x03,
        0x02, 0x02, 0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02,
        0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03, 0x03,
        0x02, 0x03, 0x91, 0x02, 0x03, 0x03, 0x03, 0x02, 0x03, 0x03, 0x03, 0x03,
        0x02, 0x03, 0x02, 0x03, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x03, 0x02,
        0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x90, 0x02, 0x03, 0x03, 0x02,
        0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03,
        0x03, 0x03, 0x03, 0x03, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02,
        0x91, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x03, 0x03, 0x03,
        0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02,
        0x02, 0x03, 0x02, 0x03, 0x02, 0x90, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02,
        0x02, 0x02, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03,
        0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x91, 0x02,
        0x03, 0x02, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02,
        0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02,
        0x03, 0x02, 0x02, 0x90, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x03,
        0x03, 0x03, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x03, 0x02, 0x03,
        0x03, 0x03, 0x03, 0x02, 0x03, 0x02, 0x02, 0x02, 0x91, 0x02, 0x02, 0x02,
        0x03, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x03,
        0x02, 0x02, 0x03, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03,
        0x03, 0x90, 0x02, 0x03, 0x03, 0x02, 0x02, 0x03, 0x02, 0x03, 0x03, 0x02,
        0x02, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0x03, 0x02, 0x03, 0x03,
        0x03, 0x02, 0x03, 0x03, 0x03, 0x02, 0x91, 0x02, 0x02, 0x03, 0x02, 0x02,
        0x03, 0x03, 0x03, 0x02, 0x03, 0x03, 0x02, 0x02, 0xa1, 0xa1, 0xa1, 0xa1,
        0xa1, 0x02, 0x03, 0x03, 0x02, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
        0xc0, 0x81, 0x03, 0x03, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03,
        0x03, 0xa1, 0xa0, 0xa0, 0xa0, 0xa1, 0x03, 0x03, 0x03, 0x03, 0xc1, 0xc1,
        0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc0, 0x85, 0x02, 0x03, 0x03, 0x03, 0x03,
        0x02, 0x03, 0x03, 0x02, 0x03, 0x03, 0xa1, 0xa0, 0xa1, 0xa0, 0xa1, 0x02,
        0x03, 0x02, 0x02, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1, 0xc0, 0x84,
        0x02, 0x02, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03, 0xa1,
        0xa0, 0xa0, 0xa0, 0xa1, 0x02, 0x02, 0x03, 0x03, 0xc1, 0xc0, 0xc1, 0xc1,
        0xc1, 0xc0, 0xc1, 0xc0, 0x85, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03,
        0x02, 0x03, 0x02, 0x02, 0xa1, 0xa1, 0xa1, 0xa1, 0xa1, 0x03, 0x03, 0x03,
        0x03, 0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0, 0xc1, 0xc0, 0x85, 0x03, 0x02,
        0x02, 0x03, 0x03, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x03, 0x02, 0x02,
        0x02, 0x03, 0x02, 0x03, 0x03, 0x03, 0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0,
        0xc1, 0xc0, 0x85, 0x02, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02,
        0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0x03, 0x03, 0x02, 0xc1,
        0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1, 0xc0, 0x85, 0x02, 0x02, 0x02, 0x03,
        0x03, 0x02, 0x03, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x03, 0x03,
        0x02, 0x02, 0x03, 0x02, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc0,
        0x85, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x03,
        0x02, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02
    };

    static auto const expected_data_length = sizeof(expected_data) / sizeof(uint8_t);
    static std::string const address = "bitcoin:1L4M4obtbpexxuKpLrDimMEYWB2Rx2yzus";
    auto const encoded_qrcode = qr::encode(to_chunk(address));

    REQUIRE(encoded_qrcode.size() == expected_data_length);
    REQUIRE(std::memcmp(encoded_qrcode.data(), expected_data, expected_data_length) == 0);
}

#endif // WITH_QRENCODE

// End Test Suite
