import tensorflow as tf

nouse = tf.Variable(123.0, name="nouse")

x1 = tf.placeholder("float", name="x1")
x2 = tf.placeholder("float", name="x2")
b = tf.Variable(3.0, name="bias")

feed_dict ={x1:1, x2:2}

# y = 1*2+3 = 5
y = tf.add(tf.multiply(x1, x2), b, name="tensor_y")
sess = tf.Session()
sess.run(tf.global_variables_initializer())

saver = tf.train.Saver()
saver.save(sess, './runtime_env/ckpt/my_test_model', global_step=1000)

