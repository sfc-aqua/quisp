from .routing import find_network_boundary
from quisp import QNodeAddr
from typing import List, Tuple


def convert_to_QNodeAddr(paths: "List[List[Tuple[int]]]") -> "List[List[QNodeAddr]]":
    """convert the addresses in paths to QNodeAddr type"""
    return [[QNodeAddr(*addr) for addr in addrs] for addrs in paths]


def test_nested_subnet1():
    paths = convert_to_QNodeAddr(
        [
            [(2, 99), (4, 99)],
            [(4, 2)],
            [(4, 3), (5, 1)],
            [(5, 2)],
            [(5, 3)],
            [(4, 4), (5, 99)],
            [(4, 5)],
            [(2, 1), (4, 1)],
        ]
    )

    result = find_network_boundary(paths, QNodeAddr(2, 99), QNodeAddr(2, 1))
    assert result == (4, QNodeAddr(4, 99), QNodeAddr(4, 2), QNodeAddr(4, 1))


def test_nested_subnet2():
    paths = convert_to_QNodeAddr(
        [
            [(1, 1), (3, 1)],
            [(3, 2), (4, 1)],
            [(4, 2)],
            [(3, 3), (4, 3)],
            [(2, 1), (3, 4)],
        ]
    )

    result = find_network_boundary(paths, QNodeAddr(1, 1), QNodeAddr(2, 1))
    assert result == (3, QNodeAddr(3, 1), QNodeAddr(3, 2), QNodeAddr(3, 4))


def test_single_subnet_in_path1():
    paths = convert_to_QNodeAddr(
        [
            [(1, 1)],
            [(6, 2), (4, 1)],
            [(4, 4)],
            [(5, 3), (4, 3)],
            [(2, 1), (3, 4)],
        ]
    )

    result = find_network_boundary(paths, QNodeAddr(1, 1), QNodeAddr(2, 1))
    assert result == (-1, QNodeAddr(-1, -1), QNodeAddr(-1, -1), QNodeAddr(-1, -1))


def test_single_subnet1():
    paths = convert_to_QNodeAddr(
        [
            [(1, 1), (3, 1)],
            [(3, 2), (4, 1)],
            [(3, 4)],
            [(3, 3), (6, 3)],
            [(2, 1), (3, 4)],
        ]
    )

    result = find_network_boundary(paths, QNodeAddr(1, 1), QNodeAddr(2, 1))
    assert result == (3, QNodeAddr(3, 1), QNodeAddr(3, 2), QNodeAddr(3, 4))


def test_single_subnet2():
    paths = convert_to_QNodeAddr(
        [
            [(1, 1), (3, 1)],
            [(2, 1), (3, 4)],
        ]
    )

    result = find_network_boundary(paths, QNodeAddr(1, 1), QNodeAddr(2, 1))
    assert result == (3, QNodeAddr(3, 1), QNodeAddr(3, 4), QNodeAddr(3, 4))


def test_no_subnet():
    paths = convert_to_QNodeAddr(
        [
            [(1, 1), (3, 1)],
            [(4, 1)],
            [(2, 1), (5, 5)],
        ]
    )

    result = find_network_boundary(paths, QNodeAddr(1, 1), QNodeAddr(2, 1))
    assert result == (-1, QNodeAddr(-1, -1), QNodeAddr(-1, -1), QNodeAddr(-1, -1))


def test_subnet_at_initiator():
    paths = convert_to_QNodeAddr(
        [
            [(1, 1), (3, 1)],
            [(3, 2)],
            [(3, 3)],
            [(3, 4)],
            [(3, 5)],
            [(1, 99), (3, 99)],
        ]
    )

    result = find_network_boundary(paths, QNodeAddr(1, 1), QNodeAddr(3, 1))
    assert result == (3, QNodeAddr(3, 1), QNodeAddr(3, 2), QNodeAddr(3, 99))


def test_subnet_at_initiator_and_longer():
    paths = convert_to_QNodeAddr(
        [
            [(1, 1), (3, 1)],
            [(3, 2)],
            [(3, 3)],
            [(3, 4)],
            [(3, 5)],
            [(1, 99), (3, 99)],
            [(2, 1)],
        ]
    )

    result = find_network_boundary(paths, QNodeAddr(1, 1), QNodeAddr(2, 1))
    assert result == (3, QNodeAddr(3, 1), QNodeAddr(3, 2), QNodeAddr(3, 99))


def test_2subnets_at_initiator_and_longer():
    paths = convert_to_QNodeAddr(
        [
            [(1, 1), (3, 1)],
            [(3, 2)],
            [(3, 3)],
            [(3, 4)],
            [(3, 5)],
            [(1, 99), (3, 99)],
            [(2, 99), (4, 99)],
            [(4, 2)],
            [(2, 1), (4, 1)],
        ]
    )

    result = find_network_boundary(paths, QNodeAddr(1, 1), QNodeAddr(2, 1))
    assert result == (3, QNodeAddr(3, 1), QNodeAddr(3, 2), QNodeAddr(3, 99))


def test_subnet_at_initiator_and_dest_in_subnet():
    paths = convert_to_QNodeAddr(
        [
            [(1, 1), (3, 1)],
            [(3, 2)],
            [(3, 3)],
            [(3, 4)],
        ]
    )

    result = find_network_boundary(paths, QNodeAddr(1, 1), QNodeAddr(3, 4))
    assert result == (3, QNodeAddr(3, 1), QNodeAddr(3, 2), QNodeAddr(3, 4))
