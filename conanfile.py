# Copyright (c) 2016-2022 Knuth Project developers.
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import os
from conans import CMake
from kthbuild import option_on_off, march_conan_manip, pass_march_to_compiler
from kthbuild import KnuthConanFile

class KnuthInfrastructureConan(KnuthConanFile):
    def recipe_dir(self):
        return os.path.dirname(os.path.abspath(__file__))

    name = "infrastructure"
    # version = get_version()
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
        "microarchitecture": "ANY", #["x86_64", "haswell", "ivybridge", "sandybridge", "bulldozer", ...]
        "fix_march": [True, False],
        "march_id": "ANY",
        "verbose": [True, False],
        "cxxflags": "ANY",
        "cflags": "ANY",
        "glibcxx_supports_cxx11_abi": "ANY",
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
        "microarchitecture": "_DUMMY_",
        "fix_march": False,
        "march_id": "_DUMMY_",
        "verbose": False,
        "cxxflags": "_DUMMY_",
        "cflags": "_DUMMY_",
        "glibcxx_supports_cxx11_abi": "_DUMMY_",
        "cmake_export_compile_commands": False,
        "log": "spdlog",
        "asio_standalone": False,
    }

    generators = "cmake"
    exports = "conan_*", "ci_utils/*"
    exports_sources = "src/*", "CMakeLists.txt", "cmake/*", "kth-infrastructureConfig.cmake.in", "include/*", "test/*", "examples/*", "test_new/*"
    package_files = "build/lkth-infrastructure.a"
    build_policy = "missing"

    def requirements(self):
        self.requires("secp256k1/0.X@%s/%s" % (self.user, self.channel))

        self.requires("boost/1.78.0")
        self.requires("fmt/8.1.1")

        if self.options.tests:
            self.requires("catch2/2.13.8")

        if self.options.log == "binlog":
            self.requires("binlog/2020.02.29@kth/stable")
        elif self.options.log == "spdlog":
            self.requires("spdlog/1.9.1")

        if self.options.with_png:
            self.requires("libpng/1.6.34@kth/stable")

        if self.options.with_qrencode:
            self.requires("libqrencode/4.0.0@kth/stable")

        if self.options.asio_standalone:
            self.requires("asio/1.19.2")


    def config_options(self):
        KnuthConanFile.config_options(self)

    def configure(self):
        # self.output.info("libcxx: %s" % (str(self.settings.compiler.libcxx),))
        KnuthConanFile.configure(self)
        self.options["fmt"].header_only = True

        if self.options.log == "spdlog":
            self.options["spdlog"].header_only = True

        # if self.options.log != "boost":
        #     self.options["boost"].without_filesystem = True
        #     self.options["boost"].without_log = True

        # self.options["*"].log = self.options.log
        self.output.info("Compiling with log: %s" % (self.options.log,))

    def package_id(self):
        KnuthConanFile.package_id(self)

    def build(self):
        cmake = self.cmake_basis()
        cmake.definitions["WITH_ICU"] = option_on_off(self.options.with_icu)
        # cmake.definitions["WITH_QRENCODE"] = option_on_off(self.options.with_qrencode)
        # cmake.definitions["WITH_PNG"] = option_on_off(self.options.with_qrencode)
        cmake.definitions["WITH_QRENCODE"] = option_on_off(self.options.with_qrencode)
        cmake.definitions["WITH_PNG"] = option_on_off(self.options.with_png)
        cmake.definitions["LOG_LIBRARY"] = self.options.log

        cmake.configure(source_dir=self.source_folder)

        if not self.options.cmake_export_compile_commands:
            cmake.build()
            #Note: Cmake Tests and Visual Studio doesn't work
            if self.options.tests:
                cmake.test()
                # cmake.test(target="tests")

    def imports(self):
        self.copy("*.h", "", "include")

    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.hpp", dst="include", src="include")
        self.copy("*.ipp", dst="include", src="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

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
