#FROM hello-world
#ADD etcd / 
#CMD ["/etcd", "--advertise-client-urls", "http://172.17.0.2:2379", "--listen-client-urls", "http://172.17.0.2:2379"]

FROM centos
ADD etcd /bin
CMD /sbin/ip addr && /bin/etcd --advertise-client-urls http://0.0.0.0:2379 --listen-client-urls http://0.0.0.0:2379
