// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <cstdlib>
#include <string>
#include <kth/infrastructure.hpp>

KTH_USE_MAIN

int kth::main(int argc, char* argv[]) {
    return 0;
}

// int kth::main(int argc, char* argv[]) {

//     data_chunk out;
//     data_sink ostream(out);

//     uint8_t const raw_input_data[] =
//     {
//         0x03, 0x00, 0x00, 0x00, 0x1d, 0x00, 0x00, 0x00, 0xc1, 0xc1, 0xc1, 0xc1,
//         0xc1, 0xc1, 0xc1, 0xc0, 0x84, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03, 0x02,
//         0x03, 0x03, 0x03, 0x02, 0x03, 0xc0, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1,
//         0xc1, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1, 0xc0, 0x85, 0x02, 0x03,
//         0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x03, 0x03, 0x02, 0x03, 0xc0, 0xc1,
//         0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1, 0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0,
//         0xc1, 0xc0, 0x84, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02,
//         0x02, 0x02, 0x03, 0xc0, 0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0, 0xc1, 0xc1,
//         0xc0, 0xc1, 0xc1, 0xc1, 0xc0, 0xc1, 0xc0, 0x85, 0x03, 0x03, 0x02, 0x03,
//         0x03, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03, 0xc0, 0xc1, 0xc0, 0xc1,
//         0xc1, 0xc1, 0xc0, 0xc1, 0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0, 0xc1, 0xc0,
//         0x84, 0x03, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03,
//         0x03, 0xc0, 0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0, 0xc1, 0xc1, 0xc0, 0xc0,
//         0xc0, 0xc0, 0xc0, 0xc1, 0xc0, 0x85, 0x03, 0x02, 0x03, 0x03, 0x03, 0x02,
//         0x03, 0x02, 0x02, 0x03, 0x02, 0x02, 0xc0, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0,
//         0xc0, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc0, 0x91, 0x90,
//         0x91, 0x90, 0x91, 0x90, 0x91, 0x90, 0x91, 0x90, 0x91, 0x90, 0x91, 0xc0,
//         0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
//         0xc0, 0xc0, 0xc0, 0x84, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02,
//         0x02, 0x03, 0x02, 0x02, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
//         0x85, 0x85, 0x85, 0x85, 0x85, 0x84, 0x91, 0x85, 0x85, 0x03, 0x02, 0x03,
//         0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03, 0x85, 0x84, 0x85,
//         0x84, 0x85, 0x84, 0x85, 0x84, 0x02, 0x02, 0x03, 0x02, 0x03, 0x03, 0x90,
//         0x03, 0x03, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03,
//         0x03, 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02,
//         0x03, 0x02, 0x03, 0x03, 0x91, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02,
//         0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03,
//         0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x90, 0x02, 0x03,
//         0x02, 0x02, 0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02,
//         0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03, 0x03,
//         0x02, 0x03, 0x91, 0x02, 0x03, 0x03, 0x03, 0x02, 0x03, 0x03, 0x03, 0x03,
//         0x02, 0x03, 0x02, 0x03, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x03, 0x02,
//         0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x90, 0x02, 0x03, 0x03, 0x02,
//         0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03,
//         0x03, 0x03, 0x03, 0x03, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02,
//         0x91, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x03, 0x03, 0x03,
//         0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02,
//         0x02, 0x03, 0x02, 0x03, 0x02, 0x90, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02,
//         0x02, 0x02, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03,
//         0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x91, 0x02,
//         0x03, 0x02, 0x02, 0x03, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02,
//         0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02,
//         0x03, 0x02, 0x02, 0x90, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x03,
//         0x03, 0x03, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02, 0x03, 0x02, 0x03,
//         0x03, 0x03, 0x03, 0x02, 0x03, 0x02, 0x02, 0x02, 0x91, 0x02, 0x02, 0x02,
//         0x03, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x03,
//         0x02, 0x02, 0x03, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03,
//         0x03, 0x90, 0x02, 0x03, 0x03, 0x02, 0x02, 0x03, 0x02, 0x03, 0x03, 0x02,
//         0x02, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0x03, 0x02, 0x03, 0x03,
//         0x03, 0x02, 0x03, 0x03, 0x03, 0x02, 0x91, 0x02, 0x02, 0x03, 0x02, 0x02,
//         0x03, 0x03, 0x03, 0x02, 0x03, 0x03, 0x02, 0x02, 0xa1, 0xa1, 0xa1, 0xa1,
//         0xa1, 0x02, 0x03, 0x03, 0x02, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
//         0xc0, 0x81, 0x03, 0x03, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03,
//         0x03, 0xa1, 0xa0, 0xa0, 0xa0, 0xa1, 0x03, 0x03, 0x03, 0x03, 0xc1, 0xc1,
//         0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc0, 0x85, 0x02, 0x03, 0x03, 0x03, 0x03,
//         0x02, 0x03, 0x03, 0x02, 0x03, 0x03, 0xa1, 0xa0, 0xa1, 0xa0, 0xa1, 0x02,
//         0x03, 0x02, 0x02, 0xc1, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1, 0xc0, 0x84,
//         0x02, 0x02, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02, 0x03, 0xa1,
//         0xa0, 0xa0, 0xa0, 0xa1, 0x02, 0x02, 0x03, 0x03, 0xc1, 0xc0, 0xc1, 0xc1,
//         0xc1, 0xc0, 0xc1, 0xc0, 0x85, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x03,
//         0x02, 0x03, 0x02, 0x02, 0xa1, 0xa1, 0xa1, 0xa1, 0xa1, 0x03, 0x03, 0x03,
//         0x03, 0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0, 0xc1, 0xc0, 0x85, 0x03, 0x02,
//         0x02, 0x03, 0x03, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02, 0x03, 0x02, 0x02,
//         0x02, 0x03, 0x02, 0x03, 0x03, 0x03, 0xc1, 0xc0, 0xc1, 0xc1, 0xc1, 0xc0,
//         0xc1, 0xc0, 0x85, 0x02, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x02,
//         0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0x03, 0x03, 0x02, 0xc1,
//         0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc1, 0xc0, 0x85, 0x02, 0x02, 0x02, 0x03,
//         0x03, 0x02, 0x03, 0x03, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x03, 0x03,
//         0x02, 0x02, 0x03, 0x02, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc0,
//         0x85, 0x02, 0x03, 0x02, 0x03, 0x02, 0x03, 0x02, 0x02, 0x02, 0x02, 0x03,
//         0x02, 0x03, 0x02, 0x02, 0x03, 0x03, 0x03, 0x02, 0x02
//     };
//     auto const input_data = to_chunk(raw_input_data);

//     uint8_t const expected_data[] =
//     {
//         0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
//         0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x21,
//         0x01, 0x03, 0x00, 0x00, 0x00, 0x6d, 0x2a, 0x50, 0x2c, 0x00, 0x00, 0x00,
//         0x06, 0x50, 0x4c, 0x54, 0x45, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xa5,
//         0xd9, 0x9f, 0xdd, 0x00, 0x00, 0x00, 0x02, 0x74, 0x52, 0x4e, 0x53, 0xff,
//         0xff, 0xc8, 0xb5, 0xdf, 0xc7, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59,
//         0x73, 0x00, 0x00, 0x0a, 0xf8, 0x00, 0x00, 0x0a, 0xf8, 0x01, 0x66, 0x26,
//         0x3c, 0xfd, 0x00, 0x00, 0x00, 0xaf, 0x49, 0x44, 0x41, 0x54, 0x08, 0x99,
//         0x63, 0xf8, 0x0f, 0x02, 0x0c, 0x10, 0xf2, 0x40, 0x89, 0x2b, 0xe3, 0x7f,
//         0x86, 0xfb, 0xe1, 0x4b, 0x6b, 0xff, 0x33, 0x5c, 0xac, 0xfd, 0xeb, 0x0a,
//         0x24, 0x5d, 0x7a, 0x41, 0x64, 0xbe, 0x24, 0x90, 0xbc, 0xef, 0xb1, 0x1d,
//         0x28, 0x7e, 0x20, 0x34, 0x14, 0xa8, 0xe6, 0xff, 0xe3, 0xef, 0x40, 0xf5,
//         0x07, 0xb9, 0x24, 0x56, 0xff, 0x67, 0xf8, 0x32, 0x25, 0x31, 0xf2, 0x3f,
//         0xc3, 0x95, 0xf2, 0xfd, 0xed, 0xff, 0x19, 0x7e, 0xdf, 0x2d, 0x03, 0x8a,
//         0x7c, 0x72, 0xd1, 0xbc, 0xfe, 0x9f, 0xe1, 0xe1, 0x39, 0x09, 0x56, 0x20,
//         0x69, 0xd0, 0xea, 0xfe, 0x9f, 0xe1, 0x6b, 0xf3, 0x55, 0xfe, 0xff, 0x0c,
//         0x1f, 0xa2, 0xe4, 0x37, 0xfe, 0x67, 0xb8, 0xfd, 0x57, 0x20, 0xf0, 0x3f,
//         0xc3, 0xf5, 0x72, 0xb9, 0xf3, 0x40, 0x5d, 0x67, 0xcd, 0x34, 0x81, 0xe6,
//         0xe7, 0xf8, 0x08, 0x03, 0xcd, 0x3c, 0xce, 0x78, 0x10, 0x68, 0x7e, 0xc0,
//         0xc4, 0x70, 0xa0, 0x5d, 0xd5, 0x92, 0x37, 0x81, 0xe2, 0xd1, 0x6b, 0x80,
//         0x76, 0x5d, 0xf4, 0x69, 0xbd, 0x08, 0x24, 0xc3, 0xe4, 0x81, 0x6a, 0xee,
//         0xc7, 0xcc, 0x9d, 0x0d, 0x72, 0x43, 0xd5, 0x71, 0x98, 0x9b, 0xc1, 0x24,
//         0x00, 0x15, 0x36, 0x6f, 0x4e, 0xff, 0x43, 0x64, 0x8e, 0x00, 0x00, 0x00,
//         0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
//     };
//     constexpr uint32_t expected_data_length = 285;

//     constexpr uint32_t size = 1;
//     /* result */ png::write_png(input_data, size, ostream);



// //    BOOST_REQUIRE_EQUAL(out.size(), expected_data_length);
// //    BOOST_REQUIRE_EQUAL(std::memcmp(out.data(), expected_data, expected_data_length), 0);

//     auto x1 = out.size() == expected_data_length;
//     auto x2 = std::memcmp(out.data(), expected_data, expected_data_length) == 0;


//     return 0;
// }


// int kth::main(int argc, char* argv[])
// {
//     kth::infrastructure::wallet::payment_address const address1("1BpEi6DfDAUFd7GtittLSdBeYJvcoaVggu"); // Legacy Address Format
//     //kth::infrastructure::wallet::payment_address const address2("bitcoincash:qpzry9x8gf2tvdw0s3jn54khce6mua7lcw20ayyn"); // CashAddrFormat Invalid
//     //kth::infrastructure::wallet::payment_address const address2("bitcoincash:qpm2qsznhks23z7629mms6s4cwef74vcwvy22gdx6a"); // CashAddrFormat
//     kth::infrastructure::wallet::payment_address const address2("bitcoincash:ppm2qsznhks23z7629mms6s4cwef74vcwvn0h829pq"); // CashAddrFormat



//     auto enccash1 = address1.encoded_cashaddr();
//     auto enccash2 = address2.encoded_cashaddr();

//     auto encleg1 = address1.encoded();
//     auto encleg2 = address2.encoded();


//     return 0;
// }

//// Testing out our http://utf8everywhere.org implementation.
//int kth::main(int argc, char* argv[])
//{
//    // Windows utf8 everywhere demonstration.
//    set_utf8_stdio();
//
//    kth::cout << "output : acción.кошка.日本国" << std::endl;
//    kth::cerr << "error : acción.кошка.日本国" << std::endl;
//
//    kth::cout << "Enter text to input..." << std::endl;
//    std::string console;
//    kth::cin >> console;
//    kth::cout << "input[0]  : " << console << std::endl;
//
//    if (argc > 1)
//        kth::cout << "argv[1] : " << argv[1] << std::endl;
//
//#ifdef _MSC_VER
//    if (environ[0] != nullptr)
//        kth::cout << "environ[0] : " << environ[0] << std::endl;
//#endif
//
//    // Extracting Satoshi's words.
//    auto const block = kth::chain::block::genesis_mainnet();
//    auto const& tx = block.transactions().front();
//    auto const& input = tx.inputs().front();
//    auto const script = input.script().to_data(false);
//    std::string message(script.begin() + sizeof(uint64_t), script.end());
//    kth::cout << message << std::endl;
//
//    return EXIT_SUCCESS;
//}
