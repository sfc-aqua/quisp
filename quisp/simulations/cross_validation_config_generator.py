#!/usr/bin/python3

import os

import numpy as np


def generate_mim_exp_config(num_memories: int, alice_to_bsa: int, bob_to_bsa: int):
    # [Config mim_imbalanced_10_10]
    # network = networks.cross_validation_mim_link_imbalanced_10_10
    # **.qrsa.hm.link_tomography = true
    # **.qrsa.hm.initial_purification = 0
    # **.qrsa.hm.purification_type = ""
    # **.buffers = 1
    pass
    # config_name = f"[Config swapping_validation_cnot_only_{cnot_error_prob}]"
    # network_name = f"networks.cross_validation_swapping"
    # error_params = [
    #     f"**.cnot_gate_error_rate = {cnot_error_prob}",
    #     f"**.cnot_gate_iz_error_ratio = {1/9}",
    #     f"**.cnot_gate_zi_error_ratio = {1/9}",
    #     f"**.cnot_gate_zz_error_ratio = {1/9}",
    #     f"**.cnot_gate_ix_error_ratio = {1/9}",
    #     f"**.cnot_gate_xi_error_ratio = {1/9}",
    #     f"**.cnot_gate_xx_error_ratio = {1/9}",
    #     f"**.cnot_gate_iy_error_ratio = {1/9}",
    #     f"**.cnot_gate_yi_error_ratio = {1/9}",
    #     f"**.cnot_gate_yy_error_ratio = {1/9}",
    # ]
    # return [config_name, network_name, *error_params]


def generate_swapping_config(cnot_error_prob: float, measurement_error_prob: float, with_depolarizing: bool):
    # [Config mim_imbalanced_10_10]
    # network = networks.cross_validation_mim_link_imbalanced_10_10
    # **.qrsa.hm.link_tomography = true
    # **.qrsa.hm.initial_purification = 0
    # **.qrsa.hm.purification_type = ""
    # **.buffers = 1

    # round error probability to 3 decimal places
    cnot_error_prob = round(cnot_error_prob, 3)
    measurement_error_prob = round(measurement_error_prob, 3)

    # delete leading 0. and change it into string
    cnot_error_prob_str = str(cnot_error_prob)[2:]
    measurement_error_prob_str = str(measurement_error_prob)[2:]
    if len(cnot_error_prob_str) == 0:
        cnot_error_prob_str = "0"
    if len(measurement_error_prob_str) == 0:
        measurement_error_prob_str = "0"

    if with_depolarizing:
        config_name = f"[Config swapping_validation_cnot_{cnot_error_prob_str}_meas_{measurement_error_prob_str}_with_1ms_decoherence]"
        # p = 0.0004623208506703652 --> resulting in P_I = 0.36781054 after 1ms
        p_decoherence = 0.0004623208506703652
    else:
        config_name = f"[Config swapping_validation_cnot_{cnot_error_prob_str}_meas_{measurement_error_prob_str}_without_decoherence]"
        p_decoherence = 0
    network_name = "network = networks.cross_validation_swapping"
    error_params = [
        f"**.cnot_gate_error_rate = {cnot_error_prob}",
        #
        f"**.x_measurement_error_rate = {measurement_error_prob}",
        f"**.y_measurement_error_rate = {measurement_error_prob}",
        f"**.z_measurement_error_rate = {measurement_error_prob}",
        #
        f"**.memory_x_error_rate = {p_decoherence}",
        f"**.memory_y_error_rate = {p_decoherence}",
        f"**.memory_z_error_rate = {p_decoherence}",
    ]
    other_params = [
        "**.qrsa.hm.link_tomography = false",
        "**.qrsa.hm.initial_purification = 0",
        '**.qrsa.hm.purification_type = ""',
        "*.EndNode1.is_initiator = true",
    ]
    return [config_name, network_name, *error_params, *other_params]


def write_config(filename: str, configs: list[list[str]]):
    # config relative path inside simulation folder
    dirname = os.path.dirname(__file__)
    general_ini_file = os.path.join(dirname, "general_config.ini")
    filename = os.path.join(dirname, filename)

    with open(filename, "w") as the_file:
        with open(general_ini_file) as f:
            for line in f:
                the_file.write(line)
        for config in configs:
            the_file.write("\n".join(config))
            the_file.write("\n\n\n")


# exp 3: gate error
# exp 3: measurement error
# exp 3: with decoherence
swapping_configs_gate_error = [generate_swapping_config(gp, 0, False) for gp in np.arange(0, 0.51, 0.025)]
swapping_configs_gate_error_with_depo = [generate_swapping_config(gp, 0, True) for gp in np.arange(0, 0.51, 0.025)]
swapping_configs_meas_error = [generate_swapping_config(0, gp, False) for gp in np.arange(0, 0.51, 0.025)]
swapping_configs_meas_error_with_depo = [generate_swapping_config(0, gp, True) for gp in np.arange(0, 0.51, 0.025)]

# delete the duplicate config in the lists, "swapping_validation_cnot_0_meas_0_"
swapping_configs_gate_error = swapping_configs_gate_error[1:]
swapping_configs_gate_error_with_depo = swapping_configs_gate_error_with_depo[1:]

write_config(
    "cross_validation_config_generated.ini",
    [
        *swapping_configs_gate_error,
        *swapping_configs_gate_error_with_depo,
        *swapping_configs_meas_error,
        *swapping_configs_meas_error_with_depo,
    ],
)
