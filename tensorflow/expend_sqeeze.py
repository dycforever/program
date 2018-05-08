# -*- coding: utf-8 -*-
import tensorflow as tf

with tf.Graph().as_default():
    v = tf.get_variable("v", shape=(2, 3, 5))
    sess = tf.Session()
    print sess.run(tf.shape(tf.expand_dims(v, 0))) # ==> [1, 2, 3, 5]
    print sess.run(tf.shape(tf.expand_dims(v, 2))) # ==> [2, 3, 1, 5]
    print sess.run(tf.shape(tf.expand_dims(v, 3))) # ==> [2, 3, 5, 1]

    # squeeze() 删除所有大小是1的维度
    v2 = tf.get_variable("v2", shape=(1, 2, 1, 3, 5, 1))
    print sess.run(tf.shape(v2))     # [1 2 1 3 5 1]
    print sess.run(tf.shape(tf.squeeze(v2)))    # [2 3 5]
