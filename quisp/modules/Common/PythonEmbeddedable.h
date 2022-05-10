#pragma once
#include <pybind11/pybind11.h>

namespace quisp::modules::python_embeddable {
namespace py = pybind11;

class PythonEmbeddable {
 public:
  PythonEmbeddable() {}
  ~PythonEmbeddable() {}
  void compile_code(const char* file_name);
  void execute_python(const char* func_name, py::object& arg1);

  pybind11::module_ module;
};
}  // namespace quisp::modules::python_embeddable
