
sudo docker run -it --net host \
    -v /home/dingyc/:/home/dingyc/ \
    --name pytorch \
    --device /dev/nvidia0:/dev/nvidia0 \
    --device /dev/nvidia1:/dev/nvidia1 \
    --device /dev/nvidiactl:/dev/nvidiactl \
    --device /dev/nvidia-uvm:/dev/nvidia-uvm \
    --device /dev/nvidia-uvm-tools:/dev/nvidia-uvm-tools \
    pytorch/pytorch:1.1.0-cuda10.0-cudnn7.5-devel
    #anibali/pytorch:cuda-9.0 bash

    #-v /usr/bin/nvidia-smi:/usr/bin/nvidia-smi \
    #-v /lib/libnvidia-ml.so.418.39:/lib/libnvidia-ml.so \

