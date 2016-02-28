
set -x

sysctl -w net.ipv4.ip_forward=1
sudo iptables -t nat -A POSTROUTING -s 10.1.0.0/16 -j MASQUERADE

ping -c 2 10.1.1.1
ping -c 2 10.1.1.2
ping -c 2 10.1.1.100
sudo ip netns exec net1 ping -c 2 10.1.1.1
sudo ip netns exec net1 ping -c 2 10.1.1.2
sudo ip netns exec net1 ping -c 2 10.1.1.100

sudo ip netns exec net1 ping -c 2 115.239.210.27



#ping -c 2 192.168.171.200
#ping -c 2 192.168.171.100
#ping -c 2 192.168.171.101
#
#sudo ip netns exec net1 ping -c 2 192.168.171.200
#sudo ip netns exec net1 ping -c 2 192.168.171.100
#sudo ip netns exec net1 ping -c 2 192.168.171.101
#sudo ip netns exec net1 ping -c 2 115.239.210.27

