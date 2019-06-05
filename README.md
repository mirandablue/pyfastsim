pyFastsim
=========

Python bindings for [libfastsim](https://github.com/jbmouret/libfastsim).

SDL DOES NOT WORK FOR NOW


Requirements
------------
- **A c++14 capable compiler is needed !**
- the pybind11 python module
- the pybind11 development package (libpybind11-dev on Debian/Ubuntu)
- libfastsim from github (https://github.com/jbmouret/libfastsim), patched with the provided patch. The patch does does 2 things:
  * Adds -fPIC flag to compilation
  * Migrates the code from boost::shared\_ptr to std::shared\_ptr (which is much easier to use with pybind11)
  * (It also removes debug flags and make the test more verbose; that is optional)

Installation
------------
- Just run `pip3 install .` from the directory



Usage
-----
You can run the example with `python3 example.py worlds/example.xml` from the example repository

It is a port of the C++ test_fastsim and should give exactly the same results.
