# -*- coding: utf-8 -*-
import tensorflow as tf
import numpy as np

with tf.Graph().as_default():
    a = tf.constant([[1,2],[3,4]],name='a')
    b = tf.constant([[1,2],[3,4]],name='b')
    c = tf.reduce_sum(tf.multiply( a, b ), 1, keep_dims=True)
    sess = tf.Session()
    print(sess.run(c))

