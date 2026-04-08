import os
import sys

import numpy as np

# Set data directory
DATA_DIR = "./test_data"
if not os.path.exists(DATA_DIR):
    os.makedirs(DATA_DIR)

def save_matrix(name, matrix):
    with open(os.path.join(DATA_DIR, f"{name}.txt"), "w") as f:
        f.write(f"{matrix.shape[0]} {matrix.shape[1]}\n")
        for row in matrix:
            f.write(" ".join(map(str, row)) + "\n")

def generate_data(M, N, K):
    # Density for sparse matrix simulation
    pct = 0.2
    
    A = np.zeros((M, N))
    B = np.zeros((M, N))
    C = np.zeros((M, K))
    D = np.zeros((K, N))
    
    # Fill matrices randomly
    for i in range(M):
        for j in range(N):
            if np.random.rand() < pct:
                A[i, j] = np.random.randint(1, 10)
            if np.random.rand() < pct:
                B[i, j] = np.random.randint(1, 10)
    
    for i in range(M):
        for j in range(K):
            if np.random.rand() < pct:
                C[i, j] = np.random.randint(1, 10)

    for i in range(K):
        for j in range(N):
            if np.random.rand() < pct:
                D[i, j] = np.random.randint(1, 10)
                
    # Operations
    add_res = A + B
    sub_res = A - B
    mul_res = np.dot(C, D)
    
    # Element-wise division
    div_res = np.zeros_like(A)
    mask = B != 0
    div_res[mask] = A[mask] / B[mask]
    
    trans_res = A.T
    
    save_matrix("input_a", A)
    save_matrix("input_b", B)
    save_matrix("input_c", C)
    save_matrix("input_d", D)
    save_matrix("expected_add", add_res)
    save_matrix("expected_sub", sub_res)
    save_matrix("expected_mul", mul_res)
    save_matrix("expected_div", div_res)
    save_matrix("expected_trans", trans_res)
    print(f"Test data generated in {DATA_DIR}")

if __name__ == "__main__":
    M = int(sys.argv[1]) if len(sys.argv) > 1 else 10
    N = int(sys.argv[2]) if len(sys.argv) > 2 else 10
    K = int(sys.argv[3]) if len(sys.argv) > 3 else 5
    generate_data(M, N, K)
