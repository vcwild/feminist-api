import unittest
import subprocess
import pytest

CLI_NAME = "ada"


class TestCli(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        command = [
            "gcc",
            "./libs/fort/fort.c",
            "-I./libs/fort",
            "-I./includes",
            "-Wall",
            "-o",
            CLI_NAME,
            "./sources/cli.c",
        ]
        subprocess.call(command)

    @classmethod
    def tearDownClass(cls):
        command = ["rm", CLI_NAME]
        subprocess.call(command)

    def test_run_cli(self):
        command = [f"./{CLI_NAME}"]
        result = subprocess.run(command, capture_output=True).stdout

        expected_result = b"Usage: ./ada [OPTION]\n\nOptional arguments:\n  -c, --clear\t\t\tClear the server events log;\n\
  -e, --endpoints\t\tShow the available endpoints;\n  -h, --help\t\t\tPrints out the help menu;\n  -l, --list\t\t\tList the server requests;\n  -o, --logs\t\t\tRead the server logs;\n  -s, --show\t\t\tAlias to --endpoints;\n  -v, --version\t\t\tGet the current CLI version.\n"

        self.assertEqual(result, expected_result)

    def test_run_clear(self):
        command = [f"./{CLI_NAME}", "-c"]
        result = subprocess.run(command, capture_output=True).stdout

        expected_result = b"Clearing server events log...\n"

        self.assertEqual(result, expected_result)

    def test_run_endpoints(self):
        command = [f"./{CLI_NAME}", "-e"]
        result = subprocess.run(command, capture_output=True).stdout

        expected_result = b"Available endpoints:\n  http://localhost:8000/\n  http://localhost:8000/api\n  http://localhost:8000/mock\n"

        self.assertEqual(result, expected_result)

    def test_run_version(self):
        command = [f"./{CLI_NAME}", "-v"]
        result = subprocess.run(command, capture_output=True).stdout[
            : len(CLI_NAME) + 4
        ]

        expected_result = f"./{CLI_NAME} v"
        expected_result = bytes(expected_result, "utf-8")

        self.assertEqual(result, expected_result)


if __name__ == "__main__":
    unittest.main()
