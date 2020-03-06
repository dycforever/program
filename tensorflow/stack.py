# -*- coding: utf-8 -*-
import tensorflow as tf

with tf.Graph().as_default():
    a = tf.constant([[1,2,3], [3,4,5]]) # shape (2,3)
    b = tf.constant([[7,8,9], [10,11,12]]) # shape (2,3)
    a_concat_b = tf.concat([a, b], axis=0) # shape (4,3)
    print("a concat b shape: %s" % a_concat_b.shape)
    a_stack_b = tf.stack([a, b], axis=2)  # shape (2,2,3)
    print("a stack b shape: %s" % a_stack_b.shape)

    sess = tf.Session()
    ####  [[[ 1  2  3]
    ####    [ 3  4  5]]
    ####
    ####   [[ 7  8  9]
    ####    [10 11 12]]]
    print(sess.run(a_stack_b))
