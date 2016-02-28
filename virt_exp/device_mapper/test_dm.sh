
sudo dd if=/dev/zero of=/tmp/data.img bs=1K count=1 seek=10M
sudo dd if=/dev/zero of=/tmp/meta.data.img bs=1K count=1 seek=1G

sudo ls -lsh /tmp/data.img /tmp/meta.data.img

sudo losetup /dev/loop2015 /tmp/data.img
sudo losetup /dev/loop2016 /tmp/meta.data.img

sudo dmsetup create thin-pool \
    --table "0 20971522 thin-pool /dev/loop2016 /dev/loop2015 \
    128 65536 1 skip_block_zeroing"

sudo dmsetup message /dev/mapper/thin-pool 0 "create_thin 0"
sudo dmsetup create thin-volumn-001 \
    --table "0 2097152 thin /dev/mapper/thin-pool 0"

sudo mkfs.ext4 /dev/mapper/thin-volumn-001


sudo mkdir -p /mnt/base
sudo mount /dev/mapper/thin-volumn-001 /mnt/base
sudo touch /mnt/base/id.txt
sudo chown dingyc /mnt/base/id.txt
sudo echo "hello world, I am a base" > /mnt/base/id.txt
sudo cat /mnt/base/id.txt

sudo dmsetup message /dev/mapper/thin-pool 0 "create_snap 1 0"
sudo dmsetup create mysnap1 \
    --table "0 2097152 thin /dev/mapper/thin-pool 1"
sudo ls -l /dev/mapper/mysnap1

sudo mkdir -p /mnt/mysnap1
sudo mount /dev/mapper/mysnap1 /mnt/mysnap1
sudo cat /mnt/mysnap1/id.txt

