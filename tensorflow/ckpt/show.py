import tensorflow as tf
from tensorflow.python.ops import data_flow_ops
from tensorflow.python.framework import dtypes
from tensorflow.python.user_ops import user_ops
from tensorflow.python.training import queue_runner
from tensorflow.contrib.framework.python.framework import checkpoint_utils

#print checkpoint_utils.list_variables("hdfs://tensorflow-on-yarn-test/user/yonggang.myg/wnd_plugin_test/kafka_reader_test/checkpoint")
checkpoint_utils.list_variables("checkpoint")
print checkpoint_utils.load_variable("checkpoint", "queue_runner_checkpoint_var")



# tvars = tf.trainable_variables()
# tvars_vals = sess.run(tvars)
#
# for var, val in zip(tvars, tvars_vals):
#     print(var.name, val)
