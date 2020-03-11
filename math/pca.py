# -*- coding: utf-8 -*-

import random
import time
import numpy as np
from sklearn.decomposition import PCA


def sim(vec1, vec2):
    sum = vec1.dot(vec2)
    sum /= np.linalg.norm(vec1, ord=2)
    sum /= np.linalg.norm(vec2, ord=2)
    return sum

random.seed(0)
np.random.seed(0)

x = np.array([1,2,3,4,5,6,7,8,9,10])
mat = np.random.rand(10,10)
mat = np.matrix("1 2; 3 4")
mat = np.matrix([[-1,1,0],
                 [-4,3,0],
                 [ 1,0,2]])

mat_mean = mat - mat.mean(axis=1)
print(mat_mean)
mat_cov = np.cov(mat_mean)
print(mat_cov)
print(np.dot(mat_mean, mat_mean.T))

exit(0)
#mat_cov = mat
eigenVal, eigenVec = np.linalg.eig(mat_cov)

print(eigenVal)
print(eigenVec)
print("=======================")
#exit(0)

pca = PCA(n_components=3)
#newData = pca.fit_transform(mat_cov)
newData = pca.fit(mat_cov)

print(pca.singular_values_)
print(pca.components_)
print(sim(pca.components_[0], pca.components_[1]))
print("=======================")

sorted_index = sorted(range(len(eigenVal)), key=lambda k: -eigenVal[k])
for i in range(len(sorted_index)):
    print(sorted_index[i])
    print(pca.components_[i])
    print(eigenVec[sorted_index[i]])
    print(sim(eigenVec[sorted_index[i]], pca.components_[i]))



# xl = eigenVec.T[1]
# print(mat_mean.T.__mul__(np.mat(xl).T))

