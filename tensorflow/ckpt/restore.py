import tensorflow as tf

sess=tf.Session()
# First let's load meta graph and restore weights
saver = tf.train.import_meta_graph('./runtime_env/ckpt/my_test_model-1000.meta')
saver.restore(sess, tf.train.latest_checkpoint('./runtime_env/ckpt'))

# Access saved Variables directly
print(sess.run('bias:0'))
# This will print 2, which is the value of bias that we saved

graph = tf.get_default_graph()
x1 = graph.get_tensor_by_name("x1:0")
x2 = graph.get_tensor_by_name("x2:0")

feed_dict ={x1:4.0, x2:5.0}

tensor_y = graph.get_tensor_by_name("tensor_y:0")
print sess.run(tensor_y, feed_dict)


nouse = graph.get_tensor_by_name("nouse:0")
print "nouse: "
print sess.run(nouse)
