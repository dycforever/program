import tensorflow as tf

import numpy as np
import tensorflow as tf

x = tf.placeholder(tf.float32)
y = tf.placeholder(tf.float32)

w = tf.get_variable("w", shape=[3, 1])
print w

# We define yhat to be our estimate of y.
f = tf.stack([tf.square(x), x, tf.ones_like(x)], 1)

yhat = tf.squeeze(tf.matmul(f, w), 1)

loss = tf.nn.l2_loss(yhat - y) + 0.1 * tf.nn.l2_loss(w)

train_op = tf.train.AdamOptimizer(0.1).minimize(loss)

def generate_data():
    x_val = np.random.uniform(-10.0, 10.0, size=100)
    y_val = 5 * np.square(x_val) + 3
    return x_val, y_val

sess = tf.Session()

# print "*" * 20
# print sess.graph_def
# print "*" * 20

# Since we are using variables we first need to initialize them.
sess.run(tf.global_variables_initializer())
for _ in range(1000):
    x_val, y_val = generate_data()
    _, loss_val = sess.run([train_op, loss], {x: x_val, y: y_val})
#    print(loss_val)
# print(sess.run([w]))

