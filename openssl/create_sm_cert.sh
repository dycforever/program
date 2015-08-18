
openssl ca \
    -config etc/signing-ca.conf \
    -in certs/simple.org.csr \
    -out certs/simple.org.crt \
    -extensions server_ext

#openssl ca \
#    -config etc/signing-ca.conf \
#    -in certs/sm.cn.csr \
#    -out certs/sm.cn.crt \
#    -extensions server_ext

