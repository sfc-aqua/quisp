#!/usr/bin/python3

import numpy as np
import os


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


def generate_swapping_config(
    cnot_error_prob: float, measurement_error_prob: float, with_depolarizing: bool
):
    # [Config mim_imbalanced_10_10]
    # network = networks.cross_validation_mim_link_imbalanced_10_10
    # **.qrsa.hm.link_tomography = true
    # **.qrsa.hm.initial_purification = 0
    # **.qrsa.hm.purification_type = ""
    # **.buffers = 1
    if with_depolarizing:
        config_name = f"[Config swapping_validation_cnot_{cnot_error_prob}_meas_{measurement_error_prob}_with_1ms_decoherence]"
        # p = 0.0004623208506703652 --> resulting in P_I = 0.36781054 after 1ms
        p_decoherence = 0.0004623208506703652
    else:
        config_name = f"[Config swapping_validation_cnot_{cnot_error_prob}_meas_{measurement_error_prob}_without_decoherence]"
        p_decoherence = 0
    network_name = f"network = networks.cross_validation_swapping"
    error_params = [
        f"**.cnot_gate_error_rate = {cnot_error_prob}",
        f"**.cnot_gate_iz_error_ratio = {1/9}",
        f"**.cnot_gate_zi_error_ratio = {1/9}",
        f"**.cnot_gate_zz_error_ratio = {1/9}",
        f"**.cnot_gate_ix_error_ratio = {1/9}",
        f"**.cnot_gate_xi_error_ratio = {1/9}",
        f"**.cnot_gate_xx_error_ratio = {1/9}",
        f"**.cnot_gate_iy_error_ratio = {1/9}",
        f"**.cnot_gate_yi_error_ratio = {1/9}",
        f"**.cnot_gate_yy_error_ratio = {1/9}",
        #
        f"**.x_measurement_error_rate = {measurement_error_prob}",
        f"**.y_measurement_error_rate = {measurement_error_prob}",
        f"**.z_measurement_error_rate = {measurement_error_prob}",
        #
        f"**.memory_x_error_rate = {p_decoherence}",
        f"**.memory_y_error_rate = {p_decoherence}",
        f"**.memory_z_error_rate = {p_decoherence}",
    ]
    return [config_name, network_name, *error_params]


def write_config(filename: str, configs: list[list[str]]):
    # config relative path inside simulation folder
    dirname = os.path.dirname(__file__)
    general_ini_file = os.path.join(dirname, "general_config.ini")

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
swapping_configs_gate_error = [
    generate_swapping_config(gp, 0, False) for gp in np.arange(0, 0.5, 0.025)
]
swapping_configs_gate_error_with_depo = [
    generate_swapping_config(gp, 0, True) for gp in np.arange(0, 0.5, 0.025)
]
swapping_configs_meas_error = [
    generate_swapping_config(0, gp, False) for gp in np.arange(0, 0.5, 0.025)
]
swapping_configs_meas_error_with_depo = [
    generate_swapping_config(0, gp, True) for gp in np.arange(0, 0.5, 0.025)
]

write_config(
    "cross_validation_config_generated.ini",
    [
        *swapping_configs_gate_error,
        *swapping_configs_gate_error_with_depo,
        *swapping_configs_meas_error,
        *swapping_configs_meas_error_with_depo,
    ],
)
