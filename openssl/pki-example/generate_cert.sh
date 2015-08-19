#!/bin/bash

if [ $# -lt 1 ]
then
    echo "usage: $0 cn"
    exit 1
fi

CERT_CN=$1 sh script/create_sm_req.sh
sh script/create_sm_cert.sh

