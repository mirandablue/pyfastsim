pyFastsim
=========

Python bindings for [libfastsim](https://github.com/jbmouret/libfastsim).

SDL DOES NOT WORK FOR NOW

Installation
------------
- **You will need a c++14-capable compiler !**
- Use libfastsim from github: (https://github.com/jbmouret/libfastsim), apply the provided patch, and compile and install it. The patch does 2 things:
  * Adds -fPIC flag to compilation
  * Migrates the code from boost::shared\_ptr to std::shared\_ptr (which is much easier to use with pybind11)
  * (It also removes debug flags and make the test more verbose; that is optional)
- Then just run `pip3 install .` from the directory



Usage
-----
You can run the example with `python3 example.py` from the example repository

It is a port of the C++ test_fastsim and should give exactly the same results.
