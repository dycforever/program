def gaussian_kl(q, p=(0., 0.)):
  """Computes KL divergence between two isotropic Gaussian distributions.

  To ensure numerical stability, this op uses mu, log(sigma^2) to represent
  the distribution. If q is not provided, it's assumed to be unit Gaussian.

  Args:
    q: A tuple (mu, log(sigma^2)) representing a multi-variatie Gaussian.
    p: A tuple (mu, log(sigma^2)) representing a multi-variatie Gaussian.
  Returns:
    A tensor representing KL(q, p).
  """
  mu1, log_sigma1_sq = q
  mu2, log_sigma2_sq = p
  return tf.reduce_sum(
    0.5 * (log_sigma2_sq - log_sigma1_sq +
           tf.exp(log_sigma1_sq - log_sigma2_sq) +
           tf.square(mu1 - mu2) / tf.exp(log_sigma2_sq) -
           1), axis=-1)
