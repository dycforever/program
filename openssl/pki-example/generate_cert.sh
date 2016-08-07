#!/bin/bash

if [ $# -lt 1 ]
then
    echo "usage: $0 cn"
    exit 1
fi

# create root and signing ca
sh script/create_root_req.sh
sh script/create_root_cert.sh
sh script/create_ca_req.sh
sh script/create_ca_cert.sh

#common name, such as host *.sm.cn
CERT_CN=$1 sh script/create_sm_req.sh
sh script/create_sm_cert.sh

