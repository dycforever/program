import math
import tensorflow as tf
import tensorflow_probability as tfp
tfd = tfp.distributions

c = tf.constant([1,2,3], dtype=float)

#graph = tf.Graph()
#with graph.as_default():
sess = tf.Session()
# fn = tfp.mcmc.random_walk_normal_fn(scale=2)
#
# for i in range(10):
#     #fn = tfp.mcmc.random_walk_normal_fn(scale=2)
#     print sess.run(fn([c], None))

def run_deterministic():
    constant = tfd.Deterministic(0.)
    ## 1.0
    print sess.run(constant.prob(0.))
    ## 0
    print sess.run(constant.prob(2.))

    for i in range(5):
        print sess.run(constant.sample())

def run_poisson():
    def poisson_pmf(lamb, k):
        ret = float(lamb ** k)
        for i in range(k):
            ret /= i + 1
        ret /= math.exp(lamb)
        return ret

    lamb = 2
    rv_poisson = tfd.Poisson(rate=lamb)
    print sess.run(rv_poisson.prob(1))
    print poisson_pmf(lamb, 1)
    print sess.run(rv_poisson.prob(5))
    print poisson_pmf(lamb, 5)

def run_bernoulli():
    bn = tfd.Bernoulli(probs=0.3)
    cnt = 0
    N = 10000
    print sess.run(bn.prob(0))
    print sess.run(bn.prob(1))
    for i in sess.run(bn.sample(sample_shape=N)):
        if i == 1:
            cnt += 1
    print cnt, "of", N

#run_poisson()
run_bernoulli()
