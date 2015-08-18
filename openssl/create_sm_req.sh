
SAN=DNS:www.simple.org \
    openssl req -new \
    -config etc/server.conf \
    -out certs/simple.org.csr \
    -keyout certs/simple.org.key

#SAN=DNS:m.sm.cn \
#    openssl req -new \
#    -config etc/server.conf \
#    -out certs/sm.cn.csr \
#    -keyout certs/sm.cn.key