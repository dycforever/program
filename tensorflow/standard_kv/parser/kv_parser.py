import tensorflow as tf
import time
from tensorflow.python.user_ops import user_ops
from tensorflow.python.training.monitored_session import MonitoredSession
import tf_util.parser.sm_standard_kv_parser as lib_parser

def main():
#    filelist = tf.train.match_filenames_once(["hdfs://tensorflow-on-yarn-test/user/yichuan.dingyc/hdfs_train_test/mini-data-processed/part-*"])
    filelist = tf.train.match_filenames_once(["part*"])
    #filelist = tf.train.match_filenames_once(["hdfs://tensorflow-on-yarn-test/user/xiangqin.oxq/nn_data/part-000*"])
    filename_queue = tf.train.string_input_producer(filelist)

    reader = user_ops.SmStandardKvReader("[dat]", "[common]", trim=True)
    file_name, record = reader.read(filename_queue)

    input_schema = "wd_input_schema.json"
    parse_schema = "wd_parse_schema.json"

    standard_kv_parser = lib_parser.StandardKvParser([record], input_schema, parse_schema)
    tensor_dict = standard_kv_parser.get_tensor_dict()

    i=0
    init_op = [tf.local_variables_initializer(), tf.global_variables_initializer()]
    with MonitoredSession() as sess:
        sess.run(init_op)

        coord = tf.train.Coordinator()
        threads = tf.train.start_queue_runners(sess=sess, coord=coord)

        try:
            begin_time = time.time()
            while True:
                if i %100 == 0:
                    print i
                sess.run(tensor_dict)
                #print(sess.run(record))
                i += 1
            coord.request_stop()
            coord.join(threads)
        except Exception as e:
            pass
            #print(str(e))

main()

