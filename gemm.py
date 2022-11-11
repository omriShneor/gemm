import argparse
import numpy as np
import time

N = 4096 
GFLOPS = 2 * N * N * N * 1e-9


def save_to_file(mat: np.array, file_name: str, premissions: str, write_to_file: bool):
    if not write_to_file:
        print(f"write_to_file is set to: {write_to_file}, will not write to file: {file_name}")
        return
    
    with open(file_name, premissions) as f:
        for line in mat:
            np.savetxt(f, line, fmt='%.5f')    
    

def parse_args():
    parser = argparse.ArgumentParser()
    # Adding optional argument
    parser.add_argument("-w", "--Write-to-file", action='store_true', help = "If -w is specified the metrices A,B,C will be written to files A.txt, B.txt, C.txt")
    args=parser.parse_args()
    return args

def main():
    A = np.matrix(np.random.rand(N,N)) # NxN matrix with values in range [0,1)
    B = np.matrix(np.random.rand(N,N)) # NxN matrix with values in range [0,1)
    st = time.monotonic()
    C = A @ B # multiply A with B
    en = time.monotonic()
    exec_time = en-st
    print(f"Took {exec_time:.5f} seconds to multiply A with B")
    print(f"Number of GFLOP/S with matmul in python: {(GFLOPS/exec_time):.4f}")
 


if __name__ == "__main__":
    # args = parse_args()
    main()
