# -*- coding: utf-8 -*-
import tensorflow as tf

with tf.Graph().as_default():
    sess = tf.Session()
    input = tf.constant([[[1, 1, 1], [2, 2, 2]],
                         [[3, 3, 3], [4, 4, 4]],
                         [[5, 5, 5], [6, 6, 6]]])

    # """[1,0,0]表示第一维偏移了1
    # 则是从[[[3, 3, 3], [4, 4, 4]],[[5, 5, 5], [6, 6, 6]]]中选取数据
    # 然后选取第一维的第一个，第二维的第一个数据，第三维的三个数据"""
    data = tf.slice(input, [1, 0, 0], [1, 1, 3])

    print(sess.run(data))

    # 输出:
    # [[[3 3 3]]]
