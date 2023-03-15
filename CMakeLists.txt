# Copyright (c) 2016-2023 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

cmake_minimum_required(VERSION 3.15)

project(kth-infrastructure VERSION 0 LANGUAGES CXX C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_SHARED "" OFF)
option(ENABLE_POSITION_INDEPENDENT_CODE "Enable POSITION_INDEPENDENT_CODE property" ON)
option(WITH_TESTS "Compile with unit tests." ON)
option(WITH_EXAMPLES "Compile with examples." OFF)
option(WITH_ICU "Compile with International Components for Unicode." OFF)
option(WITH_PNG "Compile with Libpng support." OFF)
option(WITH_QRENCODE "Compile with QREncode." OFF)
# option(LOG_LIBRARY "Setting for the logging library." OFF)
option(JUST_KTH_SOURCES "Just Knuth source code to be linted." OFF)


if (WITH_ICU)
  add_definitions(-DWITH_ICU -DBOOST_HAS_ICU)
endif()

if (WITH_PNG)
  add_definitions(-DWITH_PNG)
endif()

if (WITH_QRENCODE)
  add_definitions(-DWITH_QRENCODE)
endif()

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

if (JUST_KTH_SOURCES)
  message(STATUS "Knuth: Just Knuth source code to be linted: enabled")
endif()


set(MICROARCHITECTURE "x86_64" CACHE STRING "Specify the Microarchitecture (x86_64|...).")
message( STATUS "Knuth: Compiling for ${MICROARCHITECTURE}")

set(MARCH_ID "" CACHE STRING "Specify the Microarchitecture ID (x86_64|...).")
message( STATUS "Knuth: Compiling for Microarchitecture ID ${MARCH_ID}")

message( STATUS "Knuth: CONAN_CXX_FLAGS ${CONAN_CXX_FLAGS}")
message( STATUS "Knuth: CONAN_C_FLAGS ${CONAN_C_FLAGS}")

set(Boost_DEBUG ON)


find_package(Threads REQUIRED)
find_package(secp256k1 REQUIRED)
find_package(Boost 1.81.0 COMPONENTS program_options REQUIRED)
find_package(Boost 1.81.0 COMPONENTS thread REQUIRED)
find_package(fmt 9.1.0 REQUIRED)
find_package(spdlog 1.10.0 REQUIRED)

include(CheckCXXCompilerFlag)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/ci_utils/cmake)
include(KnuthTools)

if (NOT MSVC)
  _add_c_compile_flag(-Wall _has_all_warning_flag)
else()
  _add_c_compile_flag(-W4 _has_all_warning_flag)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

if (NOT MSVC)
  _add_c_compile_flag(-Wextra _has_extra_warning_flag)
endif()

_add_c_compile_flag(-Wpedantic _has_pedantic_warning_flag)
if (_has_pedantic_warning_flag)
  _add_c_compile_flag(-pedantic _has_pedantic_flag)
endif()

_add_cxx_compile_flag(-Wno-missing-braces _has_no_missing_braces_warning_flag)
_add_cxx_compile_flag(-Wno-mismatched-tags _has_no_mismatched_tags_warning_flag)
_add_c_compile_flag(-Wno-deprecated-declarations _has_no_deprecated_declarations_warning_flag)
_add_link_flag(-fstack-protector _has_stack_protector_flag)
_add_link_flag(-fstack-protector-all _has_stack_protector_all_flag)
_add_cxx_compile_flag(-fvisibility-hidden _has_visibility_hidden_flag)
_add_cxx_compile_flag(-fvisibility-inlines-hidden _has_visibility_inlines_hidden_flag)

if (MSVC)
  add_definitions(-D_WIN32_WINNT=0x0600)
endif()

set(MODE STATIC)
if (ENABLE_SHARED)
  set(MODE SHARED)
endif()

set(kth_infrastructure_sources_just_legacy
        src/machine/number.cpp

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

add_library(${PROJECT_NAME} ${MODE} ${kth_infrastructure_sources})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX CXX_STANDARD 20 CXX_STANDARD_REQUIRED TRUE)

if (ENABLE_POSITION_INDEPENDENT_CODE)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif(ENABLE_POSITION_INDEPENDENT_CODE)


target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

if (NOT ENABLE_SHARED)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DKI_STATIC)
endif()

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${Boost_INCLUDE_DIR})

# if (${CURRENCY} STREQUAL "LTC")
#   target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${OPENSSL_INCLUDE_DIR})
# endif()

target_link_libraries(${PROJECT_NAME} PUBLIC Boost::program_options)
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::thread)
# target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt-header-only)
# target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog_header_only)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_THREAD_LIBS_INIT})

if (MINGW)
    target_link_libraries(${PROJECT_NAME} PUBLIC ws2_32 wsock32)
endif()


target_link_libraries(${PROJECT_NAME} PUBLIC secp256k1::secp256k1)

_group_sources(${PROJECT_NAME} "${CMAKE_CURRENT_LIST_DIR}")

# Tests
# ------------------------------------------------------------------------------
if (WITH_TESTS)
  enable_testing()
  find_package(Catch2 3 REQUIRED)

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

  add_executable(kth_infrastructure_test ${kth_infrastructure_test_sources})

  target_include_directories(kth_infrastructure_test PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/test>)

  target_link_libraries(kth_infrastructure_test PRIVATE kth-infrastructure)
  target_link_libraries(kth_infrastructure_test PRIVATE Catch2::Catch2WithMain)

  include(CTest)
  include(Catch)
  catch_discover_tests(kth_infrastructure_test)
endif()

# Examples
#------------------------------------------------------------------------------
if (WITH_EXAMPLES)
  add_executable(kth_infrastructure_examples
    examples/main.cpp)

  target_link_libraries(kth_infrastructure_examples PUBLIC kth-infrastructure)

  _group_sources(kth_infrastructure_examples "${CMAKE_CURRENT_LIST_DIR}/examples")
endif()

# Install
# ------------------------------------------------------------------------------
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

set(_kth_infrastructure_headers
    kth/infrastructure/compat.h
    kth/infrastructure/compat.hpp
    kth/infrastructure/constants.hpp
    kth/infrastructure/define.hpp
    kth/infrastructure/error.hpp
    kth/infrastructure/handlers.hpp
    kth/infrastructure/path.hpp
    kth/infrastructure/version.hpp

    kth/infrastructure/machine/number.hpp
    kth/infrastructure/machine/script_pattern.hpp
    kth/infrastructure/machine/sighash_algorithm.hpp
    kth/infrastructure/machine/script_version.hpp

    kth/infrastructure/config/authority.hpp
    kth/infrastructure/config/base2.hpp
    kth/infrastructure/config/base16.hpp
    kth/infrastructure/config/base58.hpp
    kth/infrastructure/config/base64.hpp
    kth/infrastructure/config/checkpoint.hpp
    kth/infrastructure/config/directory.hpp
    kth/infrastructure/config/endpoint.hpp
    kth/infrastructure/config/hash160.hpp
    kth/infrastructure/config/hash256.hpp
    kth/infrastructure/config/parameter.hpp
    kth/infrastructure/config/printer.hpp
    kth/infrastructure/config/sodium.hpp

    kth/infrastructure/formats/base_10.hpp
    kth/infrastructure/formats/base_16.hpp
    kth/infrastructure/formats/base_58.hpp
    kth/infrastructure/formats/base_64.hpp
    kth/infrastructure/formats/base_85.hpp

    kth/infrastructure/impl/formats/base_16.ipp
    kth/infrastructure/impl/formats/base_58.ipp

    kth/infrastructure/impl/math/checksum.ipp
    kth/infrastructure/impl/math/hash.ipp

    kth/infrastructure/impl/machine/number.ipp

    kth/infrastructure/math/checksum.hpp
    kth/infrastructure/math/crypto.hpp
    kth/infrastructure/math/elliptic_curve.hpp
    kth/infrastructure/math/hash.hpp
    kth/infrastructure/math/sip_hash.hpp
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
# ------------------------------------------------------------------------------
include(CMakePackageConfigHelpers)

export(EXPORT ${PROJECT_NAME}
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")
export(PACKAGE ${PROJECT_NAME})

if (UNIX)
  set(_config_package_location "lib/cmake")
elseif (WIN32)
  set(_config_package_location "cmake")
endif()

install(EXPORT ${PROJECT_NAME}
  FILE kth-infrastructureTargets.cmake
  DESTINATION ${_config_package_location})

configure_file(kth-infrastructureConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  @ONLY)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION ${_config_package_location})
