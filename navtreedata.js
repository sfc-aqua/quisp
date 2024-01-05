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
    [ "Logging", "md_quisp_modules__logger__r_e_a_d_m_e.html", [
      [ "Usage", "md_quisp_modules__logger__r_e_a_d_m_e.html#autotoc_md14", null ]
    ] ],
    [ "Bell State Analyzer", "md_quisp_modules__physical_connection__b_s_a__r_e_a_d_m_e.html", [
      [ "How BellStateAnalyzer Module works", "md_quisp_modules__physical_connection__b_s_a__r_e_a_d_m_e.html#autotoc_md16", null ]
    ] ],
    [ "EPPS Modules and the MSM Protocol", "md_quisp_modules__physical_connection__e_p_p_s__r_e_a_d_m_e.html", [
      [ "EntangledPhotonPairSource Module", "md_quisp_modules__physical_connection__e_p_p_s__r_e_a_d_m_e.html#autotoc_md18", null ],
      [ "EPPSController Module", "md_quisp_modules__physical_connection__e_p_p_s__r_e_a_d_m_e.html#autotoc_md19", null ],
      [ "Usage", "md_quisp_modules__physical_connection__e_p_p_s__r_e_a_d_m_e.html#autotoc_md20", null ],
      [ "MSM protocol details which take part in EPPS modules", "md_quisp_modules__physical_connection__e_p_p_s__r_e_a_d_m_e.html#autotoc_md21", null ]
    ] ],
    [ "MSM protocol details which take part in the RuleEngine", "md_quisp_modules__q_r_s_a__rule_engine__r_e_a_d_m_e.html", [
      [ "- <tt>success_list</tt>: List to store the information of memory qubits that succeeded local BSM. Contains the qubit information and the correction information.", "md_quisp_modules__q_r_s_a__rule_engine__r_e_a_d_m_e.html#autotoc_md47", [
        [ "Pseudocodes", "md_quisp_modules__q_r_s_a__rule_engine__r_e_a_d_m_e.html#autotoc_md45", [
          [ "Global Variables", "md_quisp_modules__q_r_s_a__rule_engine__r_e_a_d_m_e.html#autotoc_md46", null ],
          [ "Function to emit photons from qnodes in msm links", "md_quisp_modules__q_r_s_a__rule_engine__r_e_a_d_m_e.html#autotoc_md48", null ]
        ] ]
      ] ],
      [ "1. Wait for <tt>interval</tt> time and call EMIT_PHOTONS_MSM(<tt>interval</tt>)", "md_quisp_modules__q_r_s_a__rule_engine__r_e_a_d_m_e.html#autotoc_md49", null ],
      [ "1. Free <tt>qubit</tt>", "md_quisp_modules__q_r_s_a__rule_engine__r_e_a_d_m_e.html#autotoc_md53", [
        [ "Explanation of applying the Pauli Z gate for the case where the BSM results are different", "md_quisp_modules__q_r_s_a__rule_engine__r_e_a_d_m_e.html#autotoc_md54", null ]
      ] ]
    ] ],
    [ "Runtime", "md_quisp_runtime__r_e_a_d_m_e.html", [
      [ "Intermediate Representations (IR)", "md_quisp_runtime__r_e_a_d_m_e.html#autotoc_md56", null ],
      [ "RuleSet Execution with Runtime", "md_quisp_runtime__r_e_a_d_m_e.html#autotoc_md57", null ],
      [ "Storage Scopes", "md_quisp_runtime__r_e_a_d_m_e.html#autotoc_md58", null ],
      [ "Storage types", "md_quisp_runtime__r_e_a_d_m_e.html#autotoc_md59", [
        [ "Register", "md_quisp_runtime__r_e_a_d_m_e.html#autotoc_md60", null ],
        [ "Memory", "md_quisp_runtime__r_e_a_d_m_e.html#autotoc_md61", null ],
        [ "Flags (pc, should_exit, terminated, error, and return_code)", "md_quisp_runtime__r_e_a_d_m_e.html#autotoc_md62", null ],
        [ "Qubits", "md_quisp_runtime__r_e_a_d_m_e.html#autotoc_md63", null ]
      ] ]
    ] ],
    [ "Test Utilities", "md_quisp_test_utils__r_e_a_d_m_e.html", [
      [ "Usage", "md_quisp_test_utils__r_e_a_d_m_e.html#autotoc_md65", null ],
      [ "Grab a packet", "md_quisp_test_utils__r_e_a_d_m_e.html#autotoc_md66", null ],
      [ "Example", "md_quisp_test_utils__r_e_a_d_m_e.html#autotoc_md67", null ]
    ] ],
    [ "quisp::utils", "md_quisp_utils__r_e_a_d_m_e.html", [
      [ "ComponentProvider", "md_quisp_utils__r_e_a_d_m_e.html#autotoc_md69", null ],
      [ "Unit Testing", "md_quisp_utils__r_e_a_d_m_e.html#autotoc_md70", null ]
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
"_q_nic_store_8cc.html",
"classquisp_1_1backends_1_1_stationary_qubit_configuration.html#af2628f2d7c61be191353410584adbe9e",
"classquisp_1_1backends_1_1graph__state_1_1_graph_state_qubit.html#ab9b94278d5193dc0ea9c55d1129bcf67",
"classquisp_1_1modules_1_1_connection_manager.html#a60bf9f1494aeb456bf02e2e7c07c1b50",
"classquisp_1_1modules_1_1_i_routing_daemon.html",
"classquisp_1_1modules_1_1_rule_engine.html#a40b0b79a4cdaaf2de4e346b61748d801",
"classquisp_1_1modules_1_1qnic__record_1_1_i_q_nic_record.html#afb96e5349baf66aa03c4fba962108633",
"classquisp_1_1rules_1_1_clause.html#ae97df8f9427620897fb12333e98e07ad",
"classquisp_1_1runtime_1_1_program.html#abf6369229b47351aaaedde7d594ebb66",
"classquisp_1_1utils_1_1_component_provider.html#ad119a53fb7d1f5027c242e03b74c1100",
"classquisp__test_1_1env_1_1_static_env.html#a465a2f8783fe4410b8016939a94bd4b5",
"classquisp__test_1_1mock__modules_1_1stationary__qubit_1_1_mock_qubit.html#a29a214c1e0451b6caa045d6940903bc8",
"functions_func_v.html",
"namespacequisp_1_1modules_1_1ospf.html#a24e7fd8aa5f45c453a8300701214fe23",
"structquisp_1_1backends_1_1abstract_1_1_measurement_outcome.html#acf0f14731f0fb53531035e8321b5aea8",
"structquisp_1_1modules_1_1ospf_1_1_ospf_neighbor_info.html#a6b4f89fc5c99d41e97859dff5e6130b7"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';