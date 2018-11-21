import tensorflow as tf
from tensorflow.python.user_ops import user_ops
import tf_util.parser.sm_standard_kv_parser as lib_parser
from tf_util.queue_runner.checkpoint_queue_runner import CheckpointQueueRunner 
def main():
    filelist = tf.train.match_filenames_once(["data/mini/part-0", "data/mini/part-1"])
    filename_queue = tf.train.string_input_producer(filelist,
            shared_name='input_file_name_queue',
                                                    num_epochs=5)
    #############################
    new_filename_queue = tf.FIFOQueue(1, tf.string)
    qr = CheckpointQueueRunner(filename_queue, new_filename_queue, 3)
    tf.train.add_queue_runner(qr)
    #############################
    reader = user_ops.SmStandardKvReader("[dat]", "[common]")
    file_name, record = reader.read(new_filename_queue)

    batch_record = tf.train.batch([record], batch_size=2, num_threads=5,
                        capacity=5000, allow_smaller_final_batch=True)

    init_op = [tf.local_variables_initializer(), tf.global_variables_initializer()]
    with tf.Session() as sess:
        # otherwise FIFOQueue will be closed before read
        sess.run(init_op)
        print("*" * 40)
        print(sess.run(filelist))
        print("*" * 40)
        coord = tf.train.Coordinator()
        threads = tf.train.start_queue_runners(sess=sess, coord=coord)

        input_schema = "data/mini/conf/input_schema.json"
        parse_schema = "data/mini/conf/parse_schema.json"
        standard_kv_parser = lib_parser.StandardKvParser(batch_record, input_schema, parse_schema)
        tensor_dict = standard_kv_parser.get_tensor_dict()

        for i in range(3):
            print(sess.run(tensor_dict))
        coord.request_stop()
        coord.join(threads)

main()

