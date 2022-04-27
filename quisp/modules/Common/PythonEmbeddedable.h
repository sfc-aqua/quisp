#pragma once
#include <Python.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include "pybind11/pybind11.h"

namespace quisp::modules::python_embeddable {
class PythonEmbeddable {
 public:
  PythonEmbeddable() {}
  ~PythonEmbeddable() {}
  void compile_code(const char* file_name) {
    FILE* file = std::fopen(file_name, "rt");
    if (file == NULL) {
      std::cout << file_name << " not found" << std::endl;
      return;
    }
    std::fseek(file, 0L, SEEK_END);
    auto length = std::ftell(file);
    std::rewind(file);
    char* source = (char*)malloc(length + 1);
    std::fread(source, sizeof(char), length, file);
    fclose(file);
    source[length] = '\0';
    std::cout << source << std::endl;
    code_object = Py_CompileString(source, file_name, Py_file_input);
    globals = pybind11::globals().ptr();
  }

  void execute_python() { PyEval_EvalCode(code_object, globals, pybind11::dict().ptr()); }

  PyObject* globals;
  PyObject* code_object = nullptr;
};
}  // namespace quisp::modules::python_embeddable
