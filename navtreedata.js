/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "QuISP", "index.html", [
    [ "Research questions", "index.html#autotoc_md1", null ],
    [ "Simulation goals", "index.html#autotoc_md2", null ],
    [ "Current status", "index.html#autotoc_md3", null ],
    [ "Installation requirements", "index.html#autotoc_md4", null ],
    [ "Trying it out on the web", "index.html#autotoc_md5", null ],
    [ "Building and running locally", "index.html#autotoc_md6", null ],
    [ "Moving into useful work", "index.html#autotoc_md7", null ],
    [ "Development tools", "index.html#autotoc_md8", null ],
    [ "Is QuISP right for me?", "index.html#autotoc_md9", null ],
    [ "Learning more", "index.html#autotoc_md10", null ],
    [ "Contributing", "index.html#autotoc_md11", null ],
    [ "License", "index.html#autotoc_md12", null ],
    [ "Logging", "md_quisp_2modules_2_logger_2_r_e_a_d_m_e.html", [
      [ "Usage", "md_quisp_2modules_2_logger_2_r_e_a_d_m_e.html#autotoc_md14", null ]
    ] ],
    [ "Bell State Analyzer", "md_quisp_2modules_2_physical_connection_2_b_s_a_2_r_e_a_d_m_e.html", [
      [ "How BellStateAnalyzer Module works", "md_quisp_2modules_2_physical_connection_2_b_s_a_2_r_e_a_d_m_e.html#autotoc_md16", null ]
    ] ],
    [ "EPPS Modules and the MSM Protocol", "md_quisp_2modules_2_physical_connection_2_e_p_p_s_2_r_e_a_d_m_e.html", [
      [ "EntangledPhotonPairSource Module", "md_quisp_2modules_2_physical_connection_2_e_p_p_s_2_r_e_a_d_m_e.html#autotoc_md18", null ],
      [ "EPPSController Module", "md_quisp_2modules_2_physical_connection_2_e_p_p_s_2_r_e_a_d_m_e.html#autotoc_md19", null ],
      [ "Usage", "md_quisp_2modules_2_physical_connection_2_e_p_p_s_2_r_e_a_d_m_e.html#autotoc_md20", null ],
      [ "MSM protocol details which take part in EPPS modules", "md_quisp_2modules_2_physical_connection_2_e_p_p_s_2_r_e_a_d_m_e.html#autotoc_md21", null ]
    ] ],
    [ "MSM protocol details which take part in the RuleEngine", "md_quisp_2modules_2_q_r_s_a_2_rule_engine_2_r_e_a_d_m_e.html", [
      [ "- <tt>success_list</tt>: List to store the information of memory qubits that succeeded local BSM. Contains the qubit information and the correction information.", "md_quisp_2modules_2_q_r_s_a_2_rule_engine_2_r_e_a_d_m_e.html#autotoc_md47", [
        [ "Pseudocodes", "md_quisp_2modules_2_q_r_s_a_2_rule_engine_2_r_e_a_d_m_e.html#autotoc_md45", [
          [ "Global Variables", "md_quisp_2modules_2_q_r_s_a_2_rule_engine_2_r_e_a_d_m_e.html#autotoc_md46", null ],
          [ "Function to emit photons from qnodes in msm links", "md_quisp_2modules_2_q_r_s_a_2_rule_engine_2_r_e_a_d_m_e.html#autotoc_md48", null ]
        ] ]
      ] ],
      [ "1. Wait for <tt>interval</tt> time and call EMIT_PHOTONS_MSM(<tt>interval</tt>)", "md_quisp_2modules_2_q_r_s_a_2_rule_engine_2_r_e_a_d_m_e.html#autotoc_md49", null ],
      [ "1. Free <tt>qubit</tt>", "md_quisp_2modules_2_q_r_s_a_2_rule_engine_2_r_e_a_d_m_e.html#autotoc_md53", [
        [ "Explanation of applying the Pauli Z gate for the case where the BSM results are different", "md_quisp_2modules_2_q_r_s_a_2_rule_engine_2_r_e_a_d_m_e.html#autotoc_md54", null ]
      ] ]
    ] ],
    [ "Runtime", "md_quisp_2runtime_2_r_e_a_d_m_e.html", [
      [ "Intermediate Representations (IR)", "md_quisp_2runtime_2_r_e_a_d_m_e.html#autotoc_md56", null ],
      [ "RuleSet Execution with Runtime", "md_quisp_2runtime_2_r_e_a_d_m_e.html#autotoc_md57", null ],
      [ "Storage Scopes", "md_quisp_2runtime_2_r_e_a_d_m_e.html#autotoc_md58", null ],
      [ "Storage types", "md_quisp_2runtime_2_r_e_a_d_m_e.html#autotoc_md59", [
        [ "Register", "md_quisp_2runtime_2_r_e_a_d_m_e.html#autotoc_md60", null ],
        [ "Memory", "md_quisp_2runtime_2_r_e_a_d_m_e.html#autotoc_md61", null ],
        [ "Flags (pc, should_exit, terminated, error, and return_code)", "md_quisp_2runtime_2_r_e_a_d_m_e.html#autotoc_md62", null ],
        [ "Qubits", "md_quisp_2runtime_2_r_e_a_d_m_e.html#autotoc_md63", null ]
      ] ]
    ] ],
    [ "Test Utilities", "md_quisp_2test__utils_2_r_e_a_d_m_e.html", [
      [ "Usage", "md_quisp_2test__utils_2_r_e_a_d_m_e.html#autotoc_md65", null ],
      [ "Grab a packet", "md_quisp_2test__utils_2_r_e_a_d_m_e.html#autotoc_md66", null ],
      [ "Example", "md_quisp_2test__utils_2_r_e_a_d_m_e.html#autotoc_md67", null ]
    ] ],
    [ "quisp::utils", "md_quisp_2utils_2_r_e_a_d_m_e.html", [
      [ "ComponentProvider", "md_quisp_2utils_2_r_e_a_d_m_e.html#autotoc_md69", null ],
      [ "Unit Testing", "md_quisp_2utils_2_r_e_a_d_m_e.html#autotoc_md70", null ]
    ] ],
    [ "Namespaces", "namespaces.html", [
      [ "Namespace List", "namespaces.html", "namespaces_dup" ],
      [ "Namespace Members", "namespacemembers.html", [
        [ "All", "namespacemembers.html", null ],
        [ "Functions", "namespacemembers_func.html", null ],
        [ "Variables", "namespacemembers_vars.html", null ],
        [ "Typedefs", "namespacemembers_type.html", null ],
        [ "Enumerations", "namespacemembers_enum.html", null ],
        [ "Enumerator", "namespacemembers_eval.html", null ]
      ] ]
    ] ],
    [ "Classes", "annotated.html", [
      [ "Class List", "annotated.html", "annotated_dup" ],
      [ "Class Index", "classes.html", null ],
      [ "Class Hierarchy", "hierarchy.html", "hierarchy" ],
      [ "Class Members", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", "functions_func" ],
        [ "Variables", "functions_vars.html", "functions_vars" ],
        [ "Typedefs", "functions_type.html", null ],
        [ "Enumerator", "functions_eval.html", null ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ],
      [ "File Members", "globals.html", [
        [ "All", "globals.html", null ],
        [ "Functions", "globals_func.html", null ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Enumerations", "globals_enum.html", null ],
        [ "Macros", "globals_defs.html", null ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"_access_private_8h.html",
"_q_nic_record_8cc.html",
"classquisp_1_1backends_1_1_stationary_qubit_configuration.html#ac84fdd15d7552b70bbddf8c6dacc5a79",
"classquisp_1_1backends_1_1graph__state_1_1_graph_state_qubit.html#a86b7a0efb64a393eed44e15de3e5f174",
"classquisp_1_1modules_1_1_connection_manager.html#a3a824b1a14988370a212d1279ae60fc4",
"classquisp_1_1modules_1_1_i_real_time_controller.html",
"classquisp_1_1modules_1_1_rule_engine.html#a0810738c792d45dadb9801529779f365",
"classquisp_1_1modules_1_1ospf_1_1_link_state_database.html#aeeb42e20284c4c029a4e026c761a4b35",
"classquisp_1_1rules_1_1_clause.html",
"classquisp_1_1runtime_1_1_memory_value.html#ac0c1c70da6a2d3c1d20ec1a5c076ba31",
"classquisp_1_1utils_1_1_component_provider.html#aa884f367bb4b3e65983bc0efbf30e78f",
"classquisp__test_1_1env_1_1_static_env.html#a2dd86b3e8deaeb6b3203ab7cf08e0ff5",
"classquisp__test_1_1mock__modules_1_1stationary__qubit_1_1_mock_qubit.html#a044110daabca465601139e24d7d13b8d",
"functions_func_h.html",
"namespacequisp_1_1modules_1_1_shared_resource.html",
"struct_swapping_config.html#a1e46873030558351cc3c5982a36e5e20",
"structquisp_1_1modules_1_1ospf_1_1_ospf_neighbor_info.html#a0179a73f71916afa10c541095f9ee7c5"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';