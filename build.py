import os
from conan.packager import ConanMultiPackager

if __name__ == "__main__":
    print('-*-*-*-*-* FROM PYTHON -*-*-*-*-*-*-*')
    print(os.getenv('BITPRIM_BUILD_NUMBER', '-'))
    print('-*-*-*-*-* FROM PYTHON -*-*-*-*-*-*-*')

    builder = ConanMultiPackager(username="bitprim", channel="testing",
                                 remotes="https://api.bintray.com/conan/bitprim/bitprim",
                                 archs=["x86_64"])

    builder.add_common_builds(shared_option_name="bitprim-core:shared")

    filtered_builds = []
    for settings, options, env_vars, build_requires in builder.builds:

        build_number = os.getenv('BITPRIM_BUILD_NUMBER', '-')

        print(env_vars)
        env_vars["BITPRIM_BUILD_NUMBER"] = build_number
        print(env_vars)

        if settings["build_type"] == "Release" \
                and not options["bitprim-core:shared"] \
                and (not "compiler.runtime" in settings or not settings["compiler.runtime"] == "MT"):
            filtered_builds.append([settings, options, env_vars, build_requires])

    builder.builds = filtered_builds
    builder.run()
