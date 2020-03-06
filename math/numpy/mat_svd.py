import scipy
import numpy as np

print('============SVD===================\n')
# A = np.mat("4 11 14;8 7 -2")
np.random.seed(1987)
A = np.random.randint(-10, 10 , (2,4))

print('shape A:', A.shape, A)
U,sigma,V = np.linalg.svd(A, full_matrices = False ,compute_uv = True)
# print('U', U)
# print('U[0]', U[0])
# print('sigma', sigma)
# print('V', V)
# print('V[0]', V[0])
# print('validation of the svd')

print("shape of U:", U.shape)
print("shape of sigma:", sigma.shape)
print("shape of V:", V.shape)

print('U*Sigma_matrix*V.H:', U.dot(np.diag(sigma)).dot(V))
sigma_mat = np.diag(sigma)

# smat[2][2] = 0
# smat[3][3] = 0


