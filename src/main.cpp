// Alexandre Coninx
// ISIR CNRS/UPMC
// 04/06/2019
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <libfastsim/fastsim.hpp>


int add(int i, int j) {
	return i + j;
}

namespace py = pybind11;

PYBIND11_MODULE(pyfastsim, m) {
	m.doc() = R"pbdoc(
		Pybind11 example plugin
		-----------------------

		.. currentmodule:: python_example

		.. autosummary::
		   :toctree: _generate

		   add
		   subtract
	)pbdoc";

	py::class_<fastsim::Posture>(m, "Posture")
		.def(py::init<float, float, float>(), py::arg("x"), py::arg("y"), py::arg("theta"))
		.def(py::init<>())
		.def(py::init<fastsim::Posture const&>())
		.def("theta", &fastsim::Posture::theta)
		.def("set_theta", &fastsim::Posture::set_theta)
		.def("set_x", &fastsim::Posture::set_x)
		.def("set_y", &fastsim::Posture::set_y)
		.def("x", &fastsim::Posture::x)
		.def("y", &fastsim::Posture::y)
		.def("dist_to",  py::overload_cast<float, float>(&fastsim::Posture::dist_to,  py::const_))
		.def("dist_to", py::overload_cast<const fastsim::Posture&>(&fastsim::Posture::dist_to,  py::const_))
		.def("rotate", &fastsim::Posture::rotate)
		.def(py::self + py::self)
		.def("move", &fastsim::Posture::move)
		.def_static("normalize_angle", py::overload_cast<float>(&fastsim::Posture::normalize_angle<float>))
		.def_static("normalize_angle", py::overload_cast<double>(&fastsim::Posture::normalize_angle<double>));

/*	py::class_<Laser>(m, "Laser")
		.def(py::init<float, float, float, float>(), bp::arg("angle"), bp::arg("range"), bp::arg("gap_dist")=0., bp::arg("gap_angle")=0.)
		.def("setName", &Pet::setName)
		.def("getName", &Pet::getName);*/

	m.def("add", &add, R"pbdoc(
		Add two numbers

		Some other explanation about the add function.
	)pbdoc");

	m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
		Subtract two numbers

		Some other explanation about the subtract function.
	)pbdoc");

#ifdef VERSION_INFO
	m.attr("__version__") = VERSION_INFO;
#else
	m.attr("__version__") = "dev";
#endif
}
