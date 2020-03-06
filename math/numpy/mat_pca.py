# -*- coding: utf-8 -*-
import scipy
import numpy as np
from sklearn import decomposition

def zeroMean(dataMat):
    meanVal=np.mean(dataMat,axis=0)     #按列求均值，即求各个特征的均值
    newData=dataMat-meanVal
    return newData,meanVal

np.random.seed(1987)
A = np.random.randint(-10, 10 , (3,3))
A = np.array([
    [1,2,3],
    [2,4,6],
    [3,6,9]
    ])

A, _ = zeroMean(A)
print('shape A:', A.shape, A)

pca = decomposition.PCA(n_components=2)
trans = pca.fit_transform(A)

print trans
print pca.explained_variance_
exit(0)

print "before PCA"
print A[0].dot(A[1])
print A[1].dot(A[2])
print A[0].dot(A[2])

print "after PCA"
print trans[0].dot(trans[1])
print trans[1].dot(trans[2])
print trans[0].dot(trans[2])
