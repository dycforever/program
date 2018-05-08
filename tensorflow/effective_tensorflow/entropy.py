import tensorflow as tf

def softmax(logits, dims=-1):
  """Compute softmax over specified dimensions."""
  exp = tf.exp(logits - tf.reduce_max(logits, dims, keep_dims=True))
  return exp / tf.reduce_sum(exp, dims, keep_dims=True)

def entropy(logits, dims=-1):
  """Compute entropy over specified dimensions."""
  probs = softmax(logits, dims)
  nplogp = probs * (tf.reduce_logsumexp(logits, dims, keep_dims=True) - logits)
  return tf.reduce_sum(nplogp, dims)