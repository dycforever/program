def make_parallel(fn, num_gpus, **kwargs):
  """Parallelize given model on multiple gpu devices.

  Args:
    fn: Arbitrary function that takes a set of input tensors and outputs a
        single tensor. First dimension of inputs and output tensor are assumed
        to be batch dimension.
    num_gpus: Number of GPU devices.
    **kwargs: Keyword arguments to be passed to the model.
  Returns:
    A tensor corresponding to the model output.
  """
  in_splits = {}
  for k, v in kwargs.items():
    in_splits[k] = tf.split(v, num_gpus)

  out_split = []
  for i in range(num_gpus):
    with tf.device(tf.DeviceSpec(device_type="GPU", device_index=i)):
      with tf.variable_scope(tf.get_variable_scope(), reuse=i > 0):
        out_split.append(fn(**{k : v[i] for k, v in in_splits.items()}))

  return tf.concat(out_split, axis=0)
