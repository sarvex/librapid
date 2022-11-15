<p align="center">
<img src="https://github.com/LibRapid/librapid_bin/blob/master/branding/LibRapid_light.png#gh-light-mode-only" width="800">
</p>

<p align="center">
<img src="https://github.com/LibRapid/librapid_bin/blob/master/branding/LibRapid_dark.png#gh-dark-mode-only" width="800">
</p>

![PyPI](https://img.shields.io/pypi/v/librapid?color=green&label=Release&logo=python&logoColor=green) ![PyPI - License](https://img.shields.io/pypi/l/librapid?color=gray&label=Licensed%20under) ![PyPI - Python Version](https://img.shields.io/pypi/pyversions/librapid?color=blue&label=Version&logo=python&logoColor=green) [![Discord](https://img.shields.io/discord/848914274105557043?color=blue&label=Discord&logo=Discord)](https://discord.gg/cGxTFTgCAC) ![PyPI - Downloads](https://img.shields.io/pypi/dm/librapid?color=blue&label=Downloads&logo=python&logoColor=green) ![C++ Version](https://img.shields.io/badge/Language-C%2B%2B%2017-orange)

---

[![Compile](https://github.com/LibRapid/librapid/actions/workflows/compile.yaml/badge.svg)](https://github.com/LibRapid/librapid/actions/workflows/compile.yaml) \
[![Documentation Build](https://github.com/LibRapid/librapid/actions/workflows/build-docs.yaml/badge.svg)](https://github.com/LibRapid/librapid/actions/workflows/build-docs.yaml) \
[![Documentation Online](https://github.com/LibRapid/librapid/actions/workflows/static.yaml/badge.svg)](https://librapid.github.io/librapid/md_librapid__r_e_a_d_m_e.html)

---

# Documentation

<a href="https://librapid.github.io/librapid/md_librapid__r_e_a_d_m_e.html" target="_blank"><b>Latest
Documentation</b></a>

LibRapid uses [Doxygen](https://doxygen.nl/) and [Doxygen Awesome CSS](https://github.com/jothepro/doxygen-awesome-css)
to automatically generate the documentation.

# What is LibRapid?

LibRapid is a high performance Array library, supporting a wide range of optimised calculations which can be performed
on the CPU or GPU (via CUDA). All calculations are vectorised with SIMD instructions and are run on multiple threads (if
necessary) to make them as fast as possible on any given machine.

There are also a wide range of helper functions and classes to aid the development of your own project.

LibRapid is highly templated, meaning it can conform to exactly your needs with minimal compile-times and even support
for custom data types.

# Current Development Stage

At the current point in time, LibRapid C++ is under rapid development by
me ([pencilcaseman](https://github.com/Pencilcaseman)).

I am currently doing my A-Levels and do not have time to work on the library as much as I would like, so if you or
someone you know might be willing to support the development of the library, feel free to create a pull request or chat
to us on [Discord](https://discord.com/invite/cGxTFTgCAC). Any help is greatly appreciated!

# Future Plans

My goal for LibRapid is to make it faster and easier to use than existing libraries, such as Eigen and XTensor. I plan
to develop an extensive testing and benchmarking suite alongside the code base, to ensure that everything is running as
fast as possible.

My main goal for the future is to implement as many features as possible, while maintaining the high performance
LibRapid requires.

# External Dependencies

LibRapid has a few external dependencies to improve functionality and performance. Some of these are optional, and can
be included with a CMake option. The following is a list of the external dependencies and their purpose (these are all
submodules of the library. You don't need to do anything different):

- Required
    - [fmt](https://github.com/fmtlib/fmt) - Advanced string formatting
    - [scnlib](https://github.com/eliaskosunen/scnlib) - Advanced string parsing
    - [thread-pool](https://github.com/bshoshany/thread-pool) - Thread pool for parallel execution
    - [Vc](https://github.com/VcDevel/Vc) - SIMD library
    - [cppfs](https://github.com/cginternals/cppfs.git) - Cross-platform filesystem library (required for CUDA support)
- Optional
    - [OpenMP](https://www.openmp.org/) - Multi-threading library
    - [CUDA](https://developer.nvidia.com/cuda-zone) - GPU computing library
    - [mpfr](https://github.com/Pencilcaseman/mpfr) - Arbitrary precision numbers (integer, real, rational)

# Star History

[![Star History Chart](https://api.star-history.com/svg?repos=LibRapid/librapid&type=Date)](https://star-history.com/#LibRapid/librapid&Date)

# Support

Thanks to JetBrains for providing LibRapid with free licenses for their amazing tools!

<p align="center">
  <a href="https://www.jetbrains.com">
    <img src="https://devclass.com/wp-content/uploads/2018/12/jetbrains-variant-4.png" alt="JetBrains" width="200"/>
  </a>
</p>
