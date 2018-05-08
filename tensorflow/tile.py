import tensorflow as tf

with tf.Graph().as_default():
    a = tf.constant([[1,2],[3,4]],name='a')
    # 表示在第一个维度上复制 2 次，在第二个维度上复制 3 次
    b = tf.tile(a,[2,3])
    sess = tf.Session()
    print(sess.run(b))