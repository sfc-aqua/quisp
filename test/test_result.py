"""
Tester of result of simulation.

As a future work, hope these with googletests.
THIS IS NOT A UNITTEST!

The details of each test, see quisp/quisp/network/test.ini
"""
import unittest
# This test is done on the docker container.
RESULT_FILE_PATH = "./testresults.txt"


class TestQuispResult(unittest.TestCase):
    """
    If you like to add new parameter, change here.
    """
    RESULT_SCHEMA = [
        "SrcNodeType",
        "ChannelType",
        "ChannelCost",
        "ChannelDistance",
        "ChannelFidelity",
        "BellPairPerSec",
        "DestNodeType",
        "Fidelity",
        "Xerror",
        "Zerror",
        "Yerror",
    ]

    def setUp(self):
        """
        setUp function is responsible for collecting test result and reform it.
        """
        f = open(RESULT_FILE_PATH)
        data = f.read()
        f.close()
        lines = data.split('\n')
        # formatting
        test_results = {}
        result = []
        counter = 0
        for ln in lines:
            if ln[:4] == "init":
                result = []
            elif ln == "next":
                test_results[counter] = result
                counter += 1
            elif ln != "":
                result.append(ln.lstrip())
        self.all_result = self._form_data(test_results)

    def _form_data(self, data):
        schema_size = len(self.RESULT_SCHEMA)
        all_result = {}
        for i, v in data.items():
            resar = []
            res_p = {}
            for index, val in enumerate(v):
                # NOT GOOD WAY FIXME
                try:
                    try:
                        res_p[self.RESULT_SCHEMA[index % schema_size]] = float(val.split("=")[1])
                    except ValueError:
                        res_p[self.RESULT_SCHEMA[index % schema_size]] = val.split("=")[1]
                except IndexError:
                    res_p[self.RESULT_SCHEMA[index % schema_size]] = val
                if val[:1] == "Y":  # FIXME this shouldn't hard coded
                    resar.append(res_p)
                    res_p = {}
            all_result[i] = resar
        return all_result

    def return_test_result(self, test_index):
        return self.all_result.get(test_index)

    def evaluation(self, result, estimated, neq=False, rtol=1e-05, etol=1e-08):
        """
        Arg:
            result: Test result
            estimated: Estimated result
            neq: Neally equal flag (default False)
        """
        for i, v in estimated.items():
            if i not in self.RESULT_SCHEMA:
                raise KeyError("Keyword %s is not in RESULT SCHEMA!" % i)
            else:
                # Do not use .get, because key error removed above and
                # if you use get, it's hard to recognize what is error.
                actual = result[i]
                est = estimated[i]
                if not neq:
                    self.assertEqual(actual, est)
                else:
                    self.assertAlmostEqual(actual, est)
                    # self.assertEqual(True, math.isclose(actual, est,
                    #                                     rel_tol=rtol,
                    #                                     abs_tol=etol))

    def test_0(self):
        """
        Test 0 no error.
        """
        test_number = 0  # TEST0
        results = self.return_test_result(test_number)
        estimated_result = {"Fidelity": 1.0,
                            "Xerror": 0.0,
                            "Zerror": 0.0,
                            "Yerror": 0.0}
        for res in results:
            self.evaluation(res, estimated_result, neq=False)

    def test_1(self):
        """
        Test 1
        with Xerror
        widh darkcount
        """
        test_number = 1  # TEST1
        results = self.return_test_result(test_number)
        # these are prepared for all connections
        expected_outcome = [{"Fidelity": 0.476815,
                              "Xerror": 0.523185,
                              "Zerror": 0.00651815,
                              "Yerror": -0.00651815},
                             {"Fidelity": 0.513999,
                              "Xerror": 0.486001,
                              "Zerror": 0.0127393,
                              "Yerror": -0.0127393},
                             {"Fidelity": 0.476815,
                              "Xerror": 0.523185,
                              "Zerror": 0.00651815,
                              "Yerror": -0.00651815},
                             {"Fidelity": 0.513999,
                              "Xerror": 0.486001,
                              "Zerror": 0.0127393,
                              "Yerror": -0.0127393}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_2(self):
        """
        Test 2
        with Zerror
        with Darkcount
        """
        test_number = 2  # TEST2
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 0.489214,
                              "Xerror": -0.00894144,
                              "Zerror": 0.510786,
                              "Yerror": 0.00894144},
                             {"Fidelity": 0.503574,
                              "Xerror": -0.00553946,
                              "Zerror": 0.496426,
                              "Yerror": 0.00553946},
                             {"Fidelity": 0.489214,
                              "Xerror": -0.00894144,
                              "Zerror": 0.510786,
                              "Yerror": 0.00894144},
                             {"Fidelity": 0.503574,
                              "Xerror": -0.00553946,
                              "Zerror": 0.496426,
                              "Yerror": 0.00553946}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)
        
    def test_3(self):
        """
        Test 3
        with Yerror
        with Darkcount
        CHECK is this correct?
        """
        test_number = 3  # TEST3
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 0.508346,
                              "Xerror": 0.491654,
                              "Zerror": 0.0121146,
                              "Yerror": -0.0121146},
                             {"Fidelity": 0.484926,
                              "Xerror": 0.515074,
                              "Zerror": -0.00771101,
                              "Yerror": 0.00771101},
                             {"Fidelity": 0.508346,
                              "Xerror": 0.491654,
                              "Zerror": 0.0121146,
                              "Yerror": -0.0121146},
                             {"Fidelity": 0.484926,
                              "Xerror": 0.515074,
                              "Zerror": -0.00771101,
                              "Yerror": 0.00771101}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_4(self):
        """
        Test 4
        with MemoryXerror
        no darkcount
        purificationtype 3003
        """
        test_number = 4  # TEST4
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 0.499229,
                              "Xerror": 0.500771,
                              "Zerror": -0.00856277,
                              "Yerror": 0.00856277},
                             {"Fidelity": 0.502682,
                              "Xerror": 0.497318,
                              "Zerror": -0.00521319,
                              "Yerror": 0.00521319},
                             {"Fidelity": 0.499229,
                              "Xerror": 0.500771,
                              "Zerror": -0.00856277,
                              "Yerror": 0.00856277},
                             {"Fidelity": 0.502682,
                              "Xerror": 0.497318,
                              "Zerror": -0.00521319,
                              "Yerror": 0.00521319}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)
        
    def test_5(self):
        """
        Test 5
        with Memory Yerror
        with Darkcount
        """
        test_number = 5  # TEST5
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 0.257418,
                              "Xerror": 0.234406,
                              "Zerror": 0.273832,
                              "Yerror": 0.234344},
                             {"Fidelity": 0.240313,
                              "Xerror": 0.267682,
                              "Zerror": 0.250084,
                              "Yerror": 0.241921},
                             {"Fidelity": 0.257418,
                              "Xerror": 0.234406,
                              "Zerror": 0.273832,
                              "Yerror": 0.234344},
                             {"Fidelity": 0.240313,
                              "Xerror": 0.267682,
                              "Zerror": 0.250084,
                              "Yerror": 0.241921}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_6(self):
        """
        Test 6
        with MemoryZerror
        with Darkcount
        """
        test_number = 6  # TEST6
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 0.515494,
                              "Xerror": -0.0173436,
                              "Zerror": 0.484506,
                              "Yerror": 0.0173436},
                             {"Fidelity": 0.515495,
                              "Xerror": -0.0238174,
                              "Zerror": 0.484505,
                              "Yerror": 0.0238174},
                             {"Fidelity": 0.515494,
                              "Xerror": -0.0173436,
                              "Zerror": 0.484506,
                              "Yerror": 0.0173436},
                             {"Fidelity": 0.515495,
                              "Xerror": -0.0238174,
                              "Zerror": 0.484505,
                              "Yerror": 0.0238174}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_7(self):
        """
        Test 7
        with Memory Energy Excite
        with 1031 purification
        """
        test_number = 7  # TEST7
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 0.47398,
                              "Xerror": 0.0148775,
                              "Zerror": 0.52602,
                              "Yerror": -0.0148775},
                             {"Fidelity": 0.488274,
                              "Xerror": -0.00279713,
                              "Zerror": 0.511726,
                              "Yerror": 0.00279713},
                             {"Fidelity": 0.47398,
                              "Xerror": 0.0148775,
                              "Zerror": 0.52602,
                              "Yerror": -0.0148775},
                             {"Fidelity": 0.488274,
                              "Xerror": -0.00279713,
                              "Zerror": 0.511726,
                              "Yerror": 0.00279713}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_8(self):
        """
        Test 8
        with Memory Energy Relaxation
        """
        test_number = 8  # TEST8
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 0.505806,
                              "Xerror": -0.0117037,
                              "Zerror": 0.494194,
                              "Yerror": 0.0117037},
                             {"Fidelity": 0.483137,
                              "Xerror": 0.00313725,
                              "Zerror": 0.516863,
                              "Yerror": -0.00313725},
                             {"Fidelity": 0.505806,
                              "Xerror": -0.0117037,
                              "Zerror": 0.494194,
                              "Yerror": 0.0117037},
                             {"Fidelity": 0.483137,
                              "Xerror": 0.00313725,
                              "Zerror": 0.516863,
                              "Yerror": -0.00313725}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_9(self):
        """
        Test 9
        with MemoryCompletelyMixed
        """
        test_number = 9  # TEST9
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 2.662890e-01,
                              "Xerror": 2.278130e-01,
                              "Zerror": 2.546770e-01,
                              "Yerror": 2.512210e-01},
                             {"Fidelity": 2.402990e-01,
                              "Xerror": 2.459760e-01,
                              "Zerror": 2.740240e-01,
                              "Yerror": 2.397010e-01},
                             {"Fidelity": 2.662890e-01,
                              "Xerror": 2.278130e-01,
                              "Zerror": 2.546770e-01,
                              "Yerror": 2.512210e-01},
                             {"Fidelity": 2.402990e-01,
                              "Xerror": 2.459760e-01,
                              "Zerror": 2.740240e-01,
                              "Yerror": 2.397010e-01}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_10(self):
        """
        Test 10
        with internal hom loss
        with 2002 purification
        """
        test_number = 10  # TEST10
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_11(self):
        """
        Test 11
        with internal hom error This is not implemented yet!
        with Darkcount
        with 1221 purification
        """
        test_number = 11  # TEST11
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_12(self):
        """
        Test 12
        with hom loss error
        with Darkcount
        with purification 1031
        """
        test_number = 12  # TEST12
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_13(self):
        """
        Test 13
        with homerror
        with Darkcount
        with 1001 purification
        """
        test_number = 13  # TEST13
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_14(self):
        """
        Test 14
        with Measurement Error X
        with 1221 purification
        """
        test_number = 14  # TEST14
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1.000000e+00,
                              "Xerror": 0.000000e+00,
                              "Zerror": 0.000000e+00,
                              "Yerror": 0.000000e+00},
                             {"Fidelity": 9.993500e-01,
                              "Xerror": 6.501950e-04,
                              "Zerror": 6.501950e-04,
                              "Yerror": -6.501950e-04},
                             {"Fidelity": 1.000000e+00,
                              "Xerror": 0.000000e+00,
                              "Zerror": 0.000000e+00,
                              "Yerror": 0.000000e+00},
                             {"Fidelity": 9.993500e-01,
                              "Xerror": 6.501950e-04,
                              "Zerror": 6.501950e-04,
                              "Yerror": -6.501950e-04}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_15(self):
        """
        Test 15
        with Measurement Error Y
        with 3003 purification
        """
        test_number = 15  # TEST13
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 9.993220e-01,
                              "Xerror": 6.775070e-04,
                              "Zerror": -6.775070e-04,
                              "Yerror": 6.775070e-04},
                             {"Fidelity": 9.993550e-01,
                              "Xerror": -6.451610e-04,
                              "Zerror": 6.451610e-04,
                              "Yerror": 6.451610e-04},
                             {"Fidelity": 9.993220e-01,
                              "Xerror": 6.775070e-04,
                              "Zerror": -6.775070e-04,
                              "Yerror": 6.775070e-04},
                             {"Fidelity": 9.993550e-01,
                              "Xerror": -6.451610e-04,
                              "Zerror": 6.451610e-04,
                              "Yerror": 6.451610e-04}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_16(self):
        """
        Test 16
        with Measurement Error Z
        with 1221 purification
        """
        test_number = 16  # TEST13
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 9.993670e-01,
                              "Xerror": 6.329110e-04,
                              "Zerror": 6.329110e-04,
                              "Yerror": -6.329110e-04},
                             {"Fidelity": 9.987260e-01,
                              "Xerror": 1.273890e-03,
                              "Zerror": 1.273890e-03,
                              "Yerror": -1.273890e-03},
                             {"Fidelity": 9.993670e-01,
                              "Xerror": 6.329110e-04,
                              "Zerror": 6.329110e-04,
                              "Yerror": -6.329110e-04},
                             {"Fidelity": 9.987260e-01,
                              "Xerror": 1.273890e-03,
                              "Zerror": 1.273890e-03,
                              "Yerror": -1.273890e-03}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_17(self):
        """
        Test 17
        with H gate Error X
        with 1221 purification
        """
        test_number = 17  # TEST13
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1.000000e+00,
                              "Xerror": 0.000000e+00,
                              "Zerror": 0.000000e+00,
                              "Yerror": 0.000000e+00},
                             {"Fidelity": 1.000000e+00,
                              "Xerror": 0.000000e+00,
                              "Zerror": 0.000000e+00,
                              "Yerror": 0.000000e+00},
                             {"Fidelity": 1.000000e+00,
                              "Xerror": 0.000000e+00,
                              "Zerror": 0.000000e+00,
                              "Yerror": 0.000000e+00},
                             {"Fidelity": 1.000000e+00,
                              "Xerror": 0.000000e+00,
                              "Zerror": 0.000000e+00,
                              "Yerror": 0.000000e+00}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_18(self):
        """
        Test 18
        with H gate Y error
        with 1011 purification
        """
        test_number = 18  # TEST13
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_19(self):
        """
        Test 19
        with MemError Z
        with 1011 purification
        """
        test_number = 19  # TEST13
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_20(self):
        """
        Test 20
        with X gate X error
        with 2002 purification
        """
        test_number = 20  # TEST13
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_21(self):
        """
        Test 21
        with X gate Y error
        with 2002 purification
        """
        test_number = 21  # TEST13
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_22(self):
        """
        Test 22
        with X gate Z error
        with 2002 purification
        """
        test_number = 22  # TEST13
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_23(self):
        """
        Test 23
        with Z gate X error
        with 3003 purification
        """
        test_number = 23  # TEST13
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_24(self):
        """
        Test 24
        with Z gate Y error
        with  3003 purification
        """
        test_number = 24  # TEST13
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_25(self):
        """
        Test 25
        with Z gate Z error
        with 3003 purification
        """
        test_number = 25  # TEST25
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_26(self):
        """
        Test 26
        with CNOT IZ error
        with 1221 purification
        """
        test_number = 26  # TEST26
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_27(self):
        """
        Test 27
        with CNOT ZI error
        with 1221 purification
        """
        test_number = 27  # TEST27
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_28(self):
        """
        Test 28
        with CNOT ZZ error
        with 1221 purification
        """
        test_number = 28  # TEST28
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 9.987330e-01,
                              "Xerror": -1.267430e-03,
                              "Zerror": 1.267430e-03,
                              "Yerror": 1.267430e-03},
                             {"Fidelity": 9.987220e-01,
                              "Xerror": 4.976000e-05,
                              "Zerror": 1.278260e-03,
                              "Yerror": -4.976000e-05},
                             {"Fidelity": 9.987330e-01,
                              "Xerror": -1.267430e-03,
                              "Zerror": 1.267430e-03,
                              "Yerror": 1.267430e-03},
                             {"Fidelity": 9.987220e-01,
                              "Xerror": 4.976000e-05,
                              "Zerror": 1.278260e-03,
                              "Yerror": -4.976000e-05}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)
    
    def test_29(self):
        """
        Test 29
        with CNOT ZX error
        with 1221 purification
        """
        test_number = 29  # TEST29
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 9.987200e-01,
                              "Xerror": 1.279630e-03,
                              "Zerror": 7.368330e-06,
                              "Yerror": -7.368330e-06},
                             {"Fidelity": 1.000000e+00,
                              "Xerror": 0.000000e+00,
                              "Zerror": 0.000000e+00,
                              "Yerror": 0.000000e+00},
                             {"Fidelity": 9.987200e-01,
                              "Xerror": 1.279630e-03,
                              "Zerror": 7.368330e-06,
                              "Yerror": -7.368330e-06},
                             {"Fidelity": 1.000000e+00,
                              "Xerror": 0.000000e+00,
                              "Zerror": 0.000000e+00,
                              "Yerror": 0.000000e+00}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)

    def test_30(self):
        """
        Test 30
        with CNOT XI error
        with 1221 purification
        """
        test_number = 30  # TEST30
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 9.987200e-01,
                              "Xerror": 1.279630e-03,
                              "Zerror": 7.368330e-06,
                              "Yerror": -7.368330e-06},
                             {"Fidelity": 1.000000e+00,
                              "Xerror": 0.000000e+00,
                              "Zerror": 0.000000e+00,
                              "Yerror": 0.000000e+00},
                             {"Fidelity": 9.987200e-01,
                              "Xerror": 1.279630e-03,
                              "Zerror": 7.368330e-06,
                              "Yerror": -7.368330e-06},
                             {"Fidelity": 1.000000e+00,
                              "Xerror": 0.000000e+00,
                              "Zerror": 0.000000e+00,
                              "Yerror": 0.000000e+00}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)
    
    def test_31(self):
        """
        Test 31
        with CNOT XX error
        with 1221 purification
        """
        test_number = 31  # TEST31
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1.000000e+00,
                              "Xerror": 0.000000e+00,
                              "Zerror": 0.000000e+00,
                              "Yerror": 0.000000e+00},
                             {"Fidelity": 9.980290e-01,
                              "Xerror": 1.970690e-03,
                              "Zerror": 6.853480e-04,
                              "Yerror": -6.853480e-04},
                             {"Fidelity": 1.000000e+00,
                              "Xerror": 0.000000e+00,
                              "Zerror": 0.000000e+00,
                              "Yerror": 0.000000e+00},
                             {"Fidelity": 9.980290e-01,
                              "Xerror": 1.970690e-03,
                              "Zerror": 6.853480e-04,
                              "Yerror": -6.853480e-04}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)
    
    def test_32(self):
        """
        Test 32
        with CNOT IY error
        with 1221 purification
        """
        test_number = 32  # TEST32
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)
    
    def test_33(self):
        """
        Test 33
        with CNOT YI error
        with 1221 purification
        """
        test_number = 33  # TEST34
        results = self.return_test_result(test_number)
        expected_outcome = [{"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0},
                             {"Fidelity": 1,
                              "Xerror": 0,
                              "Zerror": 0,
                              "Yerror": 0}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)
    
    def test_34(self):
        """
        Test 34
        with CNOT YY error
        with 1221 purification
        """
        test_number = 34  # TEST35
        results = self.return_test_result(test_number)
        # print("=======")
        # print("expected_outcome = [", end="")
        # for res in results:
        #     print('{"Fidelity": %e,' % res["Fidelity"])
        #     print('"Xerror": %e,' % res["Xerror"])
        #     print('"Zerror": %e,' % res["Zerror"])
        #     print('"Yerror": %e},' % res["Yerror"])
        # print("]")
        # print("=======")
        expected_outcome = [{"Fidelity": 9.987330e-01,
                              "Xerror": -1.267430e-03,
                              "Zerror": 1.267430e-03,
                              "Yerror": 1.267430e-03},
                             {"Fidelity": 9.967510e-01,
                              "Xerror": 2.020450e-03,
                              "Zerror": 1.963610e-03,
                              "Yerror": -7.351080e-04},
                             {"Fidelity": 9.987330e-01,
                              "Xerror": -1.267430e-03,
                              "Zerror": 1.267430e-03,
                              "Yerror": 1.267430e-03},
                             {"Fidelity": 9.967510e-01,
                              "Xerror": 2.020450e-03,
                              "Zerror": 1.963610e-03,
                              "Yerror": -7.351080e-04}]
        for res, es in zip(results, expected_outcome):
            self.evaluation(res, es, neq=True)


if __name__ == "__main__":
    unittest.main()
