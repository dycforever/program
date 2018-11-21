# -*- coding: utf-8 -*-
import tensorflow as tf

with tf.Graph().as_default():
    sess = tf.Session()

    t=tf.constant([[2,3,4],[5,6,7]])
    paddings = tf.constant([[1, 1,], [2, 2]])
    tp = tf.pad(t, paddings, "CONSTANT")
    print(sess.run(tp))
    # 输出结果为：
    # 上，下，左，右分别填充啦1,2,2,3行
    # array([[0, 0, 0, 0, 0, 0, 0, 0],
    #        [0, 0, 2, 3, 4, 0, 0, 0],
    #        [0, 0, 5, 6, 7, 0, 0, 0],
    #        [0, 0, 0, 0, 0, 0, 0, 0],
    #        [0, 0, 0, 0, 0, 0, 0, 0]], dtype=int32)
