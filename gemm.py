import argparse
import numpy as np
import time

N = 2 ** 10 # 1024
FLOPS = 2 * N * N * N


def save_to_file(mat: np.array, file_name: str, premissions: str, write_to_file: bool):
    if not write_to_file:
        return
    with open(file_name, premissions) as f:
        for line in mat:
            np.savetxt(f, line, fmt='%.2f')
    

def parse_args():
    parser = argparse.ArgumentParser()
    # Adding optional argument
    parser.add_argument("-w", "--Write-to-file", action='store_true', help = "If -w is specified the metrices A,B,C will be written to files A.txt, B.txt, C.txt")
    args=parser.parse_args()
    return args

def main(write_to_file=True):
    A = np.random.rand(N,N) # NxN matrix with values in range [0,1)
    B = np.random.rand(N,N) # NxN matrix with values in range [0,1)
    save_to_file(A, "A.txt", "w", write_to_file=write_to_file)
    save_to_file(B, "B.txt", "w", write_to_file=write_to_file)
    st = time.monotonic()
    C = A @ B # multiply A with B
    en = time.monotonic()
    save_to_file(C, "C.txt", "w", write_to_file=write_to_file) 
    exec_time = en-st
    print(f"Took {exec_time:.5f} seconds to multiply A with B")
    print(f"Number of GFLOPS: {FLOPS*1e-9/exec_time:.4f}")





if __name__ == "__main__":
    args = parse_args()
    main(write_to_file=args.Write_to_file)
