# ubuntu 22.04 min-install


sudo apt install make 

sudo apt install g++

sudo apt install xorriso

sudo apt install grub-efi-amd64

sudo mkdir /mnt/hgfs

sudo apt-get remove open-vm-tools

sudo apt-get purge --auto-remove open-vm-tools

sudo apt install vim 

sudo vim /etc/fstab   

    /etc/fstab  insert 
 
    .host:/  /mnt/hgfs  fuse.vmhgfs-fuse  allow_other  0  0

make clean

make mykernel.iso


# virutual version 6.1

ROM:64M  

no hd 
 
system:other DOS