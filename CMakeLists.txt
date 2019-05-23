#
# Copyright (c) 2016-2019 Knuth Project.
#
# This file is part of Knuth Project.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.4)

# knuth-infrastructure
#==============================================================================
project(knuth-infrastructure
  VERSION 0
  LANGUAGES CXX C)
  # VERSION 0.11.0


#if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
#  # using Clang
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
#  # using GCC
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
#  # using Intel C++
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
#  # using Visual Studio C++
#endif()
#if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#  # using regular Clang or AppleClang
#endif()

# message(CMAKE_CXX_COMPILER_ID)
# message(${CMAKE_CXX_COMPILER_ID})


set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Check for baseline language coverage in the compiler for the C++14 standard.
#------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Process options.
#==============================================================================

# Implement --use-conan
#------------------------------------------------------------------------------
option(USE_CONAN "Use Conan Build Tool." OFF)
option(NO_CONAN_AT_ALL "Conan totally disabled." OFF)

if (NO_CONAN_AT_ALL)
  set(USE_CONAN OFF)
endif()


# Inherit --enable-shared and define BOOST_TEST_DYN_LINK.
#------------------------------------------------------------------------------
option(ENABLE_SHARED "" OFF)

# Implement POSITION_INDEPENDENT_CODE
#------------------------------------------------------------------------------
option(ENABLE_POSITION_INDEPENDENT_CODE "Enable POSITION_INDEPENDENT_CODE property" ON)

# Implement --with-tests and declare WITH_TESTS.
#------------------------------------------------------------------------------
option(WITH_TESTS "Compile with unit tests." ON)
option(WITH_TESTS_NEW "Compile with unit tests." OFF)

# Implement --with-examples and declare WITH_EXAMPLES.
#------------------------------------------------------------------------------
option(WITH_EXAMPLES "Compile with examples." OFF)


# Implement --with-icu and define BOOST_HAS_ICU and output ${icu}.
#------------------------------------------------------------------------------
option(WITH_ICU "Compile with International Components for Unicode." OFF)
if (WITH_ICU)
  add_definitions(-DWITH_ICU -DBOOST_HAS_ICU)
  if (NO_CONAN_AT_ALL)
    message(FATAL_ERROR "WITH_ICU not yet implemented")
  endif (NO_CONAN_AT_ALL)
endif()

# Implement --with-png and output ${png}.
#------------------------------------------------------------------------------
option(WITH_PNG "Compile with Libpng support." OFF)
if (WITH_PNG)
  add_definitions(-DWITH_PNG)
endif()

# Implement --with-qrencode and output ${qrencode}.
#------------------------------------------------------------------------------
option(WITH_QRENCODE "Compile with QREncode." OFF)
if (WITH_QRENCODE)
  add_definitions(-DWITH_QRENCODE)

  if (NO_CONAN_AT_ALL)
    message(FATAL_ERROR "WITH_QRENCODE not yet implemented")
  endif (NO_CONAN_AT_ALL)
endif()


# Implement --JUST_KNUTH_SOURCES for linting.
#------------------------------------------------------------------------------
option(JUST_KNUTH_SOURCES "Just Knuth source code to be linted." OFF)
if (JUST_KNUTH_SOURCES)
  message(STATUS "Knuth: Just Knuth source code to be linted: enabled")
endif()



set(KNUTH_PROJECT_VERSION "-" CACHE STRING "Specify the Knuth Project Version.")
# message(${KNUTH_PROJECT_VERSION})
message( STATUS "Knuth: Compiling version ${KNUTH_PROJECT_VERSION}")

set(MICROARCHITECTURE "x86_64" CACHE STRING "Specify the Microarchitecture (x86_64|...).")
message( STATUS "Knuth: Compiling for ${MICROARCHITECTURE}")
# add_definitions(-DKNUTH_MICROARCHITECTURE=${MICROARCHITECTURE})
# add_definitions(-DKNUTH_MICROARCHITECTURE_STR="${MICROARCHITECTURE}")



# Conan infrastructure
#==============================================================================
if(EXISTS ${CMAKE_SOURCE_DIR}/ci_utils/cmake/knuthbuildinfo.cmake)
    include(${CMAKE_SOURCE_DIR}/ci_utils/cmake/knuthbuildinfo.cmake)
else()
    message( STATUS "knuthbuildinfo doent exists")
endif()




# get_directory_property( DirDefs DIRECTORY ${CMAKE_SOURCE_DIR} COMPILE_DEFINITIONS )
# foreach( d ${DirDefs} )
#     message( STATUS "Found Define: " ${d} )
# endforeach()
# message( STATUS "DirDefs: " ${DirDefs} )

# remove_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
# remove_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)

# get_directory_property( DirDefs DIRECTORY ${CMAKE_SOURCE_DIR} COMPILE_DEFINITIONS )
# foreach( d ${DirDefs} )
#     message( STATUS "Found Define: " ${d} )
# endforeach()
# message( STATUS "DirDefs: " ${DirDefs} )


set(Boost_DEBUG ON)

# Check dependencies.
#==============================================================================
#------------------------------------------------------------------------------
if (NO_CONAN_AT_ALL)
  # Require Boost of at least version 1.56.0 and output ${boost_CPPFLAGS/LDFLAGS}.
  #------------------------------------------------------------------------------
  if (NOT ENABLE_SHARED)
    set(Boost_USE_STATIC_LIBS ON)
  endif()

  if (MSVC)
    find_package(
      Boost 1.66.0 REQUIRED
      COMPONENTS atomic chrono date_time filesystem iostreams locale log log_setup program_options system thread unit_test_framework
      # regex
    )
  else()
    find_package(
      Boost 1.66.0 REQUIRED
      COMPONENTS chrono date_time filesystem iostreams locale log program_options system thread unit_test_framework
      # regex
    )
  endif()
endif()



# Require pthread and output ${pthread_CPPFLAGS/LIBS}.
#------------------------------------------------------------------------------
find_package(Threads REQUIRED)  #TODO(fernando): manage with conan

# Require png of at least version 1.6.25 and output ${png_CPPFLAGS/LIBS/PKG}.
#------------------------------------------------------------------------------
if (WITH_PNG)
    if (NO_CONAN_AT_ALL)
        find_package(PNG 1.6.25 REQUIRED)

        add_library(png INTERFACE IMPORTED)
        set_target_properties(png PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${PNG_INCLUDE_DIRS}"
            INTERFACE_LINK_LIBRARIES "${PNG_LIBRARIES}"
            INTERFACE_COMPILE_DEFINITIONS "${PNG_DEFINITIONS}")
    endif(NO_CONAN_AT_ALL)
endif()



# Require rt if on linux and output ${rt_LIBS}.
#------------------------------------------------------------------------------

# Require icu-i18n of at least version 51.2 and output ${icu_i18n_CPPFLAGS/LIBS/PKG}.
#------------------------------------------------------------------------------

# Require qrencode of at least version 3.4.4 and output ${qrencode_CPPFLAGS/LIBS/PKG}.



if (NOT USE_CONAN)
# Require secp256k1 of at least version 0 and output ${secp256k1_CPPFLAGS/LIBS/PKG}.
#------------------------------------------------------------------------------
  if (NOT TARGET secp256k1)
    find_package(secp256k1 0 REQUIRED) 
  endif()
endif()


# Set flags.
#==============================================================================
include(CheckCXXCompilerFlag)

# Including common functions
#------------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/ci_utils/cmake)

include(KnuthTools)


# Warn on all stuff.
#------------------------------------------------------------------------------
if (NOT MSVC)
  _add_c_compile_flag(-Wall _has_all_warning_flag)
else()
  _add_c_compile_flag(-W4 _has_all_warning_flag)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Warn on extra stuff.
#------------------------------------------------------------------------------
if (NOT MSVC)
  _add_c_compile_flag(-Wextra _has_extra_warning_flag)
endif()

# Be really annoying.
#------------------------------------------------------------------------------
_add_c_compile_flag(-Wpedantic _has_pedantic_warning_flag)
if (_has_pedantic_warning_flag)
  _add_c_compile_flag(-pedantic _has_pedantic_flag)
endif()

# Conform to style.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-Wno-missing-braces _has_no_missing_braces_warning_flag)

# Conflict in stdlib under clang. Enabled in clang only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-Wno-mismatched-tags _has_no_mismatched_tags_warning_flag)

# Clean up boost 1.55 headers. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_c_compile_flag(-Wno-deprecated-declarations _has_no_deprecated_declarations_warning_flag)

# Protect stack.
#------------------------------------------------------------------------------
_add_link_flag(-fstack-protector _has_stack_protector_flag)

# Protect stack comprehensively.
#------------------------------------------------------------------------------
_add_link_flag(-fstack-protector-all _has_stack_protector_all_flag)

# Hide internal functions from external libs. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-fvisibility-hidden _has_visibility_hidden_flag)

# Hide inlines from external libs. Enabled in gcc only.
#------------------------------------------------------------------------------
_add_cxx_compile_flag(-fvisibility-inlines-hidden _has_visibility_inlines_hidden_flag)

# Target Windows Vista. Enabled in msvc only.
#------------------------------------------------------------------------------
if (MSVC) # OR MINGW)
  add_definitions(-D_WIN32_WINNT=0x0600)
endif()

# Build
#==============================================================================

# src/knuth-infrastructure.la => ${libdir}
#------------------------------------------------------------------------------
set(MODE STATIC)
if (ENABLE_SHARED)
  set(MODE SHARED)
endif()

set(knuth_infrastructure_sources_just_libbitcoin 
        # src/machine/interpreter.cpp
        src/machine/number.cpp        #Fernando: commented for the moment...
        # src/machine/opcode.cpp
        # src/machine/operation.cpp
        # src/machine/program.cpp

        src/config/authority.cpp
        src/config/base16.cpp
        src/config/base2.cpp
        src/config/base58.cpp
        src/config/base64.cpp
        src/config/checkpoint.cpp
        src/config/directory.cpp
        src/config/endpoint.cpp
        src/config/hash160.cpp
        src/config/hash256.cpp
        src/config/parameter.cpp
        # src/config/parser.cpp
        src/config/printer.cpp
        src/config/sodium.cpp

        src/error.cpp
        # src/multi_crypto_support.cpp
        src/version.cpp

        src/formats/base_10.cpp
        src/formats/base_16.cpp
        src/formats/base_58.cpp
        src/formats/base_64.cpp
        src/formats/base_85.cpp

        src/math/checksum.cpp
        src/math/crypto.cpp
        src/math/elliptic_curve.cpp
        src/math/hash.cpp
        src/math/secp256k1_initializer.cpp
        src/math/secp256k1_initializer.hpp
        src/math/sip_hash.cpp
        # src/math/stealth.cpp                    #Depends on chain::script
        src/math/external/aes256.h
        src/math/external/crypto_scrypt.h
        src/math/external/hmac_sha256.h
        src/math/external/hmac_sha512.h
        src/math/external/lax_der_parsing.h
        src/math/external/pbkdf2_sha256.h
        src/math/external/pkcs5_pbkdf2.h
        src/math/external/ripemd160.h
        # src/math/external/scrypt.h
        src/math/external/sha1.h
        src/math/external/sha256.h
        src/math/external/sha512.h
        src/math/external/zeroize.h
        src/math/external/aes256.c
        src/math/external/crypto_scrypt.c
        src/math/external/hmac_sha256.c
        src/math/external/hmac_sha512.c
        src/math/external/lax_der_parsing.c
        src/math/external/pbkdf2_sha256.c
        src/math/external/pkcs5_pbkdf2.c
        src/math/external/ripemd160.c
        src/math/external/sha1.c
        src/math/external/sha256.c
        src/math/external/sha512.c
        src/math/external/zeroize.c

        src/log/file_collector.cpp
        src/log/file_collector_repository.cpp
        src/log/file_counter_formatter.cpp
        src/log/sink.cpp
        src/log/statsd_sink.cpp
        src/log/udp_client_sink.cpp
        
        src/message/message_tools.cpp
        src/message/messages.cpp
        src/message/network_address.cpp

        src/unicode/console_streambuf.cpp
        src/unicode/ifstream.cpp
        src/unicode/ofstream.cpp
        src/unicode/unicode.cpp
        src/unicode/unicode_istream.cpp
        src/unicode/unicode_ostream.cpp
        src/unicode/unicode_streambuf.cpp
        
        src/utility/binary.cpp
        src/utility/conditional_lock.cpp
        src/utility/deadline.cpp
        src/utility/dispatcher.cpp
        src/utility/flush_lock.cpp
        src/utility/interprocess_lock.cpp
        src/utility/istream_reader.cpp
        src/utility/monitor.cpp
        src/utility/ostream_writer.cpp
        src/utility/prioritized_mutex.cpp
        src/utility/pseudo_random.cpp
        src/utility/scope_lock.cpp
        src/utility/sequencer.cpp
        src/utility/sequential_lock.cpp
        src/utility/socket.cpp
        src/utility/string.cpp
        src/utility/thread.cpp
        src/utility/threadpool.cpp
        src/utility/work.cpp

        # src/wallet/bitcoin_uri.cpp      #Depends on wallet::payment_address
        src/wallet/dictionary.cpp
        # src/wallet/ec_private.cpp       #Depends on wallet::payment_address
        # src/wallet/ec_public.cpp        #Depends on wallet::payment_address
        # src/wallet/ek_private.cpp         #Depends on wallet::payment_address
        # src/wallet/ek_public.cpp
        # src/wallet/ek_token.cpp
        # src/wallet/encrypted_keys.cpp
        src/wallet/hd_private.cpp
        src/wallet/hd_public.cpp
        # src/wallet/message.cpp
        src/wallet/mini_keys.cpp
        src/wallet/mnemonic.cpp
        # src/wallet/parse_encrypted_keys/parse_encrypted_key.hpp
        # src/wallet/parse_encrypted_keys/parse_encrypted_key.ipp
        # src/wallet/parse_encrypted_keys/parse_encrypted_prefix.hpp
        # src/wallet/parse_encrypted_keys/parse_encrypted_prefix.ipp
        # src/wallet/parse_encrypted_keys/parse_encrypted_private.cpp
        # src/wallet/parse_encrypted_keys/parse_encrypted_private.hpp
        # src/wallet/parse_encrypted_keys/parse_encrypted_public.cpp
        # src/wallet/parse_encrypted_keys/parse_encrypted_public.hpp
        # src/wallet/parse_encrypted_keys/parse_encrypted_token.cpp   # #include <bitcoin/infrastructure/chain/script.hpp>
        # src/wallet/parse_encrypted_keys/parse_encrypted_token.hpp
        # src/wallet/payment_address.cpp

        # src/wallet/select_outputs.cpp   #  #include <bitcoin/infrastructure/chain/points_value.hpp>
        # src/wallet/stealth_address.cpp    # #include <bitcoin/infrastructure/chain/script.hpp>
        # src/wallet/stealth_receiver.cpp # #include <bitcoin/infrastructure/chain/script.hpp>
        # src/wallet/stealth_sender.cpp # #include <bitcoin/infrastructure/chain/script.hpp>
        src/wallet/uri.cpp
      )

# if (${CURRENCY} STREQUAL "LTC")
#     set(knuth_domain_sources_just_knuth 
#     ${knuth_domain_sources_just_knuth}         
#     src/math/external/scrypt.cpp
#     src/math/external/scrypt-sse2.cpp)
# endif()
  
if (WITH_PNG)
  set(knuth_infrastructure_sources_just_libbitcoin 
    ${knuth_infrastructure_sources_just_libbitcoin}
    src/utility/png.cpp
  )
endif()

if (WITH_QRENCODE)
  set(knuth_infrastructure_sources_just_libbitcoin 
    ${knuth_infrastructure_sources_just_libbitcoin}
    src/wallet/qrcode.cpp
  )
endif()


set(knuth_infrastructure_sources_just_knuth
    # src/math/external/scrypt.cpp
    # src/math/external/scrypt-sse2.cpp
    src/wallet/cashaddr.cpp
)

if (NOT JUST_KNUTH_SOURCES)
  set(knuth_infrastructure_sources 
    ${knuth_infrastructure_sources_just_libbitcoin}
  )
endif()

set(knuth_infrastructure_sources 
  ${knuth_infrastructure_sources}   
  ${knuth_infrastructure_sources_just_knuth}         
)

add_library(knuth-infrastructure ${MODE} ${knuth_infrastructure_sources})

if (ENABLE_POSITION_INDEPENDENT_CODE)
    set_property(TARGET knuth-infrastructure PROPERTY POSITION_INDEPENDENT_CODE ON)
endif(ENABLE_POSITION_INDEPENDENT_CODE)



#set_target_properties(knuth-infrastructure PROPERTIES CXX_VISIBILITY_PRESET hidden)
#set_target_properties(knuth-infrastructure PROPERTIES CXX_VISIBILITY_PRESET internal)

#-fvisibility=default|internal|hidden|protected

# add_library(knuth-infrastructure ${MODE}
#        src/wallet/uri.cpp)

target_include_directories(knuth-infrastructure PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
  
if (NOT ENABLE_SHARED)
    target_compile_definitions(knuth-infrastructure PUBLIC -DBI_STATIC) #TODO(fernando): manage with Conan????
endif()

target_compile_definitions(knuth-infrastructure PUBLIC -DKNUTH_PROJECT_VERSION="${KNUTH_PROJECT_VERSION}") #TODO(fernando): manage with Conan????

target_include_directories(knuth-infrastructure SYSTEM PUBLIC ${Boost_INCLUDE_DIR})

# if (${CURRENCY} STREQUAL "LTC")
#   target_include_directories(knuth-infrastructure SYSTEM PUBLIC ${OPENSSL_INCLUDE_DIR})
# endif()

if (NOT NO_CONAN_AT_ALL)
  target_link_libraries(knuth-infrastructure PUBLIC ${CONAN_LIBS})
else()
  if (MSVC)
    target_link_libraries(knuth-infrastructure PUBLIC
      ${Boost_ATOMIC_LIBRARY}
      ${Boost_LOG_SETUP_LIBRARY}
    )
  endif()

  target_link_libraries(knuth-infrastructure PUBLIC
    # ${Boost_CHRONO_LIBRARY}
    ${Boost_DATE_TIME_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_IOSTREAMS_LIBRARY}
    ${Boost_LOCALE_LIBRARY}
    ${Boost_LOG_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    # ${Boost_REGEX_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    # ${Boost_THREAD_LIBRARY}
  )
endif()

target_link_libraries(knuth-infrastructure PUBLIC ${CMAKE_THREAD_LIBS_INIT})  #TODO(fernando): manage with Conan????

# if (NO_CONAN_AT_ALL)
    if (MINGW) #(WIN32)
        target_link_libraries(knuth-infrastructure PUBLIC ws2_32 wsock32)
    endif()
# endif()

if (WITH_PNG)
    if (NO_CONAN_AT_ALL)
        target_link_libraries(knuth-infrastructure PUBLIC png)
    endif (NO_CONAN_AT_ALL)
endif()

# if (${CURRENCY} STREQUAL "LTC")
#   target_link_libraries(knuth-infrastructure PUBLIC ${OPENSSL_CRYPTO_LIBRARY})  #TODO(fernando): manage with Conan

#   # OPENSSL_CRYPTO_LIBRARY
#   # OPENSSL_SSL_LIBRARY
#   # OPENSSL_LIBRARIES
# endif()

if (NOT USE_CONAN)
  target_link_libraries(knuth-infrastructure PUBLIC secp256k1)
endif()

_group_sources(knuth-infrastructure "${CMAKE_CURRENT_LIST_DIR}")

# Tests
#==============================================================================

if (WITH_TESTS OR WITH_TESTS_NEW)
  enable_testing()
endif()

# local: test/knuth_infrastructure_test
#------------------------------------------------------------------------------
if (WITH_TESTS)

  set(knuth_infrastructure_test_sources
        test/config/authority.cpp
        test/config/base58.cpp
        test/config/checkpoint.cpp
        test/config/endpoint.cpp
        test/config/hash256.cpp
        test/config/parameter.cpp
        test/config/printer.cpp

        test/formats/base_10.cpp
        test/formats/base_16.cpp
        test/formats/base_58.cpp
        test/formats/base_64.cpp
        test/formats/base_85.cpp

        test/main.cpp

        # test/math/big_number.cpp
        # test/math/big_number.hppcompact
        test/math/checksum.cpp
        test/math/elliptic_curve.cpp
        test/math/hash.cpp
        test/math/hash.hpp
        # test/math/hash_number.cpp
        # test/math/limits.cpp
        # test/math/script_number.cpp
        # test/math/script_number.hpp
        # test/math/stealth.cpp

        test/unicode/unicode.cpp
        test/unicode/unicode_istream.cpp
        test/unicode/unicode_ostream.cpp
        
        test/utility/binary.cpp
        test/utility/collection.cpp
        test/utility/data.cpp
        test/utility/endian.cpp
        test/utility/png.cpp
        test/utility/pseudo_random.cpp
        test/utility/serializer.cpp
        test/utility/stream.cpp
        test/utility/thread.cpp

        test/wallet/hd_private.cpp
        test/wallet/hd_public.cpp
        test/wallet/mnemonic.cpp
        test/wallet/mnemonic.hpp
        test/wallet/qrcode.cpp
        test/wallet/uri.cpp  
  )


  if (WITH_PNG)
    set(knuth_infrastructure_test_sources 
        ${knuth_infrastructure_test_sources}
        src/utility/png.cpp
    )
  endif()

  if (WITH_QRENCODE)
    set(knuth_infrastructure_test_sources 
        ${knuth_infrastructure_test_sources}
        src/wallet/qrcode.cpp
    )
  endif()

  add_executable(knuth_infrastructure_test
                ${knuth_infrastructure_test_sources}
  )
  target_link_libraries(knuth_infrastructure_test PUBLIC knuth-infrastructure)

_group_sources(knuth_infrastructure_test "${CMAKE_CURRENT_LIST_DIR}/test")

#    TODO(fernando): chequear si hay nuevos tests en los makefiles (no Cmake)
  _add_tests(knuth_infrastructure_test

    # address_tests
    # alert_payload_tests
    # alert_tests
    authority_tests
    # base_10_tests
    base_16_tests
    base_58_tests
    base_64_tests
    base_85_tests
    base58_tests

    binary_tests
    # bitcoin_uri_tests
    # chain_block_tests
    # message_block_tests
    # block_transactions_tests
    checkpoint_tests
    checksum_tests
    collection_tests
    # compact_block_tests
    data_tests

    # ec_private_tests
    # ec_public_tests # no test cases
    elliptic_curve_tests
    # encrypted_tests
    endian_tests

    endpoint_tests


    # fee_filter_tests
    # filter_add_tests
    # filter_clear_tests
    # filter_load_tests
    # get_address_tests
    # get_block_transactions_tests
    # get_blocks_tests
    # get_data_tests
    # get_headers_tests
    # hash_number_tests
    hash_tests
    hd_private_tests
    hd_public_tests
    # chain_header_tests
    # headers_tests
    # heading_tests
    # input_tests
    # inventory_tests
    # inventory_vector_tests
    # memory_pool_tests
    # merkle_block_tests
    # message_tests
    mnemonic_tests
    # network_address_tests
    # not_found_tests
    # output_tests
    parameter_tests
    # payment_address_tests
    # ping_tests
    # point_tests
    # pong_tests
    # prefilled_transaction_tests
    printer_tests
    pseudo_random_tests

    # reject_tests
    # script_number_tests
    # script_tests
    # send_compact_blocks_tests
    # send_headers_tests

    serializer_tests
    # stealth_address_tests
    # stealth_tests
    stream_tests
    thread_tests
    # chain_transaction_tests
    # message_transaction_tests
    unicode_istream_tests
    unicode_ostream_tests
    unicode_tests
    # uri_reader_tests
    uri_tests
    # verack_tests
    # version_tests
    # transaction_functions_tests
  )

  if (WITH_PNG)
    _add_tests(knuth_infrastructure_test png_tests)
  endif()

  if (WITH_QRENCODE)
    _add_tests(knuth_infrastructure_test qrcode_tests)
  endif()
endif()

# if (WITH_TESTS_NEW)
#     add_executable(knuth_infrastructure_test_new
#             test_new/main.cpp
#     )
#     target_link_libraries(knuth_infrastructure_test_new PUBLIC knuth-infrastructure)

#     add_test(NAME knuth_infrastructure_test_new COMMAND knuth_infrastructure_test_new)
# endif()


# Examples
#==============================================================================
# local: examples/knuth_infrastructure_examples
#------------------------------------------------------------------------------
if (WITH_EXAMPLES)
  add_executable(knuth_infrastructure_examples
    examples/main.cpp)

  target_link_libraries(knuth_infrastructure_examples PUBLIC knuth-infrastructure)

  _group_sources(knuth_infrastructure_examples "${CMAKE_CURRENT_LIST_DIR}/examples")
endif()

# Install
#==============================================================================
install(TARGETS knuth-infrastructure EXPORT knuth-infrastructure
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

#install(EXPORT knuth-infrastructureTargets
#
#)

set(_knuth_infrastructure_headers
    # bitcoin/infrastructure/multi_crypto_support.hpp
    bitcoin/infrastructure/compat.h
    bitcoin/infrastructure/compat.hpp
    bitcoin/infrastructure/constants.hpp
    bitcoin/infrastructure/define.hpp
    bitcoin/infrastructure/error.hpp
    bitcoin/infrastructure/handlers.hpp
    bitcoin/infrastructure/version.hpp

    bitcoin/infrastructure/machine/interpreter.hpp
    bitcoin/infrastructure/machine/number.hpp    
    # bitcoin/infrastructure/machine/opcode.hpp
    # bitcoin/infrastructure/machine/operation.hpp
    bitcoin/infrastructure/machine/program.hpp
    # bitcoin/infrastructure/machine/rule_fork.hpp
    bitcoin/infrastructure/machine/script_pattern.hpp
    bitcoin/infrastructure/machine/sighash_algorithm.hpp
    bitcoin/infrastructure/machine/script_version.hpp

    bitcoin/infrastructure/config/authority.hpp
    bitcoin/infrastructure/config/base16.hpp
    bitcoin/infrastructure/config/base2.hpp
    bitcoin/infrastructure/config/base58.hpp
    bitcoin/infrastructure/config/base64.hpp
    bitcoin/infrastructure/config/checkpoint.hpp
    bitcoin/infrastructure/config/directory.hpp
    bitcoin/infrastructure/config/endpoint.hpp
    bitcoin/infrastructure/config/hash160.hpp
    bitcoin/infrastructure/config/hash256.hpp
    bitcoin/infrastructure/config/parameter.hpp
    # bitcoin/infrastructure/config/parser.hpp
    bitcoin/infrastructure/config/printer.hpp
    bitcoin/infrastructure/config/settings.hpp
    bitcoin/infrastructure/config/sodium.hpp

    bitcoin/infrastructure/config/header.hpp
    bitcoin/infrastructure/config/input.hpp
    bitcoin/infrastructure/config/output.hpp
    bitcoin/infrastructure/config/transaction.hpp
    bitcoin/infrastructure/config/script.hpp
    bitcoin/infrastructure/config/ec_private.hpp
    bitcoin/infrastructure/config/endorsement.hpp



    bitcoin/infrastructure/formats/base_10.hpp
    bitcoin/infrastructure/formats/base_16.hpp
    bitcoin/infrastructure/formats/base_58.hpp
    bitcoin/infrastructure/formats/base_64.hpp
    bitcoin/infrastructure/formats/base_85.hpp

    bitcoin/infrastructure/impl/formats/base_16.ipp
    bitcoin/infrastructure/impl/formats/base_58.ipp
   
    bitcoin/infrastructure/impl/math/checksum.ipp
    bitcoin/infrastructure/impl/math/hash.ipp

    bitcoin/infrastructure/impl/machine/interpreter.ipp
    bitcoin/infrastructure/impl/machine/number.ipp
    # bitcoin/infrastructure/impl/machine/operation.ipp
    bitcoin/infrastructure/impl/machine/program.ipp

    bitcoin/infrastructure/math/checksum.hpp
    bitcoin/infrastructure/math/crypto.hpp
    bitcoin/infrastructure/math/elliptic_curve.hpp
    bitcoin/infrastructure/math/hash.hpp
    # bitcoin/infrastructure/math/limits.hpp
    bitcoin/infrastructure/math/stealth.hpp
    bitcoin/infrastructure/math/uint256.hpp

    bitcoin/infrastructure/impl/log/features/counter.ipp
    bitcoin/infrastructure/impl/log/features/gauge.ipp
    bitcoin/infrastructure/impl/log/features/metric.ipp
    bitcoin/infrastructure/impl/log/features/rate.ipp
    bitcoin/infrastructure/impl/log/features/timer.ipp


    bitcoin/infrastructure/impl/utility/array_slice.ipp
    bitcoin/infrastructure/impl/utility/collection.ipp
    bitcoin/infrastructure/impl/utility/data.ipp
    bitcoin/infrastructure/impl/utility/deserializer.ipp
    bitcoin/infrastructure/impl/utility/endian.ipp
    bitcoin/infrastructure/impl/utility/istream_reader.ipp
    bitcoin/infrastructure/impl/utility/ostream_writer.ipp
    bitcoin/infrastructure/impl/utility/pending.ipp
    bitcoin/infrastructure/impl/utility/resubscriber.ipp
    bitcoin/infrastructure/impl/utility/serializer.ipp
    bitcoin/infrastructure/impl/utility/subscriber.ipp
    bitcoin/infrastructure/impl/utility/string.ipp
    bitcoin/infrastructure/impl/utility/track.ipp

    bitcoin/infrastructure/log/attributes.hpp
    bitcoin/infrastructure/log/file_char_traits.hpp
    bitcoin/infrastructure/log/file_collector.hpp
    bitcoin/infrastructure/log/file_collector_repository.hpp
    bitcoin/infrastructure/log/file_counter_formatter.hpp
    bitcoin/infrastructure/log/rotable_file.hpp    
    bitcoin/infrastructure/log/severity.hpp
    bitcoin/infrastructure/log/sink.hpp
    bitcoin/infrastructure/log/source.hpp
    bitcoin/infrastructure/log/statsd_sink.hpp
    bitcoin/infrastructure/log/statsd_source.hpp
    bitcoin/infrastructure/log/udp_client_sink.hpp

    bitcoin/infrastructure/log/features/counter.hpp
    bitcoin/infrastructure/log/features/gauge.hpp
    bitcoin/infrastructure/log/features/metric.hpp
    bitcoin/infrastructure/log/features/rate.hpp
    bitcoin/infrastructure/log/features/timer.hpp

    bitcoin/infrastructure/message/message_tools.hpp

    bitcoin/infrastructure/unicode/console_streambuf.hpp
    bitcoin/infrastructure/unicode/file_lock.hpp
    bitcoin/infrastructure/unicode/ifstream.hpp
    bitcoin/infrastructure/unicode/ofstream.hpp
    bitcoin/infrastructure/unicode/unicode.hpp
    bitcoin/infrastructure/unicode/unicode_istream.hpp
    bitcoin/infrastructure/unicode/unicode_ostream.hpp
    bitcoin/infrastructure/unicode/unicode_streambuf.hpp

    bitcoin/infrastructure/utility/array_slice.hpp
    bitcoin/infrastructure/utility/asio.hpp
    bitcoin/infrastructure/utility/assert.hpp
    bitcoin/infrastructure/utility/atomic.hpp
    bitcoin/infrastructure/utility/binary.hpp
    bitcoin/infrastructure/utility/collection.hpp
    bitcoin/infrastructure/utility/color.hpp
    bitcoin/infrastructure/utility/conditional_lock.hpp
    bitcoin/infrastructure/utility/container_sink.hpp
    bitcoin/infrastructure/utility/container_source.hpp
    bitcoin/infrastructure/utility/data.hpp
    bitcoin/infrastructure/utility/deadline.hpp
    bitcoin/infrastructure/utility/decorator.hpp
    bitcoin/infrastructure/utility/delegates.hpp
    bitcoin/infrastructure/utility/deserializer.hpp
    bitcoin/infrastructure/utility/dispatcher.hpp
    bitcoin/infrastructure/utility/enable_shared_from_base.hpp
    bitcoin/infrastructure/utility/endian.hpp
    bitcoin/infrastructure/utility/exceptions.hpp
    bitcoin/infrastructure/utility/flush_lock.hpp
    bitcoin/infrastructure/utility/interprocess_lock.hpp
    bitcoin/infrastructure/utility/istream_reader.hpp
    bitcoin/infrastructure/utility/monitor.hpp
    bitcoin/infrastructure/utility/noncopyable.hpp
    bitcoin/infrastructure/utility/ostream_writer.hpp
    bitcoin/infrastructure/utility/pending.hpp
    bitcoin/infrastructure/utility/png.hpp
    bitcoin/infrastructure/utility/prioritized_mutex.hpp
    bitcoin/infrastructure/utility/pseudo_random.hpp
    bitcoin/infrastructure/utility/reader.hpp
    bitcoin/infrastructure/utility/resubscriber.hpp
    bitcoin/infrastructure/utility/scope_lock.hpp
    bitcoin/infrastructure/utility/sequencer.hpp
    bitcoin/infrastructure/utility/sequential_lock.hpp
    bitcoin/infrastructure/utility/serializer.hpp
    bitcoin/infrastructure/utility/socket.hpp    
    bitcoin/infrastructure/utility/string.hpp
    bitcoin/infrastructure/utility/subscriber.hpp
    bitcoin/infrastructure/utility/synchronizer.hpp
    bitcoin/infrastructure/utility/thread.hpp
    bitcoin/infrastructure/utility/threadpool.hpp
    bitcoin/infrastructure/utility/timer.hpp
    bitcoin/infrastructure/utility/track.hpp
    bitcoin/infrastructure/utility/work.hpp
    bitcoin/infrastructure/utility/writer.hpp
    
    # bitcoin/infrastructure/wallet/bitcoin_uri.hpp
    
    bitcoin/infrastructure/wallet/cashaddr.hpp

    bitcoin/infrastructure/wallet/dictionary.hpp
    bitcoin/infrastructure/wallet/ec_private.hpp
    bitcoin/infrastructure/wallet/ec_public.hpp
    bitcoin/infrastructure/wallet/ek_private.hpp
    bitcoin/infrastructure/wallet/ek_public.hpp
    bitcoin/infrastructure/wallet/ek_token.hpp
    bitcoin/infrastructure/wallet/encrypted_keys.hpp
    bitcoin/infrastructure/wallet/hd_private.hpp
    bitcoin/infrastructure/wallet/hd_public.hpp
    # bitcoin/infrastructure/wallet/message.hpp
    bitcoin/infrastructure/wallet/mini_keys.hpp
    bitcoin/infrastructure/wallet/mnemonic.hpp
    # bitcoin/infrastructure/wallet/payment_address.hpp
    bitcoin/infrastructure/wallet/qrcode.hpp
    # bitcoin/infrastructure/wallet/select_outputs.hpp
    # bitcoin/infrastructure/wallet/stealth_address.hpp
    # bitcoin/infrastructure/wallet/stealth_receiver.hpp
    # bitcoin/infrastructure/wallet/stealth_sender.hpp
    bitcoin/infrastructure/wallet/uri.hpp
    # bitcoin/infrastructure/wallet/uri_reader.hpp
    # bitcoin/infrastructure/wallet/transaction_functions.hpp

    bitcoin/infrastructure.hpp
    )

foreach (_header ${_knuth_infrastructure_headers})
  get_filename_component(_directory "${_header}" DIRECTORY)
  install(FILES "include/${_header}" DESTINATION "include/${_directory}")
endforeach()

# Export
#==============================================================================
include(CMakePackageConfigHelpers)

export(EXPORT knuth-infrastructure
  FILE "${CMAKE_CURRENT_BINARY_DIR}/knuth-infrastructureTargets.cmake")
export(PACKAGE knuth-infrastructure)

if (UNIX)
  set(_config_package_location "lib/cmake")
elseif (WIN32)
  set(_config_package_location "cmake")
endif()

install(EXPORT knuth-infrastructure
  FILE knuth-infrastructureTargets.cmake
  DESTINATION ${_config_package_location})

configure_file(knuth-infrastructureConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/knuth-infrastructureConfig.cmake"
  @ONLY)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/knuth-infrastructureConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/knuth-infrastructureConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/knuth-infrastructureConfigVersion.cmake"
  DESTINATION ${_config_package_location})
