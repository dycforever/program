import tensorflow as tf
from tensorflow.python.user_ops import user_ops
import tf_util.parser.sm_standard_kv_parser as lib_parser

checkpoint_dir = './checkpoint/'

def main():
   #filelist = tf.train.match_filenames_once(["data/mini/part-0", "data/mini/part-1"])
   #filename_queue = tf.train.string_input_producer(filelist,
   #        shared_name='input_file_name_queue')


    #####################################
    file_name_list = tf.constant(["data/mini/part-0", "data/mini/part-1"], dtype=tf.string)
    var = tf.Variable("", trainable=False)
    global_step = tf.Variable(0, trainable=False)
    update_global_step = tf.assign_add(global_step, 1)
   #filelist = user_ops.files_ckpt(filename_queue.dequeue(), var, 200000)
    filelist = user_ops.files_ckpt(file_name_list, var, 200000)

    filename_queue = tf.FIFOQueue(1, tf.string)
    enq = filename_queue.enqueue(filelist)
    queue_runner = tf.train.QueueRunner(filename_queue, [enq])
    tf.train.add_queue_runner(queue_runner)
    #####################################
    saver = tf.train.Saver()

    reader = user_ops.SmStandardKvReader("[dat]", "[common]")
    file_name, record = reader.read(filename_queue)

    batch_record = tf.train.batch([record], batch_size=2, num_threads=5,
                        capacity=50, allow_smaller_final_batch=True)

    init_op = [tf.local_variables_initializer(), tf.global_variables_initializer()]
    print 'Start create session'
    sess = tf.Session()
    print 'End create session'

    summary_writer = tf.summary.FileWriter(checkpoint_dir, sess.graph)
    # otherwise FIFOQueue will be closed before read
    sess.run(init_op)
   #coord = tf.train.Coordinator()
   #threads = tf.train.start_queue_runners(sess=sess, coord=coord)

   #input_schema = "data/mini/conf/input_schema.json"
   #parse_schema = "data/mini/conf/parse_schema.json"
   #standard_kv_parser = lib_parser.StandardKvParser(batch_record, input_schema, parse_schema)
   #tensor_dict = standard_kv_parser.get_tensor_dict()

    latest_checkpoint_path = tf.train.latest_checkpoint(checkpoint_dir)
    if latest_checkpoint_path:
        saver.restore(sess, latest_checkpoint_path)

    for i in range(10):
       #sess.run(tensor_dict)
        print '*' * 100
        _, temp = sess.run([filelist, update_global_step])
        print '*' * 100
        if i % 10 == 0:
            saver.save(sess, checkpoint_dir, global_step=temp)
    summary_writer.flush()
    summary_writer.close()
       #coord.request_stop()
       #coord.join(threads)

main()

