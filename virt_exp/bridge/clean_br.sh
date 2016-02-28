
sudo ip route del 10.1.0.0/16 
sudo ip link set dev br down
sudo brctl delbr br
sudo ip netns del net1

