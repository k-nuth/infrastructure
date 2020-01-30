# Copyright (c) 2016-2020 Knuth Project developers.
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
        "with_tests": [True, False],
        "with_examples": [True, False],
        "microarchitecture": "ANY", #["x86_64", "haswell", "ivybridge", "sandybridge", "bulldozer", ...]
        "fix_march": [True, False],
        "march_id": "ANY",
        "verbose": [True, False],
        "cxxflags": "ANY",
        "cflags": "ANY",
        "glibcxx_supports_cxx11_abi": "ANY",
        "cmake_export_compile_commands": [True, False],
    }

    default_options = "shared=False", \
        "fPIC=True", \
        "with_icu=False", \
        "with_png=False", \
        "with_qrencode=False", \
        "with_tests=False", \
        "with_examples=False", \
        "microarchitecture=_DUMMY_",  \
        "fix_march=False", \
        "march_id=_DUMMY_",  \
        "verbose=False", \
        "cxxflags=_DUMMY_", \
        "cflags=_DUMMY_", \
        "glibcxx_supports_cxx11_abi=_DUMMY_", \
        "cmake_export_compile_commands=False"

    generators = "cmake"
    exports = "conan_*", "ci_utils/*"
    exports_sources = "src/*", "CMakeLists.txt", "cmake/*", "kth-infrastructureConfig.cmake.in", "include/*", "test/*", "examples/*", "test_new/*"
    package_files = "build/lkth-infrastructure.a"
    build_policy = "missing"

    def requirements(self):
        self.requires("boost/1.72.0@kth/stable")
        self.requires("secp256k1/0.X@%s/%s" % (self.user, self.channel))

        if self.options.with_png:
            self.requires("libpng/1.6.34@kth/stable")

        if self.options.with_qrencode:
            self.requires("libqrencode/4.0.0@kth/stable")

    def config_options(self):
        KnuthConanFile.config_options(self)

    def configure(self):
        # self.output.info("libcxx: %s" % (str(self.settings.compiler.libcxx),))
        KnuthConanFile.configure(self)

    def package_id(self):
        KnuthConanFile.package_id(self)
        self.info.options.with_tests = "ANY"
        self.info.options.with_examples = "ANY"
        self.info.options.cmake_export_compile_commands = "ANY"

    # default_options = "shared=False", \
    #     "fPIC=True", \
    #     "with_icu=False", \
    #     "with_png=False", \
    #     "with_qrencode=False", \
    #     "microarchitecture=_DUMMY_",  \
    #     "glibcxx_supports_cxx11_abi=_DUMMY_"

    def build(self):
        cmake = self.cmake_basis()
        cmake.definitions["WITH_TESTS"] = option_on_off(self.options.with_tests)
        cmake.definitions["WITH_TESTS_NEW"] = option_on_off(self.options.with_tests)
        cmake.definitions["WITH_EXAMPLES"] = option_on_off(self.options.with_examples)
        cmake.definitions["WITH_ICU"] = option_on_off(self.options.with_icu)
        # cmake.definitions["WITH_QRENCODE"] = option_on_off(self.options.with_qrencode)
        # cmake.definitions["WITH_PNG"] = option_on_off(self.options.with_qrencode)
        cmake.definitions["WITH_QRENCODE"] = option_on_off(self.options.with_qrencode)
        cmake.definitions["WITH_PNG"] = option_on_off(self.options.with_png)

        if self.options.cmake_export_compile_commands:
            cmake.definitions["CMAKE_EXPORT_COMPILE_COMMANDS"] = option_on_off(self.options.cmake_export_compile_commands)

        cmake.configure(source_dir=self.source_folder)

        if not self.options.cmake_export_compile_commands:
            cmake.build()

            #Note: Cmake Tests and Visual Studio doesn't work
            if self.options.with_tests:
                cmake.test()
                # cmake.test(target="tests")


    # def build(self):
    #     # for dep in self.deps_cpp_info.deps:
    #     #     # self.output.warn(self.deps_cpp_info["MyLib"].libdirs)
    #     #     print(dep)
    #     #     print(self.options[dep])
    #     #     # self.options["boost"]

        # cmake = CMake(self)
        # cmake.definitions["USE_CONAN"] = option_on_off(True)
        # cmake.definitions["NO_CONAN_AT_ALL"] = option_on_off(False)
        # cmake.verbose = self.options.verbose
        # cmake.definitions["ENABLE_SHARED"] = option_on_off(self.is_shared)
        # cmake.definitions["ENABLE_POSITION_INDEPENDENT_CODE"] = option_on_off(self.fPIC_enabled)

        # cmake.definitions["WITH_TESTS"] = option_on_off(self.options.with_tests)
        # cmake.definitions["WITH_TESTS_NEW"] = option_on_off(self.options.with_tests)
        # cmake.definitions["WITH_EXAMPLES"] = option_on_off(self.options.with_examples)
        # cmake.definitions["WITH_ICU"] = option_on_off(self.options.with_icu)
        # # cmake.definitions["WITH_QRENCODE"] = option_on_off(self.options.with_qrencode)
        # # cmake.definitions["WITH_PNG"] = option_on_off(self.options.with_qrencode)

        # cmake.definitions["WITH_QRENCODE"] = option_on_off(self.options.with_qrencode)
        # cmake.definitions["WITH_PNG"] = option_on_off(self.options.with_png)

        # if self.options.cxxflags != "_DUMMY_":
        #     cmake.definitions["CONAN_CXX_FLAGS"] = cmake.definitions.get("CONAN_CXX_FLAGS", "") + " " + str(self.options.cxxflags)
        # if self.options.cflags != "_DUMMY_":
        #     cmake.definitions["CONAN_C_FLAGS"] = cmake.definitions.get("CONAN_C_FLAGS", "") + " " + str(self.options.cflags)

        # if self.settings.compiler != "Visual Studio":
        #     # cmake.definitions["CONAN_CXX_FLAGS"] += " -Wno-deprecated-declarations"
        #     cmake.definitions["CONAN_CXX_FLAGS"] = cmake.definitions.get("CONAN_CXX_FLAGS", "") + " -Wno-deprecated-declarations"

        # if self.settings.compiler == "Visual Studio":
        #     cmake.definitions["CONAN_CXX_FLAGS"] = cmake.definitions.get("CONAN_CXX_FLAGS", "") + " /DBOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE"

        # cmake.definitions["MICROARCHITECTURE"] = self.options.microarchitecture
        # cmake.definitions["MARCH_ID"] = self.options.march_id

        # cmake.definitions["KTH_PROJECT_VERSION"] = self.version

        # if self.settings.compiler == "gcc":
        #     if float(str(self.settings.compiler.version)) >= 5:
        #         cmake.definitions["NOT_USE_CPP11_ABI"] = option_on_off(False)
        #     else:
        #         cmake.definitions["NOT_USE_CPP11_ABI"] = option_on_off(True)
        # elif self.settings.compiler == "clang":
        #     if str(self.settings.compiler.libcxx) == "libstdc++" or str(self.settings.compiler.libcxx) == "libstdc++11":
        #         cmake.definitions["NOT_USE_CPP11_ABI"] = option_on_off(False)

        # pass_march_to_compiler(self, cmake)

        # cmake.configure(source_dir=self.source_folder)

        # # self.output.info("CONAN_CXX_FLAGS: %s" % (cmake.definitions["CONAN_CXX_FLAGS"], ))
        # # self.output.info("cmake.command_line: %s" % (cmake.command_line, ))

        # cmake.build()

        # #Note: Cmake Tests and Visual Studio doesn't work
        # if self.options.with_tests:
        #     cmake.test()
        #     # cmake.test(target="tests")

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

        if self.settings.os == "Windows" and self.settings.compiler == "gcc": # MinGW
            self.cpp_info.libs.append("ws2_32")
            self.cpp_info.libs.append("wsock32")

        if not self.is_shared:
            self.cpp_info.defines.append("BI_STATIC")
