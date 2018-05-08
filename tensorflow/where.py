from tensorflow.python.framework import ops
import tensorflow as tf
from tensorflow.python.ops import math_ops
from tensorflow.python.ops import array_ops

a = tf.Variable([0,1,1,0])
b = tf.reshape(a, [2, 2])

a2 = tf.Variable([1,1,1,1])
b2 = tf.reshape(a2, [2, 2])


global_init_op = tf.global_variables_initializer()
sess = tf.Session()
sess.run(global_init_op)
print sess.run(b)
print sess.run(b2)
print sess.run(math_ops.not_equal(b, b2))
print sess.run(array_ops.where(math_ops.not_equal(b, b2), name="indices"))


