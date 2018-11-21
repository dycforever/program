from tensorflow.python.framework import ops
import tensorflow as tf
from tensorflow.python.ops import math_ops
from tensorflow.python.ops import array_ops


# shape is [1, 2, 2, 3]
a = tf.Variable([[ [[0,1,2], [1,0,3]], 
                   [[0,1,2], [1,0,3]] ]])

global_init_op = tf.global_variables_initializer()
sess = tf.Session()
sess.run(global_init_op)

# get: 4
rank = array_ops.rank(a)
print "rank:", sess.run(rank)

# get [3]
dims = array_ops.expand_dims(rank - 1, 0)
print "dims:", sess.run(dims)

# get: [1, 1, 1]
ones = array_ops.fill(dims, 1)
print "ones:", sess.run(ones)

# get [1, 2, 2, 3, 1, 1, 1]
bcast_shape = array_ops.concat([array_ops.shape(a), ones], 0)
print sess.run(bcast_shape)
