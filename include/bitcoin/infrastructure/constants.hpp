/**
 * Copyright (c) 2017-2018 Bitprim Inc.
 *
 * This file is part of Bitprim.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef BITPRIM_INFRASTRUCTURE_CONSTANTS_HPP
#define BITPRIM_INFRASTRUCTURE_CONSTANTS_HPP

#include <cstddef>
#include <cstdint>
#include <bitcoin/infrastructure/compat.hpp>
// #include <bitcoin/infrastructure/config/checkpoint.hpp>
#include <bitcoin/infrastructure/define.hpp>
// #include <bitcoin/infrastructure/math/hash.hpp>
// #include <bitcoin/infrastructure/message/network_address.hpp>
// #include <bitcoin/infrastructure/version.hpp>
#include <bitcoin/infrastructure/hash_define.hpp>

namespace libbitcoin {

// This guards assumptions within the codebase.
static_assert(sizeof(size_t) >= sizeof(uint32_t), "unsupported size_t");

// #define BI_USER_AGENT "/bitprim:" LIBBITCOIN_VERSION "/"

// Generic constants.
//-----------------------------------------------------------------------------

BI_CONSTEXPR int64_t min_int64 = MIN_INT64;
BI_CONSTEXPR int64_t max_int64 = MAX_INT64;
BI_CONSTEXPR int32_t min_int32 = MIN_INT32;
BI_CONSTEXPR int32_t max_int32 = MAX_INT32;
BI_CONSTEXPR uint64_t max_uint64 = MAX_UINT64;
BI_CONSTEXPR uint32_t max_uint32 = MAX_UINT32;
BI_CONSTEXPR uint16_t max_uint16 = MAX_UINT16;
BI_CONSTEXPR uint8_t max_uint8 = MAX_UINT8;
BI_CONSTEXPR uint64_t max_size_t = BI_MAX_SIZE;
BI_CONSTEXPR uint8_t byte_bits = 8;

// // Consensus sentinels.
// //-----------------------------------------------------------------------------

// BI_CONSTEXPR uint32_t no_previous_output = max_uint32;
// BI_CONSTEXPR uint32_t max_input_sequence = max_uint32;
// BI_CONSTEXPR uint64_t sighash_null_value = max_uint64;

// // Script/interpreter constants.
// //-----------------------------------------------------------------------------

// // Consensus
// BI_CONSTEXPR size_t max_counted_ops = 201;
// BI_CONSTEXPR size_t max_stack_size = 1000;
// BI_CONSTEXPR size_t max_script_size = 10000;
// BI_CONSTEXPR size_t max_push_data_size = 520;
// BI_CONSTEXPR size_t max_script_public_keys = 20;
// BI_CONSTEXPR size_t multisig_default_sigops = 20;
// BI_CONSTEXPR size_t max_number_size = 4;
// BI_CONSTEXPR size_t max_check_locktime_verify_number_size = 5;
// BI_CONSTEXPR size_t max_check_sequence_verify_number_size = 5;

// // Policy.
// BI_CONSTEXPR size_t max_null_data_size = 80;

// // Various validation constants.
// //-----------------------------------------------------------------------------

// BI_CONSTEXPR size_t min_coinbase_size = 2;
// BI_CONSTEXPR size_t max_coinbase_size = 100;

// BI_CONSTEXPR size_t median_time_past_interval = 11;

// #ifdef BITPRIM_CURRENCY_BCH
// BI_CONSTEXPR size_t bitcoin_cash_retarget_blocks = 6;
// //BI_CONSTEXPR size_t chain_state_timestamp_count = median_time_past_interval + bitcoin_cash_retarget_blocks;

// // Blocks used to calculate the next difficulty
// BI_CONSTEXPR size_t new_bitcoin_cash_retarget_algorithm = 147;
// BI_CONSTEXPR size_t chain_state_timestamp_count = new_bitcoin_cash_retarget_algorithm;

// BI_CONSTEXPR size_t bitcoin_cash_offset_tip = new_bitcoin_cash_retarget_algorithm - 11; // 147 - 11 = 136
// BI_CONSTEXPR size_t bitcoin_cash_offset_tip_minus_6 = bitcoin_cash_offset_tip - 6;

// BI_CONSTEXPR size_t max_block_size_old = 8000000; //eight million bytes
// BI_CONSTEXPR size_t max_block_size_new = 32000000; //thirty two million bytes

// #else

// BI_CONSTEXPR size_t max_block_size = 1000000; //one million bytes

// #endif //BITPRIM_CURRENCY_BCH


// BI_CONSTEXPR size_t coinbase_maturity = 100;
// // BI_CONSTEXPR size_t median_time_past_interval = 11;
// BI_CONSTEXPR size_t locktime_threshold = 500000000;
// // BI_CONSTEXPR size_t max_block_size = 1000000;

// #ifdef BITPRIM_CURRENCY_LTC
// //0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
// BI_CONSTEXPR uint32_t proof_of_work_limit = 0x1e0fffff;
// #else // BITPRIM_CURRENCY_LTC
// BI_CONSTEXPR size_t max_work_bits = 0x1d00ffff;
// // This may not be flexible, keep internal.
// //0x00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff
// BI_CONSTEXPR uint32_t proof_of_work_limit = 0x1d00ffff;
// #endif // BITPRIM_CURRENCY_LTC

// BI_CONSTFUNC uint32_t work_limit(bool retarget=true)
// {
//     return retarget ? retarget_proof_of_work_limit : no_retarget_proof_of_work_limit;
// }

// // Derived.
// BI_CONSTEXPR size_t max_sigops_factor = 50;


// // BI_CONSTEXPR size_t max_block_sigops = max_block_size / max_sigops_factor;
// #ifdef BITPRIM_CURRENCY_BCH
// BI_CONSTEXPR size_t max_block_sigops_old = max_block_size_old / max_sigops_factor;
// BI_CONSTEXPR size_t max_block_sigops_new = max_block_size_new / max_sigops_factor;
// #else
// BI_CONSTEXPR size_t max_block_sigops = max_block_size / max_sigops_factor; 
// #endif //BITPRIM_CURRENCY_BCH


// constexpr inline
// size_t get_max_block_size() {
// #ifdef BITPRIM_CURRENCY_BCH
//     return max_block_size_new; 
// #else
//     return max_block_size;
// #endif //BITPRIM_CURRENCY_BCH
// }

// constexpr inline
// size_t get_max_block_sigops() {
// #ifdef BITPRIM_CURRENCY_BCH
//     return max_block_sigops_new;
// #else
//     return max_block_sigops;
// #endif //BITPRIM_CURRENCY_BCH
// }

// // BI_CONSTEXPR size_t one_million_bytes_block = 1000000;
// BI_CONSTEXPR size_t sigops_per_million_bytes = 20000;

// BI_CONSTFUNC inline
// size_t get_allowed_sigops(size_t block_size) {
//     // return (1 + ((block_size - 1) / one_million_bytes_block)) * sigops_per_million_bytes;
//     return (block_size - 1) / max_sigops_factor + sigops_per_million_bytes;
// }

// // Relative locktime constants.
// //-----------------------------------------------------------------------------

// BI_CONSTEXPR size_t relative_locktime_min_version = 2;
// BI_CONSTEXPR size_t relative_locktime_seconds_shift = 9;
// BI_CONSTEXPR uint32_t relative_locktime_mask = 0x0000ffff;
// BI_CONSTEXPR uint32_t relative_locktime_disabled = 0x80000000;
// BI_CONSTEXPR uint32_t relative_locktime_time_locked = 0x00400000;

// // Timespan constants.
// //-----------------------------------------------------------------------------

// BI_CONSTEXPR uint32_t retargeting_factor = 4;

// #ifdef BITPRIM_CURRENCY_LTC
// BI_CONSTEXPR uint32_t target_spacing_seconds = 10 * 15;
// BI_CONSTEXPR uint32_t target_timespan_seconds = 2 * 7 * 24 * 60 * 15;
// #else //BITPRIM_CURRENCY_LTC
// BI_CONSTEXPR uint32_t target_spacing_seconds = 10 * 60;
// BI_CONSTEXPR uint32_t target_timespan_seconds = 2 * 7 * 24 * 60 * 60;
// #endif //BITPRIM_CURRENCY_LTC

// BI_CONSTEXPR uint32_t timestamp_future_seconds = 2 * 60 * 60;  //TODO(bitprim): New on v3.3.0 merge (September 2017), see how this affects Litecoin
// BI_CONSTEXPR uint32_t easy_spacing_factor = 2;

// // BI_CONSTEXPR uint32_t easy_spacing_seconds = 20 * 60;
// // BI_CONSTEXPR uint32_t retarget_height = easy_spacing_factor * target_spacing_seconds;
// BI_CONSTEXPR uint32_t easy_spacing_seconds = easy_spacing_factor * target_spacing_seconds;



// // The upper and lower bounds for the retargeting timespan.
// BI_CONSTEXPR uint32_t min_timespan = target_timespan_seconds / retargeting_factor;
// BI_CONSTEXPR uint32_t max_timespan = target_timespan_seconds * retargeting_factor;

// // Bitcoin:  The target number of blocks for 2 weeks of work (2016 blocks).
// // Litecoin: The target number of blocks for 3.5 days of work (2016 blocks).
// BI_CONSTEXPR size_t retargeting_interval = target_timespan_seconds / target_spacing_seconds;

// // Fork constants.
// //-----------------------------------------------------------------------------

// // Consensus rule change activation and enforcement parameters.
// BI_CONSTEXPR size_t first_version = 1;
// BI_CONSTEXPR size_t bip34_version = 2;
// BI_CONSTEXPR size_t bip66_version = 3;
// BI_CONSTEXPR size_t bip65_version = 4;
// BI_CONSTEXPR uint32_t bip9_version_bit0 = 1u << 0;
// BI_CONSTEXPR uint32_t bip9_version_bit1 = 1u << 1;
// BI_CONSTEXPR uint32_t bip9_version_base = 0x20000000;

// #ifdef BITPRIM_CURRENCY_BCH
// // BI_CONSTEXPR size_t   bch_activation_height = 478559 //478558;                       //2017-August-01 hard fork
// // BI_CONSTEXPR uint32_t bch_daa_activation_time = 1510600000;                 //2017-November-13 hard fork
// BI_CONSTEXPR uint32_t bch_monolith_activation_time = 1526400000;            //2018-May hard fork
// BI_CONSTEXPR uint32_t bch_magnetic_anomaly_activation_time = 1542300000;    //2018-November hard fork

// // inline constexpr
// // bool is_uahf_enabled(const Config &config, int nHeight) {
// //     return nHeight >= config.GetChainParams().GetConsensus().uahfHeight;
// // }


// #endif //BITPRIM_CURRENCY_BCH


// #ifdef BITPRIM_CURRENCY_LTC

// // Mainnet activation parameters (bip34-style activations).
// BI_CONSTEXPR size_t mainnet_active = 750;
// BI_CONSTEXPR size_t mainnet_enforce = 950;
// BI_CONSTEXPR size_t mainnet_sample = 1000;

// // Testnet activation parameters (bip34-style activations).
// BI_CONSTEXPR size_t testnet_active = 51;
// BI_CONSTEXPR size_t testnet_enforce = 75;
// BI_CONSTEXPR size_t testnet_sample = 100;

// // Regtest (arbitrary) frozen activation heights (frozen_activations).
// BI_CONSTEXPR size_t regtest_bip65_freeze = 1351;
// BI_CONSTEXPR size_t regtest_bip66_freeze = 1251;
// BI_CONSTEXPR size_t regtest_bip34_freeze = 100000000;

// // Mainnet frozen activation heights (frozen_activations).
// BI_CONSTEXPR size_t mainnet_bip65_freeze = MAX_UINT32; //Not Active
// BI_CONSTEXPR size_t mainnet_bip66_freeze = MAX_UINT32; //Not Active
// BI_CONSTEXPR size_t mainnet_bip34_freeze = 710000;

// // Testnet frozen activation heights (frozen_activations).
// BI_CONSTEXPR size_t testnet_bip65_freeze = MAX_UINT32; //Not Active
// BI_CONSTEXPR size_t testnet_bip66_freeze = MAX_UINT32; //Not Active
// BI_CONSTEXPR size_t testnet_bip34_freeze = 76; //Always Active

// // Block 514 is the first testnet block after date-based activation.
// // Block 173805 is the first mainnet block after date-based activation.
// BI_CONSTEXPR uint32_t bip16_activation_time = 0x4f779a80;

// // Block 170060 was mined with an invalid p2sh (code shipped late).
// // bitcointalk.org/index.php?topic=63165.msg788832#msg788832
// static const config::checkpoint mainnet_bip16_exception_checkpoint {
//     "00000000000002dc756eebf4f49723ed8d30cc28a5f108eb94b1ba88ac4f9c22", 170060
// };

// // github.com/bitcoin/bips/blob/master/bip-0030.mediawiki#specification
// static const config::checkpoint mainnet_bip30_exception_checkpoint1 {
//     // TODO: figure out why this block validates without an exception.
//     "00000000000a4d0a398161ffc163c503763b1f4360639393e0e4c8e300e0caec", 91842
// };

// static const config::checkpoint mainnet_bip30_exception_checkpoint2 {
//     "00000000000743f190a18c5577a3c2d2a1f610ae9601ac046a38084ccb7cd721", 91880
// };

// // Hard fork to stop checking unspent duplicates above fixed bip34 activation.
// static const config::checkpoint mainnet_bip34_active_checkpoint {
//     "fa09d204a83a768ed5a7c8d441fa62f2043abf420cff1226c7b4329aeb9d51cf", 710000
// };

// static const config::checkpoint testnet_bip34_active_checkpoint {
//     "8075c771ed8b495ffd943980a95f702ab34fce3c8c54e379548bda33cc8c0573", 76
// };

// static const config::checkpoint regtest_bip34_active_checkpoint
// {
//     "fa09d204a83a768ed5a7c8d441fa62f2043abf420cff1226c7b4329aeb9d51cf", 100000000
// };

// #else //BITPRIM_CURRENCY_LTC
// // Mainnet activation parameters (bip34-style activations).
// BI_CONSTEXPR size_t mainnet_active = 750;
// BI_CONSTEXPR size_t mainnet_enforce = 950;
// BI_CONSTEXPR size_t mainnet_sample = 1000;

// // Testnet activation parameters (bip34-style activations).
// BI_CONSTEXPR size_t testnet_active = 51;
// BI_CONSTEXPR size_t testnet_enforce = 75;
// BI_CONSTEXPR size_t testnet_sample = 100;

// // Mainnet frozen activation heights (frozen_activations).
// BI_CONSTEXPR size_t mainnet_bip65_freeze = 388381;
// BI_CONSTEXPR size_t mainnet_bip66_freeze = 363725;
// BI_CONSTEXPR size_t mainnet_bip34_freeze = 227931;

// // Testnet frozen activation heights (frozen_activations).
// BI_CONSTEXPR size_t testnet_bip65_freeze = 581885;
// BI_CONSTEXPR size_t testnet_bip66_freeze = 330776;
// BI_CONSTEXPR size_t testnet_bip34_freeze = 21111;

// // Regtest (arbitrary) frozen activation heights (frozen_activations).
// BI_CONSTEXPR size_t regtest_bip65_freeze = 1351;
// BI_CONSTEXPR size_t regtest_bip66_freeze = 1251;
// BI_CONSTEXPR size_t regtest_bip34_freeze = 0;

// // Block 514 is the first testnet block after date-based activation.
// // Block 166832 is the first mainnet block after date-based activation.
// BI_CONSTEXPR uint32_t bip16_activation_time = 0x4f3af580;

// // Block 170060 was mined with an invalid p2sh (code shipped late).
// // bitcointalk.org/index.php?topic=63165.msg788832#msg788832
// static const config::checkpoint mainnet_bip16_exception_checkpoint {
//     "00000000000002dc756eebf4f49723ed8d30cc28a5f108eb94b1ba88ac4f9c22", 170060
// };

// // github.com/bitcoin/bips/blob/master/bip-0030.mediawiki#specification
// static const config::checkpoint mainnet_bip30_exception_checkpoint1 {
//     "00000000000a4d0a398161ffc163c503763b1f4360639393e0e4c8e300e0caec", 91842
// };

// static const config::checkpoint mainnet_bip30_exception_checkpoint2 {
//     "00000000000743f190a18c5577a3c2d2a1f610ae9601ac046a38084ccb7cd721", 91880
// };

// // bip90 stops checking unspent duplicates above this bip34 activation.
// static const config::checkpoint mainnet_bip34_active_checkpoint {
//     "000000000000024b89b42a942fe0d9fea3bb44ab7bd1b19115dd6a759c0808b8", 227931
// };

// static const config::checkpoint testnet_bip34_active_checkpoint {
//     "0000000023b3a96d3484e5abb3755c413e7d41500f8e2a5c3f0dd01299cd8ef8", 21111
// };
// static const config::checkpoint regtest_bip34_active_checkpoint
// {
//     // Since bip90 assumes a historical bip34 activation block, use genesis.
//     "06226e46111a0b59caaf126043eb5bbf28c34f3a5e332a1fc7b2b73cf188910f", 0
// };

// #endif //BITPRIM_CURRENCY_LTC

// // These cannot be reactivated in a future branch due to window expiration.
// static const config::checkpoint mainnet_bip9_bit0_active_checkpoint {
//     "000000000000000004a1b34462cb8aeebd5799177f7a29cf28f2d1961716b5b5", 419328
// };

// static const config::checkpoint testnet_bip9_bit0_active_checkpoint {
//     "00000000025e930139bac5c6c31a403776da130831ab85be56578f3fa75369bb", 770112
// };
// static const config::checkpoint regtest_bip9_bit0_active_checkpoint
// {
//     // The activation window is fixed and closed, so assume genesis activation.
//     "06226e46111a0b59caaf126043eb5bbf28c34f3a5e332a1fc7b2b73cf188910f", 0
// };

// // These cannot be reactivated in a future branch due to window expiration.
// static const config::checkpoint mainnet_bip9_bit1_active_checkpoint
// {
//     "0000000000000000001c8018d9cb3b742ef25114f27563e3fc4a1902167f9893", 481824
// };
// static const config::checkpoint testnet_bip9_bit1_active_checkpoint
// {
//     "00000000002b980fcd729daaa248fd9316a5200e9b367f4ff2c42453e84201ca", 834624
// };
// static const config::checkpoint regtest_bip9_bit1_active_checkpoint
// {
//     // The activation window is fixed and closed, so assume genesis activation.
//     "06226e46111a0b59caaf126043eb5bbf28c34f3a5e332a1fc7b2b73cf188910f", 0
// };


// #ifdef BITPRIM_CURRENCY_BCH

// static const config::checkpoint mainnet_uahf_active_checkpoint {
//     "000000000000000000651ef99cb9fcbe0dadde1d424bd9f15ff20136191a5eec", 478559
// };

// static const config::checkpoint testnet_uahf_active_checkpoint {
//     "00000000000e38fef93ed9582a7df43815d5c2ba9fd37ef70c9a0ea4a285b8f5", 1155876
// };

// static const config::checkpoint mainnet_daa_active_checkpoint {
//     "0000000000000000011ebf65b60d0a3de80b8175be709d653b4c1a1beeb6ab9c", 504031
// };

// static const config::checkpoint testnet_daa_active_checkpoint {
//     "0000000000170ed0918077bde7b4d36cc4c91be69fa09211f748240dabe047fb", 1188697
// };

// #endif


// // Network protocol constants.
// //-----------------------------------------------------------------------------

// // Explicit size.
// BI_CONSTEXPR size_t command_size = 12;

// // Explicit limits.
// BI_CONSTEXPR size_t max_address = 1000;
// BI_CONSTEXPR size_t max_filter_add = 520;
// BI_CONSTEXPR size_t max_filter_functions = 50;
// BI_CONSTEXPR size_t max_filter_load = 36000;
// BI_CONSTEXPR size_t max_get_blocks = 500;
// BI_CONSTEXPR size_t max_get_headers = 2000;
// BI_CONSTEXPR size_t max_get_data = 50000;
// BI_CONSTEXPR size_t max_inventory = 50000;

// BI_CONSTEXPR size_t max_payload_size = 33554432;

// // Effective limit given a 32 bit chain height boundary: 10 + log2(2^32) + 1.
// BI_CONSTEXPR size_t max_locator = 43;

// // Variable integer prefix sentinels.
BI_CONSTEXPR uint8_t varint_two_bytes = 0xfd;
BI_CONSTEXPR uint8_t varint_four_bytes = 0xfe;
BI_CONSTEXPR uint8_t varint_eight_bytes = 0xff;

// String padding sentinel.
BI_CONSTEXPR uint8_t string_terminator = 0x00;

// // Witness serialization values (bip141).
// //-----------------------------------------------------------------------------

// BI_CONSTEXPR uint8_t witness_marker = 0x00;
// BI_CONSTEXPR uint8_t witness_flag = 0x01;
// BI_CONSTEXPR uint32_t witness_head = 0xaa21a9ed;
// BI_CONSTEXPR size_t fast_sigops_factor = 4;
// BI_CONSTEXPR size_t max_fast_sigops = fast_sigops_factor *  get_max_block_sigops();
// BI_CONSTEXPR size_t light_weight_factor = 4;
// BI_CONSTEXPR size_t max_block_weight = light_weight_factor *  get_max_block_size();
// BI_CONSTEXPR size_t base_size_contribution = 3;
// BI_CONSTEXPR size_t total_size_contribution = 1;
// BI_CONSTEXPR size_t min_witness_program = 2;
// BI_CONSTEXPR size_t max_witness_program = 40;

// // Currency unit constants (uint64_t).
// //-----------------------------------------------------------------------------

// BI_CONSTFUNC inline
// uint64_t max_money_recursive(uint64_t money) {
//     return money > 0 ? money + max_money_recursive(money >> 1) : 0;
// }

// BI_CONSTEXPR uint64_t satoshi_per_bitcoin = 100000000;

// BI_CONSTFUNC inline 
// uint64_t bitcoin_to_satoshi(uint64_t bitcoin_uints=1) {
//     return bitcoin_uints * satoshi_per_bitcoin;
// }

// BI_CONSTEXPR uint64_t initial_block_subsidy_bitcoin = 50;

// BI_CONSTFUNC inline 
// uint64_t initial_block_subsidy_satoshi() {
//     return bitcoin_to_satoshi(initial_block_subsidy_bitcoin);
// }

// #ifdef BITPRIM_CURRENCY_LTC
// // BI_CONSTEXPR uint64_t reward_interval = 840000;
// BI_CONSTEXPR uint64_t retarget_subsidy_interval = 840000;
// BI_CONSTEXPR uint64_t no_retarget_subsidy_interval = 150; // TODO: merge version3. check the no_retarget (regtest) value for LTC 
// #else //BITPRIM_CURRENCY_LTC
// // BI_CONSTEXPR uint64_t reward_interval = 210000;
// BI_CONSTEXPR uint64_t retarget_subsidy_interval = 210000;
// BI_CONSTEXPR uint64_t no_retarget_subsidy_interval = 150;
// #endif //BITPRIM_CURRENCY_LTC

// BI_CONSTEXPR uint64_t recursive_money = 0x02540be3f5;

// BI_CONSTFUNC uint64_t subsidy_interval(bool retarget=true)
// {
//     return retarget ? retarget_subsidy_interval : no_retarget_subsidy_interval;
// }

// BI_CONSTFUNC uint64_t max_money(bool retarget=true)
// {
//     ////// Optimize out the derivation of recursive_money.
//     ////BITCOIN_ASSERT(recursive_money == max_money_recursive(
//     ////    initial_block_subsidy_satoshi()));

//     return recursive_money * subsidy_interval(retarget);
// }

} // namespace libbitcoin

#endif
