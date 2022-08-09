#include "PythonEmbeddedable.h"
#include <omnetpp.h>
#include <pybind11/detail/common.h>
#include <pybind11/embed.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <filesystem>
#include <memory>
#include "feature_defines.h"

namespace py = pybind11;
namespace opp = omnetpp;
namespace fs = std::filesystem;
namespace quisp::modules::python_embeddable {

#ifdef ENABLE_PYTHON
PYBIND11_EMBEDDED_MODULE(opp, m) {
  py::class_<opp::cPar, std::unique_ptr<opp::cPar, py::nodelete>> OppPar(m, "Par");
  OppPar.def("str", &omnetpp::cPar::str);
  OppPar.def("int", &omnetpp::cPar::intValue);

  py::class_<opp::cSimpleModule, std::unique_ptr<opp::cSimpleModule, py::nodelete>> OppSimpleModule(m, "SimpleModule");
  OppSimpleModule.def("par", py::overload_cast<const char*>(&opp::cSimpleModule::par), py::return_value_policy::reference);
  OppSimpleModule.def("schedule_at", &opp::cSimpleModule::scheduleAt);
  m.def("sim_time", &opp::simTime, py::return_value_policy::reference);

  py::class_<opp::SimTime> OppSimTime(m, "SimTime");
  OppSimTime.def(py::self + float());
  OppSimTime.def(py::self += float());
  OppSimTime.def(float() + py::self);

  py::class_<opp::cMessage, std::unique_ptr<opp::cMessage, py::nodelete>> OppCMessage(m, "Message");
}
#endif

void PythonEmbeddable::compile_code(const char* file_name) {
  auto* env = omnetpp::getEnvir();
  auto* config = env->getConfigEx();
  fs::path exe_path(env->getArgVector()[0]);
  fs::path conf_path(env->resolveResourcePath(config->getFileName()));
  py::module sys = py::module::import("sys");
  py::cast<py::list>(sys.attr("path")).append(fs::absolute(exe_path.parent_path()).string());
  py::cast<py::list>(sys.attr("path")).append(fs::absolute(conf_path.parent_path()).string());
  py::print(sys.attr("path"));
  module = pybind11::module_::import(file_name);
}

void PythonEmbeddable::execute_python(const char* func_name, py::object& arg1) { py::object ret = module.attr(func_name)(arg1); }

}  // namespace quisp::modules::python_embeddable
