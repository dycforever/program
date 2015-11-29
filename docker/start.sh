#!/bin/bash

for ((i=2;i<5;i++))
do

docker run -d etcd \
    /bin/etcd -name infra${i} -initial-advertise-peer-urls http://172.17.0.${i}:2380 \
    -listen-peer-urls http://172.17.0.${i}:2380 \
    -listen-client-urls http://172.17.0.${i}:2379 \
    -advertise-client-urls http://172.17.0.${i}:2379 \
    -initial-cluster-token etcd-cluster-1 \
    -initial-cluster infra2=http://172.17.0.2:2380,infra3=http://172.17.0.3:2380,infra4=http://172.17.0.4:2380 \
    -initial-cluster-state new

done


#docker run -d etcd /bin/etcd --advertise-client-urls http://0.0.0.0:2379 --listen-client-urls http://0.0.0.0:2379
#docker run -d etcd /bin/etcd --advertise-client-urls http://0.0.0.0:2379 --listen-client-urls http://0.0.0.0:2379
#docker run -d etcd /bin/etcd --advertise-client-urls http://0.0.0.0:2379 --listen-client-urls http://0.0.0.0:2379

