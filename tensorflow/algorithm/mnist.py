import tensorflow as tf
from tensorflow.python.training.monitored_session import MonitoredSession

def main():
#    filelist = tf.train.match_filenames_once(["hdfs://tensorflow-on-yarn-test/user/tianjin.gutj/mnist_train.tfrecord"])
    filelist = tf.train.match_filenames_once(["mnist_train.tfrecord"])
    reader = tf.TFRecordReader()
    filename_queue = tf.train.string_input_producer(filelist)
    image, label = reader.read(filename_queue)
    init_op = [tf.local_variables_initializer(), tf.global_variables_initializer()]
#    with tf.Session() as sess:
    with MonitoredSession() as sess:
        sess.run(init_op)

        coord = tf.train.Coordinator()
        threads = tf.train.start_queue_runners(sess=sess, coord=coord)

        i = 0;
        while True:
            i += 1
            sess.run(label)
            #    print(i)

        coord.request_stop()
        coord.join(threads)

main()

