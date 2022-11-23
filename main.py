import os

# os.environ["MKL_NUM_THREADS"] = "1" 
# os.environ["NUMEXPR_NUM_THREADS"] = "1" 
# os.environ["OMP_NUM_THREADS"] = "1" 

import time
import numpy as np


N = 4096


def matrix_multiply():
    A = np.random.randn(N, N).astype(np.float32)
    B = np.random.randn(N, N).astype(np.float32)

    t0 = time.monotonic()
    C = A @ B
    t1 = time.monotonic()

    FLOPS = N * N * (2 * N)
    s = t1 - t0

    print(f"GFLOP/S: {(FLOPS / s) * 1e-9}, {s*1e3:.2f} ms")
    


if __name__ == '__main__':
    matrix_multiply()
