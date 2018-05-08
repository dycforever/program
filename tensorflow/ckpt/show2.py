import tensorflow as tf
from tensorflow.python.ops import data_flow_ops
from tensorflow.python.framework import dtypes
from tensorflow.python.user_ops import user_ops
from tensorflow.python.training import queue_runner
from tensorflow.contrib.framework.python.framework import checkpoint_utils


init_op = [tf.local_variables_initializer(), tf.global_variables_initializer()]
saver = tf.train.import_meta_graph('checkpoint/model.ckpt-630.meta')


with tf.Session() as sess:
    saver.restore(sess, tf.train.latest_checkpoint('checkpoint/'))

    print("=" * 40)
    print sess.run(ckpt)
    print("=" * 40)


# tvars = tf.trainable_variables()
# tvars_vals = sess.run(tvars)
#
# for var, val in zip(tvars, tvars_vals):
#     print(var.name, val)
