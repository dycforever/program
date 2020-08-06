import tensorflow as tf
import numpy as np

X_sparse_np = np.array([
    [1, 2, 1],
    [3, 0, 2],
    [3, 3, 3],
    [6, 1, 4],
])
b_np = np.array([1,2,3,4,5])
b = tf.constant(b_np)

# Converting your input data into a SparseTensor:
indices = X_sparse_np[:, :2].reshape((-1, 2))
values = X_sparse_np[:, 2]
dense_shape = [6, 4]
X_sparse = tf.SparseTensorValue(indices, values, dense_shape)

# Performing your operation on its dense representation:
res = tf.sparse_tensor_to_dense(X_sparse) * b

# opt. Re-obtaining the sparse representation of your result:
sparse_res = tf.SparseTensor(indices, tf.gather_nd(res, indices), dense_shape)
sparse_res = tf.sparse.reshape(sparse_res, [2,3,4])

with tf.Session() as sess:
    print(sess.run(res))
    # [[ 0  0  0  0  0]
    #  [ 0  0  3  0  0]
    #  [ 0  0  0  0  0]
    #  [ 2  0  0 12  0]
    #  [ 0  0  0  0  0]
    #  [ 0  0  0  0  0]
    #  [ 0  8  0  0  0]]
    print(sess.run(sparse_res))
    # SparseTensorValue(
    #       indices=array([[1, 2],
    #                      [3, 0],
    #                      [3, 3],
    #                      [6, 1]]),
    #       values=array([ 3,  2, 12,  8]),
    #       dense_shape=array([7, 5]))
