<p align="center">
<img src="https://github.com/Pencilcaseman/librapid/blob/master/branding/LibRapid_light.png" width="800">
</p>

[![Wheels (master)](https://github.com/LibRapid/librapid/actions/workflows/wheels.yaml/badge.svg)](https://github.com/LibRapid/librapid/actions/workflows/wheels_master.yaml) [![Documentation Status](https://readthedocs.org/projects/librapid/badge/?version=latest)](https://librapid.readthedocs.io/en/latest/?badge=latest) ![PyPI](https://img.shields.io/pypi/v/librapid?color=green&label=Release&logo=python&logoColor=green) ![PyPI - License](https://img.shields.io/pypi/l/librapid?color=gray&label=Licensed%20under) ![PyPI - Python Version](https://img.shields.io/pypi/pyversions/librapid?color=blue&label=Version&logo=python&logoColor=green) [![Discord](https://img.shields.io/discord/848914274105557043?color=blue&label=Discord&logo=Discord)](https://discord.gg/cGxTFTgCAC) ![PyPI - Downloads](https://img.shields.io/pypi/dm/librapid?color=blue&label=Downloads&logo=python&logoColor=green)

---

# What is LibRapid?

LibRapid is a high performance Array library, supporting a wide range of optimised calculations which can be performed on the CPU or GPU (via CUDA). All calculations are vectorised with SIMD instructions and are run on multiple threads (if necessary) to make them as fast as possible on any given machine.

There are also a wide range of helper functions and classes to aid the development of your own project.

LibRapid is fully templated and is header-only, meaning it can conform to exactly your needs with minimal compile-times and even support for custom datatypes.

# Current Development Stage

At the current point in time, LibRapid C++ is under rapid development by me ([pencilcaseman](https://github.com/Pencilcaseman)).

I am currently doing my A-Levels and do not have time to work on the library as much as I would like, so if you or someone you know might be willing to support the development of the library, feel free to create a pull request or chat to us on [Discord](https://discord.com/invite/cGxTFTgCAC). Any help is greatly appreciated!

# Future Plans

My goal for LibRapid is to develop the C++ interface further, at least initially. At some point I want to add Python and Javascript interfaces (in that order) to increase the range of people who can benefit from the library, but the most important thing is the performance of the underlying C++ code.