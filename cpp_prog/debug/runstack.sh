#!/bin/sh

#使用方法： sh ./runstack.sh pid "command"
#示例: 
#    sh ./runstack.sh 10933 "list main"
#    sh ./runstack.sh 10933 "set count=10"
#    sh ./runstack.sh 10933 "source script.gdb"

if test $# -ne 2; then
    echo "Usage: `basename $0 .sh` <process-id> cmd" 1>&2
    echo "For exampl: `basename $0 .sh` 1000 bt" 1>&2
    exit 1
fi
if test ! -r /proc/$1; then
    echo "Process $1 not found." 1>&2
    exit 1
fi
result=""
GDB=${GDB:-/usr/bin/gdb}
# Run GDB, strip out unwanted noise.
result=`$GDB --quiet -nx /proc/$1/exe $1 <<EOF 2>&1
$2
EOF`
echo "$result" | egrep -A 1000 -e "^\\(gdb\\)" | egrep -B 1000 -e "^\\(gdb\\)"

