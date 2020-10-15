# Copyright (c) 2016-2020 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

cmake_minimum_required(VERSION 3.8)

# kth-infrastructure
#==============================================================================
project(kth-infrastructure
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

# Check for baseline language coverage in the compiler for the C++17 standard.
#------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
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

# Implement --log_library.
#------------------------------------------------------------------------------
# option(LOG_LIBRARY "Setting for the logging library." OFF)
# if (LOG_LIBRARY)
#   add_definitions(-DKTH_USE_BINLOG)
# endif()

set(LOG_LIBRARY "boost" CACHE STRING "Setting for the logging library (boost|spdlog|binlog).")

if (${LOG_LIBRARY} STREQUAL "boost")
  add_definitions(-DKTH_LOG_LIBRARY_BOOST)
elseif (${LOG_LIBRARY} STREQUAL "spdlog")
  add_definitions(-DKTH_LOG_LIBRARY_SPDLOG)
elseif (${LOG_LIBRARY} STREQUAL "binlog")
  add_definitions(-DKTH_LOG_LIBRARY_BINLOG)
else()
  message(FATAL_ERROR "Invalid Logging Library: ${LOG_LIBRARY}")
endif()

message(STATUS "Knuth: Logging Library: ${LOG_LIBRARY}")



# Implement --JUST_KTH_SOURCES for linting.
#------------------------------------------------------------------------------
option(JUST_KTH_SOURCES "Just Knuth source code to be linted." OFF)
if (JUST_KTH_SOURCES)
  message(STATUS "Knuth: Just Knuth source code to be linted: enabled")
endif()



set(KTH_PROJECT_VERSION "-" CACHE STRING "Specify the Knuth Project Version.")
# message(${KTH_PROJECT_VERSION})
message( STATUS "Knuth: Compiling version ${KTH_PROJECT_VERSION}")

set(MICROARCHITECTURE "x86_64" CACHE STRING "Specify the Microarchitecture (x86_64|...).")
message( STATUS "Knuth: Compiling for ${MICROARCHITECTURE}")
# add_definitions(-DKTH_MICROARCHITECTURE=${MICROARCHITECTURE})
# add_definitions(-DKTH_MICROARCHITECTURE_STR="${MICROARCHITECTURE}")

set(MARCH_ID "" CACHE STRING "Specify the Microarchitecture ID (x86_64|...).")
message( STATUS "Knuth: Compiling for Microarchitecture ID ${MARCH_ID}")

message( STATUS "Knuth: CONAN_CXX_FLAGS ${CONAN_CXX_FLAGS}")
message( STATUS "Knuth: CONAN_C_FLAGS ${CONAN_C_FLAGS}")




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

# src/kth-infrastructure.la => ${libdir}
#------------------------------------------------------------------------------
set(MODE STATIC)
if (ENABLE_SHARED)
  set(MODE SHARED)
endif()

set(kth_infrastructure_sources_just_legacy 
        src/machine/number.cpp        #Fernando: commented for the moment...

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
        src/config/printer.cpp
        src/config/sodium.cpp

        src/error.cpp
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

        src/wallet/dictionary.cpp
        src/wallet/hd_private.cpp
        src/wallet/hd_public.cpp
        src/wallet/mini_keys.cpp
        src/wallet/mnemonic.cpp

        src/wallet/uri.cpp
    )

  if (${LOG_LIBRARY} STREQUAL "boost")
    set(kth_infrastructure_sources_just_legacy 
      ${kth_infrastructure_sources_just_legacy}
      src/log/file_collector.cpp
      src/log/file_collector_repository.cpp
      src/log/file_counter_formatter.cpp
      src/log/sink.cpp
      src/log/statsd_sink.cpp
      src/log/udp_client_sink.cpp
    )
  endif()

  if (${LOG_LIBRARY} STREQUAL "spdlog")
    set(kth_infrastructure_sources_just_legacy 
      ${kth_infrastructure_sources_just_legacy}
      src/log/sink.cpp
    )
  endif()


# if (${CURRENCY} STREQUAL "LTC")
#     set(knuth_domain_sources_just_knuth 
#     ${knuth_domain_sources_just_knuth}         
#     src/math/external/scrypt.cpp
#     src/math/external/scrypt-sse2.cpp)
# endif()
  
if (WITH_PNG)
  set(kth_infrastructure_sources_just_legacy 
    ${kth_infrastructure_sources_just_legacy}
    src/utility/png.cpp
  )
endif()

if (WITH_QRENCODE)
  set(kth_infrastructure_sources_just_legacy 
    ${kth_infrastructure_sources_just_legacy}
    src/wallet/qrcode.cpp
  )
endif()


set(kth_infrastructure_sources_just_knuth
    # src/math/external/scrypt.cpp
    # src/math/external/scrypt-sse2.cpp
    src/wallet/cashaddr.cpp
)

if (NOT JUST_KTH_SOURCES)
  set(kth_infrastructure_sources 
    ${kth_infrastructure_sources_just_legacy}
  )
endif()

set(kth_infrastructure_sources 
  ${kth_infrastructure_sources}   
  ${kth_infrastructure_sources_just_knuth}         
)

add_library(kth-infrastructure ${MODE} ${kth_infrastructure_sources})

if (ENABLE_POSITION_INDEPENDENT_CODE)
    set_property(TARGET kth-infrastructure PROPERTY POSITION_INDEPENDENT_CODE ON)
endif(ENABLE_POSITION_INDEPENDENT_CODE)



#set_target_properties(kth-infrastructure PROPERTIES CXX_VISIBILITY_PRESET hidden)
#set_target_properties(kth-infrastructure PROPERTIES CXX_VISIBILITY_PRESET internal)

#-fvisibility=default|internal|hidden|protected

# add_library(kth-infrastructure ${MODE}
#        src/wallet/uri.cpp)

target_include_directories(kth-infrastructure PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
  
if (NOT ENABLE_SHARED)
    target_compile_definitions(kth-infrastructure PUBLIC -DKI_STATIC) #TODO(fernando): manage with Conan????
endif()

target_compile_definitions(kth-infrastructure PUBLIC -DKTH_PROJECT_VERSION="${KTH_PROJECT_VERSION}") #TODO(fernando): manage with Conan????

target_include_directories(kth-infrastructure SYSTEM PUBLIC ${Boost_INCLUDE_DIR})

# if (${CURRENCY} STREQUAL "LTC")
#   target_include_directories(kth-infrastructure SYSTEM PUBLIC ${OPENSSL_INCLUDE_DIR})
# endif()

if (NOT NO_CONAN_AT_ALL)
  target_link_libraries(kth-infrastructure PUBLIC ${CONAN_LIBS})
else()
  if (MSVC)
    target_link_libraries(kth-infrastructure PUBLIC
      ${Boost_ATOMIC_LIBRARY}
      ${Boost_LOG_SETUP_LIBRARY}
    )
  endif()

  target_link_libraries(kth-infrastructure PUBLIC
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

target_link_libraries(kth-infrastructure PUBLIC ${CMAKE_THREAD_LIBS_INIT})  #TODO(fernando): manage with Conan????

# if (NO_CONAN_AT_ALL)
    if (MINGW) #(WIN32)
        target_link_libraries(kth-infrastructure PUBLIC ws2_32 wsock32)
    endif()
# endif()

if (WITH_PNG)
    if (NO_CONAN_AT_ALL)
        target_link_libraries(kth-infrastructure PUBLIC png)
    endif (NO_CONAN_AT_ALL)
endif()

# if (${CURRENCY} STREQUAL "LTC")
#   target_link_libraries(kth-infrastructure PUBLIC ${OPENSSL_CRYPTO_LIBRARY})  #TODO(fernando): manage with Conan

#   # OPENSSL_CRYPTO_LIBRARY
#   # OPENSSL_SSL_LIBRARY
#   # OPENSSL_LIBRARIES
# endif()

if (NOT USE_CONAN)
  target_link_libraries(kth-infrastructure PUBLIC secp256k1)
endif()

_group_sources(kth-infrastructure "${CMAKE_CURRENT_LIST_DIR}")

# Tests
#==============================================================================

if (WITH_TESTS)
  enable_testing()
endif()

# local: test/kth_infrastructure_test
#------------------------------------------------------------------------------
if (WITH_TESTS)

  set(kth_infrastructure_test_sources

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

    test/log/log.cpp

    test/machine/number.cpp

    test/math/checksum.cpp
    test/math/elliptic_curve.cpp
    test/math/hash.cpp
    test/math/uint256.cpp

    test/network_address.cpp

    test/unicode/unicode.cpp
    test/unicode/unicode_istream.cpp
    test/unicode/unicode_ostream.cpp

    test/utility/binary.cpp
    test/utility/collection.cpp
    test/utility/data.cpp
    test/utility/endian.cpp
    test/utility/operators.cpp
    test/utility/pseudo_random.cpp
    test/utility/serializer.cpp
    test/utility/stream.cpp
    test/utility/thread.cpp

    test/wallet/hd_private.cpp
    test/wallet/hd_public.cpp
    test/wallet/mnemonic.cpp
    test/wallet/uri.cpp

    test/main.cpp
  )


  if (WITH_PNG)
    set(kth_infrastructure_test_sources 
        ${kth_infrastructure_test_sources}
        src/utility/png.cpp
    )
  endif()

  if (WITH_QRENCODE)
    set(kth_infrastructure_test_sources 
        ${kth_infrastructure_test_sources}
        src/wallet/qrcode.cpp
    )
  endif()

  add_executable(kth_infrastructure_test
                ${kth_infrastructure_test_sources}
  )

  target_include_directories(kth_infrastructure_test PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/test>)

  target_link_libraries(kth_infrastructure_test PUBLIC kth-infrastructure)

  if (WITH_TESTS)
    include(CTest)
    include(Catch)
    catch_discover_tests(kth_infrastructure_test)
  endif()


#   _group_sources(kth_infrastructure_test "${CMAKE_CURRENT_LIST_DIR}/test")

# #    TODO(fernando): chequear si hay nuevos tests en los makefiles (no Cmake)
#   _add_tests(kth_infrastructure_test

#     # address_tests
#     # alert_payload_tests
#     # alert_tests
#     authority_tests
#     # base_10_tests
#     base_16_tests
#     base_58_tests
#     base_64_tests
#     base_85_tests
#     base58_tests

#     binary_tests
#     # bitcoin_uri_tests
#     # chain_block_tests
#     # message_block_tests
#     # block_transactions_tests
#     checkpoint_tests
#     checksum_tests
#     collection_tests
#     # compact_block_tests
#     data_tests

#     # ec_private_tests
#     # ec_public_tests # no test cases
#     elliptic_curve_tests
#     # encrypted_tests
#     endian_tests

#     endpoint_tests


#     # fee_filter_tests
#     # filter_add_tests
#     # filter_clear_tests
#     # filter_load_tests
#     # get_address_tests
#     # get_block_transactions_tests
#     # get_blocks_tests
#     # get_data_tests
#     # get_headers_tests
#     # hash_number_tests
#     hash_tests
#     hd_private_tests
#     hd_public_tests
#     # chain_header_tests
#     # headers_tests
#     # heading_tests
#     # input_tests
#     # inventory_tests
#     # inventory_vector_tests

#     log_tests

#     # memory_pool_tests
#     # merkle_block_tests
#     # message_tests
#     mnemonic_tests
#     network_address_tests
#     # not_found_tests
#     # output_tests
#     parameter_tests
#     # payment_address_tests
#     # ping_tests
#     # point_tests
#     # pong_tests
#     # prefilled_transaction_tests
#     printer_tests
#     pseudo_random_tests

#     # reject_tests
#     # script_number_tests
#     # script_tests
#     # send_compact_blocks_tests
#     # send_headers_tests

#     serializer_tests
#     # stealth_address_tests
#     # stealth_tests
#     stream_tests
#     thread_tests
#     # chain_transaction_tests
#     # message_transaction_tests
#     unicode_istream_tests
#     unicode_ostream_tests
#     unicode_tests
#     # uri_reader_tests
#     uri_tests
#     # verack_tests
#     # version_tests
#     # transaction_functions_tests
#   )

  # if (WITH_PNG)
  #   _add_tests(kth_infrastructure_test png_tests)
  # endif()

  # if (WITH_QRENCODE)
  #   _add_tests(kth_infrastructure_test qrcode_tests)
  # endif()
endif()

# Examples
#==============================================================================
# local: examples/kth_infrastructure_examples
#------------------------------------------------------------------------------
if (WITH_EXAMPLES)
  add_executable(kth_infrastructure_examples
    examples/main.cpp)

  target_link_libraries(kth_infrastructure_examples PUBLIC kth-infrastructure)

  _group_sources(kth_infrastructure_examples "${CMAKE_CURRENT_LIST_DIR}/examples")
endif()

# Install
#==============================================================================
install(TARGETS kth-infrastructure EXPORT kth-infrastructure
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

#install(EXPORT kth-infrastructureTargets
#
#)

set(_kth_infrastructure_headers
    kth/infrastructure/compat.h
    kth/infrastructure/compat.hpp
    kth/infrastructure/constants.hpp
    kth/infrastructure/define.hpp
    kth/infrastructure/error.hpp
    kth/infrastructure/handlers.hpp
    kth/infrastructure/version.hpp

    kth/infrastructure/machine/interpreter.hpp
    kth/infrastructure/machine/number.hpp    
    kth/infrastructure/machine/program.hpp
    kth/infrastructure/machine/script_pattern.hpp
    kth/infrastructure/machine/sighash_algorithm.hpp
    kth/infrastructure/machine/script_version.hpp

    kth/infrastructure/config/authority.hpp
    kth/infrastructure/config/base16.hpp
    kth/infrastructure/config/base2.hpp
    kth/infrastructure/config/base58.hpp
    kth/infrastructure/config/base64.hpp
    kth/infrastructure/config/checkpoint.hpp
    kth/infrastructure/config/directory.hpp
    kth/infrastructure/config/endpoint.hpp
    kth/infrastructure/config/hash160.hpp
    kth/infrastructure/config/hash256.hpp
    kth/infrastructure/config/parameter.hpp
    kth/infrastructure/config/printer.hpp
    kth/infrastructure/config/settings.hpp
    kth/infrastructure/config/sodium.hpp

    kth/infrastructure/config/header.hpp
    kth/infrastructure/config/input.hpp
    kth/infrastructure/config/output.hpp
    kth/infrastructure/config/transaction.hpp
    kth/infrastructure/config/script.hpp
    kth/infrastructure/config/ec_private.hpp
    kth/infrastructure/config/endorsement.hpp


    kth/infrastructure/formats/base_10.hpp
    kth/infrastructure/formats/base_16.hpp
    kth/infrastructure/formats/base_58.hpp
    kth/infrastructure/formats/base_64.hpp
    kth/infrastructure/formats/base_85.hpp

    kth/infrastructure/impl/formats/base_16.ipp
    kth/infrastructure/impl/formats/base_58.ipp
   
    kth/infrastructure/impl/math/checksum.ipp
    kth/infrastructure/impl/math/hash.ipp

    kth/infrastructure/impl/machine/interpreter.ipp
    kth/infrastructure/impl/machine/number.ipp
    kth/infrastructure/impl/machine/program.ipp

    kth/infrastructure/math/checksum.hpp
    kth/infrastructure/math/crypto.hpp
    kth/infrastructure/math/elliptic_curve.hpp
    kth/infrastructure/math/hash.hpp
    kth/infrastructure/math/stealth.hpp
    kth/infrastructure/math/uint256.hpp

    kth/infrastructure/impl/utility/array_slice.ipp
    kth/infrastructure/impl/utility/collection.ipp
    kth/infrastructure/impl/utility/data.ipp
    kth/infrastructure/impl/utility/deserializer.ipp
    kth/infrastructure/impl/utility/endian.ipp
    kth/infrastructure/impl/utility/istream_reader.ipp
    kth/infrastructure/impl/utility/ostream_writer.ipp
    kth/infrastructure/impl/utility/pending.ipp
    kth/infrastructure/impl/utility/resubscriber.ipp
    kth/infrastructure/impl/utility/serializer.ipp
    kth/infrastructure/impl/utility/subscriber.ipp
    kth/infrastructure/impl/utility/string.ipp
    kth/infrastructure/impl/utility/track.ipp

    kth/infrastructure/message/message_tools.hpp

    kth/infrastructure/unicode/console_streambuf.hpp
    kth/infrastructure/unicode/file_lock.hpp
    kth/infrastructure/unicode/ifstream.hpp
    kth/infrastructure/unicode/ofstream.hpp
    kth/infrastructure/unicode/unicode.hpp
    kth/infrastructure/unicode/unicode_istream.hpp
    kth/infrastructure/unicode/unicode_ostream.hpp
    kth/infrastructure/unicode/unicode_streambuf.hpp

    kth/infrastructure/utility/array_slice.hpp
    kth/infrastructure/utility/asio.hpp
    kth/infrastructure/utility/assert.hpp
    kth/infrastructure/utility/atomic.hpp
    kth/infrastructure/utility/binary.hpp
    kth/infrastructure/utility/collection.hpp
    kth/infrastructure/utility/color.hpp
    kth/infrastructure/utility/conditional_lock.hpp
    kth/infrastructure/utility/container_sink.hpp
    kth/infrastructure/utility/container_source.hpp
    kth/infrastructure/utility/data.hpp
    kth/infrastructure/utility/deadline.hpp
    kth/infrastructure/utility/decorator.hpp
    kth/infrastructure/utility/delegates.hpp
    kth/infrastructure/utility/deserializer.hpp
    kth/infrastructure/utility/dispatcher.hpp
    kth/infrastructure/utility/enable_shared_from_base.hpp
    kth/infrastructure/utility/endian.hpp
    kth/infrastructure/utility/exceptions.hpp
    kth/infrastructure/utility/flush_lock.hpp
    kth/infrastructure/utility/interprocess_lock.hpp
    kth/infrastructure/utility/istream_reader.hpp
    kth/infrastructure/utility/monitor.hpp
    kth/infrastructure/utility/noncopyable.hpp
    kth/infrastructure/utility/ostream_writer.hpp
    kth/infrastructure/utility/pending.hpp
    kth/infrastructure/utility/png.hpp
    kth/infrastructure/utility/prioritized_mutex.hpp
    kth/infrastructure/utility/pseudo_random.hpp
    kth/infrastructure/utility/reader.hpp
    kth/infrastructure/utility/resubscriber.hpp
    kth/infrastructure/utility/scope_lock.hpp
    kth/infrastructure/utility/sequencer.hpp
    kth/infrastructure/utility/sequential_lock.hpp
    kth/infrastructure/utility/serializer.hpp
    kth/infrastructure/utility/socket.hpp    
    kth/infrastructure/utility/string.hpp
    kth/infrastructure/utility/subscriber.hpp
    kth/infrastructure/utility/synchronizer.hpp
    kth/infrastructure/utility/thread.hpp
    kth/infrastructure/utility/threadpool.hpp
    kth/infrastructure/utility/timer.hpp
    kth/infrastructure/utility/track.hpp
    kth/infrastructure/utility/work.hpp
    kth/infrastructure/utility/writer.hpp
    
    kth/infrastructure/wallet/cashaddr.hpp

    kth/infrastructure/wallet/dictionary.hpp
    kth/infrastructure/wallet/ec_private.hpp
    kth/infrastructure/wallet/ec_public.hpp
    kth/infrastructure/wallet/ek_private.hpp
    kth/infrastructure/wallet/ek_public.hpp
    kth/infrastructure/wallet/ek_token.hpp
    kth/infrastructure/wallet/encrypted_keys.hpp
    kth/infrastructure/wallet/hd_private.hpp
    kth/infrastructure/wallet/hd_public.hpp
    kth/infrastructure/wallet/mini_keys.hpp
    kth/infrastructure/wallet/mnemonic.hpp
    kth/infrastructure/wallet/qrcode.hpp
    kth/infrastructure/wallet/uri.hpp

    kth/infrastructure.hpp
  )

if (${LOG_LIBRARY} STREQUAL "boost")
  set(_kth_infrastructure_headers 
    ${_kth_infrastructure_headers}
    kth/infrastructure/log/attributes.hpp
    kth/infrastructure/log/file_char_traits.hpp
    kth/infrastructure/log/file_collector.hpp
    kth/infrastructure/log/file_collector_repository.hpp
    kth/infrastructure/log/file_counter_formatter.hpp
    kth/infrastructure/log/rotable_file.hpp    
    kth/infrastructure/log/severity.hpp
    kth/infrastructure/log/sink.hpp
    kth/infrastructure/log/source.hpp
    kth/infrastructure/log/statsd_sink.hpp
    kth/infrastructure/log/statsd_source.hpp
    kth/infrastructure/log/udp_client_sink.hpp

    kth/infrastructure/log/features/counter.hpp
    kth/infrastructure/log/features/gauge.hpp
    kth/infrastructure/log/features/metric.hpp
    kth/infrastructure/log/features/rate.hpp
    kth/infrastructure/log/features/timer.hpp

    kth/infrastructure/impl/log/features/counter.ipp
    kth/infrastructure/impl/log/features/gauge.ipp
    kth/infrastructure/impl/log/features/metric.ipp
    kth/infrastructure/impl/log/features/rate.ipp
    kth/infrastructure/impl/log/features/timer.ipp
  )
endif()


foreach (_header ${_kth_infrastructure_headers})
  get_filename_component(_directory "${_header}" DIRECTORY)
  install(FILES "include/${_header}" DESTINATION "include/${_directory}")
endforeach()

# Export
#==============================================================================
include(CMakePackageConfigHelpers)

export(EXPORT kth-infrastructure
  FILE "${CMAKE_CURRENT_BINARY_DIR}/kth-infrastructureTargets.cmake")
export(PACKAGE kth-infrastructure)

if (UNIX)
  set(_config_package_location "lib/cmake")
elseif (WIN32)
  set(_config_package_location "cmake")
endif()

install(EXPORT kth-infrastructure
  FILE kth-infrastructureTargets.cmake
  DESTINATION ${_config_package_location})

configure_file(kth-infrastructureConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/kth-infrastructureConfig.cmake"
  @ONLY)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/kth-infrastructureConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/kth-infrastructureConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/kth-infrastructureConfigVersion.cmake"
  DESTINATION ${_config_package_location})
