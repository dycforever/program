import numpy as np
import os
import tensorflow as tf

import tensorflow_probability as tfp
tfd = tfp.distributions


def evaluate(tensors):
    if tf.executing_eagerly():
         return tf.contrib.framework.nest.pack_sequence_as(
             tensors,
             [t.numpy() if tf.contrib.framework.is_tensor(t) else t
             for t in tf.contrib.framework.nest.flatten(tensors)])
    return sess.run(tensors)

def session_options(enable_gpu_ram_resizing=True, enable_xla=True):
    """
    Allowing the notebook to make use of GPUs if they're available.

    XLA (Accelerated Linear Algebra) is a domain-specific compiler for linear
    algebra that optimizes TensorFlow computations.
    """
    config = tf.ConfigProto()
    config.log_device_placement = True
    if enable_gpu_ram_resizing:
        # `allow_growth=True` makes it possible to connect multiple colabs to your
        # GPU. Otherwise the colab malloc's all GPU ram.
        config.gpu_options.allow_growth = True
    if enable_xla:
        # Enable on XLA. https://www.tensorflow.org/performance/xla/.
        config.graph_options.optimizer_options.global_jit_level = (
            tf.OptimizerOptions.ON_1)
    return config


def reset_sess(config=None):
    """
    Convenience function to create the TF graph & session or reset them.
    """
    if config is None:
        config = session_options()
    global sess
    tf.reset_default_graph()
    try:
        sess.close()
    except:
        pass
    sess = tf.InteractiveSession(config=config)

reset_sess()

#these two quantities are unknown to us.
true_prob_A_ = 0.05
true_prob_B_ = 0.04

#notice the unequal sample sizes -- no problem in Bayesian analysis.
N_A_ = 1500
N_B_ = 750

#generate some observations
observations_A = tfd.Bernoulli(name="obs_A",
                          probs=true_prob_A_).sample(sample_shape=N_A_, seed=6.45)
observations_B = tfd.Bernoulli(name="obs_B",
                          probs=true_prob_B_).sample(sample_shape=N_B_, seed=6.45)
[
    observations_A_,
    observations_B_,
] = evaluate([
    observations_A,
    observations_B,
])

print("Obs from Site A: ", observations_A_[:30], "...")
print("Observed Prob_A: ", np.mean(observations_A_), "...")
print("Obs from Site B: ", observations_B_[:30], "...")
print("Observed Prob_B: ", np.mean(observations_B_))

def delta(prob_A, prob_B):
    """
    Defining the deterministic delta function. This is our unknown of interest.

    Args:
      prob_A: scalar estimate of the probability of a 1 appearing in
                observation set A
      prob_B: scalar estimate of the probability of a 1 appearing in
                observation set B
    Returns:
      Difference between prob_A and prob_B
    """
    return prob_A - prob_B

def double_joint_log_prob(observations_A, observations_B,
                   prob_A, prob_B):
    """
    Joint log probability optimization function.

    Args:
      observations_A: An array of binary values representing the set of
                      observations for site A
      observations_B: An array of binary values representing the set of
                      observations for site B
      prob_A: scalar estimate of the probability of a 1 appearing in
                observation set A
      prob_B: scalar estimate of the probability of a 1 appearing in
                observation set B
    Returns:
      Joint log probability optimization function.
    """
    tfd = tfp.distributions

    rv_prob_A = tfd.Uniform(low=0., high=1.)
    rv_prob_B = tfd.Uniform(low=0., high=1.)

    rv_obs_A = tfd.Bernoulli(probs=prob_A)
    rv_obs_B = tfd.Bernoulli(probs=prob_B)

    return (
        rv_prob_A.log_prob(prob_A)
        + rv_prob_B.log_prob(prob_B)
        + tf.reduce_sum(rv_obs_A.log_prob(observations_A))
        + tf.reduce_sum(rv_obs_B.log_prob(observations_B))
    )


number_of_steps = 37200 #@param {type:"slider", min:2000, max:50000, step:100}
#@markdown (Default is 18000).
burnin = 1000 #@param {type:"slider", min:0, max:30000, step:100}
#@markdown (Default is 1000).
leapfrog_steps=3 #@param {type:"slider", min:1, max:9, step:1}
#@markdown (Default is 6).


# Set the chain's start state.
initial_chain_state = [
    tf.reduce_mean(tf.to_float(observations_A)) * tf.ones([], dtype=tf.float32, name="init_prob_A"),
    tf.reduce_mean(tf.to_float(observations_B)) * tf.ones([], dtype=tf.float32, name="init_prob_B")
]

# Since HMC operates over unconstrained space, we need to transform the
# samples so they live in real-space.
unconstraining_bijectors = [
    tfp.bijectors.Identity(),   # Maps R to R.
    tfp.bijectors.Identity()    # Maps R to R.
]

# Define a closure over our joint_log_prob.
unnormalized_posterior_log_prob = lambda *args: double_joint_log_prob(observations_A, observations_B, *args)

with tf.variable_scope(tf.get_variable_scope(), reuse=tf.AUTO_REUSE):
    step_size = tf.get_variable(
        name='step_size',
        initializer=tf.constant(0.5, dtype=tf.float32),
        trainable=False,
        use_resource=True
    )

# Defining the HMC
hmc=tfp.mcmc.TransformedTransitionKernel(
    inner_kernel=tfp.mcmc.HamiltonianMonteCarlo(
        target_log_prob_fn=unnormalized_posterior_log_prob,
        num_leapfrog_steps=3,
        step_size=step_size,
        step_size_update_fn=tfp.mcmc.make_simple_step_size_update_policy(num_adaptation_steps=int(burnin * 0.8)),
        state_gradients_are_stopped=True),
    bijector=unconstraining_bijectors)

# Sample from the chain.
[
    posterior_prob_A,
    posterior_prob_B
], kernel_results = tfp.mcmc.sample_chain(
    num_results=number_of_steps,
    num_burnin_steps=burnin,
    current_state=initial_chain_state,
    kernel=hmc)

# Initialize any created variables.
init_g = tf.global_variables_initializer()
init_l = tf.local_variables_initializer()

evaluate(init_g)
evaluate(init_l)

[
    posterior_prob_A_,
    posterior_prob_B_,
    kernel_results_
] = evaluate([
    posterior_prob_A,
    posterior_prob_B,
    kernel_results
])

print("acceptance rate: {}".format(
    kernel_results_.inner_results.is_accepted.mean()))

burned_prob_A_trace_ = posterior_prob_A_[burnin:]
burned_prob_B_trace_ = posterior_prob_B_[burnin:]
burned_delta_trace_ = (posterior_prob_A_ - posterior_prob_B_)[burnin:]
print(burned_prob_A_trace_)
print(burned_prob_B_trace_)
print(burned_delta_trace_)
