###############################
# To create the root CA:
###############################

rm -rf root-ca
mkdir root-ca
cd root-ca
mkdir certs db private
chmod 700 private
touch db/index
openssl rand -hex 16 > db/serial
echo 1001 > db/crlnumber
cd ..

openssl req -new \
    -config etc/root_req.cnf \
    -out root-ca/root-ca.csr \
    -keyout root-ca/private/root-ca.key &> /dev/null

openssl ca -selfsign \
    -config etc/root_ca.cnf \
    -in root-ca/root-ca.csr \
    -out root-ca/root-ca.crt \
    -batch \
    -extensions ca_ext &> /dev/null

openssl x509 -subject -issuer -noout -in root-ca/root-ca.crt 


rm -rf sub-ca
mkdir -p sub-ca/private
mkdir -p sub-ca/certs
mkdir -p sub-ca/db
touch sub-ca/db/index
openssl rand -hex 16 > sub-ca/db/serial
echo 1001 > sub-ca/db/crlnumber

openssl req -new \
    -config etc/sub_req.cnf \
    -out sub-ca/sub-ca.csr \
    -keyout sub-ca/private/sub-ca.key \
    -batch &> /dev/null

openssl ca \
    -config etc/root_subca.cnf \
    -in sub-ca/sub-ca.csr \
    -out sub-ca/sub-ca.crt \
    -extensions sub_ca_ext \
    -batch &> /dev/null



rm -rf server
mkdir -p server/private
openssl req -new \
    -config etc/server_req.cnf \
    -out server/server.csr \
    -keyout server/private/server.key \
    -batch 

openssl ca \
    -config etc/sub_ca.cnf \
    -in server/server.csr \
    -out server/server.crt \
    -extensions leaf_ext \
    -batch 

openssl ca \
    -config etc/sub_ca.cnf \
    -in server/server.csr \
    -out server/server_sha1.crt \
    -extensions leaf_ext \
    -md sha1 \
    -batch 



# rm -rf client
# mkdir -p client/private
# openssl req -new \
#     -config etc/client_req.cnf \
#     -out client/client.csr \
#     -keyout client/private/client.key \
#     -batch 
# 
# openssl ca \
#     -config etc/sub_ca.cnf \
#     -in client/client.csr \
#     -out client/client.crt \
#     -extensions leaf_ext \
#     -batch 


#openssl dhparam -check -text -5 512 -out dh512.pem
#openssl dhparam -check -text -5 1024 -out dh1024.pem
#
