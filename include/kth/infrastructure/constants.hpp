// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef KTH_INFRASTRUCTURE_CONSTANTS_HPP
#define KTH_INFRASTRUCTURE_CONSTANTS_HPP

#include <cstddef>
#include <cstdint>

#include <kth/infrastructure/compat.hpp>
// #include <kth/infrastructure/config/checkpoint.hpp>
#include <kth/infrastructure/define.hpp>
// #include <kth/infrastructure/math/hash.hpp>
// #include <kth/infrastructure/message/network_address.hpp>
// #include <kth/infrastructure/version.hpp>
#include <kth/infrastructure/hash_define.hpp>

namespace kth {

// This guards assumptions within the codebase.
static_assert(sizeof(size_t) >= sizeof(uint32_t), "unsupported size_t");

// #define BI_USER_AGENT "/knuth:" KTH_VERSION "/"

// Generic constants.
//-----------------------------------------------------------------------------

constexpr int64_t min_int64 = MIN_INT64;
constexpr int64_t max_int64 = MAX_INT64;
constexpr int32_t min_int32 = MIN_INT32;
constexpr int32_t max_int32 = MAX_INT32;
constexpr uint64_t max_uint64 = MAX_UINT64;
constexpr uint32_t max_uint32 = MAX_UINT32;
constexpr uint16_t max_uint16 = MAX_UINT16;
constexpr uint8_t max_uint8 = MAX_UINT8;
constexpr uint64_t max_size_t = BC_MAX_SIZE;
constexpr uint8_t byte_bits = 8;

// // Consensus sentinels.
// //-----------------------------------------------------------------------------

// constexpr uint32_t no_previous_output = max_uint32;
// constexpr uint32_t max_input_sequence = max_uint32;
// constexpr uint64_t sighash_null_value = max_uint64;

// // Script/interpreter constants.
// //-----------------------------------------------------------------------------

// // Consensus
// constexpr size_t max_counted_ops = 201;
// constexpr size_t max_stack_size = 1000;
// constexpr size_t max_script_size = 10000;
constexpr size_t max_push_data_size = 520;
// constexpr size_t max_script_public_keys = 20;
// constexpr size_t multisig_default_sigops = 20;
// constexpr size_t max_number_size = 4;
// constexpr size_t max_check_locktime_verify_number_size = 5;
// constexpr size_t max_check_sequence_verify_number_size = 5;

// // Policy.
// constexpr size_t max_null_data_size = 80;

// // Various validation constants.
// //-----------------------------------------------------------------------------

// constexpr size_t min_coinbase_size = 2;
// constexpr size_t max_coinbase_size = 100;

// constexpr size_t median_time_past_interval = 11;

// #ifdef KTH_CURRENCY_BCH
// constexpr size_t bitcoin_cash_retarget_blocks = 6;
// //constexpr size_t chain_state_timestamp_count = median_time_past_interval + bitcoin_cash_retarget_blocks;

// // Blocks used to calculate the next difficulty
// constexpr size_t new_bitcoin_cash_retarget_algorithm = 147;
// constexpr size_t chain_state_timestamp_count = new_bitcoin_cash_retarget_algorithm;

// constexpr size_t bitcoin_cash_offset_tip = new_bitcoin_cash_retarget_algorithm - 11; // 147 - 11 = 136
// constexpr size_t bitcoin_cash_offset_tip_minus_6 = bitcoin_cash_offset_tip - 6;

// constexpr size_t max_block_size_old = 8000000; //eight million bytes
// constexpr size_t max_block_size_new = 32000000; //thirty two million bytes

// #else

// constexpr size_t max_block_size = 1000000; //one million bytes

// #endif //KTH_CURRENCY_BCH


// constexpr size_t coinbase_maturity = 100;
// // constexpr size_t median_time_past_interval = 11;
// constexpr size_t locktime_threshold = 500000000;
// // constexpr size_t max_block_size = 1000000;

// #ifdef KTH_CURRENCY_LTC
// //0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
// constexpr uint32_t proof_of_work_limit = 0x1e0fffff;
// #else // KTH_CURRENCY_LTC
// constexpr size_t max_work_bits = 0x1d00ffff;
// // This may not be flexible, keep internal.
// //0x00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff
// constexpr uint32_t proof_of_work_limit = 0x1d00ffff;
// #endif // KTH_CURRENCY_LTC

// constexpr uint32_t work_limit(bool retarget=true)
// {
//     return retarget ? retarget_proof_of_work_limit : no_retarget_proof_of_work_limit;
// }

// // Derived.
// constexpr size_t max_sigops_factor = 50;


// // constexpr size_t max_block_sigops = max_block_size / max_sigops_factor;
// #ifdef KTH_CURRENCY_BCH
// constexpr size_t max_block_sigops_old = max_block_size_old / max_sigops_factor;
// constexpr size_t max_block_sigops_new = max_block_size_new / max_sigops_factor;
// #else
// constexpr size_t max_block_sigops = max_block_size / max_sigops_factor; 
// #endif //KTH_CURRENCY_BCH


// constexpr inline
// size_t get_max_block_size() {
// #ifdef KTH_CURRENCY_BCH
//     return max_block_size_new; 
// #else
//     return max_block_size;
// #endif //KTH_CURRENCY_BCH
// }

// constexpr inline
// size_t get_max_block_sigops() {
// #ifdef KTH_CURRENCY_BCH
//     return max_block_sigops_new;
// #else
//     return max_block_sigops;
// #endif //KTH_CURRENCY_BCH
// }

// // constexpr size_t one_million_bytes_block = 1000000;
// constexpr size_t sigops_per_million_bytes = 20000;

// constexpr inline
// size_t get_allowed_sigops(size_t block_size) {
//     // return (1 + ((block_size - 1) / one_million_bytes_block)) * sigops_per_million_bytes;
//     return (block_size - 1) / max_sigops_factor + sigops_per_million_bytes;
// }

// // Relative locktime constants.
// //-----------------------------------------------------------------------------

// constexpr size_t relative_locktime_min_version = 2;
// constexpr size_t relative_locktime_seconds_shift = 9;
// constexpr uint32_t relative_locktime_mask = 0x0000ffff;
// constexpr uint32_t relative_locktime_disabled = 0x80000000;
// constexpr uint32_t relative_locktime_time_locked = 0x00400000;

// // Timespan constants.
// //-----------------------------------------------------------------------------

// constexpr uint32_t retargeting_factor = 4;

// #ifdef KTH_CURRENCY_LTC
// constexpr uint32_t target_spacing_seconds = 10 * 15;
// constexpr uint32_t target_timespan_seconds = 2 * 7 * 24 * 60 * 15;
// #else //KTH_CURRENCY_LTC
// constexpr uint32_t target_spacing_seconds = 10 * 60;
// constexpr uint32_t target_timespan_seconds = 2 * 7 * 24 * 60 * 60;
// #endif //KTH_CURRENCY_LTC

// constexpr uint32_t timestamp_future_seconds = 2 * 60 * 60;  //TODO(knuth): New on v3.3.0 merge (September 2017), see how this affects Litecoin
// constexpr uint32_t easy_spacing_factor = 2;

// // constexpr uint32_t easy_spacing_seconds = 20 * 60;
// // constexpr uint32_t retarget_height = easy_spacing_factor * target_spacing_seconds;
// constexpr uint32_t easy_spacing_seconds = easy_spacing_factor * target_spacing_seconds;



// // The upper and lower bounds for the retargeting timespan.
// constexpr uint32_t min_timespan = target_timespan_seconds / retargeting_factor;
// constexpr uint32_t max_timespan = target_timespan_seconds * retargeting_factor;

// // Bitcoin:  The target number of blocks for 2 weeks of work (2016 blocks).
// // Litecoin: The target number of blocks for 3.5 days of work (2016 blocks).
// constexpr size_t retargeting_interval = target_timespan_seconds / target_spacing_seconds;

// // Fork constants.
// //-----------------------------------------------------------------------------

// // Consensus rule change activation and enforcement parameters.
// constexpr size_t first_version = 1;
// constexpr size_t bip34_version = 2;
// constexpr size_t bip66_version = 3;
// constexpr size_t bip65_version = 4;
// constexpr uint32_t bip9_version_bit0 = 1u << 0;
// constexpr uint32_t bip9_version_bit1 = 1u << 1;
// constexpr uint32_t bip9_version_base = 0x20000000;

// #ifdef KTH_CURRENCY_BCH
// // constexpr size_t   bch_activation_height = 478559 //478558;                       //2017-August-01 hard fork
// // constexpr uint32_t bch_daa_activation_time = 1510600000;                 //2017-November-13 hard fork
// constexpr uint32_t bch_monolith_activation_time = 1526400000;            //2018-May hard fork
// constexpr uint32_t bch_magnetic_anomaly_activation_time = 1542300000;    //2018-November hard fork

// // inline constexpr
// // bool is_uahf_enabled(const Config &config, int nHeight) {
// //     return nHeight >= config.GetChainParams().GetConsensus().uahfHeight;
// // }


// #endif //KTH_CURRENCY_BCH


// #ifdef KTH_CURRENCY_LTC

// // Mainnet activation parameters (bip34-style activations).
// constexpr size_t mainnet_active = 750;
// constexpr size_t mainnet_enforce = 950;
// constexpr size_t mainnet_sample = 1000;

// // Testnet activation parameters (bip34-style activations).
// constexpr size_t testnet_active = 51;
// constexpr size_t testnet_enforce = 75;
// constexpr size_t testnet_sample = 100;

// // Regtest (arbitrary) frozen activation heights (frozen_activations).
// constexpr size_t regtest_bip65_freeze = 1351;
// constexpr size_t regtest_bip66_freeze = 1251;
// constexpr size_t regtest_bip34_freeze = 100000000;

// // Mainnet frozen activation heights (frozen_activations).
// constexpr size_t mainnet_bip65_freeze = MAX_UINT32; //Not Active
// constexpr size_t mainnet_bip66_freeze = MAX_UINT32; //Not Active
// constexpr size_t mainnet_bip34_freeze = 710000;

// // Testnet frozen activation heights (frozen_activations).
// constexpr size_t testnet_bip65_freeze = MAX_UINT32; //Not Active
// constexpr size_t testnet_bip66_freeze = MAX_UINT32; //Not Active
// constexpr size_t testnet_bip34_freeze = 76; //Always Active

// // Block 514 is the first testnet block after date-based activation.
// // Block 173805 is the first mainnet block after date-based activation.
// constexpr uint32_t bip16_activation_time = 0x4f779a80;

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

// #else //KTH_CURRENCY_LTC
// // Mainnet activation parameters (bip34-style activations).
// constexpr size_t mainnet_active = 750;
// constexpr size_t mainnet_enforce = 950;
// constexpr size_t mainnet_sample = 1000;

// // Testnet activation parameters (bip34-style activations).
// constexpr size_t testnet_active = 51;
// constexpr size_t testnet_enforce = 75;
// constexpr size_t testnet_sample = 100;

// // Mainnet frozen activation heights (frozen_activations).
// constexpr size_t mainnet_bip65_freeze = 388381;
// constexpr size_t mainnet_bip66_freeze = 363725;
// constexpr size_t mainnet_bip34_freeze = 227931;

// // Testnet frozen activation heights (frozen_activations).
// constexpr size_t testnet_bip65_freeze = 581885;
// constexpr size_t testnet_bip66_freeze = 330776;
// constexpr size_t testnet_bip34_freeze = 21111;

// // Regtest (arbitrary) frozen activation heights (frozen_activations).
// constexpr size_t regtest_bip65_freeze = 1351;
// constexpr size_t regtest_bip66_freeze = 1251;
// constexpr size_t regtest_bip34_freeze = 0;

// // Block 514 is the first testnet block after date-based activation.
// // Block 166832 is the first mainnet block after date-based activation.
// constexpr uint32_t bip16_activation_time = 0x4f3af580;

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

// #endif //KTH_CURRENCY_LTC

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


// #ifdef KTH_CURRENCY_BCH

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
// constexpr size_t command_size = 12;

// // Explicit limits.
// constexpr size_t max_address = 1000;
// constexpr size_t max_filter_add = 520;
// constexpr size_t max_filter_functions = 50;
// constexpr size_t max_filter_load = 36000;
// constexpr size_t max_get_blocks = 500;
// constexpr size_t max_get_headers = 2000;
// constexpr size_t max_get_data = 50000;
// constexpr size_t max_inventory = 50000;

// constexpr size_t max_payload_size = 33554432;

// // Effective limit given a 32 bit chain height boundary: 10 + log2(2^32) + 1.
// constexpr size_t max_locator = 43;

// // Variable integer prefix sentinels.
constexpr uint8_t varint_two_bytes = 0xfd;
constexpr uint8_t varint_four_bytes = 0xfe;
constexpr uint8_t varint_eight_bytes = 0xff;

// String padding sentinel.
constexpr uint8_t string_terminator = 0x00;

// // Witness serialization values (bip141).
// //-----------------------------------------------------------------------------

// constexpr uint8_t witness_marker = 0x00;
// constexpr uint8_t witness_flag = 0x01;
// constexpr uint32_t witness_head = 0xaa21a9ed;
// constexpr size_t fast_sigops_factor = 4;
// constexpr size_t max_fast_sigops = fast_sigops_factor *  get_max_block_sigops();
// constexpr size_t light_weight_factor = 4;
// constexpr size_t max_block_weight = light_weight_factor *  get_max_block_size();
// constexpr size_t base_size_contribution = 3;
// constexpr size_t total_size_contribution = 1;
// constexpr size_t min_witness_program = 2;
// constexpr size_t max_witness_program = 40;

// // Currency unit constants (uint64_t).
// //-----------------------------------------------------------------------------

// constexpr inline
// uint64_t max_money_recursive(uint64_t money) {
//     return money > 0 ? money + max_money_recursive(money >> 1) : 0;
// }

// constexpr uint64_t satoshi_per_bitcoin = 100000000;

// constexpr inline 
// uint64_t bitcoin_to_satoshi(uint64_t bitcoin_uints=1) {
//     return bitcoin_uints * satoshi_per_bitcoin;
// }

// constexpr uint64_t initial_block_subsidy_bitcoin = 50;

// constexpr inline 
// uint64_t initial_block_subsidy_satoshi() {
//     return bitcoin_to_satoshi(initial_block_subsidy_bitcoin);
// }

// #ifdef KTH_CURRENCY_LTC
// // constexpr uint64_t reward_interval = 840000;
// constexpr uint64_t retarget_subsidy_interval = 840000;
// constexpr uint64_t no_retarget_subsidy_interval = 150; // TODO: merge version3. check the no_retarget (regtest) value for LTC 
// #else //KTH_CURRENCY_LTC
// // constexpr uint64_t reward_interval = 210000;
// constexpr uint64_t retarget_subsidy_interval = 210000;
// constexpr uint64_t no_retarget_subsidy_interval = 150;
// #endif //KTH_CURRENCY_LTC

// constexpr uint64_t recursive_money = 0x02540be3f5;

// constexpr uint64_t subsidy_interval(bool retarget=true)
// {
//     return retarget ? retarget_subsidy_interval : no_retarget_subsidy_interval;
// }

// constexpr uint64_t max_money(bool retarget=true)
// {
//     ////// Optimize out the derivation of recursive_money.
//     ////BITCOIN_ASSERT(recursive_money == max_money_recursive(
//     ////    initial_block_subsidy_satoshi()));

//     return recursive_money * subsidy_interval(retarget);
// }

} // namespace kth

#endif
