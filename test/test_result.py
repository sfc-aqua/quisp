"""
Tester of result of simulation.

As a future work, hope these with googletests.
THIS IS NOT A UNITTEST!

The details of each test, see quisp/quisp/network/test.ini
"""
import unittest
import math
# This test is done on the docker container.
RESULT_FILE_PATH = "/root/quisp/test/testresults.txt"


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
                    self.assertEqual(True, math.isclose(actual, est,
                                                        rel_tol=rtol,
                                                        abs_tol=etol))

    def test_0(self):
        """
        Test 0 no error.
        """
        test_numer = 0  # TEST0
        results = self.return_test_result(test_numer)
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
        test_numer = 1  # TEST1
        results = self.return_test_result(test_numer)
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
        test_numer = 2  # TEST2
        results = self.return_test_result(test_numer)
        # print(len(results))
        # for res in results:
        #     print(res["Fidelity"])
        #     print(res["Xerror"])
        #     print(res["Zerror"])
        #     print(res["Yerror"])
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
        
    # def test_3(self):
    #     """
    #     Test 3
    #     with Yerror
    #     with Darkcount
    #     """
    #     test_numer = 3  # TEST3
    #     results = self.return_test_result(test_numer)
        # print(len(results))
        # for res in results:
        #     print(res["Fidelity"])
        #     print(res["Xerror"])
        #     print(res["Zerror"])
        #     print(res["Yerror"])
    #     estimated_results = [{"Fidelity": 0.49353,
    #                           "Xerror": 0.00774839,
    #                           "Zerror": 0.50647,
    #                           "Yerror": -0.00774839},
    #                          {"Fidelity": 0.496583,
    #                           "Xerror": -0.0158633,
    #                           "Zerror": 0.502209,
    #                           "Yerror": 0.017071},
    #                          {"Fidelity": 0.49353,
    #                           "Xerror": 0.00774839,
    #                           "Zerror": 0.50647,
    #                           "Yerror": -0.00774839},
    #                          {"Fidelity": 0.496583,
    #                           "Xerror": -0.0158633,
    #                           "Zerror": 0.502209,
    #                           "Yerror": 0.017071}]
    #     for res, es in zip(results, estimated_results):
    #         self.evaluation(res, es, neq=True)


if __name__ == "__main__":
    unittest.main()
