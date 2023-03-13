# Copyright (c) 2016-2023 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import os
from conan import ConanFile
from conan.tools.build.cppstd import check_min_cppstd
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy #, apply_conandata_patches, export_conandata_patches, get, rm, rmdir
from kthbuild import option_on_off, march_conan_manip, pass_march_to_compiler
from kthbuild import KnuthConanFileV2

required_conan_version = ">=2.0"

class KnuthInfrastructureConan(KnuthConanFileV2):
    name = "infrastructure"
    license = "http://www.boost.org/users/license.html"
    url = "https://github.com/knuth/infrastructure"
    description = "Multicrypto Cross-Platform C++ Development Toolkit"
    settings = "os", "compiler", "build_type", "arch"

    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "with_icu": [True, False],
        "with_png": [True, False],
        "with_qrencode": [True, False],
        "tests": [True, False],
        "examples": [True, False],

        "march_id": ["ANY"],
        "march_strategy": ["download_if_possible", "optimized", "download_or_fail"],

        "verbose": [True, False],
        "cxxflags": ["ANY"],
        "cflags": ["ANY"],
        "glibcxx_supports_cxx11_abi": ["ANY"],
        "cmake_export_compile_commands": [True, False],
        "log": ["boost", "spdlog", "binlog"],
        "asio_standalone": [True, False],
    }

    default_options = {
        "shared": False,
        "fPIC": True,
        "with_icu": False,
        "with_png": False,
        "with_qrencode": False,
        "tests": False,
        "examples": False,
        # "microarchitecture": "_DUMMY_",
        # "fix_march": False,

        "march_id": "_DUMMY_",
        "march_strategy": "download_if_possible",


        "verbose": False,
        "cxxflags": "_DUMMY_",
        "cflags": "_DUMMY_",
        "glibcxx_supports_cxx11_abi": "_DUMMY_",
        "cmake_export_compile_commands": False,
        "log": "spdlog",
        "asio_standalone": False,
    }

    # exports = "conan_*", "ci_utils/*"
    exports_sources = "src/*", "CMakeLists.txt", "ci_utils/cmake/*", "cmake/*", "kth-infrastructureConfig.cmake.in", "include/*", "test/*", "examples/*", "test_new/*"
    # package_files = "build/lkth-infrastructure.a"

    def build_requirements(self):
        if self.options.tests:
            self.test_requires("catch2/3.3.1")

    def requirements(self):
        self.requires("secp256k1/0.16.0")

        self.requires("boost/1.81.0")
        self.requires("fmt/9.1.0")

        if self.options.log == "binlog":
            self.requires("binlog/2020.02.29@kth/stable")
        elif self.options.log == "spdlog":
            self.requires("spdlog/1.11.0")

        if self.options.with_png:
            self.requires("libpng/1.6.34@kth/stable")

        if self.options.with_qrencode:
            self.requires("libqrencode/4.0.0@kth/stable")

        if self.options.asio_standalone:
            self.requires("asio/1.24.0")

    def validate(self):
        KnuthConanFileV2.validate(self)
        if self.info.settings.compiler.cppstd:
            check_min_cppstd(self, "20")

    def config_options(self):
        KnuthConanFileV2.config_options(self)

    def configure(self):
        # self.output.info("libcxx: %s" % (str(self.settings.compiler.libcxx),))
        KnuthConanFileV2.configure(self)
        self.options["fmt"].header_only = True

        if self.options.log == "spdlog":
            self.options["spdlog"].header_only = True

        # if self.options.log != "boost":
        #     self.options["boost"].without_filesystem = True
        #     self.options["boost"].without_log = True

        # self.options["*"].log = self.options.log
        self.output.info("Compiling with log: %s" % (self.options.log,))

    def package_id(self):
        KnuthConanFileV2.package_id(self)

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = self.cmake_toolchain_basis()
        # tc.variables["CMAKE_VERBOSE_MAKEFILE"] = True
        tc.variables["WITH_ICU"] = option_on_off(self.options.with_icu)
        # tc.variables["WITH_QRENCODE"] = option_on_off(self.options.with_qrencode)
        # tc.variables["WITH_PNG"] = option_on_off(self.options.with_qrencode)
        tc.variables["WITH_QRENCODE"] = option_on_off(self.options.with_qrencode)
        tc.variables["WITH_PNG"] = option_on_off(self.options.with_png)
        tc.variables["LOG_LIBRARY"] = self.options.log
        tc.variables["CONAN_DISABLE_CHECK_COMPILER"] = option_on_off(True)
        tc.generate()
        tc = CMakeDeps(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()

        if not self.options.cmake_export_compile_commands:
            cmake.build()
            #Note: Cmake Tests and Visual Studio doesn't work
            if self.options.tests:
                cmake.test()
                # cmake.test(target="tests")

    def imports(self):
        self.copy("*.h", "", "include")

    def package(self):
        cmake = CMake(self)
        cmake.install()
        # rmdir(self, os.path.join(self.package_folder, "lib", "cmake"))
        # rmdir(self, os.path.join(self.package_folder, "lib", "pkgconfig"))
        # rmdir(self, os.path.join(self.package_folder, "res"))
        # rmdir(self, os.path.join(self.package_folder, "share"))

    def package_info(self):
        self.cpp_info.includedirs = ['include']
        self.cpp_info.libs = ["kth-infrastructure"]

        if self.settings.os == "Linux" or self.settings.os == "FreeBSD":
            self.cpp_info.libs.append("pthread")

        if self.settings.os == "Linux" and self.settings.compiler == "gcc" and float(str(self.settings.compiler.version)) <= 8:
            self.cpp_info.libs.append("stdc++fs")

        if self.settings.os == "Windows" and self.settings.compiler == "gcc": # MinGW
            self.cpp_info.libs.append("ws2_32")
            self.cpp_info.libs.append("wsock32")

        if not self.is_shared:
            self.cpp_info.defines.append("KI_STATIC")
