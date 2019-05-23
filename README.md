# Knuth Infrastructure <a target="_blank" href="http://semver.org">![Version][badge.version]</a> <a target="_blank" href="https://travis-ci.org/knuth/knuth-infrastructure">![Travis status][badge.Travis]</a> <a target="_blank" href="https://ci.appveyor.com/project/knuth/knuth-infrastructure">![Appveyor status][badge.Appveyor]</a> <a target="_blank" href="https://gitter.im/knuth/Lobby">![Gitter Chat][badge.Gitter]</a>

> Infrastructure functionality


## Installation Requirements

- 64-bit machine.
- [Conan](https://www.conan.io/) package manager, version 1.4.0 or newer. See [Conan Installation](http://docs.conan.io/en/latest/installation.html#install-with-pip-recommended).

## Installation Procedure

The *Knuth* libraries can be installed on Linux, macOS, FreeBSD, Windows and others. These binaries are pre-built for the most usual operating system/compiler combinations and hosted in an online repository. If there are no pre-built binaries for your platform, a build from source will be attempted.

So, for any platform, an installation can be performed in 2 simple steps:

1. Configure the Conan remote:
```
conan remote add knuth https://api.bintray.com/conan/k-nuth/k-nuth
```

2. Install the appropriate library:

```
conan install knuth-infrastructure/0.X@knuth/stable 
```

In you want to tune the installation for better performance, please refer to [this](https://knuth.github.io/docfx/content/user_guide/installation.html#advanced-installation).


<!-- Links -->
[badge.Appveyor]: https://ci.appveyor.com/api/projects/status/github/knuth/knuth-infrastructure?svg=true&branch=dev
[badge.Gitter]: https://img.shields.io/badge/gitter-join%20chat-blue.svg
[badge.Travis]: https://travis-ci.org/knuth/knuth-infrastructure.svg?branch=master
[badge.version]: https://badge.fury.io/gh/knuth%2Fknuth-infrastructure.svg

[CMake]: http://www.cmake.org
[Doxygen]: http://www.doxygen.org
[eRuby]: http://en.wikipedia.org/wiki/ERuby
[Hana.docs]: http://boostorg.github.io/hana
[Hana.wiki]: https://github.com/boostorg/hana/wiki
[Homebrew formula]: https://github.com/Homebrew/homebrew-infrastructure/blob/master/Formula/hana.rb


