tf.train.ClusterSpec({
    "worker": [
        "localhost:22221",
        "localhost:22222"
    ],
    "ps": [
        "localhost:32222",
        "localhost:32222"
    ]})