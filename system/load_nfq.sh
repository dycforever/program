#!/bin/sh

# usage:
# sh this script and ping 220.181.37.55 in another terminal

TABLE=mangle

function remove_chain(){
    echo -n removing chain...
    {
        sudo /sbin/iptables -t ${TABLE} -D PREROUTING -j NF_QUEUE_CHAIN
        sudo /sbin/iptables -t ${TABLE} -D OUTPUT -j NF_QUEUE_CHAIN
        sudo /sbin/iptables -t ${TABLE} -F NF_QUEUE_CHAIN
        sudo /sbin/iptables -t ${TABLE} -X NF_QUEUE_CHAIN
    } &>/dev/null
    echo done
}

function create_chain(){
    echo -n creating chain...
    sudo /sbin/iptables -t ${TABLE} -N NF_QUEUE_CHAIN
    sudo /sbin/iptables -t ${TABLE} -A NF_QUEUE_CHAIN -m mark --mark 0 -j NFQUEUE --queue-num 8010
    sudo /sbin/iptables -t ${TABLE} -A NF_QUEUE_CHAIN -j MARK --set-mark 0
    sudo /sbin/iptables -t ${TABLE} -I OUTPUT -j NF_QUEUE_CHAIN
    sudo /sbin/iptables -t ${TABLE} -I PREROUTING -j NF_QUEUE_CHAIN
    echo done
}

function on_iqh(){
    echo "signal trap !"
    remove_chain
    exit 1
}

trap on_iqh INT QUIT HUP
remove_chain
create_chain
sudo ./libnfqueue 8010
remove_chain
