from tensorflow.python.framework import ops

def func3():
    from tensorflow.python.ops import data_flow_ops
    from tensorflow.python.ops import array_ops
    from tensorflow.python.framework import dtypes
    from tensorflow.python.training import queue_runner

    def limit_epochs(tensor, num_epochs=None, name=None):
      from tensorflow.python.framework import constant_op
      from tensorflow.python.ops import variables

      if num_epochs is None:
        return tensor
      if num_epochs <= 0:
        raise ValueError("num_epochs must be > 0 not %d." % num_epochs)
      with ops.name_scope(name, "limit_epochs", [tensor]) as name:
        zero64 = constant_op.constant(0, dtype=dtypes.int64)
        epochs = variables.Variable(
            zero64, name="epochs", trainable=False,
            collections=[ops.GraphKeys.LOCAL_VARIABLES])
        counter = epochs.count_up_to(num_epochs)
        with ops.control_dependencies([counter]):
          return array_ops.identity(tensor, name=name)


    q = data_flow_ops.FIFOQueue(capacity=10,
            dtypes=[dtypes.string])

    var_a = tf.Variable("aaa")
    var_a = limit_epochs(var_a, 2)
    enq_a = q.enqueue(var_a)

    var_b = tf.Variable("bbb")
    var_b = limit_epochs(var_b, 3)
    enq_b = q.enqueue(var_b)

    queue_runner.add_queue_runner(queue_runner.QueueRunner(q, [enq_a, enq_b]))

    coord = tf.train.Coordinator()

    deq = q.dequeue()

    init_op = [tf.local_variables_initializer(), tf.global_variables_initializer()]
    with tf.Session() as sess:
        sess.run(init_op)
        threads = tf.train.start_queue_runners(sess=sess, coord=coord)
        for i in range(5):
            try:
                print(sess.run(deq))
            except Exception as e:
                print e
                break
        coord.request_stop()
        coord.join(threads)

def func2():
    import tensorflow as tf
    nouse = tf.Variable(123.0, name="nouse")
    global_init_op = tf.global_variables_initializer()
    sess = tf.Session()
    #print("sess graph: ", sess.graph_def)
    sess.run(global_init_op)
    print sess.run(nouse)
    print sess.run("nouse:0")


#func3()

func2()

