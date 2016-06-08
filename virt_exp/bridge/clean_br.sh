

sudo ip link set dev br down
sudo brctl delbr br
sudo ip netns del net1


sudo ip link set dev eth0 down
sudo ip addr add 192.168.171.128/24 dev eth0
sudo ip link set dev eth0 up
sudo ip route add default via 192.168.171.2 dev eth0
