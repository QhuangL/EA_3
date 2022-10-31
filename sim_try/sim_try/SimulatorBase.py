from code import interact
import numpy as np

class Dot:
    def __init__(self, n) -> None:
        self.n = n
        self.m = np.zeros(self.n)
        self.p = np.zeros((self.n, 3))
        self.v = np.zeros((self.n, 3))
        self.a = np.zeros((self.n, 3))



        111111
        111111111
        





class Simulator:
    def __init__(self,n):
        self.n = n
        self.dot = Dot(self.n)
        self.spring = Spring(m)
        self.Fext = n*3
        self.Fint = n*3
        self.F = Fext + Fint = np.zeros((n,3))

        self.dt

    def setFext():
        pass

    def interact(self, self.dot.p, self.spring.k, self.spring.L0, self.Fext):
        pass
    # return 

    def integrate(self, self.F , self.dot.p, self.dot.v, self.dot.p):
        pass
        self.dot.p
        self.dot.v
        self.dot.a

    def show(self):




        

for:
    setFext()
    interact()
    interact
""

import numba
import cupy
import pycuda
