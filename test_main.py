import unittest
from main import Laguerre
import numpy as np

class TestLaggure(unittest.TestCase):
    def test_fx(self):
        self.function = 'x**2'
        self.assertEqual(Laguerre.fx(self,-2), 4)
        self.function = 'x+8+x**2'
        self.assertEqual(Laguerre.fx(self, 0), 8)
    def test_lk(self):
        Unit_1 = Laguerre('x**2', 1, 0, 5, 2)
        self.assertEqual(Unit_1.lk(self, 3, 0), np.exp(-0.5*3))