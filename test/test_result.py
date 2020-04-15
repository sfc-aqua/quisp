"""
Tester of result of simulation.

As a future work, hope these with googletests.
THIS IS NOT A UNITTEST!

The details of each test, see quisp/quisp/network/test.ini
"""
import unittest
import math
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
        estimated_results = [{"Fidelity": 0.476815,
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
        for res, es in zip(results, estimated_results):
            self.evaluation(res, es, neq=True)

    def test_2(self):
        """
        Test 2
        with Zerror
        with Darkcount
        """
        test_number = 2  # TEST2
        results = self.return_test_result(test_number)
        estimated_results = [{"Fidelity": 0.489214,
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
        for res, es in zip(results, estimated_results):
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
        estimated_results = [{"Fidelity": 0.508346,
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
        for res, es in zip(results, estimated_results):
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
        estimated_results = [{"Fidelity": 0.499229,
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
        for res, es in zip(results, estimated_results):
            self.evaluation(res, es, neq=True)
        
    def test_5(self):
        """
        Test 5
        with Memory Yerror
        with Darkcount
        """
        test_number = 5  # TEST5
        results = self.return_test_result(test_number)
        estimated_results = [{"Fidelity": 0.257418,
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
        for res, es in zip(results, estimated_results):
            self.evaluation(res, es, neq=True)

    def test_6(self):
        """
        Test 6
        with MemoryZerror
        with Darkcount
        """
        test_number = 6  # TEST6
        results = self.return_test_result(test_number)
        estimated_results = [{"Fidelity": 0.515494,
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
        for res, es in zip(results, estimated_results):
            self.evaluation(res, es, neq=True)

    def test_7(self):
        """
        Test 7
        with Memory Energy Excite
        with 1031 purification
        """
        test_number = 7  # TEST7
        results = self.return_test_result(test_number)
        estimated_results = [{"Fidelity": 0.47398,
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
        for res, es in zip(results, estimated_results):
            self.evaluation(res, es, neq=True)

    def test_8(self):
        """
        Test 8
        with Memory Energy Relaxation
        """
        test_number = 8  # TEST8
        results = self.return_test_result(test_number)
        estimated_results = [{"Fidelity": 0.505806,
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
        for res, es in zip(results, estimated_results):
            self.evaluation(res, es, neq=True)

    def test_9(self):
        """
        Test 9
        with MemoryCompletelyMixed
        with 5556 purification
        """
        test_number = 9  # TEST3
        results = self.return_test_result(test_number)
        estimated_results = [{"Fidelity": 1.0,
                              "Xerror": 0.0,
                              "Zerror": 0.0,
                              "Yerror": 0.0},
                             {"Fidelity": 1.0,
                              "Xerror": 0.0,
                              "Zerror": 0.0,
                              "Yerror": 0.0},
                             {"Fidelity": 1.0,
                              "Xerror": 0.0,
                              "Zerror": 0.0,
                              "Yerror": 0.0},
                             {"Fidelity": 1.0,
                              "Xerror": 0.0,
                              "Zerror": 0.0,
                              "Yerror": 0.0}]
        for res, es in zip(results, estimated_results):
            self.evaluation(res, es, neq=True)

    def test_10(self):
        """
        Test 10
        with internal hom loss
        with 2002 purification
        """
        test_number = 10  # TEST10
        results = self.return_test_result(test_number)
        estimated_results = [{"Fidelity": 0.50896,
                              "Xerror": -0.000373404,
                              "Zerror": 0.49104,
                              "Yerror": 0.000373404},
                             {"Fidelity": 0.508261,
                              "Xerror": 0.00953022,
                              "Zerror": 0.491739,
                              "Yerror": -0.00953022},
                             {"Fidelity": 0.50896,
                              "Xerror": -0.000373404,
                              "Zerror": 0.49104,
                              "Yerror": 0.000373404},
                             {"Fidelity": 0.508261,
                              "Xerror": 0.00953022,
                              "Zerror": 0.491739,
                              "Yerror": -0.00953022}]
        for res, es in zip(results, estimated_results):
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
        estimated_results = [{"Fidelity": 1,
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
        for res, es in zip(results, estimated_results):
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
        estimated_results = [{"Fidelity": 1,
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
        for res, es in zip(results, estimated_results):
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
        # print("=======")
        # print("test", test_number)
        # print("estimated_results = [", end="")
        # for res in results:
        #     print('{"Fidelity": %d,' % res["Fidelity"])
        #     print('"Xerror": %d,' % res["Xerror"])
        #     print('"Zerror": %d,' % res["Zerror"])
        #     print('"Yerror": %d},' % res["Yerror"])
        # print("]")
        # print("=======")
        estimated_results = [{"Fidelity": 1,
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
        for res, es in zip(results, estimated_results):
            self.evaluation(res, es, neq=True)


if __name__ == "__main__":
    unittest.main()
