import unittest
from unittest import TestCase

from rle_program import count_runs, to_hex_string, encode_rle, get_decoded_length, decode_rle, string_to_data

class TestRLEProgram(unittest.TestCase):
    def test_count_runs(self):
        self.assertEqual(count_runs(
            [1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,1,2,3,4,5,1,2,3,4,5]
        ), 25)
        self.assertEqual(count_runs(
            [4,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,7]
        ), 6)



    def test_to_hex_string(self):
        self.assertEqual(to_hex_string([3, 15, 6, 4]), "3f64")


if __name__ == '__main__':
    unittest.main()