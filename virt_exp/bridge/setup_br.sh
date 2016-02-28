set -x
######  bridge different networks

sudo ip netns add net1

sudo ip link add veth0 type veth peer name veth1
sudo ip link set veth1 netns net1

sudo ip addr add 10.1.1.1/16 dev veth0
sudo ip link set dev veth0 up

sudo ip netns exec net1 ip addr add 10.1.1.2/16 dev veth1
sudo ip netns exec net1 ip link set dev veth1 up

sudo brctl addbr br
sudo brctl addif br veth0 

sudo ip addr add 10.1.1.100/16 dev br
sudo ip link set dev br up

sudo ip route del 10.1.0.0/16 
sudo ip route del 10.1.0.0/16 
sudo ip route add 10.1.0.0/16 via 10.1.1.100
sudo ip netns exec net1 ip link set lo up
sudo ip netns exec net1 ip route add default via 10.1.1.100









####### bridge same networks
####
#sudo ip netns add net1
#
#sudo ip link add veth0 type veth peer name veth1
#sudo ip link set veth1 netns net1
#
#sudo ip addr add 192.168.171.100/24 dev veth0
#sudo ip link set dev veth0 up
#
#sudo ip netns exec net1 ip addr add 192.168.171.101/24 dev veth1
#sudo ip netns exec net1 ip link set dev veth1 up
#
#sudo brctl addbr br
#sudo brctl addif br veth0 
#
#sudo ip addr add 192.168.171.200/24 dev br
#sudo ip link set dev br up
#
#sudo ip netns exec net1 ip route del 192.168.171.0/24
#sudo ip netns exec net1 ip route add default via 192.168.171.200 
#
