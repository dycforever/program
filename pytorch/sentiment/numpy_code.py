#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

import numpy as np
def softmax(x):
    """
    Compute the softmax function for each row of the input x.

    Arguments:
    x -- A N dimensional vector or M x N dimensional numpy matrix.

    Return:
    x -- You are allowed to modify x in-place
    """
    orig_shape = x.shape

    if len(x.shape) > 1:
        # Matrix
        exp_minmax = lambda x: np.exp(x - np.max(x))
        denom = lambda x: 1.0 / np.sum(x)
        x = np.apply_along_axis(exp_minmax,1,x)
        denominator = np.apply_along_axis(denom,1,x)

        if len(denominator.shape) == 1:
            denominator = denominator.reshape((denominator.shape[0],1))

        x = x * denominator
    else:
        # Vector
        x_max = np.max(x)
        x = x - x_max
        numerator = np.exp(x)
        denominator =  1.0 / np.sum(numerator)
        x = numerator.dot(denominator)

    assert x.shape == orig_shape
    return x

def convert_to_one_hot(y, C):
    return np.eye(C)[y.reshape(-1)].T

y = np.array([1,2,3,4])
convert_to_one_hot(y,5)

# array([[ 0.,  0.,  0.,  0.],#        [ 1.,  0.,  0.,  0.],#        [ 0.,  1.,  0.,  0.],#        [ 0.,  0.,  1.,  0.],#        [ 0.,  0.,  0.,  1.]])
