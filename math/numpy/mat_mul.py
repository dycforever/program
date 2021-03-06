
import numpy as np

# mat = np.array([[-5, 5, 0, 0, 0],
#                 [-3, 0, 3, 0, 0],
#                 [0, -7, 0, 7, 0],
#                 [0, 0, 1, -1, 0],
#                 [0, 0, 0, -4, 4],
#                 [0, -2, 0, 0, 2]])

k = np.array([[ 1, 0, 0, 0],
              [-1, 1, 1, 0],
              [ 0,-1, 0, 0],
              [ 0, 0,-1, 1],
              [ 0, 0, 0,-1]])

g = np.array([-2, 2, 1, 1])
print k.dot(g.T)

L = k.dot(k.T)

mat = np.array([[ 1, -1,  0,  0, 0],
                [-1,  3, -1, -1, 0],
                [ 0, -1,  1,  0, 0],
                [ 0, -1,  0,  2, -1],
                [ 0,  0,  0, -1, 1]])

vec = np.array([1, 3, 1, 2, 1])

## -2  5 -2  0 -1
print mat.dot(vec) #mat * vec.T
