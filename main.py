import os

import os
os.environ["MKL_NUM_THREADS"] = "1" 
os.environ["NUMEXPR_NUM_THREADS"] = "1" 
os.environ["OMP_NUM_THREADS"] = "1" 


import numpy
import time
import numpy as np


N = 1024


def matrix_multiply():
    for _ in range(1):
        A = numpy.random.randn(N, N).astype(numpy.float32)
        B = numpy.random.randn(N, N).astype(numpy.float32)

        t0 = time.monotonic()
        C = A @ B
        t1 = time.monotonic()

        FLOPS = N * N * (2 * N)
        s = t1 - t0

        print(f"GFLOP/S: {(FLOPS / s) * 1e-9}, {s*1e3:.2f} ms")
        np.savetxt('A.txt',A, fmt='%.7f')
        np.savetxt('B.txt',B, fmt='%.7f')
        np.savetxt('C.txt',C, fmt='%.7f')
    


if __name__ == '__main__':
    matrix_multiply()
