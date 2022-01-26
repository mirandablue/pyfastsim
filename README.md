pyFastsim
=========

Python bindings for [libfastsim](https://github.com/jbmouret/libfastsim).


Requirements
------------
- **A c++14 capable compiler is needed !**
- the pybind11 python module
- the pybind11 development package (libpybind11-dev on Debian/Ubuntu)
- libfastsim from github (https://github.com/jbmouret/libfastsim)

(The current version of pyfastsim and libfastsim does not require patching libfastsin any more. The required changes have been merged into libfastsim.)

Installation
------------
- Clone, build and install [libfastsim](https://github.com/jbmouret/libfastsim).
- Run `pip3 install .` from the directory



Usage
-----
You can run the example with `python3 example.py worlds/example.xml` from the example repository

It is a port of the C++ test_fastsim and should give exactly the same results.
