/* --------------------------------------------------
   Copyright (C): OpenGATE Collaboration
   This software is distributed under the terms
   of the GNU Lesser General Public Licence (LGPL)
   See LICENSE.md for further details
   -------------------------------------------------- */

#include <pybind11/pybind11.h>

#include <memory>

#include "globals.hh"
#include "G4VisAttributes.hh"

namespace py = pybind11;

void init_G4VisAttributes(py::module &m) {
  py::class_<G4VisAttributes>(m, "G4VisAttributes")
      .def(py::init<>())

      // Extended binding: retain the existing SetColor method while exposing
      // named RGBA arguments and a default alpha value for Python callers.
      .def("SetColor",
           [](G4VisAttributes &va, G4double red, G4double green,
              G4double blue, G4double alpha) {
             va.SetColor(red, green, blue, alpha);
           },
           py::arg("r"), py::arg("g"), py::arg("b"), py::arg("a") = 1.0)

      // Extended binding: add a named argument and a convenient default to
      // the previously exposed visibility setter.
      .def("SetVisibility", &G4VisAttributes::SetVisibility,
           py::arg("visible") = true)

      // Added bindings: allow Python geometry code to explicitly request
      // solid or wireframe rendering for a volume's visual attributes.
      .def("SetForceSolid", &G4VisAttributes::SetForceSolid,
           py::arg("force") = true)
      .def("SetForceWireframe", &G4VisAttributes::SetForceWireframe,
           py::arg("force") = true);
}
