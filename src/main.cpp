// Alexandre Coninx
// ISIR CNRS/UPMC
// 04/06/2019
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <libfastsim/fastsim.hpp>
#include <pybind11/stl.h> // Automatic conversion of std::vector

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

	// posture.hpp
	py::class_<fastsim::Posture>(m, "Posture")
		.def(py::init<float, float, float>(), py::arg("x"), py::arg("y"), py::arg("theta"))
		.def(py::init<>())
		.def(py::init<fastsim::Posture const&>())
		// operator= is meaningless in python
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
		// Template -- provide float and double versions
		.def_static("normalize_angle", py::overload_cast<float>(&fastsim::Posture::normalize_angle<float>))
		.def_static("normalize_angle", py::overload_cast<double>(&fastsim::Posture::normalize_angle<double>));

	// misc.hpp
	// Exception not implemented
	// Template -- provide float and double versions
	m.def("normalize_angle", py::overload_cast<float>(&fastsim::normalize_angle<float>));
	m.def("normalize_angle", py::overload_cast<double>(&fastsim::normalize_angle<double>));
	// Template -- provide float and double versions
	m.def("normalize_angle_2pi", py::overload_cast<float>(&fastsim::normalize_angle_2pi<float>));
	m.def("normalize_angle_2pi", py::overload_cast<double>(&fastsim::normalize_angle_2pi<double>));


	// goal.hpp
	py::class_<fastsim::Goal>(m, "Goal")
		.def(py::init<float, float, float, int>(), py::arg("x"), py::arg("y"), py::arg("diam"), py::arg("color"))
		.def(py::init<float, float, float, int>(), py::arg("x"), py::arg("y"), py::arg("diam"), py::arg("color"))
		.def("get_x", &fastsim::Goal::get_x)
		.def("get_y", &fastsim::Goal::get_y)
		.def("get_diam", &fastsim::Goal::get_diam)
		.def("get_color", &fastsim::Goal::get_color);
	
	// illuminated_switch.hpp
	py::class_<fastsim::IlluminatedSwitch>(m, "IlluminatedSwitch")
		.def(py::init<int, float, float, float, bool>())
		.def("try_to_activate", &fastsim::IlluminatedSwitch::try_to_activate)
		.def("activate", &fastsim::IlluminatedSwitch::activate)
		.def("deactivate", &fastsim::IlluminatedSwitch::deactivate)
		.def("set_on", &fastsim::IlluminatedSwitch::set_on)
		.def("set_off", &fastsim::IlluminatedSwitch::set_off)
		.def("get_on", &fastsim::IlluminatedSwitch::get_on)
		.def("get_off", &fastsim::IlluminatedSwitch::get_off)
		.def("get_color", &fastsim::IlluminatedSwitch::get_color)
		.def("get_radius", &fastsim::IlluminatedSwitch::get_radius)
		.def("get_x", &fastsim::IlluminatedSwitch::get_x)
		.def("get_y", &fastsim::IlluminatedSwitch::get_y)
		.def("set_pos", &fastsim::IlluminatedSwitch::set_pos)
		.def("get_activated", &fastsim::IlluminatedSwitch::get_activated)
		.def("link", &fastsim::IlluminatedSwitch::link); // not working - TODO handle boost::shared_ptr
	// ClosestSwitch_f not implemented
	
	// map.hpp
	py::class_<fastsim::Map> map(m, "Map");
	map.def(py::init<const char*, float>(), py::arg("fname"), py::arg("real_w"))
		.def(py::init<const fastsim::Map&>())
		.def("get_pixel", &fastsim::Map::get_pixel)
		.def("set_pixel", &fastsim::Map::set_pixel)
		.def("get_real", &fastsim::Map::get_real)
		.def("real_to_pixel", &fastsim::Map::real_to_pixel)
		.def("pixel_to_real", &fastsim::Map::pixel_to_real)
		.def("get_real_w", &fastsim::Map::get_real_w)
		.def("get_real_h", &fastsim::Map::get_real_h)
		.def("get_pixel_w", &fastsim::Map::get_pixel_w)
		.def("get_pixel_h", &fastsim::Map::get_pixel_h)
		.def("check_inter_pixel", &fastsim::Map::check_inter_pixel)
		.def("check_inter_real", &fastsim::Map::check_inter_real)
		.def("check_inter_is", &fastsim::Map::check_inter_is)
		.def("get_goals", &fastsim::Map::get_goals)
		.def("add_goal", &fastsim::Map::add_goal)
		.def("add_illuminated_switch", &fastsim::Map::add_illuminated_switch) // not working - TODO handle boost::shared_ptr
		.def("get_illuminated_switches", &fastsim::Map::get_illuminated_switches) // not working - TODO handle boost::shared_ptr
		.def("get_illuminated_switch_by_color", &fastsim::Map::get_illuminated_switch_by_color) // not working - TODO handle boost::shared_ptr
		.def("clear_illuminated_switches", &fastsim::Map::clear_illuminated_switches)
		.def("update", &fastsim::Map::update)
		.def("terrain_switch", &fastsim::Map::terrain_switch)
		.def("draw_rect", &fastsim::Map::draw_rect);
	
	py::enum_<fastsim::Map::status_t>(map, "status_t")
		.value("free", fastsim::Map::status_t::free)
		.value("obstacle", fastsim::Map::status_t::obstacle)
		.export_values();

	
	// laser.hpp
	py::class_<fastsim::Laser>(m, "Laser")
		.def(py::init<float, float, float, float>(), py::arg("angle"), py::arg("range"), py::arg("gap_dist")=0., py::arg("gap_angle")=0.)
		.def("update", &fastsim::Laser::update)
		.def("get_dist", &fastsim::Laser::get_dist)
		.def("get_angle", &fastsim::Laser::get_angle)
		.def("get_range", &fastsim::Laser::get_range)
		.def("get_gap_dist", &fastsim::Laser::get_gap_dist)
		.def("get_gap_angle", &fastsim::Laser::get_gap_angle)
		.def("get_x", &fastsim::Laser::get_x)
		.def("get_y", &fastsim::Laser::get_y)
		.def("get_x_pixel", &fastsim::Laser::get_x_pixel)
		.def("get_y_pixel", &fastsim::Laser::get_y_pixel);

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