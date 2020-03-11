# -*- coding: utf-8 -*-
import tensorflow as tf

with tf.Graph().as_default():
    sess = tf.Session()
    input = tf.constant([[[1, 1, 1], [2, 2, 2]],
                         [[3, 3, 3], [4, 4, 4]],
                         [[5, 5, 5], [6, 6, 6]]])

    # """[1,0,0]表示第一维偏移了1
    # 然后第一维从 1 开始，size 为 1
    # 第一维从 0 开始，size 为 1"""
    # 第二维从 0 开始，size 为 3"""
    data = tf.slice(input, [1, 0, 0], [1, 1, 3])

    print(sess.run(data))

    # 输出:
    # [[[3 3 3]]]
