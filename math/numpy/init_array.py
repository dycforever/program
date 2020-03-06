
import numpy as np

a = np.zeros((5,5), dtype=int)
print a

#a[1,:] = np.array([1] * 5)
a[1] = np.array([1] * 5)
print a