import tensorflow as tf
import time
from tensorflow.python.user_ops import user_ops
from tensorflow.python.training.monitored_session import MonitoredSession
import tf_util.parser.sm_standard_kv_parser as lib_parser

def main():
#    filelist = tf.train.match_filenames_once(["hdfs://tensorflow-on-yarn-test/user/yichuan.dingyc/hdfs_train_test/mini-data-processed/part-*"])
    filelist = tf.train.match_filenames_once(["test_data.*"])
    #filelist = tf.train.match_filenames_once(["hdfs://tensorflow-on-yarn-test/user/xiangqin.oxq/nn_data/part-000*"])
    filename_queue = tf.train.string_input_producer(filelist,
            shared_name='input_file_name_queue', num_epochs=1000)

    batch_size = 3
    reader = user_ops.SmStandardKvReader("[dat]", "[common]", batch_size=batch_size)
    file_name, record = reader.read(filename_queue)

    #batch_record = tf.train.batch([record], batch_size=batch_size, num_threads=2,
    #                    capacity=10000, allow_smaller_final_batch=True)

    input_schema = "data/mini/conf/input_schema.json"
    parse_schema = "data/mini/conf/parse_schema.json"

    standard_kv_parser = lib_parser.StandardKvParser([record], input_schema, parse_schema)
    tensor_dict = standard_kv_parser.get_tensor_dict()

    init_op = [tf.local_variables_initializer(), tf.global_variables_initializer()]
    #with MonitoredSession() as sess:
    with tf.Session() as sess:
        # otherwise FIFOQueue will be closed before read
        sess.run(init_op)

        coord = tf.train.Coordinator()
        threads = tf.train.start_queue_runners(sess=sess, coord=coord)

        try:
            begin_time = time.time()
            for i in range(4):
                #sess.run(tensor_dict)
                #if i % 100 == 0:
                #    used_time = time.time() - begin_time
                #    print("batch per second[%d] record per second[%d]" % (batch_size * i / used_time, i / used_time))
                sess.run(record)
            coord.request_stop()
            coord.join(threads)
        except Exception as e:
            pass
            #print(str(e))

main()

